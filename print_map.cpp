#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

int miner_x[7], miner_y[7];
string hook_x="9 10 11 11 11", hook_y="2 2 1 2 3";
int hookx[70], hooky[70];

int form_hook(){
    istringstream cin_x(hook_x), cin_y(hook_y);
    int x,y,i=0;
    while(cin_x>>x){
        cin_y>>y;
        hookx[i] = x;
        hooky[i] = y;
        i++;
    }
    return i;
}
// Function: print the map.
void printMap(char map[][60]){
    for (int i = 0; i < 60; i++){
        for (int j = 0; j < 70; j++){
            if(i==0 || i==9 || i==59) map[i][j] = '#';
            else if(j == 0 || j == 69) map[i][j] = '#';
            else map[i][j] = ' ';
            int l = form_hook()-3;
            int exist = 0;
            for (int k; k < l; k++){
                if(i==hookx[k]&&j==hooky[k]) exist=1;  
            }
            if(i==hookx[l]&&j==hooky[l]) exist=2;
            else if(i==hookx[l+1]&&j==hooky[l+1]) exist=3;
            else if(i==hookx[l+2]&&j==hooky[l+2]) exist=4;
            if (exist==1 || exist==3) printf("|");
            else if(exist==2) printf("/");
            else if(exist==4) printf("\\");
            else {
                if (map[i][j] == '#') printf("#");
                else printf(" ");
            }
        }
        printf("\n");
    }
}
