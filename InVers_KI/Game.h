#pragma once
#include "includes.h"

class Game
{
private:
	int currentTurn;	//Who is on turn
	bool gameFinished;	//Is the game finished?
	std::vector<int> boardVector;	//Vector to represent the board

public:
	Game();	//Constructor
	~Game();	//Destructor
	bool isFinished();	//returns gameFinished
	bool isMoveValid(char LC, int number, char direction);	//Checks if a move is valid
	std::vector<int>getBoardVector();	//returns Board Vector
	std::vector<int>findLineValues(int line);	//find the vector-values in a given LINE  
	std::vector<int>findColumnValues(int column);	//find the vector-values in a given COLUMN
	int getCurrentTurn();	//returns currentTurn
	void saveStone(char LC, int number, char direction);	//Saves the stone that is pushed out
	void changeTurn();	//Change the turn
	void countUpTurned();	//Counts up the number of turned stones on the field for each color
	void shiftRight(int line);	//Move a line to the right
	void shiftLeft(int line);	//Move a line to the left
	void shiftDown(int column);	//Move a column down
	void shiftUp(int column);	//Move a column up
	void logMove(std::string &toRecord);	//Stores the move to print it later
	void deleteLoggedMove();	//Deletes a move that was logged
	void checkForWinner();	//Checks if someone has won

	//Saved stones
	int yellowNextTurn;
	int redNextTurn;

	//Turned stones on the board
	int yellowTurnedOnBoard;
	int redTurnedOnBoard;

	enum PlayerTurn
	{
		YELLOW_PLAYER = 0,
		RED_PLAYER = 1
	};

	//Store all moves
	struct Round
	{
		std::string yellowMove;
		std::string redMove;
	};

	std::deque<Round> rounds;
};

