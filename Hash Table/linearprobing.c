#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int 
main ()
{
    srand(time(NULL));
    int arr[701], count = 0, index[20];

    while (count < 20)
    {
        unsigned long long num = rand();
        if (num <= 0)
        {
            continue;
        }

        printf("Random Number got is : %llu\n", num);

        int pos = num % 701;

        while (arr[pos] != 0 && pos <= 700)
        {
            pos++;
        }

        arr[pos] = num;
        index[count++] = pos;
    }

    printf("\n\t- Result -\n");

    for (int i = 0 ; i<20 ; i++)
    {
        printf("On index %d there is : %d\n", index[i], arr[index[i]]);
    }
}