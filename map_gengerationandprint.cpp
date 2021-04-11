#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

int map[60][70];
int miner_x, miner_y;
string hook_x, hook_y;
int hookx[70], hooky[70];

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

void generate_miner()
{
    map[miner_x][miner_y] = 2;
    map[miner_x+1][miner_y-1] = 3;
    map[miner_x+1][miner_y] = 4;
    map[miner_x+1][miner_y+1] = 5;
    map[miner_x+2][miner_y-1] = 3;
    map[miner_x+2][miner_y+1] = 5;
}

void print_Map()
{
    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 70; j++)
        {
            if (map[i][j] == 0)
                printf(" ");
            else if (map[i][j] == 1)
                printf("#");
            else if (map[i][j] == 2)
                printf("o");
            else if (map[i][j] == 3)
                printf("/");
            else if (map[i][j] == 4)
                printf("|");
            else if (map[i][j] == 5)
                printf("\\"); 
            else if (map[i][j] == 7)
                printf("s");
            else if (map[i][j] == 8)
                printf("g");
            else if (map[i][j] == 9)
                printf("d");
        }
        printf("\n");
    }
}

int main(){
    miner_x = 6;
    miner_y = 5;
    generate_Map();
    print_Map();
    return 0;
}
