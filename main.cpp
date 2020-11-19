#include <Window.h>
#include "Board.h"
using namespace Graph_lib;

int main()
{
    Checkerboard board{ Point{400, 50}, 640 };
    return gui_main();
}