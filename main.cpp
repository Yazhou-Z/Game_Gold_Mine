#include "generate_Map.h"
#include "gold.h"
#include "window.h"
#include "move.h"
#include "calculate_reward.h"
#include "play.h"
using namespace std;

int main()
{
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    WINDOW *win = newwin(60, 70, 0, 0);
    refresh();
    box(win, 0, 0);

    miner_hook m;
    m.hook_length = 3;
    generate_miner(6, 4, m);
    designGolds();
    print_Map(m, win);

    play(m, win);
    endwin();
    return 0;
}
