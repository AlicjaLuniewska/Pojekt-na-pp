#include <stdio.h>
#include "creature.h"
#include "database.h"
#include "ui.h"

int main(){
    int wybor = -1;
    Stworzenie *lista_stworzen = NULL;

    // menu
    do{
    printf("1 - Dodaj stowrzenie\n");
    printf("2 - Wyswietl liste stworzen\n");
    printf("0 - Koniec programu\n");
    printf("Wybor: \n");

      scanf("%d", &wybor);
        
        switch(wybor){
        case 1:
        lista_stworzen = dodaj_stworzenie(lista_stworzen);
        printf("Dodano nowe stworzenie\n");
        break;
        case 2:
        wyswietl_liste(lista_stworzen);
        break;
        case 0:
        printf("Zamykanie programu...\n");
        return 0;
        default:
        printf("Nie ma takiej opcji\n");
        }
    } while(wybor != 0);
    return 0;
}