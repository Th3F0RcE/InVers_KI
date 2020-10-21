#include "ArtificialIntelligence.h"

ArtificialIntelligence::ArtificialIntelligence()
{
}

void ArtificialIntelligence::chooseStrategy(char cStrategy)
{
	if (std::tolower(cStrategy) == 'r')
	{
		strategy = RANDOM;
	}
}