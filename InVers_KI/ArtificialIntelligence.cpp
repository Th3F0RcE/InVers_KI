#include "ArtificialIntelligence.h"

ArtificialIntelligence::ArtificialIntelligence()
{
	strategy = RANDOM;
	boardWeightings =
	{
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	80,	40,	35,	35,	40,	80,	0,
		0,	40,	20,	20,	20,	20,	40,	0,
		0,	35,	20,	10,	10,	20,	35,	0,
		0,	35,	20,	10,	10,	20,	35,	0,
		0,	40,	20,	20,	20,	20,	40,	0,
		0,	80,	40,	35,	35,	40,	80,	0,
		0,	0,	0,	0,	0,	0,	0,	0
	};

	depthIntelligence = 1;
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
		std::vector<int> currentMove;
		std::vector<int> saveBoard = game.getBoardVector();
		std::vector<std::vector<int>> moveChoices;
		int bestMove = -1;

		for (int i = 0; i < allMoves.size(); i++)
		{
			currentMove = allMoves.at(i);

			//If the current move shifts the Board to the LEFT, call the according function
			if (currentMove.at(1) == LEFT)
			{
				game.shiftLeft(currentMove.at(0));
			}
			//If the current move shifts the Board to the RIGHT, call the according function
			else if (currentMove.at(1) == RIGHT)
			{
				game.shiftRight(currentMove.at(0));
			}
			//If the current move shifts the Board UP, call the according function
			else if (currentMove.at(1) == UP)
			{
				game.shiftUp(currentMove.at(0));
			}
			//If the current move shifts the Board DOWN, call the according function
			else if (currentMove.at(1) == DOWN)
			{
				game.shiftDown(currentMove.at(0));
			}

			results = minimax(game, game.getBoardVector(), game.getEnemy(), game.yellowTurnedOnBoard, game.yellowNextTurn, game.redTurnedOnBoard, game.redNextTurn, depthIntelligence, -1, 1);

			game.setBoardVector(saveBoard);

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
		game.saveStone('l', move.at(0), 'l');
		game.shiftLeft(move.at(0));
	}
	else if (move.at(1) == RIGHT)
	{
		toRecord += "LINE ";
		toRecord += std::to_string(move.at(0));
		toRecord += " RIGHT.";
		game.logMove(toRecord);
		game.saveStone('l', move.at(0), 'r');
		game.shiftRight(move.at(0));
	}
	else if (move.at(1) == UP)
	{
		toRecord += "COLUMN ";
		toRecord += std::to_string(move.at(0));
		toRecord += " UP.";
		game.logMove(toRecord);
		game.saveStone('c', move.at(0), 'u');
		game.shiftUp(move.at(0));
	}
	else if (move.at(1) == DOWN)
	{
		toRecord += "COLUMN ";
		toRecord += std::to_string(move.at(0));
		toRecord += " DOWN.";
		game.logMove(toRecord);
		game.saveStone('c', move.at(0), 'd');
		game.shiftDown(move.at(0));
	}
	//=====================Make the actual Move========================

	game.checkForWinner();
	game.changeTurn();
}

int ArtificialIntelligence::minimax(Game& game, std::vector<int>boardVector, int currentPlayer, int yellowTurnedOnBoard, int yellowNextTurn, int redTurnedOnBoard, int redNextTurn, int depth, int alpha, int beta)
{
	std::vector<int>mBoardVector = boardVector;
	int mPlayer = currentPlayer;
	int mYellowTurnedOnBoard = yellowTurnedOnBoard;
	int mRedTurnedOnBoard = redTurnedOnBoard;
	int mYellowNextTurn = yellowNextTurn;
	int mRedNextTurn = redNextTurn;
	int mDepth = depth;
	int mWinner = game.checkForWinner();

	//=============EVALUATE TURN=================
	if (mDepth == 0 || mWinner != 2)
	{
		if (mWinner == 0)
		{
			if (currentPlayer == Game::YELLOW_PLAYER)
			{
				return 1000;
			}
			else
			{
				return -1000;
			}
		}
		if (mWinner == 1)
		{
			if (currentPlayer == Game::RED_PLAYER)
			{
				return 1000;
			}
			else
			{
				return -1000;
			}
		}

		int points = 0;

		for (int i = 0; i < boardVector.size(); i++)
		{
			if ((game.getCurrentTurn() == Game::YELLOW_PLAYER && (boardVector.at(i) == 3)) ||
				(game.getCurrentTurn() == Game::RED_PLAYER && (boardVector.at(i) == 4)))
			{
				points += boardWeightings.at(i);
			}
		}
		std::cout << points << std::endl;
		return points;
	}
	//=============EVALUATE TURN=================
	game.changeTurn();

	std::vector<std::vector<int>> allMoves = game.possibleMoves();
	std::vector<int> bestMove;
	int results;
	int max = 0;

	for (int i = 0; i < allMoves.size(); i++)
	{
		std::vector<int>currentMove = allMoves.at(i);

		moveHelper(game, currentMove);

		printBoard(game);
		
		results = minimax(game, game.getBoardVector(), game.getCurrentTurn(), game.yellowTurnedOnBoard, game.yellowNextTurn, game.redTurnedOnBoard, game.redNextTurn, mDepth - 1, alpha, beta);
		
		if (game.activePlayer == game.getCurrentTurn())
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

		game.setBoardVector(mBoardVector);
		game.yellowNextTurn = mYellowNextTurn;
		game.redNextTurn = mRedNextTurn;
		game.yellowTurnedOnBoard = mYellowTurnedOnBoard;
		game.redTurnedOnBoard = mRedTurnedOnBoard;
		
	}

	if (game.activePlayer == game.getCurrentTurn())
	{
		return alpha;
	}
	else
	{
		return beta;
	}
}

//Helper function for minimax algorithm
void ArtificialIntelligence::moveHelper(Game& game, std::vector<int> currentMove)
{
	//If the current move shifts the Board to the LEFT, call the according function
	if (currentMove.at(1) == LEFT)
	{
		game.shiftLeft(currentMove.at(0));
		game.saveStone('l', currentMove[0], currentMove[1]);
	}
	//If the current move shifts the Board to the RIGHT, call the according function
	else if (currentMove.at(1) == RIGHT)
	{
		game.shiftRight(currentMove.at(0));
		game.saveStone('r', currentMove[0], currentMove[1]);
	}
	//If the current move shifts the Board UP, call the according function
	else if (currentMove.at(1) == UP)
	{
		game.shiftUp(currentMove.at(0));
		game.saveStone('u', currentMove[0], currentMove[1]);
	}
	//If the current move shifts the Board DOWN, call the according function
	else if (currentMove.at(1) == DOWN)
	{
		game.shiftDown(currentMove.at(0));
		game.saveStone('d', currentMove[0], currentMove[1]);
	}
}
