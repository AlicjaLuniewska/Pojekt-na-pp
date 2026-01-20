#include <stdio.h>
#include <string.h>
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
    printf("3 - Edytuj wybrane dane stowrzenia\n");
    printf("4 - Wyszukaj...\n");
    printf("5 - Usun pernamentnie konkretne stworzenie\n");
    printf("6 - Posortuj liste\n");
    printf("0 - Koniec programu\n");
    printf("Wybor: \n");
      wybor = sprawdzanie_wprowadzania();
        
        switch(wybor){
          //opcja dodająca stowrzenie
        case 1:
        lista_stworzen = dodaj_stworzenie(lista_stworzen);
        printf("Dodano nowe stworzenie\n");
        break;
        // samo wyświetlanie listy
        case 2:
        wyswietl_liste(lista_stworzen);
        break;
        // opcja do edycji
        case 3:
        char found_name[101];
        printf("Podaj imie stworzenia do edycji: ");
        scanf("%100s", found_name);
        edycja_stworzenia(lista_stworzen, found_name);
        break;
        // wyszukiwarka
        case 4:
        printf("1 - Szukaj po imieniu\n");
        printf("2 - Szukaj po gatunku\n");
        int wybor_szukania;
        wybor_szukania = sprawdzanie_wprowadzania();

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
          gat = sprawdzanie_wprowadzania();
          szukanie_po_gatunku(lista_stworzen, gat);
        }
        break;
        case 5:
        printf("Podaj haslo administratora: ");
        char haslo[20];
        scanf("%s", haslo);
        if(strcmp(haslo, "admin123") == 0){
        printf("1 - Usun pojedyncze stworzenie\n");
        printf("2 - Usun wszystkie stworzenia danego gatunku\n");
        int wyb_us;
        wyb_us = sprawdzanie_wprowadzania();

        if(wyb_us == 1){
        char imie_usun[101];
        printf("Podaj imie stowrzenia do usuniecia: ");
        scanf("%s", imie_usun);
        lista_stworzen = usuwanie_stworzenia_prem(lista_stworzen, imie_usun);
        } else if(wyb_us == 2){
          int g;
          printf("1 - SMOK\n");
          printf("2 - GRYF\n");
          printf("3 - FENIKS\n");
          printf("4 - PEGAZ\n");
          printf("5 - MANTYKORA\n");
          printf("Wybierz gatunek do usuniecia: ");
          g = sprawdzanie_wprowadzania();
          lista_stworzen = usuwanie_calego_gatunku(lista_stworzen, g);
        } else{
          printf("Brak dostępu\n");
        }
        }
        break;
        case 6:
        int zmien;
        printf("1 - Alfabetycznie\n");
        printf("2 - Wedlug poziomu mocy\n");
        printf("3 - Wedlug poziomu zagrozenia\n");
        printf("Wybierz w jaki sposob ma byc posortowana lista stowrzen: ");
        zmien = sprawdzanie_wprowadzania();
        sortowanie_listy(lista_stworzen, zmien);
        break;
        case 0:
        zapisywanie_do_pliku(lista_stworzen, "bazastworzen.txt");
        zwolnij(lista_stworzen);
        printf("Zamykanie programu...\n");
        break;
        default:
        printf("Nie ma takiej opcji\n");
        }
    } while(wybor != 0);
    return 0;
}