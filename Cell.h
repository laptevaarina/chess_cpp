#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H
#include "Graph.h"
#include "GUI.h"
#include "Figures.h"

using Graph_lib::Point;


struct Cell : Graph_lib::Button
{
    figure_t fig = nullptr;
    enum Type { black, white };
    Cell (Point xy, int size, Graph_lib::Callback cb, Type t, Position pos);
    void attach (Graph_lib::Window& win) override;
    void activate () { if (pw) pw->color (Graph_lib::Color::yellow); }
    void deactivate () { reset_color(); }
    [[nodiscard]] bool is_black () const { return type == black; }
    [[nodiscard]] Point location () const { return Point{loc.x, loc.y}; }
    [[nodiscard]] Position position () const { return pos; }
    ~Cell() override
        { delete fig; }
private:
    Type type;
    int size;
    Position pos;
    void reset_color ();
};


#endif //CHESS_FIELD_H
