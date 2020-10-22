#pragma once
#include "includes.h"
#include "Game.h"
#include "ArtificialIntelligence.h"

//Create Messages
void createNextMessage(std::string msg);
void appendToNextMessage(std::string msg);

void clearScreen();	//Clear the Console
void printMenu();	//Print the Menu (Commands)
void printLogo();	//Print the Logo
void printRules();	//Print the Game Rules
void printMessage();	//Print the Next Message
void printBoard(Game& game);	//Print the Board
void printSituation(Game& game);	//Print all relevant information
void printPossibleMoves(Game& game);	//Print all moves that are possible for the current Player
void printChosenGame(int gameMode); //Print the Game Mode, that was chosen

