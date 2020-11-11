#include "Board.h"
#include <sstream>

/// Инициализация игрового поля
/// @param location - верхний левый угол поля
/// @param size - размер поля, число обязательно должно быть кратно параметру scale_factor описанному в Board.h
Board::Board(Graph_lib::Point location, int size) :
Graph_lib::Rectangle(location, size + size / cells_count, size + size / cells_count) // create a frame for a board whose thickness is half the thickness of the cell
{
    check_argument(size);

    cell_size = size / cells_count;
    board_location = Graph_lib::Point {location.x + size / scale_factor, location.y + size / scale_factor};

    for (int i = 0; i < cells_count; ++i)
        for (int j = 0; j < cells_count; ++j)
        {
            cells.push_back(new Graph_lib::Rectangle
            (Graph_lib::Point(board_location.x + j * cell_size,
                              board_location.y + i * cell_size), cell_size, cell_size));

            cells[cells.size() - 1].set_fill_color((i + j) % 2 ? black_cell : white_cell);
            cells[cells.size() - 1].set_color(Graph_lib::Color::black);
        }

    set_color(Graph_lib::Color::black);
    set_fill_color(white_cell);

    create_signatures(location);
}


void Board::draw_lines() const
{
    Rectangle::draw_lines();
    for (int i = 0; i < cells.size(); ++i)
        cells[i].draw();

    for (int i = 0; i < signatures.size(); ++i) {
        signatures[i].draw_lines();
    }
}

void Board::create_signatures(Graph_lib::Point location)
{
    int font_size = cell_size/scale;

    for (int j = 0; j < cells_count; ++j)
    {
        char c = j + 65;
        std::ostringstream ost;
        ost << c;
        std::string letter = ost.str();
        signatures.push_back(new Graph_lib::Text(
                Graph_lib::Point{location.x + cell_size - cell_size/cells_count + j*cell_size,
                                 location.y + font_size - font_size/cells_count}, letter));
        signatures[signatures.size() - 1].set_font_size(font_size);
        signatures[signatures.size() - 1].set_font(Graph_lib::Font::times);
    }

    for (int i = 0; i < cells_count; ++i)
    {
        std::ostringstream ost;
        ost << i + 1;
        std::string num = ost.str();
        signatures.push_back(new Graph_lib::Text(
                Graph_lib::Point{location.x + scale*font_size/cells_count,
                                 location.y + cell_size + cell_size/cells_count + i*cell_size }, num));
        signatures[signatures.size() - 1].set_font_size(font_size);
        signatures[signatures.size() - 1].set_font(Graph_lib::Font::times);
    }


}

void Board::check_argument(int size)
{
    if (size % scale_factor)
    {
        std::ostringstream os;
        os << "Alert! Field size is not a multiple of the scale factor: " << scale_factor
           << "\nUnexpected board behavior";
        throw std::invalid_argument(os.str());
    }
}
