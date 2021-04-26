#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <curses.h>
#include <random>
using namespace std;

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

int Random_generator()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 10);
    return dis(gen);
}

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

void designGolds()
{
    for (int i = 0; i < 10; i++)
    {
        int n = Random_generator();
        gold[i].id = i;
        gold[i].exist = true;
        if (n % 2)
            gold[i].type = 'g';
        else
            gold[i].type = 's';
        if (n < 3)
            gold[i].size = 2;
        else if (n < 6)
            gold[i].size = 3;
        else if (n < 9)
            gold[i].size = 5;
        else
        {
            gold[i].type = 'd';
            gold[i].size = 2;
        }
        gold[i].x = 4 * n + i % 2 * 3 + 11;
        gold[i].y = i % 3 * 17 + n % 2 * 15 + 15;
    }
}

void initGolds()
{
    for (int i = 0; i < 10; i++)
    {
        if (!gold[i].exist)
        {
            continue;
        }
        if (gold[i].size == 3)
        {
            for (int p = 0; p < 3; p++)
            {
                for (int q = 0; q < 3; q++)
                {
                    if (gold[i].type == 's')
                        map[gold[i].x + p][gold[i].y + q] = 7;
                    if (gold[i].type == 'g')
                        map[gold[i].x + p][gold[i].y + q] = 8;
                }
            }
        }
        if (gold[i].size == 5)
        {
            for (int p = 0; p < 5; p++)
            {
                for (int q = 0; q < 5; q++)
                {
                    if (gold[i].type == 's')
                        map[gold[i].x + p][gold[i].y + q] = 7;
                    if (gold[i].type == 'g')
                        map[gold[i].x + p][gold[i].y + q] = 8;
                }
            }
        }
        else
        {
            for (int p = 0; p < 2; p++)
            {
                for (int q = 0; q < 2; q++)
                {
                    if (gold[i].type == 's')
                        map[gold[i].x + p][gold[i].y + q] = 7;
                    if (gold[i].type == 'g')
                        map[gold[i].x + p][gold[i].y + q] = 8;
                    if (gold[i].type == 'd')
                        map[gold[i].x + p][gold[i].y + q] = 9;
                }
            }
        }
    }
}

void print_Map(miner_hook &m, WINDOW *&win)
{
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
    wrefresh(win);
}

int check_hook(miner_hook m)
{
    int x = m.hook_catcher_x[0], y = m.hook_catcher_y[1];
    char ore = '0';
    int num = 10;
    for (int i = -1; i < 1; i++)
    {
        if (map[x][y + i] == 1)
            ore = 'w'; // wall
        else if (map[x][y + i] == 7)
            ore = 's'; // stone
        else if (map[x][y + i] == 8)
            ore = 'g'; // gold
        else if (map[x][y + i] == 9)
            ore = 'd'; // diamond
    }

    if (ore == 'w')
    {
        num = 11;
    }

    // get the ore information
    else if (ore == 's')
    {
        for (int i = 0; i < 10; i++)
        {
            if (gold[i].type == 's' && gold[i].x == x + 1)
            {
                num = i;
            }
        }
    }
    else if (ore == 'g')
    {
        for (int i = 0; i < 10; i++)
        {
            if (gold[i].type == 'g' && gold[i].x == x + 1)
            {
                num = i;
            }
        }
    }
    else if (ore == 'd')
        num = 9; // diamond
    return num;
}

int move_ore(miner_hook &m, WINDOW *&win)
{
    int ore = check_hook(m);
    while (m.hook_catcher_x[1] != 9) //
    {

        if (ore == 11) //  wall
        {
            if (m.hook_length - 6 >= 2)
                m.hook_length -= 6;
            else
                m.hook_length = 2;
            generate_miner(m.miner_x, m.miner_y, m);
            print_Map(m, win);
        }

        else if (gold[ore].size == 2)
        {
            if (m.hook_length - 5 >= 2)
                {m.hook_length -= 5;
                gold[ore].x -= 5;}
            else
                {m.hook_length = 2;
                gold[ore].x = 3;}
            generate_miner(m.miner_x, m.miner_y, m);
            print_Map(m, win);
        }
        else if (gold[ore].size == 3)
        {
            if (m.hook_length - 3 >= 2)
            {
                m.hook_length -= 3;
                gold[ore].x -= 3;
            }
            else
            {
                m.hook_length = 2;
                gold[ore].x = 3;
            }
            generate_miner(m.miner_x, m.miner_y, m);
            print_Map(m, win);
        }
        else
        {
            m.hook_length--;
            gold[ore].x--;
            generate_miner(m.miner_x, m.miner_y, m);
            print_Map(m, win);
        }
    }
    gold[ore].exist = false;
    generate_miner(m.miner_x, m.miner_y, m);
    print_Map(m, win);
    return ore;
}

int launch_hook(miner_hook &m, WINDOW *&win)
{
    int ore;
    m.hook_length++;
    generate_miner(m.miner_x, m.miner_y, m);
    print_Map(m, win);
    while (check_hook(m) == 10)
    {
        m.hook_length += 2;
        generate_miner(m.miner_x, m.miner_y, m);
        print_Map(m, win);
    }
    ore = move_ore(m, win); // upward
    return ore;
}

// move miner horizontally
void move_miner(miner_hook &m, WINDOW *&win)
{
    if (m.miner_y == 57)
    {
        m.miner_y = 4;
        generate_miner(m.miner_x, m.miner_y, m);
        print_Map(m, win);
    }
    else
    {
        m.miner_y++;
        generate_miner(m.miner_x, m.miner_y, m);
        print_Map(m, win);
    }
}

int calculate_reward(int id)
{
    int type, size;

    if (gold[id].type == 's')
        type = 2;
    else if (gold[id].type == 'g')
        type = 10;
    else
        type = 50;

    if (gold[id].size == 5)
        size = 50;
    else if (gold[id].size == 3)
        size = 30;
    else
        size = 10;

    return type * size;
}

void play(miner_hook &m, WINDOW *&win)
{
    int sh;
    while (epoch < 1000000)
    {
        while ((sh = getch()) == ERR)
        {
            move_miner(m, win);
        }
        int ore = launch_hook(m, win);
        reward += calculate_reward(ore);
    }
}

int main()
{
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    WINDOW *win = newwin(60, 70, 0, 0);
    refresh();
    box(win, 0, 0);

    miner_hook m;
    m.hook_length = 3;
    generate_miner(6, 4, m);
    designGolds();
    print_Map(m, win);

    play(m, win);
    //endwin();
    return 0;
}
