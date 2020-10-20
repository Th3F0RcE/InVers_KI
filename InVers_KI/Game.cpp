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
	//Variable to store the vector-values
	std::vector<int>values;

	//If the Player chose LINE, find line values
	if (std::tolower(LC) == 'l')
	{
		values = findLineValues(number);
	}
	//If the Player chose COLUMN, find column values
	else if (std::tolower(LC) == 'c')
	{
		values = findColumnValues(number);
	}

	//If the Player chose RIGHT or DOWN, check the LAST value in the vector
	//That is because the counter in the loops of the shift-functions of RIGHT and DOWN count down
	if (std::tolower(direction) == 'r' || std::tolower(direction) == 'd')
	{
		//If Yellow is on turn and wants to push out a turned red stone (and vice versa), print Error-Message
		if((this->boardVector.at(values.at(5)) == YELLOW_CELL_TURNED && currentTurn == RED_PLAYER) ||
			(this->boardVector.at(values.at(5)) == RED_CELL_TURNED && currentTurn == YELLOW_PLAYER))
		{
			return false;
		}
	}

	//If the Player chose LEFT or UP, check the FIRST value in the vector
	//That is because the counter in the loops of the shift-functions of LEFT and UP count up
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
	//Variable to compare to the given line
	int iLine = 0;

	//Variable to store the vector-values
	std::vector<int>values;

	//Loop through all cells of the vector
	for (unsigned int i = 0; i < this->boardVector.size(); i++)
	{
		//If in the given line AND the value is not a border-cell, add the values to the variable
		if (iLine == line && this->boardVector.at(i) != 2)
		{
			values.push_back(i);
		}
		//If at the last position of a line, count up the lineCounter
		if (i % 8 == 7)
		{
			iLine += 1;
		}
	}

	return values;
}

std::vector<int> Game::findColumnValues(int column)
{
	//Variable to compare to the given column
	int iColumn = 0;

	//Variable to multiply it by 8 (Because of the vector structure)
	int multiplier = 1;

	//Variable to store the vector-values
	std::vector<int>values;

	//Loop through all vector-cells
	for (unsigned int i = 0; i < this->boardVector.size(); i++)
	{
		//If at the given column AND the vector-cell is not a border-cell, add the values to the variable
		if (i == column + (8 * multiplier) && this->boardVector.at(i) != 2)
		{
			values.push_back(i);
			multiplier += 1;
		}
	}

	return values;
}

std::vector<std::vector<int>> Game::possibleMoves()
{
	//Border cells of the Board of the game (NOT the outer border, but the last "movable" stones)
	std::vector<int> leftBorderCells = findColumnValues(1);
	std::vector<int> rightBorderCells = findColumnValues(6);
	std::vector<int> topBorderCells = findLineValues(1);
	std::vector<int> bottomBorderCells = findLineValues(6);

	//Variable to store all possible moves
	std::vector<std::vector<int>> allMoves;

	//Variable to store the current Board of the game
	std::vector<int> currentBoard = getBoardVector();

	//Array to store char value of line/column numbers
	//char numbers[] = "123456";//{ '1', '2', '3', '4', '5', '6' };

	//Variable to store, who is on turn atm
	int currentTurn = getCurrentTurn();

	for (int i = 0; i < 6; i++)
	{
		//Check if YELLOW is on turn
		if (currentTurn == 0)
		{
			//If a left Border cell is not a turned RED stone, add the move to the vector
			if (currentBoard.at(leftBorderCells.at(i)) != RED_CELL_TURNED)
			{
				allMoves.push_back({ i + 1, LEFT });
			}
			//If a right Border cell is not a turned RED stone, add the move to the vector
			if (currentBoard.at(rightBorderCells.at(i)) != RED_CELL_TURNED)
			{
				allMoves.push_back({ i + 1, RIGHT });
			}
			//If a top Border cell is not a turned RED stone, add the move to the vector
			if (currentBoard.at(topBorderCells.at(i)) != RED_CELL_TURNED)
			{
				allMoves.push_back({ i + 1, UP });
			}
			//If a bottom Border cell is not a turned RED stone, add the move to the vector
			if (currentBoard.at(bottomBorderCells.at(i)) != RED_CELL_TURNED)
			{
				allMoves.push_back({ i + 1, DOWN });
			}
		}
		//Check if RED is on turn
		else if (true)
		{
			//If a left Border cell is not a turned YELLOW stone, add the move to the vector
			if (currentBoard.at(leftBorderCells.at(i)) != YELLOW_CELL_TURNED)
			{
				allMoves.push_back({ i + 1, LEFT });
			}
			//If a right Border cell is not a turned YELLOW stone, add the move to the vector
			if (currentBoard.at(rightBorderCells.at(i)) != YELLOW_CELL_TURNED)
			{
				allMoves.push_back({ i + 1, RIGHT });
			}
			//If a top Border cell is not a turned YELLOW stone, add the move to the vector
			if (currentBoard.at(topBorderCells.at(i)) != YELLOW_CELL_TURNED)
			{
				allMoves.push_back({ i + 1, UP });
			}
			//If a bottom Border cell is not a turned YELLOW stone, add the move to the vector
			if (currentBoard.at(bottomBorderCells.at(i)) != YELLOW_CELL_TURNED)
			{
				allMoves.push_back({ i + 1, DOWN });
			}
		}
	}

	return allMoves;
}

int Game::getCurrentTurn()
{
	return currentTurn;
}

void Game::saveStone(char LC, int number, char direction)
{
	//Variable to store the vector-values
	std::vector<int> values;

	//Variable to store the stone that will be pushed out
	int pushedStone = 0;

	//If the Player chose LINE, find line values
	if (std::tolower(LC) == 'l')
	{
		values = findLineValues(number);

		//If the Player chose LEFT, check the FIRST value in the vector
		if (std::tolower(direction) == 'l')
		{
			pushedStone = this->boardVector.at(values.at(0));
		}
		//If the Player chose RIGHT, check the LAST value in the vector
		else
		{
			pushedStone = this->boardVector.at(values.at(5));
		}
	}
	//If the Player chose COLUMN, find column values
	else if (std::tolower(LC) == 'c')
	{
		values = findColumnValues(number);

		//If the Player chose UP, check the FIRST value in the vector
		if (std::tolower(direction) == 'u')
		{
			pushedStone = this->boardVector.at(values.at(0));
		}
		//If the Player chose DOWN, check the LAST value in the vector
		else if (std::tolower(direction) == 'd')
		{
			pushedStone = this->boardVector.at(values.at(5));
		}
	}

	//If the pushed out stone is a Yellow stone, turn it
	if (pushedStone == YELLOW_CELL)
	{
		pushedStone = YELLOW_CELL_TURNED;
	}
	//If the pushed out stone is a Red stone, turn it
	else if (pushedStone == RED_CELL)
	{
		pushedStone = RED_CELL_TURNED;
	}

	//If Player Yellow is on turn, save the stone for yellow
	if (currentTurn == YELLOW_PLAYER)
	{
		yellowNextTurn = pushedStone;
	}
	//If Player Red is on turn, save the stone for red
	else
	{
		redNextTurn = pushedStone;
	}
}

void Game::changeTurn()
{
	//If Player Yellow is on turn, change to Player Red
	if (currentTurn == YELLOW_PLAYER)
	{
		currentTurn = RED_PLAYER;
	}
	//If Player Red is on turn, change to Player Yellow
	else
	{
		currentTurn = YELLOW_PLAYER;
	}
}

void Game::countUpTurned()
{
	//If Player Yellow is on turn, count up the value for Yellow
	if (currentTurn == YELLOW_PLAYER)
	{
		yellowTurnedOnBoard += 1;
	}
	//If Player Red is on turn, count up the value for Red
	else
	{
		redTurnedOnBoard += 1;
	}
}

void Game::logMove(std::string& toRecord)
{
	//Add hard spaces
	if (toRecord.length() == 5)
	{
		toRecord += " ";
	}

	//If Yellow is on turn, log the move for Yellow
	if (getCurrentTurn() == YELLOW_PLAYER)
	{
		Round round;
		round.yellowMove = toRecord;
		round.redMove = "";

		rounds.push_back(round);
	}
	//If Red is on turn, log the move for Red
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
	//Variable to return if someone has won
	bool hasWon = false;
	
	//If 19 turned yellow stone on the board, yellow wins the game
	if (yellowTurnedOnBoard >= 19)
	{
		appendToNextMessage("YELLOW HAS WON THE ROUND!\n");
		hasWon = true;
	}
	//If 19 turnes red stones on the board, red wins the game
	if (redTurnedOnBoard >= 19)
	{
		appendToNextMessage("RED HAS WON THE ROUND!\n");
		hasWon = true;
	}
	gameFinished = hasWon;
}

void Game::shiftRight(int line)
{
	//Variable to store the vector-values
	std::vector<int>lineValues = findLineValues(line);

	//Loop through all 6 values (Count Down)
	for (int i = 5; i >= 0; i--)
	{
		//If at the last value (The one that will be pushed out)
		if (i == 5)
		{
			//If the pushed out stone is a turned yellow stone, count down the counter for Yellow
			if (this->boardVector.at(lineValues.at(i)) == 3)
			{
				yellowTurnedOnBoard -= 1;
			}
			//If the pushed out stone is a turned red stone, count down the counter for Red
			else if (this->boardVector.at(lineValues.at(i)) == 4)
			{
				redTurnedOnBoard -= 1;
			}
		}

		//If at the first value (The one that will be pushed on the board)
		if (i == 0)
		{
			//If Player Yellow is on turn, put the stone in Yellow's hand, else put stone in Red's hand
			this->boardVector.at(lineValues.at(i)) = currentTurn == YELLOW_PLAYER ? yellowNextTurn : redNextTurn;
		}
		//If not at the first value
		else
		{
			//Move the cells
			this->boardVector.at(lineValues.at(i)) = this->boardVector.at(lineValues.at(i - 1));
		}
	}
	countUpTurned();
	changeTurn();
}

void Game::shiftLeft(int line)
{
	//Variable to store the vector-values
	std::vector<int>lineValues = findLineValues(line);

	//Loop through all 6 values (Count Up)
	for (int i = 0; i < 6; i++)
	{
		//If at the first value (The one that will be pushed out)
		if (i == 0)
		{
			//If the pushed out stone is a turned yellow stone, count down the counter for Yellow
			if (this->boardVector.at(lineValues.at(i)) == 3)
			{
				yellowTurnedOnBoard -= 1;
			}
			//If the pushed out stone is a turned red stone, count down the counter for Red
			else if (this->boardVector.at(lineValues.at(i)) == 4)
			{
				redTurnedOnBoard -= 1;
			}
		}

		//If at the last value (The one that will be pushed on the board)
		if (i == 5)
		{
			//If Player Yellow is on turn, put the stone in Yellow's hand, else put stone in Red's hand
			this->boardVector.at(lineValues.at(i)) = currentTurn == YELLOW_PLAYER ? yellowNextTurn : redNextTurn;
		}
		//If not at the last value
		else
		{
			//Move the cells
			this->boardVector.at(lineValues.at(i)) = this->boardVector.at(lineValues.at(i + 1));
		}
	}
	countUpTurned();
	changeTurn();
}

void Game::shiftDown(int column)
{
	//Variable to store the vector-values
	std::vector<int>columnValues = findColumnValues(column);

	//Loop through all 6 values (Count Down)
	for (int i = 5; i >= 0; i--)
	{
		//If at the last value (The one that will be pushed out)
		if (i == 5)
		{
			//If the pushed out stone is a turned yellow stone, count down the counter for Yellow
			if (this->boardVector.at(columnValues.at(i)) == 3)
			{
				yellowTurnedOnBoard -= 1;
			}
			//If the pushed out stone is a turned red stone, count down the counter for Red
			else if (this->boardVector.at(columnValues.at(i)) == 4)
			{
				redTurnedOnBoard -= 1;
			}
		}

		//If at the first value (The one that will be pushed on the board)
		if (i == 0)
		{
			//If Player Yellow is on turn, put the stone in Yellow's hand, else put stone in Red's hand
			this->boardVector.at(columnValues.at(i)) = currentTurn == YELLOW_PLAYER ? yellowNextTurn : redNextTurn;
		}
		//If not at the first value
		else
		{
			//Move the cells
			this->boardVector.at(columnValues.at(i)) = this->boardVector.at(columnValues.at(i - 1));
		}
	}
	countUpTurned();
	changeTurn();
}

void Game::shiftUp(int column)
{
	//Variable to store the vector-values
	std::vector<int>columnValues = findColumnValues(column);

	//Loop through all 6 values (Count Up)
	for (int i = 0; i < 6; i++)
	{
		//If at the first value (The one that will be pushed out)
		if (i == 0)
		{
			//If the pushed out stone is a turned yellow stone, count down the counter for Yellow
			if (this->boardVector.at(columnValues.at(i)) == 3)
			{
				yellowTurnedOnBoard -= 1;
			}
			//If the pushed out stone is a turned red stone, count down the counter for Red
			else if (this->boardVector.at(columnValues.at(i)) == 4)
			{
				redTurnedOnBoard -= 1;
			}
		}

		//If at the last value (The one that will be pushed on the board)
		if (i == 5)
		{
			//If Player Yellow is on turn, put the stone in Yellow's hand, else put stone in Red's hand
			this->boardVector.at(columnValues.at(i)) = currentTurn == YELLOW_PLAYER ? yellowNextTurn : redNextTurn;
		}
		//If not at the last value
		else
		{
			//Move the cells
			this->boardVector.at(columnValues.at(i)) = this->boardVector.at(columnValues.at(i + 1));
		}
	}
	countUpTurned();
	changeTurn();
}


