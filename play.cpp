#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;
int map[60][70];
int epoch = 0;
int reward = 0;

// Golds
struct Golds_ret {
    int x, y;
    char size;
    char type;
};

Golds_ret gold[MAX];

void designGolds(){
    for (int i = 0; i < 10; i++) {
        if (i % 2) gold[i].type = 'g';
        else gold[i].type = 's';
        if (i < 3) gold[i].size = 'S';
        else if (i < 6) gold[i].size = 'M';
        else if (i < 9) gold[i].size = 'L';
        else {
            gold[i].type = 'd';
            gold[i].size = 's';
        }
        gold[i].x = 4 * i + i % 2 * 3 + 11;
        gold[i].y = i % 3 * 17 + i % 2 * 15 + 15;
   }
}

void initGolds(){
 for (int i = 0; i < 10; i++){
     if (gold[i].size == 'M'){
         for (int p = 0; p < 3; p++){
             for (int q = 0; q < 3; q++){
                 if (gold[i].type == 's') map[gold[i].x + p][gold[i].y + q] = 7;
                 if (gold[i].type == 'g') map[gold[i].x + p][gold[i].y + q] = 8;
             }
         }
     }
     if (gold[i].size == 'L') {
         for (int p = 0; p < 5; p++){
             for (int q = 0; q < 5; q++){
                 if (gold[i].type == 's') map[gold[i].x + p][gold[i].y + q] = 7;
                 if (gold[i].type == 'g') map[gold[i].x + p][gold[i].y + q] = 8;
             }
         }
     }
     else{
         for (int p = 0; p < 2; p++){
             for (int q = 0; q < 2; q++){
                if (gold[i].type == 's') map[gold[i].x + p][gold[i].y+ q] = 7;
                if (gold[i].type == 'g') map[gold[i].x + p][gold[i].y+ q] = 8;
                if (gold[i].type == 'd') map[gold[i].x + p][gold[i].y+ q] = 9;
             }
         }
     }
 }
}

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

// Map
void change_Map(miner_hook &m);

void init_miner_hock(miner_hook &m);

void print_Map();

// 确定钩子是触到矿石还是触到墙壁
char check_hock(miner_hook & m){
    char ore = '0'; 
    int x = m.x, y = m.y;
    if (map[x][y] == 1) ore = 'w';  // wall
    else if(map[x][y] == 7) ore = 's';  // stone
    else if(map[x][y] == 8) ore = 'g';  // gold
    else if(map[x][y] == 9) ore = 'd';  // diamond
    return ore;
}

// 钩子绑定矿石返回，移动矿石坐标，移动钩子
// speed: empty: 6; small: 5; Medium: 3; Large: 1
int move_ore(miner_hook & m){
    char ore = check_hock(m);
    int num;

    if (ore == 'w'){
        m.x = m.x - 6;
    }

    // get the ore information
    else if (ore == 's'){
        for (int i = 0; i < 10; i ++) {
            if (gold[i].type == 's' && gold[i].x == m.x + 1) {
                num = i;
            }
        }
    }
    else if (ore == 'g'){
        for (int i = 0; i < 10; i ++) {
            if (gold[i].type == 'g' && gold[i].x == m.x + 1) {
                num = i;
            }
        }
    }
    else num = 9; // diamond

    if (gold[num].size == 'L'){ 
        m.x = m.x - 1;
        gold[num].x --;
    }
    else if (gold[num].size == 'M') {
        m.x = m.x - 3;
        gold[num].x = gold[num].x - 3;
    }
    else {
        m.x = m.x - 5;
        gold[num].x = gold[num].x - 5;
    }
    
    return num;

}

// hock downward, upward
int move_hock_down_up(miner_hook & m, WINDOW * &win){
    int num;
    char check = check_hock(m);

    // hock downward
    while (check == '0'){
        m.x = 3 + m.x;
        epoch ++;
        change_Map(m);
        print_Map(win);
        check = check_hock(m);
    }

    // hock upward
    while (m.x != 9){
        num = move_ore(m);
        change_Map(m);
        epoch ++;
        print_Map(win);
    }
    return num;
}

// move miner horizontally
void move_miner(miner_hook & m, WINDOW * &win){
    if (m.miner_y == 57) {
        m.miner_y = 4;
        epoch ++;
        change_Map(m);
        print_Map(win);
    }
    else{
        m.miner_y ++;
        epoch ++;
        change_Map(m);
        print_Map(win);
    }
}

// stone: L: 50*2; M: 30*2; S: 10*2;
// gold: L: 50*5; M: 30*5; S: 10*5;
// diamond: 10*50;
int calculate_reward(int num){
    int type, size;

    if (gold[num].type == 's') type = 2;
    else if (gold[num].type == 'g') type = 5;
    else type = 50;

    if (gold[num].size == 'L') size = 50;
    else if (gold[num].size == 'M') size = 30;
    else size = 10;

    return type * size;
}

void play(bool get, miner_hook &m, WINDOW *&win) {
    while (not get) {
        move_miner(m,win);
    }
    int num = move_hock_down_up(m,win);
    reward = calculate_reward(num) + reward;
}

int main(){
    initscr();
    WINDOW *win = newwin(60, 70, 0, 0);
    refresh();
    box(win,0,0);
    miner_hook m;
    while (epoch != 10000){
        bool get;
        init_miner_hock(m,win);
        play(get, m, win);
    }
    /*
    GAME OVER
    YOUR REWARD IS...
    */
}
