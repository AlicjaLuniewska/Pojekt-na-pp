#include <stdio.h>
#include "ui.h"
#include "creature.h"

       
     char* nazwa_gatunku(enum Gatunek g){

        switch(g){
            case SMOK:
            return "Smok";
            break;
            case GRYF:
            return "Gryf";
            break;
            case FENIKS: 
            return "Feniks";
            break;
            case PEGAZ:
            return "Pegaz";
            break;
            case MANTYKORA:
            return "Mantykora";
            break;
            default: 
            return "Nieznany";
        }
    }

    char* nazwa_statusu(enum Status s){

        switch(s){
        case STABILNY:
        return "Stabilny";
        break;
        case NIESPOKOJNY:
        return "Niespokojny";
        break;
        case AGRESYWNY:
        return "Agresywny";
        break;
        case NIEBEZPIECZNY:
        return "Niebezpieczny";
        break;
        case KWARANTANNA:
        return "Kwarantanna";
        break;
        default:
        return "Nieznnane";
        }
    }

//funkcja do wyświetlania listy
void wyswietl_liste(Stworzenie* glowa){
    Stworzenie* aktualne = glowa;
    int licznik = 0;

    if(aktualne == NULL){
        printf("W rajestrze nie ma zadnych stworzen\n");
        return;
    }

    printf("\n LISTA REZERWATU \n");

    while(aktualne != NULL){
        licznik++;

        char* gatunek_tekst = nazwa_gatunku(aktualne->gatunek);
        char* status_tekst = nazwa_statusu(aktualne->status);

        printf("%d. [%s] Imie: %-15s | Moc: %d | Poziom zagrozenia: %d | Data ostatniego karmienia: %s | Status: %s\n", licznik, gatunek_tekst, aktualne->imie, aktualne->moc_magiczna, aktualne->poziom_zagrozenia, aktualne->data_karmienia, status_tekst);

        aktualne = aktualne->next;
    }

    printf("Razem znaleziono: %d stworzen\n", licznik);
}
   


