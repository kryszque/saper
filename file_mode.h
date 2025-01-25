#ifndef FILE_MODE_H
#define FILE_MODE_H
#include "board.h"
#include <stdio.h>

typedef struct move{
    int y;
    int x;
    char type;
    char *move_skip;
}Move;


Cell *read_board(FILE *in, int *row, int *col);
ssize_t getline(char **lineptr, size_t *n, FILE *in);
void print_read_board(Cell *read_board, int row, int col);
Move *read_moves(FILE *in, int* moves_ctr);
void print_read_moves(Move *read_moves, int moves_ctr);
void free_read_moves(Move *read_moves, int moves_ctr);
int solve(Cell *read_board, Move *read_moves, int row, int col, int moves_ctr);

#endif