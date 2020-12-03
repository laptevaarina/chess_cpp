#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include <Graph.h>
#include "Cell.h"
#include "Simple_window.h"


struct Checkerboard : Graph_lib::Window
{
    explicit Checkerboard (int size);
    Cell& at (Position pos);
    Cell& at (Point p);
    void init_game();
private:
    void create_signatures();
    static void check_argument(int size);
    static void cb_clicked (Graph_lib::Address widget, Graph_lib::Address win)
    {
        Graph_lib::reference_to<Checkerboard>(win).clicked (widget);
    }
    void clicked (Graph_lib::Address widget);
    void set_figure(Position pos, Figure_Color col, Figure_Type type);
    void set_figure(Point pos, figure_t fig);
    [[nodiscard]]figure_t delete_figure(Point pos);

    bool turn = false;
    Point from;

    Graph_lib::Vector_ref<Cell> cells;
    Graph_lib::Vector_ref<Graph_lib::Text> signatures;
    Graph_lib::Point board_location;
};


#endif //CHESS_BOARD_H
