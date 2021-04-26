// gold.h
#include <sstream>
#include <cstdlib>
#include <curses.h>
#include "generate_Map.h"
#include <random>

#ifndef GOLD_H
#define GOLD_H


struct Golds_ret
{
    int x, y, id;
    bool exist; //whether had been mined
    int size;   //small:2  middle:3  large:5
    char type;
};


int Random_generator();
void designGolds();
void initGolds();
#endif