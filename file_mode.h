#ifndef FILE_MODE_H
#define FILE_MODE_H
#include "board.h"
#include <stdio.h>

Cell *read_board(FILE *in);
ssize_t getline(char **lineptr, size_t *n, FILE *in);
void print_read_board(Cell *read_board, int row, int col);

#endif