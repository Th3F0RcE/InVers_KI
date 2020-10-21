#pragma once
#include "includes.h"
#include "Game.h"
#include "ArtificialIntelligence.h"

//Create Messages
void createNextMessage(std::string msg);
void appendToNextMessage(std::string msg);

void clearScreen();
void printMenu();
void printLogo();
void printRules();
void printMessage();
void printBoard(Game& game);
void printSituation(Game& game);	//Print all relevant information
void printPossibleMoves(Game& game);
void printChosenGame();

