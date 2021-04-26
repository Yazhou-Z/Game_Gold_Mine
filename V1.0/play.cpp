#include "generate_Map.h"
#include "gold.h"
#include "window.h"
#include "move.h"
#include "calculate_reward.h"
#include "play.h"
using namespace std;

int reward;

void play(miner_hook &m, WINDOW *&win)
{
    int sh;
    while ((sh = getch()) == ERR)
        startting(win);
    while (epoch < 180)
    {
        while ((sh = getch()) == ERR)
        {
            move_miner(m, win);
        }
        int ore = launch_hook(m, win);
        reward += calculate_reward(ore);
    }
    endding(win);
    sh = getch();
}