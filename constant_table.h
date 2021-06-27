#ifndef CHESS_CONSTANT_TABLE_H
#define CHESS_CONSTANT_TABLE_H

const unsigned int black_cell { 64 };
const unsigned int white_cell { 174 };
const int first_letter = 65;

constexpr int cells_count { 8 };
constexpr int board_size = 640;
constexpr int scale_factor = cells_count * 2;
constexpr int cell_size = board_size / cells_count;
constexpr int side_size = board_size / scale_factor;
constexpr int window_size = board_size + side_size * 2;
constexpr int font_size = cell_size / 2;


#endif //CHESS_CONSTANT_TABLE_H
