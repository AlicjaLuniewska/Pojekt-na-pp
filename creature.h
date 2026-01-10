#ifndef CREATURE_H
#define CREATURE_H

typedef enum  Status{
    STABILNY,
    NIESPOKOJNY,
    AGRESYWNY,
    NIEBEZPIECZNY,
    KWARANTANNA
} Status;

typedef enum Gatunek{
    SMOK,
    GRYF,
    FENIKS,
    PEGAZ,
    MANTYKORA
} Gatunek;

typedef struct Stworzenie {
    char imie[101];
    Gatunek gatunek;
    int moc_magiczna;
    int poziom_zagrozenia;
    char data_karmienia[11];
    Status status;

    struct Stworzenie *next;
} Stworzenie;

#endif
