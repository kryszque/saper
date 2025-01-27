#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void update_board_on_first_move(Cell *board, int row, int col, int max_row, int max_col);
int is_game_over(Cell *board, int max_col, int max_row);
void reveal(Cell *board, int row, int col, int max_col, int max_row);
void move(Cell *board, int x, int y, int max_col, int max_row, char order);
int game(Cell *board, int max_col, int max_row, int total_bombs);
int count_score(int moves);
void reveal_whole_map(Cell *board, int max_col, int max_row);
void set_multiplier(int level);
#endif
