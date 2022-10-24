#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK 10

typedef struct STACK{
    int top;
    int data[10];
}; struct STACK tumpuk; 

void init() 
{
    tumpuk.top = -1;
}

int isFull()
{
    return (tumpuk.top == MAX_STACK - 1) ? 1 : 0;
}

int isEmpty()
{
    return (tumpuk.top == 1) ? 1 : 0;
}

void push(int x)
{
    tumpuk.data[++tumpuk.top] = x;
}

void pop()
{
    printf("data terambil %d\n", tumpuk.data[tumpuk.top]);
    tumpuk.top--;
}

void tampil()
{
    for (int i = tumpuk.top ; i>=0 ; i--)
    {
        printf("Data stack ke %d adalah %d", i, tumpuk.data[i]);
    }
}

void masuk()
{
    int x;

    while (!isFull)
    {
        printf("Masukkan data >>");
        scanf("%d", &x);
        push(x);
    }
}

void ambil()
{
    while (!isEmpty)
    {
        pop();
    }
}

int 
main()
{
    init();
    masuk();
    tampil();
    ambil();
    return 0;
}