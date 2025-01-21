#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "users.h"
#include "board.h"
#define file_name "tabela_wynikow.txt"

#define EASY_ROW 9
#define EASY_COL 9
#define EASY_B_NUM 10
#define MED_ROW 16
#define MED_COL 16
#define MED_B_NUM 40
#define HARD_ROW 16
#define HARD_COL 30
#define HARD_B_NUM 99



int main(int argc, char *argv[]){
    int option;
    int lev_choice;
    Cell *saper;
    option = getopt(argc, argv,"nf:");
    char usr_name[20];
    char *score;

    printf("\n\n\t\t\t\t\tG R A  S A P E R\n\n\n");
    
    switch(option){ //!!!!Jesli wpisze -neee lub -fooo tez zadziala!!!!
        case('n'):
            if(argc > 2){
                fprintf(stderr, "Zle podano argument wywolania!!!");
                exit(EXIT_FAILURE);
            }
            else{ 
                printf("Wybierz poziom trudnosci (latwy - wpisz 1, sredni - wpisz 2, trudny - wpisz 3, aby stworzyc wlasna plansze - wpisz 4) ... ");
                scanf(" %d",&lev_choice);
                
                while(lev_choice != 1 && lev_choice != 2 && lev_choice != 3 && lev_choice != 4){
                    printf("\nNiepoprawnie podany poziom trudnosci!!! Podaj ponownie...");
                    scanf(" %d",&lev_choice);
                }

                switch (lev_choice){
                    case(1):
                        saper = create_board(EASY_ROW, EASY_COL);
                        initialize_board(saper, EASY_ROW, EASY_COL);
                        generate_bombs(saper, EASY_B_NUM, EASY_ROW, EASY_COL);
                        check_for_bombs(saper, EASY_ROW, EASY_COL);
                        print_board(saper, EASY_ROW, EASY_COL);
                        break;
                    
                    case(2):
                        saper = create_board(MED_ROW, MED_COL);
                        initialize_board(saper, MED_ROW, MED_COL);
                        generate_bombs(saper, MED_B_NUM, MED_ROW, MED_COL);
                        check_for_bombs(saper, MED_ROW, MED_COL);
                        print_board(saper, MED_ROW, MED_COL);
                        break;
                    
                    case(3):
                        saper = create_board(HARD_ROW, HARD_COL);
                        initialize_board(saper, HARD_ROW, HARD_COL);
                        generate_bombs(saper, HARD_B_NUM, HARD_ROW, HARD_COL);
                        check_for_bombs(saper, HARD_ROW, HARD_COL);
                        print_board(saper, HARD_ROW, HARD_COL);
                        break;
                    case(4):
                        printf("poziom wlasny");
                        break;
                }
                printf("\n\nPodaj swoja nazwe gracza...");
                scanf("%s",usr_name); //!!!!sprawdzic czy usr_name jest valid!!!!
                printf("\n\nPodaj wynik gracza...");
                scanf("%s",score);
                add_usr(usr_name, score, file_name);
                display_list(file_name);
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
