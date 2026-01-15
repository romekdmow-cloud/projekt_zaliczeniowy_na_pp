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

void edytujPost(Post* glowa, int id) {
    Post* iterator = glowa;
    while (iterator != NULL) {
        if (iterator->id == id) {
            printf("\n--- EDYCJA POSTA ID: %d ---\n", id);
            printf("Autor: %s\n", iterator->autor);
            printf("Obecna tresc: %s\n", iterator->tresc);
            printf("Obecny status: %s\n", statusDoTekstu(iterator->status));
                 //mini menu
            printf("\n C o chcesz zmienic? \n");
            printf("1. Tresc posta\n");
            printf("2. Status moderacji\n");
            printf("0. Anuluj\n");
            printf("Wybor: ");
            int wyborEdycji;
            if (scanf("%d", &wyborEdycji) != 1) {
                wyczyscBufor();
                return;
            }
            wyczyscBufor();
            switch (wyborEdycji) {
                case 1:
                    printf("Podaj nowa tresc: ");
                    wczytajTekst(iterator->tresc, MAX_TRESC);
                    printf("Tresc zaktualizowana.\n");
                    break;
                case 2:
                printf("Wybierz nowy status:\n");
                    printf("0 - Do weryfikacji\n");
                    printf("1 - W trakcie analizy\n");
                    printf("2 - Zatwierdzone\n");
                    printf("3 - Usuniete\n");
                    printf("Twoj wybor: ");

                    int nowyStatus;
                    if(scanf("%d", &nowyStatus) == 1) {
                        if (nowyStatus >= 0 && nowyStatus <= 3) {
                            iterator->status = (StatusPosta)nowyStatus;
                            printf("Status zmieniony na: %s\n", statusDoTekstu(iterator->status));
                        } else {
                            printf("Blad: Nieprawidłowy numer statusu.\n");
                        }
                    }
                    wyczyscBufor();
                    break;
                case 0:
                    printf("Anulowano edycje.\n");
                    break;
                default:
                    printf("Nieznana opcja.\n");
            }
            return;
            }
            iterator = iterator->nastepny;
        }
        printf("Nie znaleziono posta o ID: %d\n", id);
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
        printf("3. Usun post\n");
        printf("4. Edytuj Post\n");
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
            case 4:
                printf("\n----- EDYCJA POST A ------- \n");
                int idEdycja;
                printf("Podaj ID posta do edycji: ");
                if(scanf("%d", &idEdycja) == 1) {
                    edytujPost(bazaPostow, idEdycja);
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
