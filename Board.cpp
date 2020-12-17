#include "Board.h"
#include <sstream>


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
                                      cb_clicked, type_of_cell(i,j),
                                      Position {static_cast<char>('a' + j), 8 - i}});
            attach (cells[cells.size() - 1]);
        }
    create_signatures();
    //init_game();
        //TODO: добавлять и удалять фигуры для теста здесь


    set_figure(Position{'e', 4}, Figure_Color::black, Figure_Type::horse);
    set_figure(Position{'a', 1}, Figure_Color::black, Figure_Type::rook);
    set_figure(Position{'b', 7}, Figure_Color::white, Figure_Type::elephant);
    set_figure(Position{'h', 1}, Figure_Color::black, Figure_Type::rook);
    set_figure(Position{'f', 4}, Figure_Color::black, Figure_Type::queen);
    set_figure(Position{'e', 1}, Figure_Color::white, Figure_Type::king);
    set_figure(Position{'c', 3}, Figure_Color::white, Figure_Type::pawn);
    set_figure(Position{'d', 3}, Figure_Color::black, Figure_Type::pawn);

}

void print_result(Rules& rules, Graph_lib::Point board_location)
{
  std::string text;
  if (rules.get_loser() == Figure_Color::white)
    text = "Winner is black figures!";
  else
    text = "Winner is white figures!";

  Simple_window result_win{Graph_lib::Point{board_location.x+board_size/3, board_location.y+board_size/2}
      , board_size*3/4, board_size/6, "Score"};

  Graph_lib::Rectangle background {Graph_lib::Point{0, 0}, board_size, board_size/4};
  background.set_fill_color(black_cell);
  result_win.attach(background);

  Graph_lib::Text result {Graph_lib::Point {board_size/16, board_size/12}, text};
  result.set_font(Graph_lib::Font::times);
  result.set_font_size(font_size);
  result.set_color(white_cell);
  result_win.attach(result);

  result_win.wait_for_button();
}

bool turn_is_in(std::vector<Position> &turns, Position pos)
{
  for (auto i : turns)
    if ((i.letter == pos.letter) && (i.number == pos.number))
      return true;
  return false;
}

Position Rules::get_king(Checkerboard& board)
{
  Position king {'a', 1};
  for (int i = 0; i < 8; ++i)
    for (int j = 1; j <= 8; ++j)
    {
      Position pos = {char('a' + i), j};
      if (board.at(pos).fig != nullptr && board.at(pos).fig->get_type() == Figure_Type::king
          && board.at(pos).fig->get_color() == current_turn)
        king = {pos};
    }
  return king;
}

/*
bool Rules::is_shah(Checkerboard& board)
{
  Position king = get_king(board);

  for (int i = 0; i < 8; ++i)
    for (int j = 1; j <= 8; ++j)
    {
      Position pos = {char('a' + i), j};
      if (board.at(pos).fig != nullptr && board.at(pos).fig->get_type() != Figure_Type::king
          && board.at(pos).fig->get_color() != current_turn)
      {
        current_turn = board.at(pos).fig->get_color();
        std::vector<Position> turns_figures = get_available_turns(board, pos);
        current_turn = board.at(king).fig->get_color();
        if(turn_is_in(turns_figures, king))
          return true;
      }
    }
  return false;
}
 */

void Checkerboard::clicked (Graph_lib::Address widget)
{
    if (rules.check_end_game(*this))
      print_result(rules, board_location);

    auto& w = Graph_lib::reference_to<Fl_Widget>(widget);
    Point current {w.x(), w.y()};
    Cell& tmp = at (current);

    if (!moving && rules.is_shah(*this, rules.get_king(*this)) )
    {
      Position king = rules.get_king(*this);
      available_turns = rules.get_available_turns(*this, king);
      for (auto pos : available_turns)
        at(pos).activate();
      at(king).activate();
      current = at(king).location();
      from = current;
      moving = true;

    }
    else if (!moving && tmp.fig != nullptr && tmp.fig->get_color() == rules.get_turn_color())
      {
        available_turns = rules.get_available_turns(*this, tmp.position());

        for (auto pos : available_turns)
            at(pos).activate();
        tmp.activate();
        from = current;
        moving = true;
    }
    else if (moving && is_available(&tmp))
    {
        Cell& tmp_from = at(from);
        tmp_from.deactivate();
        for (auto pos : available_turns)
            at(pos).deactivate();
        available_turns.clear();
        figure_t figure = delete_figure(from);
        if (figure != nullptr)
        {
            figure->move(tmp.loc.x - tmp_from.loc.x, tmp.loc.y - tmp_from.loc.y);
            set_figure(current, figure);
        }
        //figure->last_turn = from; //для взятия на проходе и для проверки передачи хода ладье при рокировке
        moving = false;
        rules.end_turn();
    }
    else if (moving && tmp.location() == from)
    {
        tmp.deactivate();
        for (auto pos : available_turns)
            at(pos).deactivate();
        available_turns.clear();
        moving = false;
    }
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
    --pos.number;
    int i = (cells_count - pos.number) - 1;
    int j = pos.letter - 'a';
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

bool Checkerboard::is_available(Cell *compare)
{
    for (auto i : available_turns)
    {
        if (compare == &at(i))
            return true;
    }
    return false;
}

std::vector<Position> Rules::get_available_turns(Checkerboard &board, Position pos)
{
    switch (board.at(pos).fig->get_type())
    {
        case pawn:
            return get_pawn_turns(board, pos);
        case rook:
            return get_rook_turns(board, pos);
        case horse:
            return get_horse_turns(board, pos);
        case elephant:
            return get_elephant_turns(board, pos);
        case queen:
            return get_queen_turns(board, pos);
        case king:
            return get_king_turns(board, pos);
    }
}

void Rules::exclude_out_of_board(std::vector<Position> &turns)
{
    std::vector<Position> answer;
    for (auto i : turns)
    {
        if ((i.number >= 1 && i.number <= 8) && (i.letter >= 'a' && i.letter <= 'h'))
            answer.push_back(i);
    }
    turns = answer;
}

void Rules::exclude_friendly_fire(Checkerboard& board, std::vector<Position> &turns)
{
    std::vector<Position> answer;
    for (auto i : turns)
    {
        if(board.at(i).fig == nullptr || board.at(i).fig->get_color() != current_turn)
            answer.push_back(i);
    }
    turns = answer;
}

bool check_obstacle (Checkerboard &board, std::vector<Position> &turns, Position pos, Position i)
{
    if (i.number != pos.number || i.letter != pos.letter)
    {
        turns.push_back(i);
        if (board.at(i).fig != nullptr)
            return true;
    }
    return false;
}

void Rules::diagonal_moving(Checkerboard &board, std::vector<Position> &turns, Position pos)
{
    for (Position i = pos; i.letter <= 'h' && i.number <= 8; ++i.letter, ++i.number)
    {
        if (check_obstacle(board, turns, pos, i))
            break;
    }

    for (Position i = pos; i.letter <= 'h' && i.number >= 1; ++i.letter, --i.number)
    {
        if (check_obstacle(board, turns, pos, i))
            break;
    }

    for (Position i = pos; i.letter >= 'a' && i.number <= 8; --i.letter, ++i.number)
    {
        if (check_obstacle(board, turns, pos, i))
            break;
    }

    for (Position i = pos; i.letter >= 'a' && i.number >= 1; --i.letter, --i.number)
    {
        if (check_obstacle(board, turns, pos, i))
            break;
    }
}

void Rules::vertical_moving(Checkerboard &board, std::vector<Position> &turns, Position pos)
{
    for (Position i = pos; i.letter <= 'h'; ++i.letter)
    {
        if (check_obstacle(board, turns, pos, i))
            break;
    }

    for (Position i = pos; i.letter >= 'a'; --i.letter)
    {
        if (check_obstacle(board, turns, pos, i))
            break;
    }

    for (Position i = pos; i.number >= 1; --i.number)
    {
        if (check_obstacle(board, turns, pos, i))
            break;
    }

    for (Position i = pos; i.number <= 8; ++i.number)
    {
        if (check_obstacle(board, turns, pos, i))
            break;
    }

}

std::vector<Position> Rules::get_rook_turns(Checkerboard &board, Position pos)
{
    std::vector<Position> turns;
    vertical_moving(board, turns, pos);

    exclude_out_of_board(turns);
    exclude_friendly_fire(board, turns);

    return turns;
}

std::vector<Position> Rules::get_queen_turns(Checkerboard &board, Position pos)
{
    std::vector<Position> turns;
    vertical_moving(board, turns, pos);
    diagonal_moving(board, turns, pos);

    exclude_out_of_board(turns);
    exclude_friendly_fire(board, turns);

    return turns;
}


/*
void Rules::add_castling(Checkerboard &board, std::vector<Position> &turns, Position pos)
{
  int i = 1;
  bool is_clear_left = true;
  while ((pos.letter - i) > int('a'))
  {
    if (board.at(Position{char(pos.letter - i), pos.number}).fig != nullptr) {
      is_clear_left = false;
      break;
    }
    ++i;
  }

  if (is_clear_left)
  {
    if (board.at(Position{char(pos.letter-i), pos.number}).fig != nullptr
        && board.at(Position{char(pos.letter-i), pos.number}).fig->get_type() == Figure_Type::rook)
      turns.push_back(Position{char(pos.letter - 2), pos.number});
  }

  int j = 1;
  bool is_clear_right = true;
  while ((pos.letter + j) < int('h'))
  {
    if (board.at(Position{char(pos.letter + j), pos.number}).fig != nullptr) {
      is_clear_right = false;
      break;
    }
    ++j;
  }

  if (is_clear_right)
  {
    if (board.at(Position{char(pos.letter+j), pos.number}).fig != nullptr
        && board.at(Position{char(pos.letter+j), pos.number}).fig->get_type() == Figure_Type::rook)
      turns.push_back(Position{char(pos.letter + 2), pos.number});
  }

}
*/

bool Rules::around_own(Checkerboard &board, Position pos)
{
  std::vector<Position> positions;
  for (int i = -1; i <= 1; ++i)
    for (int j = -1; j <= 1; ++j)
    {
      Position cur {char(pos.letter + i), pos.number + j};
      positions.push_back(cur);
    }
  exclude_out_of_board(positions);

  for (auto i : positions)
    if (board.at(i).fig != nullptr && board.at(i).fig->get_color() != board.at(pos).fig->get_color())
      return false;

  return true;
}

std::vector<Position> Rules::get_king_turns(Checkerboard &board, Position pos)
{
    std::vector<Position> turns;
    for (int i = -1; i <= 1; ++i)
      for (int j = -1; j <= 1; ++j) {
        turns.push_back(Position{char(pos.letter + i), pos.number + j});
      }

//    if (board.at(pos).fig->first_turn)
//      add_castling(board, turns, pos);
//    //сразу передать ход ладье и дать единственный возможный ход ???
//    board.at(pos).fig->first_turn = false;

    exclude_out_of_board(turns);
    exclude_friendly_fire(board, turns);
    exclude_shah(board, turns, pos);

    return turns;
}

int Rules::pawn_direction(Checkerboard &board, Position pos)
{
  if (board.at(pos).fig->get_color() == Figure_Color::white)
    return 1;
  return -1;
}

void Rules::add_pawn_fire(Checkerboard &board, std::vector<Position> &turns, Position pos)
{
  int direction = pawn_direction(board, pos);
  for (int i = -1; i <= 1; i += 2)
  {
    Position pos_of_turn {char(pos.letter + i), pos.number + direction};
    if (board.at(pos_of_turn).fig != nullptr
        && board.at(pos_of_turn).fig->get_color() != board.at(pos).fig->get_color())
      turns.push_back(pos_of_turn);

//    Position pos_of_aisle = {char(pos.letter + i), pos.number};
//    if (board.at(pos_of_aisle).fig != nullptr)
//      if (board.at(pos_of_aisle).fig->last_turn == board.at(Position{pos_of_aisle.letter, pos_of_turn.number - 2*direction}).loc)
//        turns.push_back(pos_of_turn);

  }

}

std::vector<Position> Rules::get_pawn_turns(Checkerboard &board, Position pos)
{
    std::vector<Position> turns;
    int direction = pawn_direction(board, pos);

    Position pos_of_turn {pos.letter, pos.number + direction};
    if (check_obstacle(board, turns, pos, pos_of_turn))
      turns.pop_back();

    pos_of_turn = {pos.letter, pos.number + 2*direction};
    if (board.at(pos).fig->first_turn)
    {
      if (check_obstacle(board, turns, pos, pos_of_turn))
        turns.pop_back();

      board.at(pos).fig->first_turn = false;
    }

    add_pawn_fire(board, turns, pos);
    exclude_out_of_board(turns);

    return turns;
}

std::vector<Position> Rules::get_elephant_turns(Checkerboard &board, Position pos)
{
    std::vector<Position> turns;
    diagonal_moving(board, turns, pos);

    exclude_out_of_board(turns);
    exclude_friendly_fire(board, turns);

    return turns;
}

std::vector<Position> Rules::get_horse_turns(Checkerboard &board, Position pos)
{
    std::vector<Position> turns;
    for (int i = -2; i <= 2; i += 4)
        for (int j = -1; j <= 1; j += 2)
        {
            turns.push_back(Position{char(pos.letter + j), pos.number + i});
            turns.push_back(Position{char(pos.letter + i), pos.number + j});
        }

    exclude_out_of_board(turns);
    exclude_friendly_fire(board, turns);

    return turns;
}

bool Rules::check_end_game(Checkerboard& board)
{
    if(is_shah(board, get_king(board)) &&
    get_available_turns(board,get_king(board)).empty())
    {
        loser = current_turn;
        return true;
    }
    return false;
}

extern Graph_lib::Point get_position(Position pos);

bool Rules::is_shah(Checkerboard &board, Position pos)
{
    Position king = get_king(board);
    bool other_pos = (pos.letter != king.letter || pos.number != king.number);
    figure_t first_tmp = board.delete_figure(get_position(king));
    figure_t second_tmp;
    if (other_pos)
        second_tmp = board.delete_figure(get_position(pos));

    for (char i = 'a'; i <= 'h'; ++i)
        for(int j = 1; j <= 8; ++j)
        {
            Position check{i, j};
            if (board.at(check).fig != nullptr && board.at(check).fig->get_color() != current_turn)
            {
                Figure_Color tmp_color = current_turn;
                current_turn = board.at(check).fig->get_color();
                std::vector<Position> turns_figures;
                if(board.at(check).fig->get_type() == Figure_Type::pawn)
                {
                    board.set_figure(get_position(pos), first_tmp);
                    turns_figures = get_available_turns(board, check);
                    first_tmp = board.delete_figure(get_position(pos));
                }
                else
                    turns_figures = get_available_turns(board, check);

                current_turn = tmp_color;
                if(turn_is_in(turns_figures, pos))
                {
                    if (other_pos)
                        board.set_figure(get_position(pos), second_tmp);
                    board.set_figure(get_position(king), first_tmp);
                    return true;
                }
            }
        }
    if (other_pos)
        board.set_figure(get_position(pos), second_tmp);
    board.set_figure(get_position(king), first_tmp);
    return false;
}

void Rules::exclude_shah(Checkerboard &board, std::vector<Position> &turns, Position k)
{
    std::vector<Position> answer;
    for (auto i : turns)
        if (!is_shah(board, i))
            answer.push_back(i);
    turns = answer;
}
