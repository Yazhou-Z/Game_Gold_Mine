#include <iostream>
#include <string>
using namespace std;

char map[400][800];
int pos = 0;

struct golds_ret
{
    int x1, x2, y1, y2;
};

// Function: print the map.
void printMap();

// Function:
void getPoint();

// move the man.
void move_man();

// move hock
void move_hock();

// chaeck get the gold or not
bool check();

// get input
void getInput();

// move the gold
void move_gold();

bool gameover();
