#include <stdio.h>
#include <stdlib.h>
#include "board.h"

Cell* create_board(int row, int col) {
    Cell *board = malloc(row * col * sizeof(Cell));
    if (board == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return board;
}

int count_adjacent_bombs(Cell *board, int row, int col, int max_row, int max_col) { // counts the amount of bombs around current field
    int bomb_count = 0;
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            
            int new_row = row + i;
            int new_col = col + j;
            
            if (new_row >= 0 && new_row < max_row && 
                new_col >= 0 && new_col < max_col) {
                if (board[new_row * max_col + new_col].bomb == 1) {
                    bomb_count++;
                }
            }
        }
    }
    
    return bomb_count;
}

void check_for_bombs(Cell *board, int max_row, int max_col) {
    for (int i = 0; i < max_row; i++) {
        for (int j = 0; j < max_col; j++) {
            if (board[i * max_col + j].bomb == 1) {
                board[i * max_col + j].num = 'B';
                continue;
            }
            
            int nearby_bombs = count_adjacent_bombs(board, i, j, max_row, max_col);
            
            board[i * max_col + j].num = nearby_bombs > 0 ? nearby_bombs + '0' : ' ';
        }
    }
}

void initialize_board(Cell *board, int row, int col){
    for(int i=0; i<row*col; i++){
        board[i].num = ' ';
        board[i].bomb = 0;
        board[i].flag = 0;
        board[i].visible = 0;
    }
}

void print_board(Cell *board, int row, int col) {
    // Print column indices
    printf("   ");  // Space for row indices
    for (int j = 0; j < col; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    // Print top border
    printf("   ");
    for (int j = 0; j < col; j++) {
        printf("---");
    }
    printf("\n");

    // Print board content
    for (int i = 0; i < row; i++) {
        printf("%2d|", i);  // Row index with border
        for (int j = 0; j < col; j++) {
            printf(" ");  // Leading space
            if (board[i * col + j].visible) {
                if (board[i * col + j].bomb) {
                    printf("B");
                } else {
                    printf("%c", board[i * col + j].num);
                }
            } else {
                printf(".");  // Hidden cell
            }
            printf(" ");  // Trailing space
        }
        printf("|\n");
    }

    // Print bottom border
    printf("   ");
    for (int j = 0; j < col; j++) {
        printf("---");
    }
    printf("\n");
}

void generate_bombs(Cell *board, int bombnum, int row, int col){
    while(bombnum != 0){
        int rand_row = rand() % row;
        int rand_col = rand() % col;
        if(is_valid(board, col, rand_row, rand_col) == 1){
            board[rand_row*col + rand_col].bomb = 1;
            bombnum--;
        }
    }
}

int is_valid(Cell *board,  int max_cols, int row, int col){
    int row_s = row / 3;
    int col_s = col / 3;
    int counter = 0;
    if(board[row*max_cols + col].bomb == 1){
        return -1;
    }
    for(int rowt = row_s*3; rowt<row_s*3+3; rowt++){
        for(int colt = col_s*3; colt<col_s*3+3; colt++){
            if(board[rowt * row + colt].bomb == 1){
                counter++;
            }
        }
    }
    return (counter == 9) ? -1 : 1; 
}

