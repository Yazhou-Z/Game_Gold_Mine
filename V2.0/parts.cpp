#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <curses.h>
#include <random>
#include "parts.h"
using namespace std;
/*
Generate a random number
No input
Output an integer
*/
int Random_generator()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 10);
    return dis(gen);
}

