#include "Figures.h"
#include <iostream>

//TODO: мы убираем доступные ходы из фигур и отправляем это в класс правил
//TODO: как только возьмешь заготовки кода отсюда для написания ходов удали
//TODO: пожалуйста не дублируй код по 1000 раз ознакомься с интерфейсом класса Rules

Graph_lib::Point get_position(Position pos)
{
    int x = (pos.letter - 'a') * cell_size + side_size;
    int y = (cells_count - pos.number) * cell_size + side_size;

    return Graph_lib::Point {x, y};
}

void Figures::draw_lines() const
{
  Figures::body->draw (point(0).x, point(0).y, cell_size, cell_size, 0, 0);
}

void Figures::move(int dx, int dy)
{
  //delete figure and create new on new position

  Shape::move(dx, dy);
  pos.number -= dy / cell_size;
  pos.letter += dx / cell_size;
  body->draw(point(0).x, point(0).y);
}

King::King(Position pos, const Figure_Color &color)
{
  add(get_position(pos));

  Figures::pos = pos;
  Figures::color = color;
  std::string w_k = "white_king.png";
  if (color == Figure_Color::white)
    body = new Fl_PNG_Image(w_k.c_str());
  else
    body = new Fl_PNG_Image("black_king.png");
}

/*std::vector<Position> King::available_turns()
{
  std::vector<Position> turns {};

  std::vector<Position> all_turns {};
  for (int i = -1; i <= 1; ++i)
    for (int j = -1; j <= 1; ++j) {
        all_turns.push_back(Position{static_cast<char>(pos.letter + i), pos.number + j});
    }


  for (Position k : all_turns)
  {
    if ((k.number >= 1 && k.number <= 8) && (k.letter >= 'a' && k.letter < 'a' + 8) && (k.letter != pos.letter
        || k.number != pos.number))
        turns.push_back(k);
  }

  return turns;
}*/

Queen::Queen(Position pos, const Figure_Color &color)
{
  add(get_position(pos));

  Figures::pos = pos;
  Figures::color = color;
  if (color == Figure_Color::white)
    body = new Fl_PNG_Image("white_queen.png");
  else
    body = new Fl_PNG_Image("black_queen.png");
}

/*std::vector<Position> Queen::available_turns()
{
  std::vector<Position> turns;

  std::vector<Position> all_turns;
  for (int i = -8; i <= 8; ++i)
  {
    all_turns.push_back(Position{char(pos.letter + i), pos.number + i});
    all_turns.push_back(Position{char(pos.letter + i), pos.number - i});
  }

  for (auto k : all_turns)
  {
    if ((k.number >= 1 && k.number <= 8) && (k.letter >= 65 && k.letter <= 65 + 8))
      turns.push_back(k);
  }

  for (int i = -8; i <= 8; ++i)
  {
    if (pos.number + i >= 1 && pos.number + i <= 8)
      turns.push_back(Position {pos.letter, pos.number + i});

    if (pos.letter + i >= 65 && pos.letter <= 65 + 8)
      turns.push_back(Position {char(pos.letter + i), pos.number});
  }

  return turns;
}*/

Pawn::Pawn(Position pos, const Figure_Color &color)
{
  add(get_position(pos));

  Figures::pos = pos;
  Figures::color = color;
  if (color == Figure_Color::white)
    body = new Fl_PNG_Image("white_pawn.png");
  else
    body = new Fl_PNG_Image("black_pawn.png");
}

/*std::vector<Position> Pawn::available_turns()
{
  std::vector<Position> turns;
  if (pos.number + 1 <= 8 && pos.number - 1 >= 1)
  {
    turns.push_back(Position{pos.letter, pos.number + 1});
    turns.push_back(Position{pos.letter, pos.number - 1});
  }
  if (pos.number + 2 <= 8 && pos.number - 2 >= 1)
  {
    turns.push_back(Position{pos.letter, pos.number + 2});
    turns.push_back(Position{pos.letter, pos.number - 2});
  }
    return turns;
}*/

Rook::Rook(Position pos, const Figure_Color &color)
{
    add(get_position(pos));

    Figures::pos = pos;
    Figures::color = color;
    Figures::type = Figure_Type::rook;
    if (color == Figure_Color::white)
        body = new Fl_PNG_Image("white_rook.png");
    else
        body = new Fl_PNG_Image("black_rook.png");
}

/*std::vector<Position> Rook::available_turns()
{
  std::vector<Position> turns;

  for (int i = -8; i <= 8; ++i)
  {
    if (pos.number + i >= 1 && pos.number + i <= 8)
      turns.push_back(Position {pos.letter, pos.number + i});

    if (pos.letter + i >= 65 && pos.letter <= 65 + 8)
      turns.push_back(Position {char(pos.letter + i), pos.number});
  }

  return turns;
}*/

Horse::Horse(Position pos, const Figure_Color &color)
{
    add(get_position(pos));

    Figures::pos = pos;
    Figures::color = color;
    Figures::type = Figure_Type::horse;
    if (color == Figure_Color::white)
        body = new Fl_PNG_Image("white_horse.png");
    else
        body = new Fl_PNG_Image("black_horse.png");
}

/*std::vector<Position> Horse::available_turns()
{
  std::vector<Position> turns;

  std::vector<Position> all_turns;
  for (int i = -2; i <= 2; i += 4)
    for (int j = -1; j <= 1; j += 2)
    {
      all_turns.push_back(Position{char(pos.letter + j), pos.number + i});
      all_turns.push_back(Position{char(pos.letter + i), pos.number + j});
    }

  for (auto k : all_turns)
  {
    if ((k.number >= 1 && k.number <= 8) && (k.letter >= 'a' && k.letter <= 'h'))
      turns.push_back(k);
  }

  return turns;
}*/

Elephant::Elephant(Position pos, const Figure_Color &color)
{
    add(get_position(pos));

    Figures::pos = pos;
    Figures::color = color;
    Figures::type = Figure_Type::elephant;
    if (color == Figure_Color::white)
        body = new Fl_PNG_Image("white_elephant.png");
    else
        body = new Fl_PNG_Image("black_elephant.png");
}

/*std::vector<Position> Elephant::available_turns()
{
  std::vector<Position> turns;

  std::vector<Position> all_turns;
  for (int i = -8; i <= 8; ++i)
  {
    all_turns.push_back(Position{char(pos.letter + i), pos.number + i});
    all_turns.push_back(Position{char(pos.letter + i), pos.number - i});
  }

  for (auto k : all_turns)
  {
    if ((k.number >= 1 && k.number <= 8) && (k.letter >= 65 && k.letter <= 65 + 8))
      turns.push_back(k);
  }

  return turns;
}*/
