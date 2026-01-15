#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

#define MAX_AUTOR 100
#define MAX_TRESC 280
#define MAX_KATEGORIA 30

void wyczyscBufor() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void wczytajTekst(char* bufor, int rozmiar) {
    if (fgets(bufor, rozmiar, stdin) != NULL) {
        bufor[strcspn(bufor, "\n")] = 0;
    }
}
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
nowy->status = ZATWIERDZONE;
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

Post* usunPost(Post* glowa, int idDoUsuniecia) {
    if (glowa == NULL) {
        printf("Lista jest pusta, nic nie usunieto;.\n");
        return NULL;
    }
    if (glowa->id ==idDoUsuniecia) {
        if (glowa ->status == DO_WERYFIKACJI) {
            printf("[BLAD] Nie mozna usunac posta przed weryfikacja!\n");
            return glowa;
        }
    Post* nowaGlowa = glowa->nastepny;
    free(glowa);
    printf("Usunieto post ID: %d\n", idDoUsuniecia);
    return nowaGlowa;
}
    Post* iterator = glowa;
    while (iterator->nastepny != NULL) {
        if (iterator->nastepny->id == idDoUsuniecia) {
            Post* doUsuniecia = iterator->nastepny;

            if (doUsuniecia->status == DO_WERYFIKACJI) {
                printf("[BLAD] Nie można usunac posta przed weryfikacja!\n");
                return glowa;
            }
            iterator->nastepny = doUsuniecia->nastepny;
            free(doUsuniecia);
            printf("Usunieto post ID: %d\n", idDoUsuniecia);
            return glowa; 
        }
        iterator = iterator->nastepny;
    }
    printf("Nie znaleziono posta o ID: %d\n", idDoUsuniecia);
    return glowa;
}

int main() {
    Post* bazaPostow = NULL;
    int wybor = -1;
    int licznikId = 1;
    
    char tempAutor[MAX_AUTOR];
    char tempTresc[MAX_TRESC];

    printf("Witaj w QuickTalk Manager v1.0\n");

    do {
        printf("\n--- MENU GLOWNE ---\n");
        printf("1. Dodaj nowy post\n");
        printf("2. Wyswietl wszystkie posty\n");
        printf("3. Usun post (wg ID)\n");
        printf("0. Wyjdz\n");
        printf("Twoj wybor: ");
        
        if (scanf("%d", &wybor) != 1) {
            printf("Blad! To nie jest liczba.\n");
            wyczyscBufor();
            continue;
        }
        wyczyscBufor(); 

        switch (wybor) {
            case 1:
                printf("\n--- DODAWANIE POSTA ---\n");
                
                printf("Podaj autora: ");
                wczytajTekst(tempAutor, MAX_AUTOR);
                
                printf("Podaj tresc: ");
                wczytajTekst(tempTresc, MAX_TRESC);
                
                bazaPostow = dodajNaPoczatek(bazaPostow, licznikId, tempAutor, tempTresc);
                
                printf("Sukces! Dodano post ID: %d\n", licznikId);
                licznikId++;
                break;
            case 2:
                if (bazaPostow == NULL) {
                    printf("\n[INFO] Baza jest pusta.\n");
                } else {
                    wyswietlListe(bazaPostow);
                }
                break;

            case 0:
                printf("Zamykanie programu...\n");
                break;
            case 3:
                printf("\n----- USUWANIE POSTA ------\n");
                int idKasowane;
                printf("Podaj ID posta do usuniecia: ");
                if(scanf("%d", &idKasowane) == 1) {
                    bazaPostow = usunPost(bazaPostow, idKasowane);
                } else {
                    printf("Blad: ID musi byc liczba.\n");
                }
                wyczyscBufor();
                break;
            default:
                printf("Nieznana opcja. Sprobuj ponownie.\n");
        }
    } while (wybor != 0);
    Post* doUsuniecia;
    while (bazaPostow != NULL) {
        doUsuniecia = bazaPostow;
        bazaPostow = bazaPostow->nastepny;
        free(doUsuniecia);
    }
    printf("Pamiec wyczyszczona. \n");
    return 0;
}
