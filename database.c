#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "ui.h"

//określanie statusu stworzenia na podstawie mocy i zagrożenia
Status sugerowanie_statusu(char* data_przyb, int moc, int zagrozenie){
    int rok_przybycia = atoi(data_przyb);
    Status wynik;
    if(rok_przybycia >= 2026){
        wynik = KWARANTANNA;
    } else if((zagrozenie > 10) || (moc > 80 && zagrozenie > 5)){
        wynik = NIEBEZPIECZNY;
    } else if((zagrozenie >= 6) || (moc > 70)){
        wynik = AGRESYWNY;
    } else if(zagrozenie >= 3 || (moc > 50)){
        wynik = NIESPOKOJNY;
    } else {
        wynik = STABILNY;
    }
    return wynik;
}

//dodawanie stworzen do listy
Stworzenie* dodaj_stworzenie(Stworzenie* glowa){
    char wprowadzane_imie[101];
    printf("Podaj imie stworzenia: \n");
    scanf("%100s", wprowadzane_imie);

    Stworzenie* temp = glowa;
    while(temp != NULL){
        if(strcmp(wprowadzane_imie, temp->imie) == 0){
            printf("Stowrzenie o imieniu %s już istnieje\n", wprowadzane_imie);
            return glowa;
        }
        temp = temp->next;
    }

    Stworzenie* nowy = (Stworzenie*)malloc(sizeof(Stworzenie));
    if(nowy == NULL){
        printf("Brak pamieci\n");
        return glowa;
    }

    strcpy(nowy->imie, wprowadzane_imie);

    printf("Podaj moc tego stworzenia: \n");
    scanf("%d", &nowy->moc_magiczna);
    if(nowy->moc_magiczna < 0){
        nowy->moc_magiczna = 0;
    }
    if(nowy->moc_magiczna > 100){
        nowy->moc_magiczna = 100;
    }

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
        printf("Podany gatunek nie widnieje w bazie. Przypisuje automatycznie NIEZINDENTYFIKOWANY\n");
        nowy->gatunek = NIEZIDENTYFIKOWANY;
    }

    int wyb_plci;
    printf("1 - Zenska\n");
    printf("2 - Meska\n");
    printf("3 - Niezindentyfikowano\n");
    printf("Wybierz plec stworzenia: ");
    scanf("%d", &wyb_plci);

    switch(wyb_plci){
        case 1:
        nowy->plec = ZENSKA;
        break;
        case 2:
        nowy->plec = MESKA;
        break;
        case 3:
        nowy->plec = NIEZIDENTYFIKOWANY;
        break;
        default:
        printf("Podana plec nie widnieje w bazie. Przypisuje automatycznie NIEZIDENTYFIKOWANY\n");
        nowy->plec = NIEZIDENTYFIKOWANE;
    }

    printf("Podaj poziom zagrozenia (sugerowany zakres: 0-10, powyzej niego status stworzenia automatycznie bedzie zapisany jako NIEBIEZPIECZNY): \n");
    scanf("%d", &nowy->poziom_zagrozenia);
    if(nowy->poziom_zagrozenia < 0){
        nowy->poziom_zagrozenia = 0;
    } else if(nowy->poziom_zagrozenia > 15){
        nowy->poziom_zagrozenia = 15;
    }

    printf("Podaj date przybycia (rrrr-mm-dd): \n");
    scanf("%10s", nowy->data_przybycia);

    printf("Podaj ostatnia date karmienia (rrrr-mm-dd): \n");
    scanf("%10s", nowy->data_karmienia);

    Status sugerowany = sugerowanie_statusu(nowy->data_przybycia, nowy->moc_magiczna, nowy->poziom_zagrozenia);

    printf("Na podstawie analizy podanych wyzej danych sugerowany status stowrzenia to: %s\n", nazwa_statusu(sugerowany));
    printf("Czy chcesz go zastosowac?\n");
    printf("1 - Tak\n");
    printf("2 - Nie, chce wybrac status recznie\n");
    int decyzja;
    scanf("%d", &decyzja);
    if(decyzja == 1){
        nowy->status = sugerowany;
    } else if(decyzja == 2){
    int wybor_statusu;
    printf("1 - Stabilny\n");
    printf("2 - Niespokojny\n");
    printf("3 - Agresywny\n");
    printf("4 - Niebezpieczny\n");
    printf("5 - Kwarantanna\n");
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
        printf("Nie ma takiej opcji, automaycznie przypisuje stan KWARANTANNA\n");
        nowy->status = KWARANTANNA;
    }
    } else{
        printf("Nie ma mozliwosci takiego wyboru/n");
    }
    nowy->next = glowa;

    return nowy;
}

// funkcja umożliwiająca edytowanie możliwych do tego danych
void edycja_stworzenia(Stworzenie* glowa, char* imie_szukane){
    Stworzenie* akt = glowa;
    Status nowa_sugestia;
    while(akt != NULL){
        if(strcmp(akt->imie, imie_szukane) == 0){
            printf("Edytowane stowrzenie: %s\n", akt->imie);
            printf("1 - Moc magiczna (aktualnie: %d)\n", akt->moc_magiczna);
            printf("2 - Poziom zgrozenia (aktualnie: %d)\n", akt->poziom_zagrozenia);
            printf("3 - Status (aktualnie: %d)\n", akt->status + 1);
            printf("4 - Data karmienia (ostania: %s)\n", akt->data_karmienia);
            printf("0 - Wyjscie\n");
            printf("Wybierz co konkretnie chcesz edytować: ");

            int wybor_edycji;
            scanf("%d", &wybor_edycji);
            switch(wybor_edycji){
                case 1:
                int m;
                printf("Podaj nowa moc: ");
                scanf("%d", &m);
                if(m < 0){
                    m = 0;
                } else if(m > 100){
                    m = 100;
                }
                akt->moc_magiczna = m;
                nowa_sugestia = sugerowanie_statusu(akt->data_przybycia, akt->moc_magiczna, akt->poziom_zagrozenia);
                printf("Zmieniono moc. Sugerowany nowy status to: %s\n", nazwa_statusu(nowa_sugestia));
                printf("Czy chcesz go zmienic?\n");
                printf("1 - Tak\n");
                printf("0 - Nie\n");
                int dec;
                scanf("%d", &dec);
                if(dec == 1){
                    akt->status = nowa_sugestia;
                }
                break;
                case 2:
                printf("Podaj nowy poziom zagrozenia (0-10): ");
                int p;
                scanf("%d", &p);
                if(p < 0){
                    p = 0;
                }
                if(p > 15){
                    p = 15;
                } 
                akt->poziom_zagrozenia = p;
                nowa_sugestia = sugerowanie_statusu(akt->data_przybycia, akt->moc_magiczna, akt->poziom_zagrozenia);
                printf("Zmieniono poziom zagrozenia. Sugerowany nowy status to: %s\n", nazwa_statusu(nowa_sugestia));
                printf("Czy chcesz go zmienic?\n");
                printf("1 - Tak\n");
                printf("0 - Nie\n");
                int d;
                scanf("%d", &d);
                if(d == 1){
                    akt->status = nowa_sugestia;
                }
                break;
                case 3:
                printf("1 - Stabilny\n");
                printf("2 - Niespokojny\n");
                printf("3 - Agresywny\n");
                printf("4 - Niebezpieczny\n");
                printf("5 - Kwarantanna\n");
                printf("Wybierz nowy status storzenia: \n");
                int s;
                scanf("%d", &s);
                akt->status = (Status)(s-1);
                break;
                case 4:
                printf("Podaj nowa date karmienia (rrrr-mm-dd): ");
                scanf("%10s", akt->data_karmienia);
                break;
                case 0:
                return;
                break;
                default:
                printf("Wybrales opcje, ktorej nie da sie edytowac\n");
                return;
            }
            return;
        }
        akt = akt->next;
    }
    printf("Nie znaleziono takiego stowrzenia jak: %s\n", imie_szukane);
}

//funkcja do szukania po gatunku
void szukanie_po_gatunku(Stworzenie* glowa, int szukany_gatunek){
    Stworzenie* aktualne = glowa;
    int znaleziono = 0;

    printf("LISTA WYSZYSTKICH STWORZEN\n");

    while(aktualne != NULL){
        if((int)aktualne->gatunek == (szukany_gatunek - 1)){
            char* tekst_gatunku = nazwa_gatunku(aktualne->gatunek);
            char* tekst_plci = nazwa_plci(aktualne->plec);
            char* tekst_status = nazwa_statusu(aktualne->status);
        printf("[%s, Plec: %s] Imie: %-15s | Moc: %d | Poziom zagrozenia: %d | Data przybycia: %s | Data karmienia: %s | Status: %s\n", tekst_gatunku, tekst_plci, aktualne->imie, aktualne->moc_magiczna, aktualne->poziom_zagrozenia, aktualne->data_przybycia, aktualne->data_karmienia, tekst_status);
        znaleziono = 1;
    }
    aktualne = aktualne->next;
}
if(!znaleziono){
    printf("Brak stworzen tego gatunku\n");
}
}

//funkcja do szukania po imieniu
void szukanie_po_imieniu(Stworzenie* glowa, char* szukane_imie) {
    Stworzenie* aktualne = glowa;
    int znaleziono = 0;

    while (aktualne != NULL) {
        if (strcmp(aktualne->imie, szukane_imie) == 0) {
            char* tekst_gatunku = nazwa_gatunku(aktualne->gatunek);
            printf("Imie: %s | Gatunek: %s\n", aktualne->imie, tekst_gatunku);
            printf("Moc: %d | Zagrozenie: %d\n", aktualne->moc_magiczna, aktualne->poziom_zagrozenia);
            printf("Status: %d | Ostatnie karmienie: %s\n", aktualne->status + 1, aktualne->data_karmienia);
            znaleziono = 1;
        }
        aktualne = aktualne->next;
    }

    if (!znaleziono) {
        printf("Nie znaleziono stworzenia o imieniu: %s\n", szukane_imie);
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
        if(strlen(aktualne->imie) > 0){
        fprintf(plik, "%s %d %d %d %d %s %s %d\n", aktualne->imie, aktualne->moc_magiczna, aktualne->gatunek, aktualne->plec, aktualne->poziom_zagrozenia,aktualne->data_przybycia, aktualne->data_karmienia, aktualne->status);
        }
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
    int moc, gat, sex, poz, stat;
    char data[11];
    char data_przyb[11];

    while(fscanf(plik, "%100s %d %d %d %d %10s %10s %d", imie, &moc, &gat, &sex, &poz, data_przyb, data, &stat) == 8){
        Stworzenie* nowy = (Stworzenie*)malloc(sizeof(Stworzenie));
        if(nowy != NULL){
            strcpy(nowy->imie, imie);
            nowy->moc_magiczna = moc;
            nowy->gatunek = (Gatunek)gat;
            nowy->plec = (Plec)sex;
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

//fukncja do ususnięcia całego gatunku (bez NIEBEZPIECZNY)
Stworzenie* usuwanie_calego_gatunku(Stworzenie* glowa, int gatunek_do_usuniecia){
    Stworzenie* akt = glowa;
    Stworzenie* poprzed = NULL;
    int licznik = 0;

    while(akt != NULL){
        if((int)akt->gatunek == (gatunek_do_usuniecia - 1)){
            if(akt->status == NIEBEZPIECZNY){
                printf("Nie można usunąć %s ze wzgledu na status NIEBEZPIECZNY\n", akt->imie);
                poprzed = akt;
                akt = akt->next;
                continue;
            }

            Stworzenie* do_usuniecia = akt;
            if(poprzed == NULL){
                glowa = akt->next;
                akt = glowa;
            } else{
                poprzed->next = akt->next;
                akt = poprzed->next;
            }
            free(do_usuniecia);
            licznik++;
        } else {
            poprzed = akt;
            akt = akt->next;
        }
    }
    printf("Usunieto zbiorowo %d stworzen\n", licznik);
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

                //według płci
                Plec temp_plec = ptr1->plec;
                ptr1->plec = ptr1->next->plec;
                ptr1->next->plec = temp_plec;

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

void zwolnij(Stworzenie* glowa){
    Stworzenie* temp;
    while(glowa != NULL){
        temp = glowa;
        glowa = glowa->next;
        free(temp);
    }
}