// printMap.h
#include <sstream>
#include <cstdlib>
#include <curses.h>
#include "generate_Map.h"
#include "gold.h"

#ifndef PRINTMAP_H
#define PRINTMAP_H

void print_Map(miner_hook &m, WINDOW *&win);
#endif