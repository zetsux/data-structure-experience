#include <stdio.h>
#include <string.h>

int
main()
{
    char str[100];
    char *a, *b;
    scanf("%s", str);

    a = &str[0];
    b = &str[strlen(str) - 1];

    int flag = 1;

    while (a < b)
    {
        if (*a != *b)
        {
            flag = 0;
            break;
        }

        a++;
        b--;
    }

    if (flag == 0)
    {
        printf("Bukan Palindrom!");
    }

    else if (flag == 1)
    {
        printf("Palindrom!");
    }
}