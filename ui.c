#include <stdio.h>
#include "ui.h"
#include "creature.h"

void wyswietl_liste(Stworzenie* kolejne){
    Stworzenie* aktualne = kolejne;
    int licznik = 0;

    if(aktualne == NULL){
        printf("W rejestrze nie ma zadnych stworzen\n");
        return;
    }

    while(aktualne != NULL){
        licznik++;
        printf("Imie: %-15s | Moc: %d\n", aktualne->imie, aktualne->moc_magiczna);
        aktualne = aktualne->next;
    }
    printf("Razem znaleziono: %d stworzen.\n", licznik);
}
