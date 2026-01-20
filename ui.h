#ifndef UI_H
#define UI_H
#include "creature.h"

void wyswietl_liste(Stworzenie* glowa);

char* nazwa_gatunku(enum Gatunek g);

char* nazwa_plci(enum Plec p);

char* nazwa_statusu(enum Status s);

int sprawdzanie_wprowadzania();

#endif 
