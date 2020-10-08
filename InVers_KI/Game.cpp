#include "Game.h"
#include "UserInterface.h"

Game::Game()
{
	//Yellow Player always starts
	currentTurn = YELLOW_PLAYER;

	//Initial Board
	boardVector = 
	{
		2,2,2,2,2,2,2,2,
		2,0,1,0,1,0,1,2,
		2,1,0,1,0,1,0,2,
		2,0,1,0,1,0,1,2,
		2,1,0,1,0,1,0,2,
		2,0,1,0,1,0,1,2,
		2,1,0,1,0,1,0,2,
		2,2,2,2,2,2,2,2
	};

	//No Turned Stones on the Board
	yellowTurnedOnBoard = 0;
	redTurnedOnBoard = 0;

	//First Turn Stones
	yellowNextTurn = YELLOW_CELL_TURNED;
	redNextTurn = RED_CELL_TURNED;

	//Go
	gameFinished = false;
}

Game::~Game()
{
}

bool Game::isFinished()
{
	return gameFinished;
}

bool Game::isMoveValid(char LC, int number, char direction)
{
	std::vector<int>values;

	if (std::tolower(LC) == 'l')
	{
		values = findLineValues(number);
	}
	else if (std::tolower(LC) == 'c')
	{
		values = findColumnValues(number);
	}

	if (std::tolower(direction) == 'r' || std::tolower(direction) == 'd')
	{
		if((this->boardVector.at(values.at(5)) == YELLOW_CELL_TURNED && currentTurn == RED_PLAYER) ||
			(this->boardVector.at(values.at(5)) == RED_CELL_TURNED && currentTurn == YELLOW_PLAYER))
		{
			return false;
		}
	}

	if (std::tolower(direction) == 'l' || std::tolower(direction) == 'u')
	{
		if ((this->boardVector.at(values.at(0)) == YELLOW_CELL_TURNED && currentTurn == RED_PLAYER) ||
			(this->boardVector.at(values.at(0)) == RED_CELL_TURNED && currentTurn == YELLOW_PLAYER))
		{
			return false;
		}
	}
	return true;
}

std::vector<int> Game::getBoardVector()
{
	return boardVector;
}

std::vector<int> Game::findLineValues(int line)
{
	int iLine = 0;
	std::vector<int>values;

	for (unsigned int i = 0; i < this->boardVector.size(); i++)
	{
		if (iLine == line && this->boardVector.at(i) != 2)
		{
			values.push_back(i);
		}

		if (i % 8 == 7)
		{
			iLine += 1;
		}
	}
	return values;
}

std::vector<int> Game::findColumnValues(int column)
{
	int iColumn = 0;
	int multiplier = 1;
	std::vector<int>values;

	for (unsigned int i = 0; i < this->boardVector.size(); i++)
	{
		if (i == column + (8 * multiplier) && this->boardVector.at(i) != 2)
		{
			values.push_back(i);
			multiplier += 1;
		}
	}

	return values;
}

int Game::getCurrentTurn()
{
	return currentTurn;
}

void Game::saveStone(char LC, int number, char direction)
{
	std::vector<int> values;
	int pushedStone = 0;

	if (std::tolower(LC) == 'l')
	{
		values = findLineValues(number);

		if (std::tolower(direction) == 'l')
		{
			pushedStone = this->boardVector.at(values.at(0));
		}
		else
		{
			pushedStone = this->boardVector.at(values.at(5));
		}
	}
	else if (std::tolower(LC) == 'c')
	{
		values = findColumnValues(number);

		if (std::tolower(direction) == 'u')
		{
			pushedStone = this->boardVector.at(values.at(0));
		}
		else if (std::tolower(direction) == 'd')
		{
			pushedStone = this->boardVector.at(values.at(5));
		}
	}

	if (pushedStone == YELLOW_CELL)
	{
		pushedStone = YELLOW_CELL_TURNED;
	}
	else if (pushedStone == RED_CELL)
	{
		pushedStone = RED_CELL_TURNED;
	}

	if (currentTurn == YELLOW_PLAYER)
	{
		yellowNextTurn = pushedStone;
	}
	else
	{
		redNextTurn = pushedStone;
	}
}

void Game::changeTurn()
{
	if (currentTurn == YELLOW_PLAYER)
	{
		currentTurn = RED_PLAYER;
	}
	else
	{
		currentTurn = YELLOW_PLAYER;
	}
}

void Game::countUpTurned()
{
	if (currentTurn == YELLOW_PLAYER)
	{
		yellowTurnedOnBoard += 1;
	}
	else
	{
		redTurnedOnBoard += 1;
	}
}

void Game::logMove(std::string& toRecord)
{
	if (toRecord.length() == 5)
	{
		toRecord += " ";
	}

	if (getCurrentTurn() == YELLOW_PLAYER)
	{
		Round round;
		round.yellowMove = toRecord;
		round.redMove = "";

		rounds.push_back(round);
	}
	else
	{
		Round round = rounds[rounds.size() - 1];
		round.redMove = toRecord;

		rounds.pop_back();
		rounds.push_back(round);
	}
}

void Game::deleteLoggedMove()
{
	rounds.pop_back();
}

void Game::checkForWinner()
{
	bool hasWon = false;
	
	if (yellowTurnedOnBoard >= 19)
	{
		appendToNextMessage("YELLOW HAS WON THE ROUND!\n");
		hasWon = true;
	}
	if (redTurnedOnBoard >= 19)
	{
		appendToNextMessage("RED HAS WON THE ROUND!\n");
		hasWon = true;
	}
	gameFinished = hasWon;
}

void Game::shiftRight(int line)
{
	std::vector<int>lineValues = findLineValues(line);

	for (int i = 5; i >= 0; i--)
	{
		if (i == 5)
		{
			if (this->boardVector.at(lineValues.at(i)) == 3)
			{
				yellowTurnedOnBoard -= 1;
			}
			else if (this->boardVector.at(lineValues.at(i)) == 4)
			{
				redTurnedOnBoard -= 1;
			}
		}

		if (i == 0)
		{
			this->boardVector.at(lineValues.at(i)) = currentTurn == YELLOW_PLAYER ? yellowNextTurn : redNextTurn;
		}
		else
		{
			this->boardVector.at(lineValues.at(i)) = this->boardVector.at(lineValues.at(i - 1));
		}
	}
	countUpTurned();
	changeTurn();
}

void Game::shiftLeft(int line)
{
	std::vector<int>lineValues = findLineValues(line);

	for (int i = 0; i < 6; i++)
	{
		if (i == 0)
		{
			if (this->boardVector.at(lineValues.at(i)) == 3)
			{
				yellowTurnedOnBoard -= 1;
			}
			else if (this->boardVector.at(lineValues.at(i)) == 4)
			{
				redTurnedOnBoard -= 1;
			}
		}

		if (i == 5)
		{
			this->boardVector.at(lineValues.at(i)) = currentTurn == YELLOW_PLAYER ? yellowNextTurn : redNextTurn;
		}
		else
		{
			this->boardVector.at(lineValues.at(i)) = this->boardVector.at(lineValues.at(i + 1));
		}
	}
	countUpTurned();
	changeTurn();
}

void Game::shiftDown(int column)
{
	std::vector<int>columnValues = findColumnValues(column);

	for (int i = 5; i >= 0; i--)
	{
		if (i == 5)
		{
			if (this->boardVector.at(columnValues.at(i)) == 3)
			{
				yellowTurnedOnBoard -= 1;
			}
			else if (this->boardVector.at(columnValues.at(i)) == 4)
			{
				redTurnedOnBoard -= 1;
			}
		}

		if (i == 0)
		{
			this->boardVector.at(columnValues.at(i)) = currentTurn == YELLOW_PLAYER ? yellowNextTurn : redNextTurn;
		}
		else
		{
			this->boardVector.at(columnValues.at(i)) = this->boardVector.at(columnValues.at(i - 1));
		}
	}
	countUpTurned();
	changeTurn();
}

void Game::shiftUp(int column)
{
	std::vector<int>columnValues = findColumnValues(column);

	for (int i = 0; i < 6; i++)
	{
		if (i == 0)
		{
			if (this->boardVector.at(columnValues.at(i)) == 3)
			{
				yellowTurnedOnBoard -= 1;
			}
			else if (this->boardVector.at(columnValues.at(i)) == 4)
			{
				redTurnedOnBoard -= 1;
			}
		}

		if (i == 5)
		{
			this->boardVector.at(columnValues.at(i)) = currentTurn == YELLOW_PLAYER ? yellowNextTurn : redNextTurn;
		}
		else
		{
			this->boardVector.at(columnValues.at(i)) = this->boardVector.at(columnValues.at(i + 1));
		}
	}
	countUpTurned();
	changeTurn();
}


