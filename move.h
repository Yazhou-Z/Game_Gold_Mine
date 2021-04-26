// move.h
#include <sstream>
#include <cstdlib>
#include <curses.h>
#include "generate_Map.h"
#include "printMap.h"

#ifndef MOVE_H
#define MOVE_H

int check_hook(miner_hook m);
int move_ore(miner_hook &m, WINDOW *&win);
int launch_hook(miner_hook &m, WINDOW *&win);
void move_miner(miner_hook &m, WINDOW *&win);
#endif