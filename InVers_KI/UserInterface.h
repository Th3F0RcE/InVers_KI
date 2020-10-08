#pragma once
#include "includes.h"
#include "Game.h"

constexpr auto CELL_SIZE = 6;
constexpr auto YELLOW_CELL = 0;
constexpr auto RED_CELL = 1;
constexpr auto BORDER_CELL = 2;
constexpr auto YELLOW_CELL_TURNED = 3;
constexpr auto RED_CELL_TURNED = 4;

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

