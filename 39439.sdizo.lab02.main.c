//SDIZO I1 223A LAB02
//Łukasz Stefanowski
//sl39439@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct A {
    int klucz;
    double d;
    char c;
    struct A *next;
    struct A *prev;
} A;

A *pierwszy = NULL;

int sprawdzklucz(int klucz) {
    A *temp = pierwszy;
    do {
        if (temp->klucz == klucz) {
            return 1;
        }
        temp = temp->next;
    } while (temp != pierwszy);
    return 0;
}

//1
int wstaw(int klucz) {
    A *nowyElem = (A *) malloc(sizeof(A));
    nowyElem->klucz = klucz;
    nowyElem->d = rand();
    nowyElem->c = 'T';
    if (pierwszy == NULL) {
        nowyElem->next = nowyElem;
        nowyElem->prev = nowyElem;
        pierwszy = nowyElem;
        return 0;
        //jeżeli klucz się powtarza
    } else if (sprawdzklucz(klucz) == 1) {
        free(nowyElem);
        return 1;
    }

    if (pierwszy->next == pierwszy && pierwszy->prev == pierwszy) {
        pierwszy->next = nowyElem;
        pierwszy->prev = nowyElem;
        nowyElem->prev = pierwszy;
        nowyElem->next = pierwszy;
        if (pierwszy->klucz > nowyElem->klucz) {
            pierwszy = nowyElem;
        }
    }
    else {

        if (pierwszy->klucz > nowyElem->klucz) {
            //początek
            nowyElem->prev = pierwszy->prev;
            pierwszy->prev->next = nowyElem;
            nowyElem->next = pierwszy;
            pierwszy->prev = nowyElem;
            pierwszy = nowyElem;
        } else if (pierwszy->prev->klucz < nowyElem->klucz) {
            //koniec
            nowyElem->prev = pierwszy->prev;
            nowyElem->next = pierwszy;

            pierwszy->prev->next = nowyElem;
            pierwszy->prev = nowyElem;
        } else {
            //środek
            A *temp = pierwszy;
            int wstawiono = 0;
            while (wstawiono == 0) {
                if (nowyElem->klucz < temp->klucz) {
                    nowyElem->prev = temp->prev;
                    temp->prev->next = nowyElem;
                    nowyElem->next = temp;
                    temp->prev = nowyElem;
                    ++wstawiono;
                }
                temp = temp->next;
            }
        }
    }
    return 0;
}


//2
void wstawXelementow(int X) {

    for (int i = 0; i < X; i++) {
        int klucz = (rand() % 99900) + 99;
//        printf("Wylosowano %d\n", klucz)
//          jeżeli się powtórzył (funkcja wstawiania
//          zwróciła 1) cofa iterację
        if (wstaw(klucz)) {
//            printf("Nieprawidlowy klucz\n");
            i--;
        }

    }
}

//3
int wyszukajElement(int klucz) {
    int exist = 0;
    A *temp = pierwszy;

    if (pierwszy == NULL) {
        printf("Element o podanej wartosci skladowej kluczowej nie istnieje.\n");
        return 0;
    }
    else {
        do {
            if (temp->klucz == klucz) {
                ++exist;
                printf("Element zostal znaleziony.\n");
            }
            temp = temp->next;
        } while (temp != pierwszy);

        if (exist == 0)
            printf("Element o podanej wartosci skladowej kluczowej nie istnieje.\n");
    }
    return 0;

}

//4
int usunWybrany(int klucz) {
    int deleted = 0;
    A *temp = pierwszy;
    if (pierwszy == NULL)
        printf("Lista jest pusta");
    else {
        do {

            if (temp->next == pierwszy && temp->klucz != klucz) {
                printf("Nie ma takiego elementu.\n");
                break;

            }
            if (temp->klucz == klucz) {
                ++deleted;

                if (temp->next == pierwszy->prev){
                    temp->next = pierwszy;
                    pierwszy->prev = temp->prev;
                    free(temp);
                    printf("Wybrany element %d został usunięty.\n", klucz);
                }
                else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;

                    free(temp);
                    printf("Wybrany element %d został usunięty.\n", klucz);
                }
            }
            temp = temp->next;

        } while (deleted == 0);

    }
    return 0;
}

//5
void wypiszYpierwszych(int Y) {
    printf("\n");
    A *temp = pierwszy;
    if (pierwszy == NULL)
        printf("Lista jest pusta");
    else {
        for (int i = 0; i < Y; i++) {
            printf("Klucz: %d, Double: %f, Char: %c\n", temp->klucz, temp->d, temp->c);

            temp = temp->next;

            if (temp->next == pierwszy->prev){
                printf("Lista zzwiera mniej niż 20 elementów");

                break;

            }
        }
    }
}

//6
void wypiszZostatnich(int Z) {

    A *temp = pierwszy->prev;
    if (pierwszy == NULL)
        printf("Lista jest pusta");
    else {
        for (int i = Z; i > 0; i--) {
            printf("Klucz: %d, Double: %f, Char: %c\n", temp->klucz, temp->d, temp->c);

            temp = temp->prev;

            if (temp->prev == temp->prev->next){
                printf("Lista zzwiera mniej niż 11 elementów");
                break;
            }
        }
    }
}
//7
int ileElementow() {
    A *temp = pierwszy;
    int licznik = 0;

    if (pierwszy == NULL)
        return 0;

    do {
        ++licznik;
        temp = temp->next;
    } while (temp != pierwszy);
    return licznik;
}

//8
void usunWszystko(){
    int q = ileElementow();

    if (q == 0)
        printf("Lista jest pusta, nie ma czego usuwac.\n");
    else
    {
        A *temp = pierwszy;
        A *next = pierwszy->next;
        for (int i = 0; i<q; i++) {
            free(temp);
            temp = next;
            next = next->next;
        }
    }
}


int main() {
    int X, k1, k2, k3, k4, k5;
    FILE* fp = fopen("inlab02.txt", "r");
    if (fp == NULL)
        return -1;
    fscanf (fp, "%d %d %d %d %d %d", &X, &k1, &k2, &k3, &k4, &k5);
    fclose(fp);
    srand(time(NULL));
    clock_t begin, end;
    double time_spent;
    begin = clock();

    wyszukajElement(k1);
    wstawXelementow(X);
    int nodes=ileElementow();
    printf("Liczba wezlow: %d\n", nodes);
    wypiszYpierwszych(20);
    wstaw(k2);
    wypiszYpierwszych(20);
    wstaw(k3);
    wypiszYpierwszych(20);
    wstaw(k4);
    wypiszYpierwszych(20);
    wstaw(k5);
    usunWybrany(k3);
    wypiszYpierwszych(20);
    usunWybrany(k2);
    wypiszYpierwszych(20);
    usunWybrany(k5);
    int nodes2 = ileElementow();
    printf("Liczba wezlow: %d\n", nodes2);
    wyszukajElement(k5);
    wypiszZostatnich(11);
    usunWszystko();
    wypiszZostatnich(11);
    int nodes3 = ileElementow();
    printf("Liczba wezlow: %d\n", nodes3);


    end = clock();
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("%lf", time_spent);


    return 0;
}