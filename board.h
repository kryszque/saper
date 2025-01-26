#ifndef __BOARD_H__
#define __BOARD_H__

extern float multiplier;

typedef struct {
    int bomb;
    char num;
    int flag;
    int visible;
} Cell;



int count_adjacent_bombs(Cell *board, int row, int col, int max_row, int max_col);
void check_for_bombs(Cell *board, int max_row, int max_col);
Cell* create_board(int row, int col);
void initialize_board(Cell *board, int row, int col);
void generate_bombs(Cell *board, int bombnum, int row, int col);
int is_valid(Cell *board, int max_row, int row, int col);
void print_board(Cell *board, int row, int col);
void free_board(Cell *board);
void clear_console();

#endif