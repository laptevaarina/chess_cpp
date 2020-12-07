#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include <Graph.h>
#include "Cell.h"
#include "Simple_window.h"

struct Checkerboard;

class Rules
{
    Figure_Color current_turn = Figure_Color::white;
    static void exclude_out_of_board(std::vector<Position>& turns);
    void exclude_friendly_fire(Checkerboard& board, std::vector<Position>& turns);
    static void add_pawn_fire(Checkerboard& board, std::vector<Position>& turns, Position pos);
    static int pawn_direction(Checkerboard &board, Position pos);
    void exclude_shah(Checkerboard &board, std::vector<Position> &turns, Position k);
    void add_castling(Checkerboard &board, std::vector<Position> &turns, Position pos);
    static void diagonal_moving(Checkerboard& board, std::vector<Position>& turns, Position pos);
    static void vertical_moving(Checkerboard& board, std::vector<Position>& turns, Position pos);
    std::vector<Position> get_horse_turns(Checkerboard& board, Position pos);
    static std::vector<Position> get_pawn_turns(Checkerboard& board, Position pos);
    std::vector<Position> get_rook_turns(Checkerboard& board, Position pos);
    std::vector<Position> get_elephant_turns(Checkerboard& board, Position pos);
    std::vector<Position> get_queen_turns(Checkerboard& board, Position pos);
    std::vector<Position> get_king_turns(Checkerboard& board, Position pos);
    bool check_end_game();
public:
    std::vector<Position> get_available_turns(Checkerboard& board, Position pos);
    void end_turn() { if (current_turn == Figure_Color::white) current_turn = Figure_Color::black;
                      else current_turn = Figure_Color::white; };
    Figure_Color get_turn_color() { return current_turn; };


};


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

    bool moving = false;
    Point from;
    std::vector<Position> available_turns;
    bool is_available(Cell* compare);
    void filter_turns();

    Graph_lib::Vector_ref<Cell> cells;
    Graph_lib::Vector_ref<Graph_lib::Text> signatures;
    Graph_lib::Point board_location;
    Rules rules;
};




#endif //CHESS_BOARD_H
