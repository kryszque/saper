#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int option;
    if(argc > 2){
        fprintf(stderr, "Zle podano argument wywolania!!!");
        exit(EXIT_FAILURE);
    }
    while((option = getopt(argc, argv,"nf:")) != -1){
        switch(option){
            case('n'):
                printf("Wybrano tryb normalny\n");
                break;
            case('f'):
                printf("Wybrano tryb sczytywania z pliku z plikiem %s\n", optarg);
                break;
            default:
                fprintf(stderr, "Zle podano argument wywolania!!!");
                exit(EXIT_FAILURE);
                break;
        }
    }

    return 0;
}