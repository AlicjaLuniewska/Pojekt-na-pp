#ifndef CREATURE_H
#define CREATURE_H

typedef enum  Status{
    STABILNY,
    NIESPOKOJNY,
    AGRESYWNY,
    NIEBEZPIECZNY,
    KWARANTANNA
} Status;

typedef enum Plec{
    ZENSKA,
    MESKA,
    NIEZIDENTYFIKOWANE 
}Plec;

typedef enum Gatunek{
    SMOK,
    GRYF,
    FENIKS,
    PEGAZ,
    MANTYKORA,
    NIEZIDENTYFIKOWANY
} Gatunek;

typedef struct Stworzenie {
    char imie[101];
    Gatunek gatunek;
    Plec plec;
    int moc_magiczna;
    int poziom_zagrozenia;
    char data_przybycia[11];
    char data_karmienia[11];
    Status status;

    struct Stworzenie *next;
} Stworzenie;

#endif
