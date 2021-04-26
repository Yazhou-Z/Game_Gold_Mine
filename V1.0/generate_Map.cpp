//  generate_Map.cpp
#include <iostream>
#include "generate_Map.h"
using namespace std;

int map[60][70];

void generate_Map()
{
    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 70; j++)
        {
            if (i == 0 || i == 9 || i == 59)
                map[i][j] = 1;
            else if (j == 0 || j == 69)
                map[i][j] = 1;
            else
                map[i][j] = 0;
        }
    }
}

void generate_miner(int x, int y, miner_hook &m)
{
    m.miner_x = x;
    m.miner_y = y;
    int l = m.hook_length;
    m.hook_line_x[0] = x + 1;
    m.hook_line_y[0] = y - 2;
    for (int i = 1; i < l; i++)
    {
        m.hook_line_x[i] = m.hook_line_x[i - 1] + 1;
        m.hook_line_y[i] = m.hook_line_y[i - 1];
    }
    m.hook_catcher_x[1] = m.hook_line_x[l - 1] + 1;
    m.hook_catcher_y[1] = m.hook_line_y[l - 1];
    m.hook_catcher_x[0] = m.hook_catcher_x[1];
    m.hook_catcher_y[0] = m.hook_catcher_y[1] - 1;
    m.hook_catcher_x[2] = m.hook_catcher_x[1];
    m.hook_catcher_y[2] = m.hook_catcher_y[1] + 1;
}

void init_minor(miner_hook m)
{
    map[m.miner_x][m.miner_y] = 2;
    map[m.miner_x + 1][m.miner_y - 1] = 3;
    map[m.miner_x + 1][m.miner_y] = 4;
    map[m.miner_x + 1][m.miner_y + 1] = 5;
    map[m.miner_x + 2][m.miner_y - 1] = 3;
    map[m.miner_x + 2][m.miner_y + 1] = 5;
    for (int i = 0; i < m.hook_length; i++)
    {
        map[m.hook_line_x[i]][m.hook_line_y[i]] = 4;
    }
    map[m.hook_catcher_x[0]][m.hook_catcher_y[0]] = 3;
    map[m.hook_catcher_x[1]][m.hook_catcher_y[1]] = 4;
    map[m.hook_catcher_x[2]][m.hook_catcher_y[2]] = 5;
}
