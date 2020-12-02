#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include <Graph.h>
#include "Cell.h"
#include "Simple_window.h"


struct Checkerboard : Graph_lib::Window
{
    Checkerboard (Point location, int size);
    Cell& at2 (Position pos);
    Cell& at (Point p);
    static constexpr int cells_count { 8 };
    static constexpr int scale { 2 };
    static constexpr int scale_factor = cells_count * 2;
private:
    Graph_lib::Vector_ref<Cell> cells;
    Graph_lib::Vector_ref<Graph_lib::Text> signatures;
    Graph_lib::Point board_location;
    int cell_size;
    int size;
    void create_signatures(Graph_lib::Point location);
    static void check_argument(int size);
    static void cb_clicked (Graph_lib::Address widget, Graph_lib::Address win)
    {
        Graph_lib::reference_to<Checkerboard>(win).clicked (widget);
    }
    void clicked (Graph_lib::Address widget);
};


#endif //CHESS_BOARD_H
