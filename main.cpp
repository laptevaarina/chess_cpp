#include <Window.h>
#include "Board.h"
using namespace Graph_lib;

int main()
{
    Checkerboard board{board_size };
    board.init_game();
    return gui_main();
}