#include "Board.h"
#include <sstream>


Cell::Type type_of_cell (int i, int j)
{
    if (i % 2 == 0)
        return (j % 2 == 0) ? Cell::white : Cell::black;
    else
        return (j % 2 == 0) ? Cell::black : Cell::white;
}

Checkerboard::Checkerboard (Point location, int size)
        : Window{location,size + size/cells_count, size + size/cells_count, "Chess" },
        size { size }
{
    size_range (size + size/cells_count, size + size/cells_count,
                size + size/cells_count, size + size/cells_count); // fixed window size
    check_argument(size);
    color(black_cell);



    cell_size = size / cells_count;
    board_location = Graph_lib::Point {size / scale_factor, size / scale_factor};
    for (int i = 0; i < cells_count; ++i)
        for (int j = 0; j < cells_count; ++j)
        {
            cells.push_back(new Cell{ Point{board_location.x + j * cell_size,
                                            board_location.y + i * cell_size}, cell_size,
                                      cb_clicked, type_of_cell(i,j) });
            attach (cells[cells.size() - 1]);
        }
    create_signatures(location);
    // create figures here, later
}

void Checkerboard::clicked (Graph_lib::Address widget)
{
    Fl_Widget& w = Graph_lib::reference_to<Fl_Widget>(widget);
    Cell& c = at (Point{w.x(), w.y()});
    if (!c.activated)
        c.activate();
    else
        c.deactivate();
    c.activated = !c.activated;
    Fl::redraw();
}

Cell& Checkerboard::at (Point p)
{
    int i = (p.y - size/scale_factor) / cell_size;
    int j = (p.x - size/scale_factor) / cell_size;
    return cells[i * cells_count + j];
}

Cell& Checkerboard::at (char c, int i)
{
    --i;
    int j = c - 'a';
    return cells[i * cells_count + j];
}

void Checkerboard::check_argument(int size)
{
    if (size % scale_factor)
    {
        std::ostringstream os;
        os << "Alert! Field size is not a multiple of the scale factor: " << scale_factor
           << "\nUnexpected board behavior";
        throw std::invalid_argument(os.str());
    }
}

void Checkerboard::create_signatures(Graph_lib::Point location)
{
    int font_size = cell_size/scale;

    for (int j = 0; j < cells_count; ++j)
    {
        char c = j + 65;
        std::ostringstream ost;
        ost << c;
        std::string letter = ost.str();
        signatures.push_back(new Graph_lib::Text(
                Graph_lib::Point{cell_size - cell_size/cells_count + j*cell_size,
                                 font_size - font_size/cells_count}, letter));
        signatures[signatures.size() - 1].set_font_size(font_size);
        signatures[signatures.size() - 1].set_font(Graph_lib::Font::times);
        signatures[signatures.size() - 1].set_color(white_cell);
        attach(signatures[signatures.size() - 1]);
    }

    for (int i = 0; i < cells_count; ++i)
    {
        std::ostringstream ost;
        ost << i + 1;
        std::string num = ost.str();
        signatures.push_back(new Graph_lib::Text(
                Graph_lib::Point{scale*font_size/cells_count,
                                 size + cell_size / scale / scale - cell_size/cells_count - i*cell_size }, num));
        signatures[signatures.size() - 1].set_font_size(font_size);
        signatures[signatures.size() - 1].set_font(Graph_lib::Font::times);
        signatures[signatures.size() - 1].set_color(white_cell);
        attach(signatures[signatures.size() - 1]);
    }
}
