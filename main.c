#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "users.h"
#include "file_mode.h"
#define file_name "tabela_wynikow.txt"

int main(int argc, char *argv[]){
    int option;
    int lev_choice;
    option = getopt(argc, argv,"nf:");
    char usr_name[20];
    char *score;

    printf("\n\n\t\t\t\t\tG R A  S A P E R\n\n\n");
    
    switch(option){ //!!!!Jesli wpisze -neee lub -fooo tez zadziala!!!!
        case('n'):
            if(argc > 2){
                fprintf(stderr, "Zle podano argument wywolania!!!\n\n");
                exit(EXIT_FAILURE);
            }
            else{ 
                printf("Wybierz poziom trudnosci (latwy - wpisz 1, sredni - wpisz 2, trudny - wpisz 3, aby stworzyc wlasna plansze - wpisz 4) ... ");
                scanf(" %d",&lev_choice);
                
                while(lev_choice != 1 && lev_choice != 2 && lev_choice != 3 && lev_choice != 4){
                    printf("\n\nNiepoprawnie podany poziom trudnosci!!! Podaj ponownie...");
                    scanf(" %d",&lev_choice);
                }

                switch (lev_choice){
                    case(1):
                        printf("\nWybrano poziom latwy");
                        break;
                    
                    case(2):
                        printf("\nWybrano poziom sredni");
                        break;
                    
                    case(3):
                        printf("\nWybrano poziom trudny");
                        break;
                    case(4):
                        printf("\nWybrano poziom wlasny");
                        break;
                }
                printf("\n\nPodaj swoja nazwe gracza...");
                scanf("%s",usr_name); //!!!!sprawdzic czy usr_name jest valid!!!!
                printf("Podaj wynik gracza...");
                scanf("%s",score);
                add_usr(usr_name, score, file_name);
                printf("\n\nTOP 5: \n\n");
                display_list(file_name);
            }  
            break;

        case('f'):
                if(argc > 3){
                    fprintf(stderr, "Zle podano argument wywolania!!!");
                    exit(EXIT_FAILURE);
                }
            printf("Wybrano tryb sczytywania z pliku z plikiem %s\n\n", optarg);
            
            FILE *in = fopen(optarg, "r");
            if(!in){
                fprintf(stderr, "Otwieranie pliku nie powiodlo sie!!!\n\n");
                exit(EXIT_FAILURE);
            }
            
            int row = 0;
            int col = 0;
            int moves_ctr = 0;
            Cell *r_board = read_board(in, &row, &col);
            printf("\n\nWycztana plansza:\n\n");
            print_read_board(r_board, row, col);
            Move * r_moves = read_moves(in, &moves_ctr);
            int result = solve(r_board, r_moves, row, col, moves_ctr);
            switch(result){
                case(0):
                    printf("\nWczytane ruchy:\n\n");
                    print_read_moves(r_moves, moves_ctr);
                    printf("\nOdkrywaja bombe (INT BOOM) - GRA PRZEGRANA :(\n\n");
                    break;
                case(1):
                    printf("\nWczytane ruchy:\n\n");
                    print_read_moves(r_moves, moves_ctr);
                    printf("\nOdkrywaja wszystkie pola bez bomb i nie odkrywaja bomby - GRA WYGRANA :)\n\n");
                    break;
                case(2):
                    printf("\nWczytane ruchy:\n\n");
                    print_read_moves(r_moves, moves_ctr);
                    printf("\nNie odkrywaja bomby, ale nie rownoczesnie nie odkrywaja wszystkich pol bez bomb - GRA NIEROZSTRZYGNIETA :/\n\n");
                    break;
            }
            free(r_board);
            free_read_moves(r_moves, moves_ctr);
            break;
        
        default:
            fprintf(stderr, "Zle podano argument wywolania!!!");
            exit(EXIT_FAILURE);
            break;
    }
    

    return 0;
}