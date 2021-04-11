#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

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
            gold[i].type = 's';
        }
        gold[i].x = 6 * i + i % 2 * 3;
        gold[i].y = i % 3 * 14 + i % 2 * 15 + 10;
   }
}

void initGolds(){
 int map[60][70];
 for (int i = 0; i < 10; i++){
     if (gold[i].size == 'M'){
         for (int p = 0; p < 2; p++){
             for (int q = 0; q < 2; q++){
                 if (gold[i].type == 's') map[gold[i + p].x][gold[i + q].y] = 7;
                 if (gold[i].type == 'g') map[gold[i + p].x][gold[i + q].y] = 8;
             }
         }
     }
     if (gold[i].size == 'L') {
         for (int p = 0; p < 3; p++){
             for (int q = 0; q < 3; q++){
                 if (gold[i].type == 's') map[gold[i + p].x][gold[i + q].y] = 7;
                 if (gold[i].type == 'g') map[gold[i + p].x][gold[i + q].y] = 8;
             }
         }
     }
     else{
         if (gold[i].type == 's') map[gold[i].x][gold[i].y] = 7;
         if (gold[i].type == 'g') map[gold[i].x][gold[i].y] = 8;
         if (gold[i].type == 'd') map[gold[i].x][gold[i].y] = 9;
     }
 }
}

