#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <Windows.h>

constexpr auto CELL_SIZE = 6;
constexpr auto YELLOW_CELL = 0;
constexpr auto RED_CELL = 1;
constexpr auto BORDER_CELL = 2;
constexpr auto YELLOW_CELL_TURNED = 3;
constexpr auto RED_CELL_TURNED = 4;

constexpr auto LEFT = 0;
constexpr auto RIGHT = 1;
constexpr auto UP = 2;
constexpr auto DOWN = 3;