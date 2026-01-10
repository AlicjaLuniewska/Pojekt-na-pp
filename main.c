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
    printf("5 - Usun pernamentnie konkretne stworzenie\n");
    printf("6 - Posortuj liste\n");
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
          printf("1 - SMOK\n");
          printf("2 - GRYF\n");
          printf("3 - FENIKS\n");
          printf("4 - PEGAZ\n");
          printf("5 - MANTYKORA\n");
          printf("Gatunek do wyświetlenia: ");
          scanf("%d", &gat);
          szukanie_po_gatunku(lista_stworzen, gat);
        }
        break;
        case 5:
        char imie_usun[101];
        printf("Podaj imie stowrzenia do usuniecia: ");
        scanf("%s", imie_usun);
        lista_stworzen = usuwanie_stworzenia_prem(lista_stworzen, imie_usun);
        break;
        case 6:
        int zmien;
        printf("1 - Alfabetycznie\n");
        printf("2 - Wedlug poziomu mocy\n");
        printf("3 - Wedlug poziomu zagrozenia\n");
        printf("Wybierz w jaki sposob ma byc posortowana lista stowrzen: ");
        scanf("%d", &zmien);
        sortowanie_listy(lista_stworzen, zmien);
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