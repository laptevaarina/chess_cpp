//TODO: write class Figures
//в конструктор Cell нужно указать есть ли фигура и какая, cells в Checkerboard - public,
// тогда можно проверять необходимые нам клетки на наличие там фигуры

#ifndef CHESS_FIGURES_H
#define CHESS_FIGURES_H

#include <Graph.h>
#include "Board.h"
#include "Cell.h"

enum class Figure_Type { black = 0, white };

class Figures
{
  const Graph_lib::Image body;
  const Figure_Type color;

public:
  Figures (Graph_lib::Point p, const Figure_Type &color, const Graph_lib::Image &body);

  virtual std::vector<Cell> avialable_turns(Checkerboard b, const Cell &pos) =0;
};

struct King : Figures
{
  King (Graph_lib::Point p, const Figure_Type &color, const Graph_lib::Image &body)
      : Figures (p, color, body) {};
  std::vector<Cell> avialable_turns(Checkerboard b, const Cell &pos) override;
};

struct Queen : Figures
{
  Queen (Graph_lib::Point p, const Figure_Type &color, const Graph_lib::Image &body)
  : Figures (p, color, body) {};
  std::vector<Cell> avialable_turns(Checkerboard b, const Cell &pos) override;
};

struct Pawn : Figures
{
  Pawn (Graph_lib::Point p, const Figure_Type &color, const Graph_lib::Image &body)
  : Figures (p, color, body) {};
  std::vector<Cell> avialable_turns(Checkerboard b, const Cell &pos) override;
};

struct Rook : Figures
{
  Rook (Graph_lib::Point p, const Figure_Type &color, const Graph_lib::Image &body)
  : Figures (p, color, body) {};
  std::vector<Cell> avialable_turns(Checkerboard b, const Cell &pos) override;
};

struct Horse : Figures
{
  Horse (Graph_lib::Point p, const Figure_Type &color, const Graph_lib::Image &body)
  : Figures (p, color, body) {};
  std::vector<Cell> avialable_turns(Checkerboard b, const Cell &pos) override;
};

struct Elephant : Figures
{
  Elephant (Graph_lib::Point p, const Figure_Type &color, const Graph_lib::Image &body)
  : Figures (p, color, body) {};
  std::vector<Cell> avialable_turns(Checkerboard b, const Cell &pos) override;
};

#endif // CHESS_FIGURES_H

