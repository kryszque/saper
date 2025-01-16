#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "users.h"
#define file_name "tabela_wynikow.txt"

int main(int argc, char *argv[]){
    int option;
    char lev_choice;
    option = getopt(argc, argv,"nf:");
    char usr_name[20];

    printf("\n\n\t\t\t\t\tG R A  S A P E R\n\n\n");
    
    switch(option){ //!!!!Jesli wpisze -neee lub -fooo tez zadziala!!!!
        case('n'):
            if(argc > 2){
                fprintf(stderr, "Zle podano argument wywolania!!!");
                exit(EXIT_FAILURE);
            }
            else{ 
                printf("Wybierz poziom trudnosci (latwy - wpisz l, trudny wpisz -t, aby stworzyc wlasna plansze - wpisz w) ... ");
                scanf(" %c",&lev_choice);
                
                while(lev_choice != 'l' && lev_choice != 't' && lev_choice != 'w'){
                    printf("\nNiepoprawnie podany poziom trudnosci!!! Podaj ponownie...");
                    scanf(" %c",&lev_choice);
                }

                switch (lev_choice){
                    case('l'):
                        printf("poziom l");
                        break;
                    
                    case('t'):
                        printf("poziom t");
                        break;
                    
                    case('w'):
                        printf("poziom w");
                        break;
                }
                printf("\n\nPodaj swoja nazwe gracza...");
                scanf("%s",&usr_name); //!!!!sprawdzic czy usr_name jest valid!!!!
                add_usr(usr_name, "100", file_name);
                display_list(file_name); //!!!!musi jeszcze sortowac i wyswietlac top5!!!!
            }  
            break;

        case('f'):
                if(argc > 3){
                    fprintf(stderr, "Zle podano argument wywolania!!!");
                    exit(EXIT_FAILURE);
                }
            printf("Wybrano tryb sczytywania z pliku z plikiem %s\n", optarg);
            break;
        default:
            fprintf(stderr, "Zle podano argument wywolania!!!");
            exit(EXIT_FAILURE);
            break;
    }
    

    return 0;
}