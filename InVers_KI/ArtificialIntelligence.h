#pragma once
#include "includes.h"
#include "Game.h"

class ArtificialIntelligence
{
public:
	enum Strategies
	{
		RANDOM = 0
	};

	int strategy;

	void chooseStrategy(char cStrategy);
};

