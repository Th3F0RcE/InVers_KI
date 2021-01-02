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
}

void ArtificialIntelligence::chooseStrategy(char cStrategy)
{
	if (std::tolower(cStrategy) == 'r')
	{
		strategy = RANDOM;
	}
	else if (std::tolower(cStrategy) == 'a')
	{
		strategy = ALPHABETA;
	}
}

std::vector<int> ArtificialIntelligence::chooseRandomMove(Game& game)
{
	std::vector<std::vector<int>> allMoves = game.possibleMoves();

	int randomNumber = rand() % allMoves.size();

	std::vector<int> chosenMove = allMoves.at(randomNumber);

	return chosenMove;
}

void ArtificialIntelligence::makeMove(Game& game)
{
	std::vector<int> move;
	std::string toRecord = "Player ";

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

	game.checkForWinner();
	game.changeTurn();
}

int ArtificialIntelligence::minimax(Game& game, std::vector<int>boardVector, int currentPlayer, int yellowTurnedOnBoard, int yellowNextTurn, int redTurnedOnBoard, int redNextTurn, int depth)
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
			if ((currentPlayer == Game::YELLOW_PLAYER && (boardVector.at(i) == 3)) ||
				(currentPlayer == Game::RED_PLAYER && (boardVector.at(i) == 4)))
			{
				points += boardWeightings.at(i);
			}
		}
		std::cout << points << std::endl;
		return points;
	}
	//=============EVALUATE TURN=================

	std::vector<std::vector<int>> allMoves = game.possibleMoves();
	std::vector<int> bestMove;
	std::vector<int>results;
	int max = 0;

	for (int i = 0; i < allMoves.size(); i++)
	{
		std::vector<int>currentMove = allMoves.at(i);

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
	
		printBoard(game);
		results.push_back(minimax(game, game.getBoardVector(), currentPlayer, mYellowTurnedOnBoard, mYellowNextTurn, mRedTurnedOnBoard, mRedNextTurn, mDepth - 1));
		
		if (results.back() > max)
		{
			max = results.back();
			bestMove = currentMove;
		}

		game.setBoardVector(boardVector);
		game.yellowNextTurn = yellowNextTurn;
		game.redNextTurn = redNextTurn;
		game.yellowTurnedOnBoard = yellowTurnedOnBoard;
		game.redTurnedOnBoard = redTurnedOnBoard;
	}
	//int max = *std::max_element(results.begin(), results.end());
	return max;
}
//TODO
/*int ArtificialIntelligence::minimax(Game& game, std::vector<int>boardVector, int currentPlayer, int yellowTurnedOnBoard, int yellowNextTurn, int redTurnedOnBoard, int redNextTurn, int depth, int alpha, int beta)
{
	//Variables to store the game BEFORE going through all moves
	//Will be restored after
	std::vector<int>mBoardVector= boardVector;
	int mPlayer = currentPlayer;
	int mYellowTurnedOnBoard = yellowTurnedOnBoard;
	int mRedTurnedOnBoard = redTurnedOnBoard;
	int mYellowNextTurn = yellowNextTurn;
	int mRedNextTurn = redNextTurn;

	//Variables to store the parameters
	int mDepth = depth;
	int mAlpha = alpha;
	int mBeta = beta;

	//Is there a winner in the next moves?
	int mWinner = game.checkForWinner();

	//Store the result
	int results;

	//If the max depth is reached, look if there's a winner in the combination of moves
	if (mDepth == 0)
	{
		//If there is no winner, return amount of stones on the Board
		if (mWinner == 2)
		{
			std::vector<int> pointsForOuterStones = game.findOuterValues();
			int points;

			//Add a point to the result for each Stone MORE that is on the Board for the current Player
			//Add a point to the result for each Stone LESS that is on the Board for the enemy Player
			if (currentPlayer == Game::YELLOW_PLAYER)
			{
				if (game.getCurrentTurn() == Game::YELLOW_PLAYER)
				{
					points = (game.yellowTurnedOnBoard - yellowTurnedOnBoard) + (redTurnedOnBoard - game.redTurnedOnBoard);

					for (int j = 0; j < pointsForOuterStones.size(); j++)
					{
						if (game.getBoardVector().at(pointsForOuterStones.at(j)) == YELLOW_CELL_TURNED)
						{
							points += 1;
						}
					}

					return points;
				}
				else
				{
					points = ((game.redTurnedOnBoard - redTurnedOnBoard) + (yellowTurnedOnBoard - game.yellowTurnedOnBoard));

					for (int j = 0; j < pointsForOuterStones.size(); j++)
					{
						if (game.getBoardVector().at(pointsForOuterStones.at(j)) == RED_CELL_TURNED)
						{
							points += 1;
						}
					}

					return points * -1;
				}
			}
			else
			{
				if (game.getCurrentTurn() == Game::RED_PLAYER)
				{
					points = ((game.redTurnedOnBoard - redTurnedOnBoard) + (yellowTurnedOnBoard - game.yellowTurnedOnBoard));

					for (int j = 0; j < pointsForOuterStones.size(); j++)
					{
						if (game.getBoardVector().at(pointsForOuterStones.at(j)) == RED_CELL_TURNED)
						{
							points += 1;
						}
					}
					return points;
				}
				else
				{
					points = (game.yellowTurnedOnBoard - yellowTurnedOnBoard) + (redTurnedOnBoard - game.redTurnedOnBoard);

					for (int j = 0; j < pointsForOuterStones.size(); j++)
					{
						if (game.getBoardVector().at(pointsForOuterStones.at(j)) == YELLOW_CELL_TURNED)
						{
							points += 1;
						}
					}

					return points * -1;
				}
			}
		}
		//If the current Player is the winner, return 1000
		else if (mWinner == currentPlayer)
		{
			return 1000;
		}
		//If the enemy Player is the winner, return -1000
		else
		{
			return -1000;
		}
	}

	//Get all the Moves that are possible 
	std::vector<std::vector<int>>allMoves = game.possibleMoves();

	//Loop through all Moves
	for (int i = 0; i < allMoves.size(); i++)
	{
		//Store the current move
		std::vector<int> currentMove = allMoves.at(i);

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

		//Recursive call on the function until the depth is 0
		results = minimax(game, mBoardVector, currentPlayer, mYellowTurnedOnBoard, mYellowNextTurn, mRedTurnedOnBoard, mRedNextTurn, mDepth - 1, mAlpha, mBeta);

		//Restore the values of the variables before the algorithm
		game.setBoardVector(boardVector);
		game.yellowNextTurn = yellowNextTurn;
		game.redNextTurn = redNextTurn;
		game.yellowTurnedOnBoard = yellowTurnedOnBoard;
		game.redTurnedOnBoard = redTurnedOnBoard;

		if (currentPlayer == game.getCurrentTurn())
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

		if (currentPlayer == Game::YELLOW_PLAYER)
		{
			if (game.getCurrentTurn() == Game::YELLOW_PLAYER)
			{
				if (results > alpha)
				{
					results = alpha;
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
		}
	}

	if (currentPlayer == game.getCurrentTurn())
	{
		return alpha;
	}
	else
	{
		return beta;
	}
}*/
