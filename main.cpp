#include <iostream>
#include <Window.h>
#include <Graph.h>
#include <GUI.h>
#include <Simple_window.h>
using namespace Graph_lib;

int main()
{
    Simple_window win {Point{400, 600}, 400, 600, "test"};
    Graph_lib::Rectangle x {Point{200, 300}, 100, 100} ;
    win.attach(x);
    win.wait_for_button();
}