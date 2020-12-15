#ifndef CHESS_FIGURES_H
#define CHESS_FIGURES_H

#include <Graph.h>
#include "constant_table.h"

/*!
 \brief class Figures

 class Figures является родительским для всех видов фигур.
 Дочерние классы Pawn, Horse, King, Elephant, Queen, Rook
 наследуются от класса Figures.
 */

class Figures;
using figure_t = Figures*;
enum class Figure_Color { black, white };
enum Figure_Type {pawn, horse, king, elephant, queen, rook};

struct Position
{
  char letter;
  int number;
};

class Figures : public Graph_lib::Shape
{
protected:
    Position pos;
    Figure_Color color;
    Figure_Type type;
    Fl_PNG_Image* body;

public:
    Figures () {};
    void move(int dc, int di) override;
    void draw_lines() const override;
    Figure_Color get_color() { return color; }
    Figure_Type get_type() { return type; }

    bool first_turn = true;
    Graph_lib::Point last_turn;

    virtual ~Figures() { delete body; };
};

struct King : public Figures
{
  King (Position pos, const Figure_Color &color);
};

struct Queen : Figures
{
  Queen (Position pos, const Figure_Color &color);
};

struct Pawn : Figures
{
  Pawn (Position pos, const Figure_Color &color);
};

struct Rook : Figures
{
  Rook (Position pos, const Figure_Color &color);
};

struct Horse : Figures
{
  Horse (Position pos, const Figure_Color &color);
};

struct Elephant : Figures
{
  Elephant (Position pos, const Figure_Color &color);
};

#endif // CHESS_FIGURES_H

