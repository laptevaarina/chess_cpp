#include <Window.h>
#include "Board.h"
using namespace Graph_lib;

int main()
{
    Checkerboard board{ Point{400, 50}, 640 };
    board.at2(Position{'d', 3}).fig = new Pawn (Position {'d', 3}, Figure_Color::black);
    board.attach(*board.at2(Position{'d', 3}).fig);
    //board.at2(Position{'c', 7}).fig->move(int('c'-'a'),10);
    return gui_main();
}