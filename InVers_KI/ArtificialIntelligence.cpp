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
