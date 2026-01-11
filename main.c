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
        deafult: return "Nieznany";
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

int main() {
    printf("System Moderacji QuickTalk\n");
    Post* p1 = stworzPost(1, "IncognitoZiomuś007", "alee słoodki kootek!");
    Post* p2 = stworzPost(2, "Hejter", "nienawidze cie grubasie");
    
    if (p1 != NULL) {
        printf("\nPost ID: %d\nAutor: %s\nTresc: %s\nStatus: %s\n", p1->id, p1->autor, p1->tresc, statusDoTekstu(p1->status));    
    }

    if (p1 != NULL) {
        printf("\nPost ID: %d\nAutor: %s\nTresc; %s\nStatus: %s\n", p2->id, p2->autor, p2->tresc, statusDoTekstu(p2->status));
    }
    free(p1);
    free(p2);
    printf("\nPamiec wyczyszczona --- Koniec Programu. \n");
    
    return 0;
}