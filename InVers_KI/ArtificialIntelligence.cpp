#include "ArtificialIntelligence.h"

ArtificialIntelligence::ArtificialIntelligence()
{
	strategy = RANDOM;
	boardWeightings =
	{
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	100,50,	35,	35,	50,	100,0,
		0,	50,	20,	20,	20,	20,	50,	0,
		0,	35,	20,	10,	10,	20,	35,	0,
		0,	35,	20,	10,	10,	20,	35,	0,
		0,	50,	20,	20,	20,	20,	50,	0,
		0,	100,40,	35,	35,	50,	100,0,
		0,	0,	0,	0,	0,	0,	0,	0
	};

	boardWeightingsUnturned =
	{
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	100,100,100,100,100,100,0,
		0,	100,-80,-80,-80,-80,100,0,
		0,	100,-80,-100,-100,-80,100,0,
		0,	100,-80,-100,-100,-80,100,0,
		0,	100,-80,-80,-80,-80,100,0,
		0,	100,100,100,100,100,100,0,
		0,	0,	0,	0,	0,	0,	0,	0
	};

	depthIntelligence = 2;
}

void ArtificialIntelligence::chooseStrategy(char cStrategy)
{
	if (std::tolower(cStrategy) == 'r')
	{
		strategy = RANDOM;
	}
	else if (std::tolower(cStrategy) == 'm')
	{
		strategy = MINIMAX;
	}
}

std::vector<int> ArtificialIntelligence::chooseRandomMove(Game& game)
{
	std::vector<std::vector<int>> allMoves = game.possibleMoves();

	int randomNumber = rand() % allMoves.size();

	std::vector<int> chosenMove = allMoves.at(randomNumber);

	return chosenMove;
}

//Main function to determine the next move of the AI
void ArtificialIntelligence::makeMove(Game& game)
{
	std::vector<int> move;
	std::vector<std::vector<int>> allMoves = game.possibleMoves();
	std::string toRecord = "Player ";
	int results;
	int pushedStone = 0;

	if (game.getCurrentTurn() == Game::YELLOW_PLAYER)
	{
		toRecord += "YELLOW ";
	}
	else
	{
		toRecord += "RED ";
	}
	
	toRecord += "moved ";

	if (strategy == RANDOM)
	{
		move = chooseRandomMove(game);
	}

	if (strategy == MINIMAX)
	{
		std::vector<int> saveBoard = game.getBoardVector();
		int savePlayer = game.getCurrentTurn();
		int saveYellowNextTurn = game.yellowNextTurn;
		int saveYellowTurnedOnBoard = game.yellowTurnedOnBoard;
		int saveRedNextTurn = game.redNextTurn;
		int saveRedTurnedOnBoard = game.redTurnedOnBoard;

		std::vector<std::vector<int>> moveChoices;
		std::vector<int> currentMove;
		int bestMove = -1000;

		for (int i = 0; i < allMoves.size(); i++)
		{
			currentMove = allMoves.at(i);

			moveHelper(game, currentMove);

			results = minimax(game, depthIntelligence - 1, -1, 1);

			game.setBoardVector(saveBoard);
			if (savePlayer != game.getCurrentTurn())
			{
				game.changeTurn();
			}
			game.yellowNextTurn = saveYellowNextTurn;
			game.yellowTurnedOnBoard = saveYellowTurnedOnBoard;
			game.redNextTurn = saveRedNextTurn;
			game.redTurnedOnBoard = saveRedTurnedOnBoard;

			if (results > bestMove)
			{
				bestMove = results;
				moveChoices.clear();
				moveChoices.push_back(currentMove);
			}

			if (results == bestMove)
			{
				moveChoices.push_back(currentMove);
			}
		}

		//TODO EXCEPTION??????
		int randomIndex = rand() % moveChoices.size();

		move = moveChoices.at(randomIndex);
	}

	//=====================Make the actual Move========================
	if (move.at(1) == LEFT)
	{
		toRecord += "LINE ";
		toRecord += std::to_string(move.at(0));
		toRecord += " LEFT.";
		game.logMove(toRecord);
		pushedStone = game.saveStone('l', move.at(0), 'l');
		game.shiftLeft(move.at(0));
	}
	else if (move.at(1) == RIGHT)
	{
		toRecord += "LINE ";
		toRecord += std::to_string(move.at(0));
		toRecord += " RIGHT.";
		game.logMove(toRecord);
		pushedStone = game.saveStone('l', move.at(0), 'r');
		game.shiftRight(move.at(0));
	}
	else if (move.at(1) == UP)
	{
		toRecord += "COLUMN ";
		toRecord += std::to_string(move.at(0));
		toRecord += " UP.";
		game.logMove(toRecord);
		pushedStone = game.saveStone('c', move.at(0), 'u');
		game.shiftUp(move.at(0));
	}
	else if (move.at(1) == DOWN)
	{
		toRecord += "COLUMN ";
		toRecord += std::to_string(move.at(0));
		toRecord += " DOWN.";
		game.logMove(toRecord);
		pushedStone = game.saveStone('c', move.at(0), 'd');
		game.shiftDown(move.at(0));
	}

	if (game.getCurrentTurn() == Game::YELLOW_PLAYER)
	{
		game.yellowNextTurn = pushedStone;
	}
	else
	{
		game.redNextTurn = pushedStone;
	}
	//=====================Make the actual Move========================

	game.checkForWinner();
	game.changeTurn();
}

int ArtificialIntelligence::minimax(Game& game, int depth, int alpha, int beta)
{
	std::vector<int>saveBoardVector = game.getBoardVector();
	int savePlayer = game.getCurrentTurn();
	int saveYellowTurnedOnBoard = game.yellowTurnedOnBoard;
	int saveRedTurnedOnBoard = game.redTurnedOnBoard;
	int saveYellowNextTurn = game.yellowNextTurn;
	int saveRedNextTurn = game.redNextTurn;

	int mWinner = game.checkForWinner();

	//=============EVALUATE TURN=================
	if (depth == 0 || mWinner != 2)
	{
		if (mWinner == 0)
		{
			if (game.activePlayer == Game::YELLOW_PLAYER)
			{
				return 1000000;
			}
			else
			{
				return -1000000;
			}
		}
		if (mWinner == 1)
		{
			if (game.activePlayer == Game::RED_PLAYER)
			{
				return 1000000;
			}
			else
			{
				return -1000000;
			}
		}

		int points = 0;

		for (int i = 0; i < game.getBoardVector().size(); i++)
		{
			if ((game.activePlayer == Game::YELLOW_PLAYER && (game.getBoardVector().at(i) == 3)) ||
				(game.activePlayer == Game::RED_PLAYER && (game.getBoardVector().at(i) == 4)))
			{
				points += boardWeightings.at(i);

				if (game.activePlayer == Game::YELLOW_PLAYER)
				{
					points += game.yellowTurnedOnBoard * 50;
				}
				else
				{
					points += game.redTurnedOnBoard * 50;
				}
			}

			if (game.activePlayer == Game::YELLOW_PLAYER && game.getBoardVector().at(i) == 0 ||
				game.activePlayer == Game::RED_PLAYER && game.getBoardVector().at(i) == 1)
			{
				points += boardWeightingsUnturned.at(i);
			}
		}
		//std::cout << points << std::endl;
		return points;
	}
	//=============EVALUATE TURN=================

	std::vector<std::vector<int>> allMoves = game.possibleMoves();
	std::vector<int> bestMove;
	int results;
	int max = 0;
	int min = 10000;

	for (int i = 0; i < allMoves.size(); i++)
	{
		std::vector<int>currentMove = allMoves.at(i);

		moveHelper(game, currentMove);

		//printBoard(game);
		
		results = minimax(game, depth - 1, alpha, beta);
		
		game.setBoardVector(saveBoardVector);
		if (game.getCurrentTurn() != savePlayer)
		{
			game.changeTurn();
		}
		game.yellowNextTurn = saveYellowNextTurn;
		game.redNextTurn = saveRedNextTurn;
		game.yellowTurnedOnBoard = saveYellowTurnedOnBoard;
		game.redTurnedOnBoard = saveRedTurnedOnBoard;

		if (game.activePlayer == game.getCurrentTurn())
		{
			if (results > max)
			{
				max = results;
			}
		}
		else
		{
			if (results < min)
			{
				min = results;
			}
		}
		/*
		if (game.activePlayer == game.getEnemy())
		{
			if (results > alpha)
			{
				alpha = results;
			}

			if (alpha >= beta)
			{
				return beta;
			}
		}
		else
		{
			if (results < beta)
			{
				beta = results;
			}
			
			if (beta <= alpha)
			{
				return alpha;
			}
		}
		*/
		
	}
	if (game.activePlayer == game.getCurrentTurn())
	{
		return max;
	}
	else
	{
		return min;
	}

	/*
	if (game.activePlayer == game.getCurrentTurn())
	{
		return alpha;
	}
	else
	{
		return beta;
	}
	*/
}

//Helper function for minimax algorithm
void ArtificialIntelligence::moveHelper(Game& game, std::vector<int> currentMove)
{
	//If the current move shifts the Board to the LEFT, call the according function
	if (currentMove.at(1) == LEFT)
	{
		game.shiftLeft(currentMove.at(0));
		game.saveStone('l', currentMove[0], currentMove[1]);
		game.changeTurn();
	}
	//If the current move shifts the Board to the RIGHT, call the according function
	else if (currentMove.at(1) == RIGHT)
	{
		game.shiftRight(currentMove.at(0));
		game.saveStone('r', currentMove[0], currentMove[1]);
		game.changeTurn();
	}
	//If the current move shifts the Board UP, call the according function
	else if (currentMove.at(1) == UP)
	{
		game.shiftUp(currentMove.at(0));
		game.saveStone('u', currentMove[0], currentMove[1]);
		game.changeTurn();
	}
	//If the current move shifts the Board DOWN, call the according function
	else if (currentMove.at(1) == DOWN)
	{
		game.shiftDown(currentMove.at(0));
		game.saveStone('d', currentMove[0], currentMove[1]);
		game.changeTurn();
	}
}
