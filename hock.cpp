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
    int x;
    int y;
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

// 
void generate_hock(int x, int y);

void print_Map();

void generate_miner(int x, int y);

// 钩子绑定矿石返回，移动矿石坐标，移动钩子
// speed: empty: 6; small: 5; Medium: 3; Large: 1
int move_ore(int x, int y){
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
    
    return num;

}

// hock downward, upward
int move_hock_down_up(int x, int y){
    int num;
    char check = check_hock(x, y);
    
    // hock downward
    while (check == '0'){
        x ++;
        epoch ++;
        generate_hock(x, y);
        print_Map();
        check = check_hock(x, y);
    }

    // hock upward
    while (x != 9){
        num = move_ore(x, y);
        epoch ++;
        print_Map();
    }
    return num;
}

// move miner horizontally
void move_miner(miner_hook &m){
    if (m.miner_y == 57) {
        m.miner_y = 4;
        epoch ++;
        generate_miner(m.miner_x, m.miner_y);
        generate_hock(m.x, m.y);
        print_Map();
    }
    else{
        m.miner_y ++;
        epoch ++;
        generate_miner(m.miner_x, m.miner_y);
        generate_hock(m.x, m.y);
        print_Map();
    }
}

int calculate_reward(int num){
    
}

void play(bool get, miner_hook &m) {
    while (not get) {
        move_miner(m);
    }
    move_hock_down_up(m.x, m.y);
    
}
