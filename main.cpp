#include <Window.h>
#include "Board.h"
using namespace Graph_lib;

int main()
{
    Checkerboard board{ Point{0, 0}, 512 };
    return gui_main();
}