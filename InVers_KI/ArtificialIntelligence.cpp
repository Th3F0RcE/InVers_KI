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

	if (strategy == RANDOM)
	{
		move = chooseRandomMove(game);
	}

	if (move.at(1) == LEFT)
	{
		game.shiftLeft(move.at(0));
	}
	else if (move.at(1) == RIGHT)
	{
		game.shiftRight(move.at(0));
	}
	else if (move.at(1) == UP)
	{
		game.shiftUp(move.at(0));
	}
	else if (move.at(1) == DOWN)
	{
		game.shiftDown(move.at(0));
	}
}
