#pragma once

#include "../dependencies/kbhit.h"
#include <array>
#include <fstream>
#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <thread>
#include <vector>

#define ROW_NUMBER 25
#define COLUMN_NUMBER 55
#define DEFAULT_NUMBER_OF_ROCKS 16
#define INITIAL_COORDINATE -1

#define QUIT 'q'

#define UP_W 'w'
#define DOWN_S 's'
#define RIGHT_D 'd'
#define LEFT_A 'a'

#define UP_ARROW 'A'
#define DOWN_ARROW 'B'
#define RIGHT_ARROW 'C'
#define LEFT_ARROW 'D'

#define ANACONDA_SCORE 'A'
#define PYTHON_SCORE 'P'

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3
#define NONE 4

struct Point
{
    size_t X;
    size_t Y;
};

typedef std::array<std::array<const char*, 55>, 25> matrix;
typedef std::vector<Point>                          coordinateVector;