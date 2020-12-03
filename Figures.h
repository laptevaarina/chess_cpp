//TODO: write class Figures

#ifndef CHESS_FIGURES_H
#define CHESS_FIGURES_H

#include <Graph.h>
#include "constant_table.h"

using figure_t = Graph_lib::Shape*;
enum class Figure_Color { black, white };
enum Figure_Type {pawn, horse, king, elephant, queen, rook};

struct Position
{
  char c;
  int i;
};

class Figures : public Graph_lib::Shape
{
protected:
  Position pos;
  Figure_Color color;
  Fl_PNG_Image* body;

public:
  Figures () {};

  virtual std::vector<Position> available_turns() { return std::vector<Position> {}; };
  void move(int dc, int di) override;
  void draw_lines() const override;

  virtual ~Figures() { delete body; };
};

struct King : public Figures
{
  King (Position pos, const Figure_Color &color);
  std::vector<Position> available_turns() override;
};

struct Queen : Figures
{
  Queen (Position pos, const Figure_Color &color);
  std::vector<Position> available_turns() override;
};

struct Pawn : Figures
{
  Pawn (Position pos, const Figure_Color &color);
  std::vector<Position> available_turns() override;
};

struct Rook : Figures
{
  Rook (Position pos, const Figure_Color &color);
  std::vector<Position> available_turns() override;
};

struct Horse : Figures
{
  Horse (Position pos, const Figure_Color &color);
  std::vector<Position> available_turns() override;
};

struct Elephant : Figures
{
  Elephant (Position pos, const Figure_Color &color);
  std::vector<Position> available_turns() override;
};

#endif // CHESS_FIGURES_H

