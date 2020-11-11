#include <iostream>
#include <Window.h>
#include <Graph.h>
#include <GUI.h>
#include "Board.h"
#include <Simple_window.h>
using namespace Graph_lib;

int main()
{
    Simple_window win {Point{200, 200}, 1000, 1000, "test"};
    Graph_lib::Rectangle x {Point{200, 300}, 100, 100} ;
    Board y(Point(50, 50), 512);
    win.attach(y);
    win.wait_for_button();
}