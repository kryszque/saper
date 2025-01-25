#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void check_first_move(Cell *board, int row, int col, int max_col);
void reveal(Cell *board, int row, int col, int max_col, int max_row);
void move(Cell *board, int x, int y, int max_col, int max_row, char order);
void game(Cell *board, int max_col, int max_row);

#endif
