#ifndef __BOARD_H__
#define __BOARD_H__



void generate_bombs(int *board, int bombnum, int row, int col);
int is_valid(int *board, int max_row, int row, int col);
void print_board(int *board, int row, int col); 
#endif
