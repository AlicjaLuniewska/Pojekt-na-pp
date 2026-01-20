#ifndef DATABASE_H
#define DATABASE_H
#include "creature.h"

Status sugerowanie_statusu(char* data_przyb, int moc, int zagrozenie);

Stworzenie* dodaj_stworzenie(Stworzenie* kolejne);

void edycja_stworzenia(Stworzenie* glowa, char* imie_szukane);

void szukanie_po_imieniu(Stworzenie* glowa, char* szukane_imie);

void szukanie_po_gatunku(Stworzenie* glowa, int szukany_gatunek);

void zapisywanie_do_pliku(Stworzenie* glowa, const char* nazwa_pliku);
Stworzenie* wczytywanie_z_pliku(const char* nazwa_pliku);

Stworzenie* usuwanie_stworzenia_prem(Stworzenie* glowa, char* imie_do_usuniecia);

Stworzenie* usuwanie_calego_gatunku(Stworzenie* glowa, int gatunek_do_usuniecia);

void sortowanie_listy(Stworzenie* glowa, int tryb);

void zwolnij(Stworzenie* glowa);
#endif