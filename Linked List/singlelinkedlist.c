#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct Mahasiswa {
    int nim;
    struct Mahasiswa *next;
}Mahasiswa;

void init(Mahasiswa **p)
{
    *p = NULL;
}

Mahasiswa* alokasi(int nim)
{
    Mahasiswa *P;
    P = (Mahasiswa*) malloc(sizeof(Mahasiswa));
    if (P != NULL)
    {
        P->next = NULL;
        P->nim = nim;
    }

    return (P);
}

void Add(Mahasiswa **p, int nim)
{
    *p = alokasi(nim);
    printf("%d", (*p)->nim);
}

int main()
{
    Mahasiswa *head;
    init(&head);
    Add(&head, 20);
    getch();
}