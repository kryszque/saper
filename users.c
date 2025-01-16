#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_usr(char *usr_name, char* score, char *file_name){
    FILE *file = fopen(file_name, "a");
    fprintf(file, "gracz: %s      wynik:%s\n", usr_name, score);
    fclose(file);
}

void display_list(char *file_name){
    unsigned int ctr = 0;
    //!!!!zrobic struct user gdzie bedzie nazwa usera i jego wynik zmiast dwoch tablic!!!!
    char **usrs = (char**)malloc(100); // 5 userow kazde imie co najwyzej 20 znakow
    char **scores = (char**)malloc(30); //5 x chyba wiecej niz milion nie bedzie dalo sie uzyskac/jesli liczba int zostanie zapisana do pliku odczytywana jest pozniej jako string
    char linia[24];
    FILE *file = fopen(file_name, "r");
    while(fgets(linia, 24, file) != NULL){
        printf("%s", linia);
        usrs[ctr] = strtok(linia,"      ");
        scores[ctr] = strtok(NULL,"      ");
    }
    fclose(file);
    for(int i = 0; i < ctr; i++){
        printf("%s      %s",usrs[i], scores[i]);
    }
}