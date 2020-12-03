#include "Board.h"
#include <sstream>
#include <iostream>


Cell::Type type_of_cell (int i, int j)
{
    if (i % 2 == 0)
        return (j % 2 == 0) ? Cell::white : Cell::black;
    else
        return (j % 2 == 0) ? Cell::black : Cell::white;
}

Checkerboard::Checkerboard (int size)
        : Window{window_size, window_size, "Chess" }
{
    size_range (window_size, window_size,
                window_size, window_size); // fixed window size
    check_argument(size);
    color(black_cell);


    board_location = Graph_lib::Point {side_size, side_size};
    for (int i = 0; i < cells_count; ++i)
        for (int j = 0; j < cells_count; ++j)
        {
            cells.push_back(new Cell{ Point{board_location.x + j * cell_size,
                                            board_location.y + i * cell_size}, cell_size,
                                      cb_clicked, type_of_cell(i,j) });
            attach (cells[cells.size() - 1]);
        }
    create_signatures();
    // create figures here, later
}

void Checkerboard::clicked (Graph_lib::Address widget)
{
    auto& w = Graph_lib::reference_to<Fl_Widget>(widget);
    Point current {w.x(), w.y()};
    Cell& tmp = at (current);
    if (!turn)
    {
        tmp.activate();
        from = current;
    }
    else
    {
        Cell& tmp_from = at(from);
        tmp_from.deactivate();
        figure_t figure = delete_figure(from);
        if (figure != nullptr)
        {
            figure->move(tmp.loc.x - tmp_from.loc.x, tmp.loc.y - tmp_from.loc.y);
            set_figure(current, figure);
        } else std::cout << "SHIEEET!!!\n";
    }
    turn = !turn;
    Fl::redraw();
}

Cell& Checkerboard::at (Point p)
{
    int i = (p.y - side_size) / cell_size;
    int j = (p.x - side_size) / cell_size;
    return cells[i * cells_count + j];
}

Cell& Checkerboard::at (Position pos)
{
    --pos.i;
    int i = (cells_count - pos.i) - 1;
    int j = pos.c - 'a';
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

Graph_lib::Point calculate_letter_pos(int it)
{
    return Point {cell_size - cell_size / cells_count + it * cell_size,
                  font_size - font_size / cells_count};
}

Graph_lib::Point calculate_num_pos(int it)
{
    return Point {2 * font_size / cells_count,
                  board_size + cell_size / 4 - cell_size / cells_count - it * cell_size};
}

void Checkerboard::create_signatures()
{
    for (int j = 0; j < 2 * cells_count; ++j)
    {
        std::ostringstream ost;
        Point pos;
        if (j < cells_count)
        {
            char c = static_cast<char>(j + first_letter);
            ost << c;
            pos = calculate_letter_pos(j);
        }
        else
        {
            ost << j + 1 - cells_count;
            pos = calculate_num_pos(j - cells_count);
        }
        std::string symbol = ost.str();

        signatures.push_back(new Graph_lib::Text(pos, symbol));
        signatures[signatures.size() - 1].set_font_size(font_size);
        signatures[signatures.size() - 1].set_font(Graph_lib::Font::times);
        signatures[signatures.size() - 1].set_color(white_cell);
        attach(signatures[signatures.size() - 1]);
    }
}

void Checkerboard::set_figure(Position pos, Figure_Color col, Figure_Type type)
{
    Cell& tmp = at(pos);
    switch (type)
    {
        case pawn:
            tmp.fig = new Pawn(pos, col);
            break;
        case rook:
            tmp.fig = new Rook(pos, col);
            break;
        case horse:
            tmp.fig = new Horse(pos, col);
            break;
        case elephant:
            tmp.fig = new Elephant(pos, col);
            break;
        case queen:
            tmp.fig = new Queen(pos, col);
            break;
        case king:
            tmp.fig = new King(pos, col);
            break;
    }
    attach(*tmp.fig);
}

figure_t Checkerboard::delete_figure(Point pos)
{
    Cell& tmp = at(pos);
    detach(*tmp.fig);
    figure_t ret = tmp.fig;
    tmp.fig = nullptr;
    return ret;
}

void Checkerboard::set_figure(Point pos, figure_t fig)
{
    Cell& tmp = at(pos);
    delete delete_figure(pos);
    tmp.fig = fig;
    attach(*tmp.fig);
}

void Checkerboard::init_game()
{
    for (char c = 'a'; c <= 'h'; ++c)
    {
        set_figure(Position{c, 2}, Figure_Color::white, Figure_Type::pawn);
        set_figure(Position{c, 7}, Figure_Color::black, Figure_Type::pawn);
    }

    set_figure(Position{'a', 8}, Figure_Color::black, Figure_Type::rook);
    set_figure(Position{'h', 8}, Figure_Color::black, Figure_Type::rook);
    set_figure(Position{'a', 1}, Figure_Color::white, Figure_Type::rook);
    set_figure(Position{'h', 1}, Figure_Color::white, Figure_Type::rook);

    set_figure(Position{'b', 8}, Figure_Color::black, Figure_Type::horse);
    set_figure(Position{'g', 8}, Figure_Color::black, Figure_Type::horse);
    set_figure(Position{'b', 1}, Figure_Color::white, Figure_Type::horse);
    set_figure(Position{'g', 1}, Figure_Color::white, Figure_Type::horse);

    set_figure(Position{'c', 8}, Figure_Color::black, Figure_Type::elephant);
    set_figure(Position{'f', 8}, Figure_Color::black, Figure_Type::elephant);
    set_figure(Position{'c', 1}, Figure_Color::white, Figure_Type::elephant);
    set_figure(Position{'f', 1}, Figure_Color::white, Figure_Type::elephant);

    set_figure(Position{'e', 8}, Figure_Color::black, Figure_Type::king);
    set_figure(Position{'d', 8}, Figure_Color::black, Figure_Type::queen);
    set_figure(Position{'e', 1}, Figure_Color::white, Figure_Type::king);
    set_figure(Position{'d', 1}, Figure_Color::white, Figure_Type::queen);
}

