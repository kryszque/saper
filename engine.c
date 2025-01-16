#include <stdio.h>
#include "board.h"

void check_first_move(Cell *board, int row, int col, int max_col){
    if(board[row * max_col + col].bomb == 1){
        //swap the bomb coordinates
    }
}

void check_for_bombs(Cell *board, int max_row, int max_col){
    for(int i=0; i<max_row*max_col; i++){
        

        
    }

}

void reveal(){ // changes the value of visible based on this change the print_board func

}

void move(Cell *board, int row, int col, int max_col){
    int x;
    int y;
    char order;
    printf("Napisz f x y, aby dodac flage lub r x y, aby odslonic pole w x, y.\n");
    scanf("%c %d %d", &order, &x, &y);

    switch (order) {
        case 'r':
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



