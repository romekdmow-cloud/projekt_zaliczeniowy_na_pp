#ifndef POST_H
#define POST_H

#include <stdio.h> 

#define MAX_AUTOR 100
#define MAX_TRESC 280
#define MAX_KATEGORIA 30

typedef enum {
    DO_WERYFIKACJI, 
    W_TRAKCIE,
    ZATWIERDZONE, 
    USUNIETE
} StatusPosta;

typedef struct Post {
    int id;
    char autor[MAX_AUTOR];
    char tresc[MAX_TRESC];
    char kategoria[MAX_KATEGORIA];
    int liczba_zgloszen;
    StatusPosta status;
    struct Post* nastepny;
} Post;

void wyczyscBufor();
void wczytajTekst(char* bufor, int rozmiar);
const char* statusDoTekstu(StatusPosta s);

Post* stworzPost(int id, const char* autor, const char* tresc);
Post* dodajNaPoczatek(Post* aktualnaGlowa, int id, const char* autor, const char* tresc);
void wyswietlListe(Post* glowa);
Post* usunPost(Post* glowa, int idDoUsuniecia);
void edytujPost(Post* glowa, int id);
void wyszukajPoAutorze(Post* glowa, const char* szukanyFragment);
void filtrujPoZgloszeniach(Post* glowa, int minZgloszen);
void zapisz_baze(Post* glowa);
Post* wczytaj_baze();
Post* odtworz_post(Post* glowa, int id, char* autor, char* tresc, char* kat, int zgl, int stat);


#endif 