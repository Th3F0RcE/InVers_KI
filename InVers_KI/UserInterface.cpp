#include "UserInterface.h"

std::string next_message;

void createNextMessage(std::string msg)
{
	next_message = msg;
}

void appendToNextMessage(std::string msg)
{
	next_message += msg;
}

void clearScreen()
{
	system("cls");
}

void printMenu()
{
	std::cout << "Commands: (N)ew Game\t(M)ove\t(Q)uit\t(R)ules\n";
}

void printLogo()
{
	std::cout << "	==============================\n";
	std::cout << "	 _____   __      __\n";
	std::cout << "	|_   _|  \\ \\    / /\n";
	std::cout << "	  | |  _ _\\ \\  / /__ _ __ ___\n";
	std::cout << "	  | | | '_ \\ \\/ / _ \\ '__/ __|\n";
	std::cout << "	 _| |_| | | \\  /  __/ |  \\__ \\\n";
	std::cout << "	|_____|_| |_|\\/ \\___|_|  |___/\n";
	std::cout << "	==============================\n";
	std::cout << "\n\n\n";
}

void printRules()
{
	std::cout << "Invers is a two-player abstract game in which players alternately slide tiles out of a 6x6 grid and flip them over. One face is plain red or yellow, the other is a red or yellow dot.\n";
	std::cout << "On your next turn you push the inverted tile into the grid, forcing another tile out.\n";
	std::cout << "You only invert the tiles once to show the dot side and you cannot slide out the opponent's dot.\n";
	std::cout << "Gradually the board locks up, unless you start sliding out your own flipped tiles. Winner is the first to invert all their tiles, or have the most flipped when no further moves are possible.\n";
}

void printMessage()
{
	std::cout << next_message << std::endl;

	next_message = "";
}

void printBoard(Game& game)
{
	//Variable to store the position 
	//For a Cell-size of 6, 3 lines are printed for each cell
	int lineCounter = 0;

	//Loop through every cell in the board-vector
	for (unsigned int i = 0; i < game.getBoardVector().size(); i++)
	{
		//Loop it 6 times(Cell-size)
		for (int j = 0; j < CELL_SIZE; j++)
		{
			//print yellow cells
			if (game.getBoardVector().at(i) == YELLOW_CELL)
			{
				//If in the 2nd line, print Y
				if (lineCounter == 1 && j == 3)
				{
					std::cout << "Y";
				}
				else
				{
					std::cout << char(0xDB);
				}
			}
			//print red cells
			else if (game.getBoardVector().at(i) == RED_CELL)
			{
				//If in the 2nd line, print R
				if (lineCounter == 1 && j == 3)
				{
					std::cout << "R";
				}
				else
				{
					std::cout << char(0xFF);
				}
			}
			//print border cells
			else if (game.getBoardVector().at(i) == BORDER_CELL)
			{
				//If in the 2nd line, print 0
				if (lineCounter == 1 && j == 3)
				{
					std::cout << "0";
				}
				else
				{
					std::cout << char(0x20);
				}
			}
			//print turned yellow cells
			else if (game.getBoardVector().at(i) == YELLOW_CELL_TURNED)
			{
				//If in the 2nd line, print 1
				if (lineCounter == 1 && j == 3)
				{
					std::cout << "1";
				}
				else
				{
					std::cout << char(0xDB);
				}
			}
			//print turned red cells
			else if (game.getBoardVector().at(i) == RED_CELL_TURNED)
			{
				//If in the 2nd line, print 2
				if (lineCounter == 1 && j == 3)
				{
					std::cout << "2";
				}
				else
				{
					std::cout << char(0xFF);
				}
			}
		}

		//If 3 lines printed, go to the next line in the board-vector
		if (lineCounter > 2)
		{
			lineCounter = 0;
			i += 8;
		}
		//If not all 3 lines are printed, count up lineCounter and loop through the line again
		if ((i % 8 == 7) && lineCounter <= 2)
		{
			i -= 8;
			lineCounter += 1;
			std::cout << '\n';
		}
	}
	std::cout << std::endl;
}

void printSituation(Game& game)
{
	//If at least 1 move was made, print the last moves that were made
	if (game.rounds.size() != 0)
	{
		std::cout << "Last Moves:\n";

		//Variable to store how many moves were made already
		int moves = game.rounds.size();

		//Only show the last 5 moves of each Player
		int toShow = moves >= 5 ? 5 : moves;

		std::string space = "";

		//Add hard spaces
		while (toShow--)
		{
			if (moves < 10)
			{
				space = " ";
			}
			//Print out the last moves
			std::cout << space << moves << " ..... " << game.rounds[moves - 1].yellowMove.c_str() << " | " << game.rounds[moves - 1].redMove.c_str() << "\n";
			moves--;
		}
	}

	//Print how many turned stones each Player has on the board
	std::cout << "Turned Red Stones on the Board: " << game.redTurnedOnBoard << "\n";
	std::cout << "Turned Yellow Stones on the Board: " << game.yellowTurnedOnBoard << "\n";

	//Print current turn
	std::cout << "Current Turn :" << (game.getCurrentTurn() == Game::YELLOW_PLAYER ? "YELLOW" : "RED") << "\n";

	//Print the Stone that will be pushed in the board
	std::cout << "Stone in your hand: " << (game.getCurrentTurn() == Game::YELLOW_PLAYER ? game.yellowNextTurn : game.redNextTurn) << "\n\n";
}

