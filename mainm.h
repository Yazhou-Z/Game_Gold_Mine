#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <curses.h>
#include <random>
#include "parts.h"
#ifndef MAINM_H
#define MAINM_H

int map[60][70];
int miner_x, miner_y;
const int MAX = 10;
int epoch = 0;
int reward = 0;

struct miner_hook
{
    int miner_x;
    int miner_y;
    int hook_length;
    int hook_line_x[70];
    int hook_line_y[70];
    int hook_catcher_x[3];
    int hook_catcher_y[3];
};

struct Golds_ret
{
    int x, y, id;
    bool exist; //whether had been mined
    int size;   //small:2  middle:3  large:5
    char type;
};

Golds_ret gold[MAX];

void generate_Map();
void generate_miner(int x, int y, miner_hook &m);
void init_minor(miner_hook m);
void designGolds();
void initGolds();
void print_Map(miner_hook &m, WINDOW *&win);
int check_hook(miner_hook m);
int move_ore(miner_hook &m, WINDOW *&win);
int launch_hook(miner_hook &m, WINDOW *&win);
void move_miner(miner_hook &m, WINDOW *&win);
int calculate_reward(int id);
void startting(WINDOW *&win);
void endding(WINDOW *&win);
void play(miner_hook &m, WINDOW *&win);
int main();
#endif