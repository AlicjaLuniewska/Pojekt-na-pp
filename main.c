#include <stdio.h>
#include "creature.h"
#include "database.h"
#include "ui.h"

int main(){
    int wybor;
    Stworzenie *lista_stworzen = wczytywanie_z_pliku("bazastworzen.txt");

    // menu
    do{
    printf("1 - Dodaj stowrzenie\n");
    printf("2 - Wyswietl liste stworzen\n");
    printf("3 - Usun ostatnio dodane stworzenie\n");
    printf("4 - Wyszukaj...\n");
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
        case 3:
        lista_stworzen = usun_stworzenie(lista_stworzen);
        if(lista_stworzen != NULL || printf("W bazie nie ma zdanych stworzen\n")){
          printf("Usunieto stworzenie\n");
        }
        break;
        case 4:
        printf("1 - Szukaj po imieniu\n");
        printf("2 - Szukaj po gatunku\n");
        int wybor_szukania;
        scanf("%d", &wybor_szukania);

        if(wybor_szukania == 1){
          char imie_do_szukania[100];
          printf("Podaj imie do wyszukania: ");
          scanf("%s", imie_do_szukania);
          szukanie_po_imieniu(lista_stworzen, imie_do_szukania);
        }
        else if(wybor_szukania == 2){
          int gat;
          printf("Gatunek do wyświetlenia (1 - SMOK, 2 - GRYF, 3 - FENIKS, 4 - PEGAZ, 5 - MANTYKORA): ");
          scanf("%d", &gat);
          szukanie_po_gatunku(lista_stworzen, gat);
        }
        break;
        case 0:
        zapisywanie_do_pliku(lista_stworzen, "bazastworzen.txt");
        printf("Zamykanie programu...\n");
        break;
        default:
        printf("Nie ma takiej opcji\n");
        }
    } while(wybor != 0);
    return 0;
}