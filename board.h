#ifndef __BOARD_H__
#define __BOARD_H__


typedef struct {
    int bomb;
    char num;
} Cell;
Cell* create_board(int row, int col);
void initialize_board(Cell *board, int row, int col);
void generate_bombs(Cell *board, int bombnum, int row, int col);
int is_valid(Cell *board, int max_row, int row, int col);
void print_board(Cell *board, int row, int col); 
#endif
