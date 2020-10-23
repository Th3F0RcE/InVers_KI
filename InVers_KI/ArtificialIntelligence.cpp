#include "ArtificialIntelligence.h"

ArtificialIntelligence::ArtificialIntelligence()
{
	strategy = RANDOM;
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
}

int ArtificialIntelligence::minimax(Game& game, std::vector<int>boardVector, int currentPlayer, int depth, int alpha, int beta)
{
	std::vector<int>mBoardVector= boardVector;
	int mPlayer = currentPlayer;
	int mDepth = depth;
	int mAlpha = alpha;
	int mBeta = beta;
	int mWinner = game.checkForWinner();

	int results;

	if (mDepth == 0)
	{
		if (mWinner == 2)
		{
			return 0;
		}
		else if (mWinner == currentPlayer)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}

	std::vector<std::vector<int>>allMoves = game.possibleMoves();

	for (int i = 0; i < allMoves.size(); i++)
	{
		std::vector<int> currentMove = allMoves.at(i);

		if (currentMove.at(1) == LEFT)
		{
			game.shiftLeft(currentMove.at(0));
		}
		else if (currentMove.at(1) == RIGHT)
		{
			game.shiftRight(currentMove.at(0));
		}
		else if (currentMove.at(1) == UP)
		{
			game.shiftUp(currentMove.at(0));
		}
		else if (currentMove.at(1) == DOWN)
		{
			game.shiftDown(currentMove.at(0));
		}

		results = minimax(game, mBoardVector, game.getCurrentTurn(), mDepth - 1, mAlpha, mBeta);

		game.setBoardVector(boardVector);

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
	}

	if (currentPlayer == game.getCurrentTurn())
	{
		return alpha;
	}
	else
	{
		return beta;
	}
}
