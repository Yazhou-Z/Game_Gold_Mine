#include <iostream>
#include <string>
using namespace std;

int map[60][70];
int time = 0;
int epoch = 0;
int reward = 0;

struct miner_hook{
    int miner_x;
    int miner_y;
    int hook_length;
    int hook_line_x[70];
    int hook_line_y[70];
    int hook_catcher_x[3];
    int hook_catcher_y[3];
};

// 确定钩子是触到矿石还是触到墙壁
char check_hock(int x, int y){
    miner_hook m;
    char ore = '0';
    if (map[x][y] == 1) ore = 'w';  // wall
    else if(map[x][y] == 7) ore = 's';  // stone
    else if(map[x][y] == 8) ore = 'g';  // gold
    else if(map[x][y] == 9) ore = 'd';  // diamond
    return ore;
}

void generate_hook();

void print_Map();

// 钩子绑定矿石返回，移动矿石坐标，移动钩子
// speed: empty: 6; small: 5; Medium: 3; Large: 1
void move_ore(int x, int y){
    char ore = check_hock(x,y);
    int num;

    if (ore == 'w'){
        x = x - 6;
    }

    // get the ore information
    else if (ore == 's'){
        for (int i = 0; i < 10; i ++) {
            if (gold[i].type == 's' && gold[i].x == x + 1) {
                num = i;
            }
        }
    }
    else if (ore == 'g'){
        for (int i = 0; i < 10; i ++) {
            if (gold[i].type == 'g' && gold[i].x == x + 1) {
                num = i;
            }
        }
    }
    else num = 9; // diamond

    if (gold[num].size == 'L'){ 
        x = x - 1;
        gold[num].x --;
    }
    else if (gold[num].size == 'M') {
        x = x - 3;
        gold[num].x = gold[num].x - 3;
    }
    else {
        x = x - 5;
        gold[num].x = gold[num].x - 5;
    }
    
    // get reward

}

void move_hock_miner(int x, int y, bool get){

    char check = check_hock(x, y);
    
    // hock downward
    while (get && check == '0'){
        x ++;
        epoch ++;
        generate_hook();
        print_Map();
        check = check_hock(x, y);
    }

    // hock upward
    while (x != 30){
        move_ore(x, y);
        epoch ++;
        print_Map();
    }

}



