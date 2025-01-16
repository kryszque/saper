#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void print_board(int *board, int row, int col) {
    // Wypisz górną ramkę
    printf("   "); // Miejsce na indeksy kolumn
    for (int j = 0; j < col; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    printf("   "); // Dla estetyki pod ramką
    for (int j = 0; j < col; j++) {
        printf("---");
    }
    printf("\n");

    // Wypisz wiersze z zawartością i bocznymi ramkami
    for (int i = 0; i < row; i++) {
        printf("%2d|", i); // Indeks wiersza z ramką
        for (int j = 0; j < col; j++) {
            printf(" %d ", board[i * col+ j]); // Wartość z tablicy
        }
        printf("|\n"); // Zamknięcie prawej ramki
    }

    // Dolna ramka (opcjonalna)
    printf("   ");
    for (int j = 0; j < col; j++) {
        printf("---");
    }
    printf("\n");
}
void generate_bombs(int *board, int bombnum, int row, int col){
    while(bombnum != 0){
        int rand_row = rand() % row;
        int rand_col = rand() % col;
        if(is_valid(board, col, rand_row, rand_col) == 1){
            board[rand_row*col + rand_col] = 1;
            bombnum--;
        }
    }
}

int is_valid(int *board,  int max_cols, int row, int col){
    int row_s = row / 3;
    int col_s = col / 3;
    int counter = 0;
    if(board[row*max_cols + col] == 1){
        return -1;
    }
    for(int rowt = row_s*3; rowt<row_s*3+3; rowt++){
        for(int colt = col_s*3; colt<col_s*3+3; colt++){
            if(board[rowt * row + colt] == 1){
                counter++;
            }
        }
    }
    if(counter == 9){ 
        return -1;
    }else{
        return 1;
    }
}

