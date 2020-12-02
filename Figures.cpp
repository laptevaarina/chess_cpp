#include "Figures.h"
//тут везде с магическими константами 80 - cell size

void Figures::draw_lines() const
{
  Figures::body->draw (point(0).x, point(0).y, 80, 80, 0, 0);
}

void Figures::move(int dc, int di)
{
  int dx = int((pos.c - dc)*80);
  int dy = (pos.i - di)*80;

  //delete figure and create new on new position

  Shape::move(dx, dy);
  body->draw(point(0).x, point(0).y);
}

King::King(Position pos, const Figure_Color &color)
{
  int x = int((pos.c-'a')*80)+40; //40 нужно чтобы фигуры стояли посередине клетки а не на пересечении
  int y = (pos.i-1)*80+40;
  add(Graph_lib::Point {x, y});
  Figures::pos = pos;
  Figures::color = color;
  std::string w_k = "white_king.png";
  if (color == Figure_Color::white)
    body = new Fl_PNG_Image(w_k.c_str());
  else
    body = new Fl_PNG_Image("black_king.png");
}

std::vector<Position> King::available_turns()
{
  std::vector<Position> turns {};

  std::vector<Position> all_turns {};
  for (int i = -1; i <= 1; ++i)
    for (int j = -1; j <= 1; ++j)
      all_turns.push_back(Position {char(pos.c+i), pos.i+j});

  for (auto k : all_turns)
  {
    if ((k.i >= 1 && k.i <= 8) && (k.c >= 65 && k.c <= 65+8))
      turns.push_back(k);
  }

  return turns;
}

Queen::Queen(Position pos, const Figure_Color &color)
{
  int x = int((pos.c-'a')*80)+40;
  int y = (pos.i-1)*80+40;
  add(Graph_lib::Point {x, y});

  Figures::pos = pos;
  Figures::color = color;
  if (color == Figure_Color::white)
    body = new Fl_PNG_Image("white_queen.png");
  else
    body = new Fl_PNG_Image("black_queen.png");
}

std::vector<Position> Queen::available_turns()
{
  std::vector<Position> turns;

  std::vector<Position> all_turns;
  for (int i = -8; i <= 8; ++i)
  {
    all_turns.push_back(Position{char(pos.c + i), pos.i + i});
    all_turns.push_back(Position{char(pos.c + i), pos.i - i});
  }

  for (auto k : all_turns)
  {
    if ((k.i >= 1 && k.i <= 8) && (k.c >= 65 && k.c <= 65+8))
      turns.push_back(k);
  }

  for (int i = -8; i <= 8; ++i)
  {
    if (pos.i+i >= 1 && pos.i+i <= 8)
      turns.push_back(Position {pos.c, pos.i+i});

    if (pos.c+i >= 65 && pos.c <= 65+8)
      turns.push_back(Position {char(pos.c+i), pos.i});
  }

  return turns;
}

Pawn::Pawn(Position pos, const Figure_Color &color)
{
  int x = int((pos.c-'a')*80)+40;
  int y = (pos.i+1)*80+40;
  add(Graph_lib::Point {x, y});

  Figures::pos = pos;
  Figures::color = color;
  if (color == Figure_Color::white)
    body = new Fl_PNG_Image("white_pawn.png");
  else
    body = new Fl_PNG_Image("black_pawn.png");
}

std::vector<Position> Pawn::available_turns()
{
  std::vector<Position> turns;
  if (pos.i+1 <= 8 && pos.i-1 >= 1)
  {
    turns.push_back(Position{pos.c, pos.i + 1});
    turns.push_back(Position{pos.c, pos.i - 1});
  }
  if (pos.i+2 <= 8 && pos.i-2 >= 1)
  {
    turns.push_back(Position{pos.c, pos.i + 2});
    turns.push_back(Position{pos.c, pos.i - 2});
  }
}

Rook::Rook(Position pos, const Figure_Color &color)
{
  int x = int((pos.c-'a')*80)+40;
  int y = (pos.i-1)*80+40;
  add(Graph_lib::Point {x, y});

  Figures::pos = pos;
  Figures::color = color;
  if (color == Figure_Color::white)
    body = new Fl_PNG_Image("white_rook.png");
  else
    body = new Fl_PNG_Image("black_rook.png");
}

std::vector<Position> Rook::available_turns()
{
  std::vector<Position> turns;

  for (int i = -8; i <= 8; ++i)
  {
    if (pos.i+i >= 1 && pos.i+i <= 8)
      turns.push_back(Position {pos.c, pos.i+i});

    if (pos.c+i >= 65 && pos.c <= 65+8)
      turns.push_back(Position {char(pos.c+i), pos.i});
  }

  return turns;
}

Horse::Horse(Position pos, const Figure_Color &color)
{
  int x = int((pos.c-'a')*80)+40;
  int y = (pos.i-1)*80+40;
  add(Graph_lib::Point {x, y});

  Figures::pos = pos;
  Figures::color = color;
  if (color == Figure_Color::white)
    body = new Fl_PNG_Image("white_horse.png");
  else
    body = new Fl_PNG_Image("black_horse.png");
}

std::vector<Position> Horse::available_turns()
{
  std::vector<Position> turns;

  std::vector<Position> all_turns;
  for (int i = -3; i <= 3; i += 6)
    for (int j = -1; j <= 1; j += 2)
    {
      all_turns.push_back(Position{char(pos.c + j), pos.i + i});
      all_turns.push_back(Position{char(pos.c + i), pos.i + j});
    }

  for (auto k : all_turns)
  {
    if ((k.i >= 1 && k.i <= 8) && (k.c >= 65 && k.c <= 65+8))
      turns.push_back(k);
  }

  return turns;
}

Elephant::Elephant(Position pos, const Figure_Color &color)
{
  int x = int((pos.c-'a')*80)+40;
  int y = (pos.i-1)*80+40;
  add(Graph_lib::Point {x, y});

  Figures::pos = pos;
  Figures::color = color;
  if (color == Figure_Color::white)
    body = new Fl_PNG_Image("white_elephant.png");
  else
    body = new Fl_PNG_Image("black_elephant.png");
}

std::vector<Position> Elephant::available_turns()
{
  std::vector<Position> turns;

  std::vector<Position> all_turns;
  for (int i = -8; i <= 8; ++i)
  {
    all_turns.push_back(Position{char(pos.c + i), pos.i + i});
    all_turns.push_back(Position{char(pos.c + i), pos.i - i});
  }

  for (auto k : all_turns)
  {
    if ((k.i >= 1 && k.i <= 8) && (k.c >= 65 && k.c <= 65+8))
      turns.push_back(k);
  }

  return turns;
}
