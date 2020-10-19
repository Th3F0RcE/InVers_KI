#include "ArtificialIntelligence.h"
#include "Game.h"
#include "UserInterface.h"

void ArtificialIntelligence::chooseStrategy(char cStrategy)
{
	if (std::tolower(cStrategy) == 'r')
	{
		strategy = RANDOM;
	}
}

std::vector<char[2]> ArtificialIntelligence::possibleMoves(Game& game)
{
	//Border cells of the Board of the game (NOT the outer border, but the last "movable" stones)
	std::vector<int> leftBorderCells = game.findColumnValues(1);
	std::vector<int> rightBorderCells = game.findColumnValues(6);
	std::vector<int> topBorderCells = game.findLineValues(1);
	std::vector<int> bottomBorderCells = game.findLineValues(6);

	//Variable to store all possible moves
	std::vector<char[2]> allMoves;

	//Variable to store the current Board of the game
	std::vector<int> currentBoard = game.getBoardVector();

	//Array to store char value of line/column numbers
	char numbers[6] = { '1', '2', '3', '4', '5', '6' };

	//Variable to store, who is on turn atm
	int currentTurn = game.getCurrentTurn();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			//Check if YELLOW is on turn
			if (currentTurn == 0)
			{
				//If a left Border cell is not a turned RED stone, add the move to the vector
				if (currentBoard.at(leftBorderCells.at(j)) != RED_CELL_TURNED)
				{
					allMoves.push_back({numbers[j], 'l' });
				}
				//If a right Border cell is not a turned RED stone, add the move to the vector
				if (currentBoard.at(rightBorderCells.at(j)) != RED_CELL_TURNED)
				{
					allMoves.push_back({numbers[j], 'r' });
				}
				//If a top Border cell is not a turned RED stone, add the move to the vector
				if (currentBoard.at(topBorderCells.at(j)) != RED_CELL_TURNED)
				{
					allMoves.push_back({numbers[j], 'u' });
				}
				//If a bottom Border cell is not a turned RED stone, add the move to the vector
				if (currentBoard.at(bottomBorderCells.at(j)) != RED_CELL_TURNED)
				{
					allMoves.push_back({numbers[j], 'd' });
				}
			}
			//Check if RED is on turn
			else if (true)
			{
				//If a left Border cell is not a turned YELLOW stone, add the move to the vector
				if (currentBoard.at(leftBorderCells.at(j)) != YELLOW_CELL_TURNED)
				{
					allMoves.push_back({ numbers[j], 'l' });
				}
				//If a right Border cell is not a turned YELLOW stone, add the move to the vector
				if (currentBoard.at(rightBorderCells.at(j)) != YELLOW_CELL_TURNED)
				{
					allMoves.push_back({ numbers[j], 'r' });
				}
				//If a top Border cell is not a turned YELLOW stone, add the move to the vector
				if (currentBoard.at(topBorderCells.at(j)) != YELLOW_CELL_TURNED)
				{
					allMoves.push_back({ numbers[j], 'u' });
				}
				//If a bottom Border cell is not a turned YELLOW stone, add the move to the vector
				if (currentBoard.at(bottomBorderCells.at(j)) != YELLOW_CELL_TURNED)
				{
					allMoves.push_back({ numbers[j], 'd' });
				}
			}
		}
	}

	return allMoves;
}
