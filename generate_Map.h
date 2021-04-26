// generate_Map.h
#ifndef GENERATE_MAP_H
#define GENERATE_MAP_H

int miner_x, miner_y;
int epoch = 0;

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

void generate_Map();
void generate_miner(int x, int y, miner_hook &m);
void init_minor(miner_hook m);
#endif