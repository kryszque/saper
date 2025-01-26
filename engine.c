#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

int game_loop = 1;


float multiplier = 1.0f;

int is_game_over(Cell *board, int max_row, int max_col) {
    int total_cells = max_row * max_col;
    int uncovered_cells = 0;

    for (int i = 0; i < total_cells; i++) {
        if (board[i].visible == 1 && board[i].bomb == 1) {

            return 1;
        }

        if (board[i].visible == 1 || board[i].bomb == 1) {

            uncovered_cells++;
        }
    }

    if (uncovered_cells == total_cells) {

        return 1;
    }

    return 0;
}


void set_multiplier(int level) {
    switch (level) {
        case 1: // Łatwy
            multiplier = 1.0f;
            break;
        case 2: // Średni
            multiplier = 1.5f;
            break;
        case 3: // Trudny
            multiplier = 2.0f;
            break;
        default: // Domyślnie łatwy
            multiplier = 1.0f;
            break;
    }
}

void update_board_on_first_move(Cell *board, int row, int col, int max_row, int max_col) {
    srand(time(NULL));

    if (board[row * max_col + col].bomb == 1) {
        board[row * max_col + col].bomb = 0;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int neighbor_row = row + i;
                int neighbor_col = col + j;


                if (neighbor_row >= 0 && neighbor_row < max_row &&
                    neighbor_col >= 0 && neighbor_col < max_col) {
                    if (board[neighbor_row * max_col + neighbor_col].num > 0) {
                        board[neighbor_row * max_col + neighbor_col].num--;
                    }
                }
            }
        }


        int rand_row, rand_col;
        do {
            rand_row = rand() % max_row;
            rand_col = rand() % max_col;
        } while (board[rand_row * max_col + rand_col].bomb == 1 ||
                 (rand_row == row && rand_col == col));


        board[rand_row * max_col + rand_col].bomb = 1;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int neighbor_row = rand_row + i;
                int neighbor_col = rand_col + j;

                if (neighbor_row >= 0 && neighbor_row < max_row &&
                    neighbor_col >= 0 && neighbor_col < max_col) {
                    board[neighbor_row * max_col + neighbor_col].num++;
                }
            }
        }
    }
}

void reveal_whole_map(Cell *board, int max_col, int max_row) {
    for (int i = 0; i < max_row; i++) {
        for (int j = 0; j < max_col; j++) {
            board[i * max_col + j].visible = 1;
        }
    }
}

int count_score(int moves) {
    return ((moves * multiplier)-1);
}

void reveal(Cell *board, int row, int col, int max_col, int max_row) {
    if (row < 0 || row >= max_row || col < 0 || col >= max_col) return;
    if (board[row * max_col + col].visible == 1) return;

    board[row * max_col + col].visible = 1;

    if (board[row * max_col + col].bomb == 1) {
        board[row * max_col + col].visible = 1;
        clear_console();
        print_board(board, max_row, max_col);
        game_loop = 0;
        }


    if (board[row * max_col + col].num == ' ') {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                reveal(board, row + i, col + j, max_col, max_row);
                print_board(board, max_row, max_col);
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
            if(board[x*max_col + y].flag == 0){
                board[x*max_col + y].flag = 1;
            } else {
                board[x*max_col + y].flag = 0;
            }

            break;
    }
}

void game(Cell *board, int max_col, int max_row) {
    int first_move = 1;
    int moves = 0;
    while (game_loop == 1) {
        clear_console();
        print_board(board, max_row, max_col);
        if (is_game_over(board, max_row, max_col)) {
            game_loop = 0; // Koniec gry
            break;
        }
        int x;
        int y;
        char order;
        printf("Napisz f x y, aby dodac flage lub r x y, aby odslonic pole w x, y.\n");
        scanf("%c %d %d", &order, &y, &x);
        if (first_move == 1) {
            update_board_on_first_move(board, x, y, max_row, max_col);
            first_move = 0;
            continue;
        }
        moves++;
        move(board, x, y, max_col, max_row, order);
    }
    reveal_whole_map(board, max_col, max_row);
    print_board(board, max_row, max_col);
    printf("Koniec gry! Twoj wynik to: %d\n", count_score(moves));
}