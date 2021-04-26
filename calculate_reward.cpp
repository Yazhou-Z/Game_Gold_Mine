// calculate_reward.cpp
#include <iostream>
#include "calculate_reward.h"
#include ""
using namespace std;

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
