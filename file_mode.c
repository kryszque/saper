#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include <string.h>
#include <ctype.h>

ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
    if (lineptr == NULL || n == NULL || stream == NULL) {
        return -1;
    }

    if (*lineptr == NULL) {
        *n = 128; 
        *lineptr = malloc(*n);
        if (*lineptr == NULL) {
            return -1; 
        }
    }

    size_t pos = 0;
    int c;

    while ((c = fgetc(stream)) != EOF) {
        if (pos + 1 >= *n) {
            size_t new_size = *n * 2;
            char *new_ptr = realloc(*lineptr, new_size);
            if (new_ptr == NULL) {
                return -1;
            }
            *lineptr = new_ptr;
            *n = new_size;
        }

        (*lineptr)[pos++] = c;

        if (c == '\n') {
            break;
        }
    }

    if (pos == 0 && c == EOF) {
        return -1;
    }

    (*lineptr)[pos] = '\0';

    return pos;
}

//dodac obsluge bledow!!!
void print_read_board(Cell *read_board, int row, int col) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            printf("%d ", read_board[i * col + j].bomb);
        }
        printf("\n");
    }
}

Cell *read_board(FILE *in) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int row = 0;
    int col = 0;
    Cell *read_board = NULL;

    read = getline(&line, &len, in);
    if (read == -1) {
        free(line);
        return NULL;
    }

    col = strlen(line);
    if (line[col-1] == '\n') col--;

    read_board = malloc(col * sizeof(Cell));
    if (!read_board) {
        free(line);
        return NULL;
    }

    do {
        if (read <= 1) break;
        
        Cell *temp = realloc(read_board, (row + 1) * col * sizeof(Cell));
        if (!temp) {
            free(read_board);
            free(line);
            return NULL;
        }
        read_board = temp;

        for(int i = 0; i < col; i++) {
            if (i < strlen(line) && isdigit(line[i])) {
                read_board[row * col + i].bomb = line[i] - '0';
            } else {
                read_board[row * col + i].bomb = 0;
            }
        }
        row++;
    } while ((read = getline(&line, &len, in)) != -1);

    print_read_board(read_board, row, col);
    free(line);
    return read_board;
}