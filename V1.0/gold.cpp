#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <curses.h>
#include <random>
#include "generate_Map.h"
#include "gold.h"
using namespace std;

const int MAX = 10;
int map[60][70];
Golds_ret gold[MAX];

int Random_generator()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 10);
    return dis(gen);
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
