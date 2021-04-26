#include <cstdlib>
#include <curses.h>
#include "generate_Map.h"
#include "gold.h"
#include "printMap.h"

int map[60][70];
int reward;

void print_Map(miner_hook &m, WINDOW *&win)
{
    if (epoch >= 180)
        return;
    time_t seconds;
    seconds = time(NULL);
    int begin = seconds;
    while ((seconds = time(NULL)))
    {
        if (seconds - begin == 1)
            break;
    }
    epoch++;

    generate_Map();
    generate_miner(m.miner_x, m.miner_y, m);
    init_minor(m);
    initGolds();

    box(win, 0, 0);
    refresh();
    wmove(win, 0, 0);

    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 70; j++)
        {
            if (map[i][j] == 0)
            {
                wmove(win, i, j);
                waddch(win, 32);
            }
            else if (map[i][j] == 1)
            {
                wmove(win, i, j);
                waddch(win, 35);
            }
            else if (map[i][j] == 2)
            {
                wmove(win, i, j);
                waddch(win, 111);
            }
            else if (map[i][j] == 3)
            {
                wmove(win, i, j);
                waddch(win, 47);
            }
            else if (map[i][j] == 4)
            {
                wmove(win, i, j);
                waddch(win, 124);
            }
            else if (map[i][j] == 5)
            {
                wmove(win, i, j);
                waddch(win, 92);
            }
            else if (map[i][j] == 7)
            {
                wmove(win, i, j);
                waddch(win, 115);
            }
            else if (map[i][j] == 8)
            {
                wmove(win, i, j);
                waddch(win, 103);
            }
            else if (map[i][j] == 9)
            {
                wmove(win, i, j);
                waddch(win, 100);
            }
        }
    }
    
    mvwprintw(win, 2, 50, "TIME: %d", 180-epoch);
    mvwprintw(win, 3, 50, "SCORES: %d", reward);
    wrefresh(win);
}
