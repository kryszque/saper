#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "file_mode.h"
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
void print_read_board(Cell *read_board, int row, int col) { //col ilosc kolumn - x, row ilosc rzedow - y
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            printf("%d ", read_board[i * col + j].bomb);
        }
        printf("\n");
    }
}

void free_read_moves(Move *read_moves, int moves_ctr){
    for(int i = 0; i < moves_ctr; i++){
        if(read_moves[i].move_skip != NULL) free(read_moves[i].move_skip);
    }
    free(read_moves);
}

void print_read_moves(Move *read_moves, int moves_ctr){
    for(int i = 0; i < moves_ctr; i++){
        if(read_moves[i].move_skip == NULL) printf("%c %d %d\n",read_moves[i].type, read_moves[i].x, read_moves[i].y);
        else printf("%s | ruch nr %d\n", read_moves[i].move_skip, i+1);
    }
}

Cell *read_board(FILE *in, int *row, int *col) { //plansza musi miec co najmniej 1 cyfre 0 lub 1
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    Cell *read_board = NULL;

    read = getline(&line, &len, in);
    if (read == -1) {
        free(line);
        return NULL;
    }

    *col = strlen(line);
    if (line[*col-1] == '\n') (*col)--;

    read_board = malloc(*col * sizeof(Cell));
    if (!read_board) {
        free(line);
        return NULL;
    }

    do {
        if (read <= 1) break;
        
        Cell *temp = realloc(read_board, (*row + 1) * *col * sizeof(Cell));
        if (!temp) {
            free(read_board);
            free(line);
            fprintf(stderr,"Nieudana alokacja dla read_board!!!");
            return NULL;
        }
        read_board = temp;

        for(int i = 0; i < *col; i++) {
            if (i < strlen(line) && isdigit(line[i])) {
                read_board[*row * *col + i].bomb = line[i] - '0';
            } else {
                read_board[*row * *col + i].bomb = 0;
            }
        }
        (*row)++;
    } while ((read = getline(&line, &len, in)) != -1);

    free(line);
    return read_board;
}

Move *read_moves(FILE *in, int *moves_ctr){
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    Move *read_moves = NULL;

    read = getline(&line, &len, in);
    if (read == -1) {
        free(line);
        return NULL;
    }

    read_moves = malloc(sizeof(Move));
    if(!read_moves){
        fprintf(stderr, "Nieudana alokacja pamieci dla read_moves!!!");
        free(line);
        return NULL;
    }

    do{
        Move *temp = realloc(read_moves, (*moves_ctr+1) * sizeof(Move));
        if(!temp){
            free(read_moves);
            free(line);
            fprintf(stderr,"Nieudana alokacja dla read_moves!!!");
            return NULL;
        }
        read_moves = temp;
        
        if(line[0] == 'f' || line[0] == 'r'){
            read_moves[*moves_ctr].type = line[0];
            read_moves[*moves_ctr].move_skip = NULL;
        }
        
        else{
            read_moves[*moves_ctr].type = '\0';
            read_moves[*moves_ctr].x = -1;
            read_moves[*moves_ctr].y = -1;
            read_moves[*moves_ctr].move_skip = "Pominiecie ruchu z uwagi na niepoprawny typ ruchu";
            (*moves_ctr)++;
            continue;
        }
        
        if(isdigit(line[1]) && isdigit(line[2])){
            read_moves[*moves_ctr].x = line[1] - '0';
            read_moves[*moves_ctr].y = line[2] - '0';
            (*moves_ctr)++;
        }
        else{
            read_moves[*moves_ctr].type = '\0';
            read_moves[*moves_ctr].x = -1;
            read_moves[*moves_ctr].y = -1;
            read_moves[*moves_ctr].move_skip = "Pominiecie ruchu z uwagi na niepoprawne wspolrzedne";
            (*moves_ctr)++;
            continue;
        }

    }while((read = getline(&line, &len, in))!=-1);
    free(line);
    return read_moves;
}

int solve(Cell *read_board, Move *read_moves, int row, int col, int moves_ctr){
    int bombs_ctr = 0;
    int revealed_ctr = 0;
    int pos = -1;
    if(!read_board || !read_moves) return 0;
    for(int i = 0; i < moves_ctr; i++){
        if(read_moves[i].move_skip == NULL){
            switch (read_moves[i].type)
            {
            case('f'):
                pos = (read_moves[i].y-1)*col+(read_moves[i].x-1);
                if(read_moves[i].x > col || read_moves[i].y > row){
                    read_moves[i].x = -1;
                    read_moves[i].y = -1;
                    read_moves[i].type = '\0';
                    read_moves[i].move_skip = "Pominiecie ruchu z uwagi na niepoprawne wspolrzedne (poza plansza)";
                    break;
                }
                else{
                    read_board[pos].flag = 1;
                }
                break;
            case('r'):
                pos = (read_moves[i].y-1)*col+(read_moves[i].x-1);
                if(read_moves[i].x > col || read_moves[i].y > row){
                    read_moves[i].x = -1;
                    read_moves[i].y = -1;
                    read_moves[i].type = '\0';
                    read_moves[i].move_skip = "Pominiecie ruchu z uwagi na niepoprawne wspolrzedne (poza plansza)";
                    break;
                }
                else{
                    if(read_board[pos].bomb == 1) return 0;
                    read_board[pos].visible = 1;
                }
                break;
            }
        }
    }
    for(int j = 0; j < col*row; j++){
        if(read_board[j].bomb == 1){
             bombs_ctr++;
             continue;
        }
        if(read_board[j].flag == 1 || read_board[j].visible == 1) revealed_ctr++;
    }
    return col*row - bombs_ctr == revealed_ctr ? 1 : 2;
}