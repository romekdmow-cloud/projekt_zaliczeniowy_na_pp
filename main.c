#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include "post.h"

void wyczyscEkran() {
    system("cls");
}


int main() {
    Post* bazaPostow = wczytaj_baze();
    int wybor = -1;
    int licznikId = 1;

    if (bazaPostow != NULL) {
        Post* temp = bazaPostow;
        int maxId = 0;
        while (temp != NULL) {
            if (temp->id > maxId) {
                maxId = temp->id;
            }
            temp = temp->nastepny;
        }
        licznikId = maxId + 1;
        printf("--> [DEBUG] Wczytano dane. Nowy licznik startuje od: %d\n", licznikId);
    }
    char tempAutor[MAX_AUTOR];
    char tempTresc[MAX_TRESC];

    printf("Witaj w QuickTalk Manager v1.0\n");

    do {
        printf("\n--- MENU GLOWNE ---\n");
        printf("1. Dodaj nowy post\n");
        printf("2. Wyswietl wszystkie posty\n");
        printf("3. Usun post\n");
        printf("4. Edytuj post\n");
        printf("5. Szukaj (wg Autora)\n");   
        printf("6. Filtruj (wg Zgloszen)\n"); 
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
                zapisz_baze(bazaPostow);
                return 0;
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
                printf("\n----- EDYCJA POSTA -------\n");
                int idEdycja;
                printf("Podaj ID posta do edycji: ");
                if(scanf("%d", &idEdycja) == 1) {
                    wyczyscBufor(); 
                    edytujPost(bazaPostow, idEdycja);    
                } else {
                    printf("Blad: ID musi byc liczba.\n");
                    wyczyscBufor(); 
                }
                break;
            case 5:
                printf("\nPodaj fragment nazwy autora: ");
                char szukane[MAX_AUTOR];
                wyczyscBufor(); 
                wczytajTekst(szukane, MAX_AUTOR);
                wyszukajPoAutorze(bazaPostow, szukane);
                break;
            case 6:
                printf("\nPokaz posty majace wiecej zgloszen niz: ");
                int limit;
                if (scanf("%d", &limit) == 1) {
                    filtrujPoZgloszeniach(bazaPostow, limit);
                } else {
                    printf("Blad: to nie liczba.\n");
                }
                wyczyscBufor();
                break;
            default:
                printf("Nieznana opcja. Sprobuj ponownie.\n");
        }
        if (wybor != 0) {
            printf("\n[Wcisnij ENTER, aby wrocic do menu...]");
            getchar(); 
            getchar(); 
            system("cls"); 
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

