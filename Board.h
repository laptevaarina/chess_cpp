#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include <Graph.h>
const Graph_lib::Color black_cell { 64 };
const Graph_lib::Color white_cell { 174 };
const int cells_count { 8 };
const int scale { 2 };
const int scale_factor = cells_count * 2;


class Board : public Graph_lib::Rectangle
{
    Graph_lib::Vector_ref<Graph_lib::Rectangle> cells;
    Graph_lib::Vector_ref<Graph_lib::Text> signatures;
    Graph_lib::Point board_location;
    int cell_size;

    void create_signatures(Graph_lib::Point location);
    static void check_argument(int size);

public:
    Board(Graph_lib::Point location, int size);
    void draw_lines() const override;
};


#endif //CHESS_BOARD_H
