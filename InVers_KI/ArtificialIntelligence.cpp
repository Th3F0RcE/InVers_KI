#include "ArtificialIntelligence.h"

void ArtificialIntelligence::chooseStrategy(char cStrategy)
{
	if (std::tolower(cStrategy) == 'r')
	{
		strategy = RANDOM;
	}
}

std::vector<char[3]> ArtificialIntelligence::possibleMoves()
{
	std::vector<int> borderCells;
	std::vector<char[3]> allMoves;
	int moveCounter = 0;

	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i < 12)
			{
				if (i < 6)
				{

				}
			}
		}
	}

	return std::vector<char[3]>();
}
