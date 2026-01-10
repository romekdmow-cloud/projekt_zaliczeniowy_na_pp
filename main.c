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
int main() {
    printf("System Moderacji QuickTalk - Inicjalizacja struktur...\n");
    Post testowyPost;
    testowyPost.id = 1;

    strcpy(testowyPost.autor, "Incognito_ziomuś007");
    strcpy(testowyPost.tresc, "To jest przykładowy post o polityce");
    strcpy(testowyPost.kategoria, "szydera");
    testowyPost.liczba_zgloszen = 0;
    testowyPost.status = ZATWIERDZONE;
    testowyPost.nastepny = NULL; 

    printf("ID: %d | Autor: %s | Status: %s\n", 
           testowyPost.id, 
           testowyPost.autor, 
           statusDoTekstu(testowyPost.status));
    return 0;
}
 // tutaj miała być intruskcja MAIN z całym MENU programu(niedokonczona)
 // int main() {
 // int wybor;
 // do {
 //    printf("\n-----MENU------\n");
 //    printf("1. numer ID wpisu\n");
 //    printf("2. nazwa Autora\n");
 //    printf("3. Treść posta\n");
 //    printf("4. Kategoria Zgłoszenia\n");
 //    printf("5. Liczba Zgłoszeń\n");
 //    printf("6. Status Moderacji\n");
 //    printf("\n 0. -----KONIEC PROGRAMU--------\n");
 //    scanf("%d", &wybor);
 //    switch(wybor) {
 //          case 1:
 //                 tu bedzie cos
 //                 break;
 //           case 2:
 //                 tu bedzie cos
 //                 break;
 //           case 3:
 //                 tu bedzie cos
 //                 break;
 //          case 4:
 //                 tu bedzie cos
 //                 break;
 //          case 5:
 //                 tu bedzie cos
 //                 break;
 //          case 6:
 //                 tu bedzie cos
 //                 break;
 //           case 0:
 //                 tu bedzie cos
 //                 break;
 //           default:
 //                 tu bedzie cos     
 //       }
 //   } while (wybor != 0);
 //   return 0;
 // }