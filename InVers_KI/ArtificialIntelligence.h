#pragma once
#include "includes.h"
#include "Game.h"
#include "UserInterface.h"

constexpr auto MAX_MOVES = 24;

class ArtificialIntelligence
{
public:
	ArtificialIntelligence();
	enum Strategies
	{
		RANDOM = 0,
		MINIMAX = 1
	};

	int strategy;
	int depthIntelligence;
	std::vector<int> boardWeightings;
	std::vector<int> boardWeightingsUnturned;

	void chooseStrategy(char cStrategy);
	std::vector<int> chooseRandomMove(Game& game);
	void makeMove(Game& game);
	int minimax(Game& game, int depth, int alpha, int beta);
	void moveHelper(Game& game, std::vector<int> currentMove);
};

