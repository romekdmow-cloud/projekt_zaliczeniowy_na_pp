#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "post.h" 

void wyczyscBufor() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void wczytajTekst(char* bufor, int rozmiar) {
    if (fgets(bufor, rozmiar, stdin) != NULL) {
        bufor[strcspn(bufor, "\n")] = 0;
    }
}

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
        printf("Blad, brak pamieci!\n");
        return NULL;
    }
    nowy->id = id;
    strcpy(nowy->autor, autor);
    strcpy(nowy->tresc, tresc);
    strcpy(nowy->kategoria, "ogolna"); 
    nowy->liczba_zgloszen = 0;
    nowy->status = DO_WERYFIKACJI;
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
        printf("ID: %d | Autor: %s | Tresc: %s | Status: %s\n", 
               iterator->id, iterator->autor, iterator->tresc, statusDoTekstu(iterator->status));    
        iterator = iterator->nastepny;
    }
    printf("--------------\n");
}

Post* usunPost(Post* glowa, int idDoUsuniecia) {
    if (glowa == NULL) {
        printf("Lista jest pusta, nic nie usunieto.\n");
        return NULL;
    }
    if (glowa->id == idDoUsuniecia) {
        if (glowa->status == DO_WERYFIKACJI) {
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
                printf("[BLAD] Nie mozna usunac posta przed weryfikacja!\n");
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
            printf("\nCo chcesz zmienic?\n");
            printf("1. Tresc posta\n");
            printf("2. Status moderacji\n");
            printf("0. Anuluj\n");
            printf("Wybor: ");
            
            int wyborEdycji;
            if (scanf("%d", &wyborEdycji) != 1) {
                wyczyscBufor(); return;
            }
            wyczyscBufor();

            switch (wyborEdycji) {
                case 1:
                    printf("Podaj nowa tresc: ");
                    wczytajTekst(iterator->tresc, MAX_TRESC);
                    printf("Tresc zaktualizowana.\n");
                    break;
                case 2:
                    printf("Wybierz nowy status (0-Weryf, 1-W trakcie, 2-Zatw, 3-Usun): ");
                    int nowyStatus;
                    if (scanf("%d", &nowyStatus) == 1) {
                         if (nowyStatus >= 0 && nowyStatus <= 3) 
                            iterator->status = (StatusPosta)nowyStatus;
                    }
                    wyczyscBufor();
                    break;
                case 0:
                    printf("Anulowano.\n");
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
    void wyszukajPoAutorze(Post* glowa, const char* szukanyFragment) {
        printf("\n--- WYNIKI WYSZUKIWANIA: '%s' ---\n", szukanyFragment);
        Post* iterator = glowa;
        int znaleziono = 0;
        while (iterator != NULL) {
            if (strstr(iterator->autor, szukanyFragment) != NULL) {
                printf("ID: %d | Autor: %s | Tresc: %s\n",
                    iterator->id, iterator->autor, iterator->tresc);
                znaleziono = 1;    
            }
            iterator = iterator->nastepny;
        }
        if (znaleziono == 0) {
            printf("Nie znaleziono postow dla frazy: '%s'\n", szukanyFragment);
        }
        printf("-----------------------------------\n");
        }
void filtrujPoZgloszeniach(Post* glowa, int minZgloszen) {
    printf("\n--- FILTR: Zgloszenia > %d ---\n", minZgloszen);
    Post* iterator = glowa;
    int znaleziono = 0;
    while (iterator != NULL) {
        if (iterator->liczba_zgloszen > minZgloszen) {
            printf("ID: %d | Zgloszen: %d | Tresc: %s\n", 
                   iterator->id, iterator->liczba_zgloszen, iterator->tresc);
            znaleziono = 1;    
        }
        iterator = iterator->nastepny;
    }
    if (znaleziono == 0) {
        printf("Brak postow spelniajacych kryteria.\n");
    }
    printf("-------------------\n");
    }
    void zapisz_baze(Post* glowa) {
        FILE* plik = fopen("baza_danych.txt", "w");
        if (plik == NULL) {
            printf("Blad: Nie udało się otworzyć pliku do zapisu!\n");
            return ;
        }
        Post* iterator = glowa;
        while (iterator != NULL) {
            fprintf(plik, "%d %s %s %s %d %d\n" ,
                iterator -> id,
                iterator -> autor,
                iterator -> tresc,
                iterator -> kategoria,
                iterator -> liczba_zgloszen,
                (int)iterator->status);
            iterator = iterator->nastepny;
        } 

        fclose(plik);
        printf("--> [SYSTEMMM] Zapisano stan aplikacji do pliku.\n");
    }

    Post* odtworz_post(Post* glowa, int id, char* autor, char* tresc, char* kat, int zgl, int stat) {
    Post* nowy = (Post*) malloc(sizeof(Post));

    nowy->id = id;
    strcpy(nowy->autor, autor);
    strcpy(nowy->tresc, tresc);
    strcpy(nowy->kategoria, kat);
    nowy->liczba_zgloszen = zgl;
    nowy->status = (StatusPosta)stat;
    nowy->nastepny = NULL;

    if(glowa == NULL) {
        return nowy;
    } else {
        Post* temp = glowa;
        while (temp->nastepny != NULL) {
            temp = temp->nastepny;
        }
        temp->nastepny = nowy;
        return glowa;
    }
}

Post *wczytaj_baze() {
    FILE* plik = fopen("baza_danych.txt", "r");
    if (plik == NULL) {
        return NULL;
    }
    Post* glowa = NULL;
    int t_id, t_zgl, t_stat;
    char t_autor[100], t_tresc[100], t_kat[100];
    while (fscanf(plik, "%d %s %s %s %d %d",
            &t_id, t_autor, t_tresc, t_kat, &t_zgl, &t_stat) == 6) {
                glowa = odtworz_post(glowa, t_id, t_autor, t_tresc, t_kat, t_zgl, t_stat);
    }
    fclose(plik);
    printf("---> [SYSTEEMMM] WCZYTANO historie postow z pliku.\n");
    return glowa;
}
