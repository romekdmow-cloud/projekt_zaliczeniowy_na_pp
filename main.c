#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

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

const char* statusDoTekstu(StatusPosta s) {
    switch (s) {
        case DO_WERYFIKACJI: return "Do weryfikacji";
        case W_TRAKCIE: return "W trakcie analizy";
        case ZATWIERDZONE: return "Zatwierdzone";
        case USUNIETE: return "Usuniete";
        default: return "Nieznany";
    }
}

Post* stworzPost(int id, const char* autor, const char* tresc) {
    Post* nowy = (Post*)malloc(sizeof(Post));
    if (nowy == NULL) {
        printf("Błąd, brak pamieci!\n");
        return NULL;
    }

nowy->id = id;
strcpy(nowy->autor, autor);
strcpy(nowy->tresc, tresc);
strcpy(nowy->kategoria, "ogolna"); 
nowy->liczba_zgloszen = 0;
nowy->status = DO_WERYFIKACJI;
nowy->nastepny = NULL;

return nowy;
}

Post* dodajNaPoczatek(Post* aktualnaGlowa, int id, const char* autor, const char* tresc) {
    Post* nowy = stworzPost(id, autor, tresc);
    if (nowy == NULL) return aktualnaGlowa;
    nowy->nastepny = aktualnaGlowa;
    return nowy;
}

void wyswietlListe(Post* glowa) {
    printf("\n--- LISTA POSTOW ---\n");
    Post* iterator = glowa;
    while (iterator != NULL) {
        printf("ID: %d | Autor: %s | Tresc: %s\n", iterator->id, iterator->autor, iterator->tresc);    
        iterator = iterator->nastepny;
    }
    printf("--------------\n");
}

int main() {
    Post* bazaPostow = NULL;

    bazaPostow = dodajNaPoczatek(bazaPostow, 1, "Basia", "Elo, to muj 1wszy pej");
    bazaPostow = dodajNaPoczatek(bazaPostow, 2, "Wacław", "Siemanko, witam grono odbiorcuf");
    bazaPostow = dodajNaPoczatek(bazaPostow, 3, "ADMIN", "Gorąco Witamy na Platformie QuickTalk!");

    wyswietlListe(bazaPostow);

    Post* doUsuniecia;
    while (bazaPostow != NULL) {
        doUsuniecia = bazaPostow;
        bazaPostow = bazaPostow->nastepny;
        free(doUsuniecia);
    }
    printf("Pamiec wyczyszczona. \n");
    return 0;
}