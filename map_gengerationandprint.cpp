#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <curses.h>
using namespace std;

int map[60][70];
int miner_x, miner_y;

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

void miner_tomap(miner_hook m)
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

void print_Map(WINDOW *&win)
{
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
}

void generate_hook(int x, int y, miner_hook &m){
    int different = x - m.hook_catcher_x[1];
    m.hook_length += different;
    generate_miner(m.miner_x,m.miner_y,m);
}

int main()
{
    initscr();
    WINDOW *win = newwin(60, 70, 0, 0);
    refresh();
    box(win, 0, 0);
    miner_hook m;
    m.hook_length = 2;
    generate_Map();
    generate_miner(6, 4, m);
    miner_tomap(m);
    print_Map(win);
    wrefresh(win);
    int sh = getch();
    endwin();
    return 0;
}
