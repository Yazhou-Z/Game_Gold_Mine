#include <cstdlib>
#include <curses.h>
#include "generate_Map.h"
#include "gold.h"
#include "printMap.h"
#include "move.h"

const int MAX = 10;
Golds_ret gold[MAX];
int map[60][70];

int check_hook(miner_hook m)
{
    int x = m.hook_catcher_x[0], y = m.hook_catcher_y[1];
    char ore = '0';
    int num = 10;
    for (int i = -1; i < 2; i++)
    {
        if (map[x + 1][y + i] == 1)
            ore = 'w'; // wall
        else if (map[x + 1][y + i] == 7)
            ore = 's'; // stone
        else if (map[x + 1][y + i] == 8)
            ore = 'g'; // gold
        else if (map[x + 1][y + i] == 9)
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
            if (gold[i].type == 's' && gold[i].x == x + 1 && (gold[i].y == y || gold[i].y == y + 1 || gold[i].y == y - 1))
            {
                num = i;
            }
        }
    }
    else if (ore == 'g')
    {
        for (int i = 0; i < 10; i++)
        {
            if (gold[i].type == 'g' && gold[i].x == x + 1 && (gold[i].y == y || gold[i].y == y + 1 || gold[i].y == y - 1))
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
            {
                m.hook_length -= 5;
                gold[ore].x -= 5;
            }
            else
            {
                m.hook_length = 2;
                gold[ore].x = 3;
            }
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
        m.hook_length += 1;
        generate_miner(m.miner_x, m.miner_y, m);
        print_Map(m, win);
    }
    ore = move_ore(m, win); // upward
    return ore;
}

// move miner horizontally
void move_miner(miner_hook &m, WINDOW *&win)
{
    if (m.miner_y == 59)
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
