#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H
#include "Graph.h"
#include "GUI.h"

using Graph_lib::Point;
const unsigned int black_cell { 64 };
const unsigned int white_cell { 174 };


struct Cell : Graph_lib::Button
{
    enum Type { black, white };
    bool activated = false;
    Cell (Point xy, int size, Graph_lib::Callback cb, Type t);
    void attach (Graph_lib::Window& win) override;
    void activate () { if (pw) pw->color (Graph_lib::Color::yellow); }
    void deactivate () { reset_color(); }
    [[nodiscard]] bool is_black () const { return type == black; }
    [[nodiscard]] Point center () const { return Point{ loc.x + width/2, loc.y + height/2 }; }
private:
    Type type;
    int size;
    void reset_color ();
};


#endif //CHESS_FIELD_H
