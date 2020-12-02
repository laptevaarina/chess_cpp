#include "Cell.h"

Cell::Cell (Point xy, int size, Graph_lib::Callback cb, Type t) :
        Button{ xy, size, size, "", cb },
        type{ t } {}

void Cell::attach (Graph_lib::Window& win)
{
    Button::attach (win);
    reset_color();
}

void Cell::reset_color ()
{
    if (!pw) Graph_lib::error ("Cell is not attached to a window");
    if (is_black())
        pw->color (black_cell);
    else
        pw->color (white_cell);
}