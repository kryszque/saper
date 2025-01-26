#include <stdio.h>
#include <stdlib.h>
#include "board.h"


void check_first_move(Cell *board, int row, int col, int max_col){
    if(board[row * max_col + col].bomb == 1){
        board[row * max_col + col].bomb = 0;
        int rand_row = rand() % max_col;
        int rand_col = rand() % max_col;
        while(board[rand_row * max_col + rand_col].bomb == 1){
            rand_row = rand() % max_col;
            rand_col = rand() % max_col;
            max_col--;
        }
        board[rand_row * max_col + rand_col].bomb = 1;
    }
}

void reveal(Cell *board, int row, int col, int max_col, int max_row) {
    if (row < 0 || row >= max_row || col < 0 || col >= max_col) return;
    if (board[row * max_col + col].visible == 1) return;

    board[row * max_col + col].visible = 1;

    if (board[row * max_col + col].bomb == 1) {
        board[row * max_col + col].visible = 1;
        system("clear");
        print_board(board, max_row, max_col);
        printf("Przegrales\n");
        exit(0);
    }

    if (board[row * max_col + col].num == ' ') {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                reveal(board, row + i, col + j, max_col, max_row);
            }
        }
    }
}

void move(Cell *board, int x, int y, int max_col, int max_row, char order){
    switch (order) {
        case 'r':
            reveal(board, x, y, max_col, max_row);
            break;
        case 'f':
            board[x*max_col + y].flag = 1;
            break;
    }
}

void game(Cell *board, int max_col, int max_row) {
    int first_move = 1;
    while (1) {
        system("clear");
        print_board(board, max_row, max_col);
        int x;
        int y;
        char order;
        printf("Napisz f x y, aby dodac flage lub r x y, aby odslonic pole w x, y.\n");
        scanf("%c %d %d", &order, &y, &x);
        if (first_move == 1) {
        check_first_move(board, x, y, max_col);
        first_move = 0;
        }
        move(board, x, y, max_col, max_row, order);
        print_board(board, max_row, max_col);
    }
}
