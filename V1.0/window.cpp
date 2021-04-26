#include <sstream>
#include <cstdlib>
#include <curses.h>
#include "generate_Map.h"
#include "calculate_reward.h"
#include "printMap.h"
#include "gold.h"
#include "window.h"

int map[60][70];
int reward;

void startting(WINDOW *&win)
{
    generate_Map();
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
        }
    }
    mvwprintw(win, 4, 24, "PRESS ANY KEY TO START");
    wrefresh(win);
}

void endding(WINDOW *&win)
{
    generate_Map();
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
        }
    }


    mvwprintw(win, 4, 30, "GAME OVER");
    mvwprintw(win, 5, 27, "YOUR SCORES: %d", reward);
    wrefresh(win);
}
