#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

int map[60][70];
int miner_x[7], miner_y[7];
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
        }
        printf("\n");
    }
}

int main(){
    generate_Map();
    print_Map();
    return 0;
}
