#include <stdio.h>
#include <stdlib.h>
#include "database.h"

Stworzenie* dodaj_stworzenie(Stworzenie* kolejne){
    Stworzenie* nowy = (Stworzenie*)malloc(sizeof(Stworzenie));

    if(nowy == NULL){
        printf("Brak pamięci\n");
        return kolejne;
    }
    printf("Podaj imie stworzenia: \n");
    scanf("%100s", nowy->imie);

    printf("Podaj moc tego stworzenia: \n");
    scanf("%d", &nowy->moc_magiczna);

    int wybor_gatunku;
    printf("1 - SMOK\n");
    printf("2 - GRYF\n");
    printf("3 - FENIKS\n");
    printf("4 - PEGAZ\n");
    printf("5 - MANTYKORA\n");
    printf("Wybierz jakiego gatunku jest to stworzenie: \n");

    scanf("%d", &wybor_gatunku);

    switch(wybor_gatunku){
        case 1:
        nowy->gatunek = SMOK;
        break;
        case 2:
        nowy->gatunek = GRYF;
        break;
        case 3:
        nowy->gatunek = FENIKS;
        break;
        case 4:
        nowy->gatunek = PEGAZ;
        break;
        case 5:
        nowy->gatunek = MANTYKORA;
        break;
        default:
        printf("Podany gatunek nie widnieje w bazie. Przypisuje automatycznie SMOK\n");
        nowy->gatunek = SMOK;
    }

    nowy->next = kolejne;

    return nowy;
}