#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "ui.h"

//dodawanie stworzen do listy
Stworzenie* dodaj_stworzenie(Stworzenie* glowa){
    Stworzenie* nowy = (Stworzenie*)malloc(sizeof(Stworzenie));

    if(nowy == NULL){
        printf("Brak pamięci\n");
        return glowa;
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

    printf("Podaj poziom zagrozenia: \n");
    scanf("%d", &nowy->poziom_zagrozenia);

    printf("Podaj date przybycia: \n");
    scanf("%10s", nowy->data_przybycia);

    printf("Podaj ostatnia date karmienia: \n");
    scanf("%10s", nowy->data_karmienia);

    int wybor_statusu;
    printf("1 - Stabilny\n");
    printf("2 - Niespokojny\n");
    printf("3 - Agresywny\n");
    printf("4 - Niebezpieczny\n");
    printf("5 - Kwarantanna");
    printf("Wybierz status storzenia: \n");

    scanf(" %d", &wybor_statusu);

    switch(wybor_statusu){
        case 1:
        nowy->status = STABILNY;
        break;
        case 2:
        nowy->status = NIESPOKOJNY;
        break;
        case 3:
        nowy->status = AGRESYWNY;
        break;
        case 4:
        nowy->status = NIEBEZPIECZNY;
        break;
        case 5:
        nowy->status = KWARANTANNA;
        break;
        default:
        printf("Nie ma takiej opcji, automaycznie przypisuje stan STABILNY\n");
        nowy->status = STABILNY;
    }

    nowy->next = glowa;

    return nowy;
}

// usuwanie ostatniego stworzenia z listy
Stworzenie* usun_stworzenie(Stworzenie* glowa){
    if (glowa == NULL){
        printf("Nie ma zadnych stworzen w bazie\n");
        return NULL;
    }
    Stworzenie* temp = glowa;
    glowa = glowa->next;
    free(temp);
    return glowa;
}

//funkcja do szukania po imieniu stworzenia
void szukanie_po_imieniu(Stworzenie* glowa, char* szukane_imie){
    Stworzenie* aktualne = glowa;
    int znaleziono = 0;

    while(aktualne != NULL){
        if(strcmp(aktualne->imie, szukane_imie) == 0){
            printf("Znaleziono: %s | Moc: %d\n", aktualne->imie, aktualne->moc_magiczna);
            znaleziono = 1;
        }
        aktualne = aktualne->next;
    }

    if(!znaleziono){
        printf("Nie ma w bazie stworzenia o takim imieniu\n", szukane_imie);
    }
}

//funkcja do szukania po gatunku
void szukanie_po_gatunku(Stworzenie* glowa, int szukany_gatunek){
    Stworzenie* aktualne = glowa;
    int znaleziono = 0;

    printf("LISTA WYSZYSTKICH STWORZEN\n");

    while(aktualne != NULL){
        if((int)aktualne->gatunek == (szukany_gatunek - 1)){
            char* tekst_gatunku = nazwa_gatunku(aktualne->gatunek);
        printf("[%s] Imie: %-15s | Moc: %d\n", tekst_gatunku, aktualne->imie, aktualne->moc_magiczna);
        znaleziono = 1;
    }
    aktualne = aktualne->next;
}
if(!znaleziono){
    printf("Brak stworzen tego gatunku\n");
}
}

//funkcje do wczytywania i zapisywania w pliku
void zapisywanie_do_pliku(Stworzenie* glowa, const char* nazwa_pliku){
    FILE* plik = fopen(nazwa_pliku, "w");
    if(plik == NULL){
        printf("Blad otwarcia pliku do zapisy\n");
        return;
    }

    Stworzenie* aktualne = glowa;
    while(aktualne != NULL){
        fprintf(plik, "%s %d %d %d %s %s %d\n", aktualne->imie, aktualne->moc_magiczna, aktualne->gatunek, aktualne->poziom_zagrozenia,aktualne->data_przybycia, aktualne->data_karmienia, aktualne->status);
        aktualne = aktualne->next;
    }

    fclose(plik);
    printf("Zapisano do pliku: %s\n", nazwa_pliku);
}

Stworzenie* wczytywanie_z_pliku(const char* nazwa_pliku){
    FILE* plik = fopen(nazwa_pliku, "r");
    if(plik == NULL){
        printf("Nie znaleziono niczego. Rozpoczynanie z pusta lista\n");
        return NULL;
    }

    Stworzenie* nowa_glowa = NULL;
    char imie[101];
    int moc, gat, poz, stat;
    char data[11];
    char data_przyb[11];

    while(fscanf(plik, "%100s %d %d %d %10s %10s %d", imie, &moc, &gat, &poz, data_przyb, data, &stat) == 7){
        Stworzenie* nowy = (Stworzenie*)malloc(sizeof(Stworzenie));
        if(nowy != NULL){
            strcpy(nowy->imie, imie);
            nowy->moc_magiczna = moc;
            nowy->gatunek = (Gatunek)gat;
            nowy->poziom_zagrozenia = poz;
            strcpy(nowy->data_przybycia, data_przyb);
            strcpy(nowy->data_karmienia, data);
            nowy->status = (Status)stat;

            nowy->next = nowa_glowa;
            nowa_glowa = nowy;
        }
    }

    fclose(plik);
    printf("Dane zostaly wczytane\n");
    return nowa_glowa;
}

//usuwanie z niemożliwością usunięcia niebezpiecznego
Stworzenie* usuwanie_stworzenia_prem(Stworzenie* glowa, char* imie_do_usuniecia){
    if(glowa == NULL){
        printf("Lista jest pusta\n");
        return NULL;
    }

    Stworzenie *aktualne = glowa;
    Stworzenie *poprzednie = NULL;

    while(aktualne != NULL){
        if(strcmp(aktualne->imie, imie_do_usuniecia) == 0){

            if(aktualne->status == NIEBEZPIECZNY){
                printf("NIE MOZNA USUNAC STWORZENIA: %s\n", imie_do_usuniecia);
                printf("Procedury bezpieczenstwa zabraniaja usuniecia stowrzenia o statusie NIEBEZPIECZNY\n");
                return glowa;
            }

            if(poprzednie == NULL){
                glowa = aktualne->next;
            }else{
                poprzednie->next = aktualne->next;
            }

            free(aktualne);
            printf("Stworzenie %s zostalo pomysnie usuniete z systemu\n", imie_do_usuniecia);
            return glowa;
        }

        poprzednie = aktualne;
        aktualne = aktualne->next;
    }

    printf("Nie znaleziono stowrzenia o imieniu: %s\n", imie_do_usuniecia);
    return glowa;
}

//wszelakie sortowanie (do wyboru użytkownika)
void sortowanie_listy(Stworzenie* glowa, int tryb){
    if(glowa == NULL) return;

    int zamiana;
    Stworzenie* ptr1;
    Stworzenie* lptr = NULL;

    do{
        zamiana = 0;
        ptr1 = glowa;

        while(ptr1->next != lptr){
            int warunek = 0;
            if(tryb == 1){
                warunek = strcmp(ptr1->imie, ptr1->next->imie) > 0;
            } else if(tryb == 2){
                warunek = ptr1->moc_magiczna > ptr1->next->moc_magiczna;
            } else if(tryb == 3){
                warunek = ptr1->poziom_zagrozenia > ptr1->next->poziom_zagrozenia;
            }

            if(warunek){
                //sortowanie według imion
                char temp_imie[101];
                strcpy(temp_imie, ptr1->imie);
                strcpy(ptr1->imie, ptr1->next->imie);
                strcpy(ptr1->next->imie, temp_imie);

                //według mocy
                int temp_moc = ptr1->moc_magiczna;
                ptr1->moc_magiczna = ptr1->next->moc_magiczna;
                ptr1->next->moc_magiczna = temp_moc;

                //według gatunku
                Gatunek temp_gatunek = ptr1->gatunek;
                ptr1->gatunek = ptr1->next->gatunek;
                ptr1->next->gatunek = temp_gatunek;

                //wedlug zagrożenia
                int temp_zagrozenie = ptr1->poziom_zagrozenia;
                ptr1->poziom_zagrozenia = ptr1->next->poziom_zagrozenia;
                ptr1->next->poziom_zagrozenia = temp_zagrozenie;

                //według statusu
                Status temp_status = ptr1->status;
                ptr1->status = ptr1->next->status;
                ptr1->next->status = temp_status;

                //według daty karmienia
                char temp_data[11];
                strcpy(temp_data, ptr1->data_karmienia);
                strcpy(ptr1->data_karmienia, ptr1->next->data_karmienia);
                strcpy(ptr1->next->data_karmienia, temp_data);

                //według daty przybycia
                char temp_data_przyb[11];
                strcpy(temp_data_przyb, ptr1->data_przybycia);
                strcpy(ptr1->data_przybycia, ptr1->next->data_przybycia);
                strcpy(ptr1->next->data_przybycia, temp_data_przyb);

                zamiana = 1;
            }

            ptr1 = ptr1->next;
        }

        lptr = ptr1;
    }while(zamiana);

    printf("Lista została posortowana\n");
}