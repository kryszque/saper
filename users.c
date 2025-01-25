#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strndup(const char *s, size_t n) {
    size_t len = strnlen(s, n);
    char *new_str = (char *)malloc(len + 1);
    if (!new_str) {
        return NULL;
    }
    strncpy(new_str, s, len);
    new_str[len] = '\0';
    return new_str;
}

int compare(const void *a, const void *b){
    const user *user_a = *(const user **)a;
    const user *user_b = *(const user **)b;
    int score_a = atoi(user_a->score);
    int score_b = atoi(user_b->score);
    return score_b - score_a;
}

user **create_user_list(){
    user **user_list = (user**)malloc(5*sizeof(user*));
    if(!user_list){
        for(int i = 0; i < 5; i++){
            free(user_list[i]);
        }
        free(user_list);
        fprintf(stderr,"Nieudana alokacja pamieci dla user_list!!!");
        exit(EXIT_FAILURE);
    }
    return user_list;
}

void add_usr(char *usr_name, char* score, char *file_name){
    FILE *file = fopen(file_name, "a");
    if(!file){
        fprintf(stderr, "Nieudane otwieranie pliku podczas wpisywania wynikow!!!");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "gracz:%s      wynik:%s\n", usr_name, score);
    fclose(file);
}

void display_list(char *file_name){
    unsigned int ctr = 0;
    char *user_name;
    char *score;
    int *n_score;
    user **user_list = create_user_list();
    char linia[100];
    FILE *file = fopen(file_name, "r");
    if(!file){
        fprintf(stderr, "Nieudane otwieranie pliku podczas odczytywania wynikow!!!");
        exit(EXIT_FAILURE);
    }

    while(fgets(linia, 100, file) != NULL){
        
        if(ctr%5 == 0) user_list = (user**)realloc(user_list, sizeof(user*)*(ctr+5));
        if(!user_list){
            for(int i = 0; i < ctr; i++){
                free(user_list[i]);
            }
            free(user_list);
            fprintf(stderr, "Niepoprawnie realokowana pamiec dla user_list");
            exit(EXIT_FAILURE);
        }

        user *new_user = (user*)malloc(sizeof(user));
        if(!new_user){
            fprintf(stderr,"Nieudana alokacja pamieci dla new_user!!!");
            free(new_user);
            for(int i = 0; i < ctr; i++){
                free(user_list[i]);
            }
            free(user_list);
            fclose(file);
            exit(EXIT_FAILURE);
        }
        user_name = strtok(linia,"      ");
        score = strtok(NULL,"      ");
        score = &score[6];
        new_user->user_name = strndup(user_name, strlen(user_name));
        new_user->score = strndup(score, strlen(score));
        user_list[ctr++] = new_user;
    }
    
    qsort(user_list, ctr, sizeof(user*), compare);
    
    ctr = (ctr > 5)? 5 : ctr;

    for(unsigned int i = 0; i < ctr; i++){
        printf("%s    %s",user_list[i]->user_name, user_list[i]->score);
    }

    fclose(file);
}