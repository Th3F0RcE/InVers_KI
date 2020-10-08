#pragma once
class InVers
{
public:
	const char initialBoard[6][6] =
	{
		//This represents the stones on the board
		{'R', 'Y', 'R', 'Y', 'R', 'Y'},
		{'Y', 'R', 'Y', 'R', 'Y', 'R'},
		{'R', 'Y', 'R', 'Y', 'R', 'Y'},
		{'Y', 'R', 'Y', 'R', 'Y', 'R'},
		{'R', 'Y', 'R', 'Y', 'R', 'Y'},
		{'Y', 'R', 'Y', 'R', 'Y', 'R'}
	};
};

class Game : InVers
{
public:
	Game();
	~Game();
};

