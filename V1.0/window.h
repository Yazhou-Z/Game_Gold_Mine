// window.h
#include <sstream>
#include <cstdlib>
#include <curses.h>
#include "generate_Map.h"
#include "calculate_reward.h"
#include "printMap.h"
#include "gold.h"

#ifndef WINDOW_H
#define WINDOW_H

void startting(WINDOW *&win);
void endding(WINDOW *&win);
#endif