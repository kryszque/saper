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

void reveal(Cell *board, int row, int col, int max_col){ // changes the value of visible based on this change the print_board func
    if(board[row * max_col + col].bomb == 1){
        
    }
    
}

void move(Cell *board, int row, int col, int max_col){
    int x;
    int y;
    char order;
    printf("Napisz f x y, aby dodac flage lub r x y, aby odslonic pole w x, y.\n");
    scanf("%c %d %d", &order, &x, &y);

    switch (order) {
        case 'r':
            if(board[row * max_col + col].bomb == 1){
                
                
            }
            //reveal func
            break;
        case 'f':
            board[x*max_col + y].flag = 1;
            break;
    
    }
}

void game(){
    while(1){
        

    }

}



