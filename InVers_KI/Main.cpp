#include "includes.h"

#include "Game.h"
#include "UserInterface.h"

//----------------------------------------------------------------------------
// Global variable
//----------------------------------------------------------------------------
Game* current_game = NULL;

//----------------------------------------------------------------------------
// Start New Game
//----------------------------------------------------------------------------
void newGame()
{
	if (NULL != current_game)
	{
		delete current_game;
	}

	current_game = new Game();
}

//----------------------------------------------------------------------------
// Insert a Stone
//----------------------------------------------------------------------------
void insertPiece()
{
	//Variable to store the output of the move
	std::string toRecord = "Player ";

	//Inputs from the user
	std::string LC;
	std::string number;
	std::string direction;

	//Get user input for if they want to move a line or a column
	std::cout << "Do you want to move a Line(horizontal) or a Column(vertical)?\n";
	std::cout << "(L)ine/(C)olumn: ";
	getline(std::cin, LC);

	//If length is longer than one character, print Error-Message
	if (LC.length() != 1)
	{
		createNextMessage("Invalid input, try using only one character (L, C)!\n");
		return;
	}
	//If character in not l or c, print Error-Message
	if (std::tolower(LC[0]) != 'l' && std::tolower(LC[0]) != 'c')
	{
		createNextMessage("Invalid command!\n");
		return;
	}

	//Get user input for the number of the line/column they want to put their stone in
	std::cout << "Choose your Line- or Column-number (1-6)!\n";
	std::cout << "Type here: ";
	getline(std::cin, number);

	//If length is longer than one character, print Error-Message
	if (number.length() != 1)
	{
		createNextMessage("Invalid input, try using only one number (1-6)!\n");
		return;
	}
	//If character is not between 1 and 6, print Error-Message
	if (number[0] < '1' || number[0] > '6')
	{
		createNextMessage("Invalid Line- or Column-number!\n");
		return;
	}

	//Choose direction Left/Right for lines, Up/Down for columns
	if (std::tolower(LC[0]) == 'l')
	{
		std::cout << "Choose your direction!\n";
		std::cout << "(L)eft\t (R)ight: ";
		getline(std::cin, direction);
	}
	else if (std::tolower(LC[0]) == 'c')
	{
		std::cout << "Choose your direction!\n";
		std::cout << "(U)p\t (D)own: ";
		getline(std::cin, direction);
	}

	//Put together whole position to put stone
	std::string position = LC + number + direction;

	//Check if the move is valid
	if (!current_game->isMoveValid(position[0], position[1] - '0', position[2]))
	{
		createNextMessage("It is not allowed to push a turned stone of the Enemy-Player off the Board!");
		return;
	}
	else
	{
		//Log the Player that is on turn
		if (current_game->getCurrentTurn() == Game::YELLOW_PLAYER)
		{
			toRecord += "YELLOW";
		}
		else
		{
			toRecord += "RED";
		}

		//Add to log for more readability
		toRecord += " moved ";

		//Log if he chose Line or Column
		if (std::tolower(position[0]) == 'l')
		{
			toRecord += "LINE ";
		}
		else
		{
			toRecord += "COLUMN ";
		}

		//Log which line or column he chose
		toRecord += position[1];

		//Log if he chose Up/Down	Left/Right
		if (std::tolower(position[2]) == 'u')
		{
			toRecord += " UP.";
		}
		else if (std::tolower(position[2]) == 'd')
		{
			toRecord += " DOWN.";
		}
		else if (std::tolower(position[2]) == 'l')
		{
			toRecord += " LEFT.";
		}
		else if (std::tolower(position[2]) == 'r')
		{
			toRecord += " RIGHT.";
		}

		//Log the complete turn of a Player
		current_game->logMove(toRecord);

		//Save the Stone that will be pushed out for the next turn
		current_game->saveStone(position[0], position[1] - '0', position[2]);

		//Move the stones on the board based on the user input
		if (std::tolower(position[0]) == 'l')
		{
			if (std::tolower(position[2]) == 'l')
			{
				current_game->shiftLeft(position[1] - '0');
			}
			else if (std::tolower(position[2] == 'r'))
			{
				current_game->shiftRight(position[1] - '0');
			}
		}
		else if (std::tolower(position[0]) == 'c')
		{
			if (std::tolower(position[2]) == 'u')
			{
				current_game->shiftUp(position[1] - '0');
			}
			else if (std::tolower(position[2]) == 'd')
			{
				current_game->shiftDown(position[1] - '0');
			}
		}

		//Check if a Player won the round
		current_game->checkForWinner();
	}
	
	return;
}

//----------------------------------------------------------------------------
// Run the Game
//----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	bool run = true;

	clearScreen();
	printLogo();

	std::string input = "";

	while (run)
	{
		printMessage();
		printMenu();

		//get input from user
		std::cout << "type here: ";
		getline(std::cin, input);

		//If input is longer than one character, print Error-Message
		if (input.length() != 1)
		{
			std::cout << "Invalid input, try to write one letter only!\n\n";
			continue;
		}


		switch (input[0])
		{
			//Start new Game
			case 'N':
			case 'n':
			{
				newGame();
				clearScreen();
				printLogo();
				printBoard(*current_game);
			}
			break;

			//Make a move
			case 'M':
			case 'm':
			{
				if (current_game != NULL)
				{
					//If the game is already finished, print Message
					if (current_game->isFinished())
					{
						std::cout << "This game has already finished!\n";
					}
					else
					{
						insertPiece();
						printLogo();
						printBoard(*current_game);
						printSituation(*current_game);
					}
				}
			}
			break;

			//Print the rules
			case 'R':
			case 'r':
			{
				printRules();
			}
			break;

			//Quit
			case 'Q':
			case 'q':
			{
				run = false;
			}
			break;
		}
	}
	return 0;
}