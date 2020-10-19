#pragma once
#include "includes.h"
#include "Game.h"

constexpr auto MAX_MOVES = 24;

class ArtificialIntelligence
{
public:
	enum Strategies
	{
		RANDOM = 0
	};

	int strategy;

	void chooseStrategy(char cStrategy);
	std::vector<char[2]> possibleMoves(Game& game);
};

