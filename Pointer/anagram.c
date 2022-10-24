#include <stdio.h>
#include <string.h>

int
main()
{
    char str1[100], str2[100];
    char *a, *b;
    int count = 0;

    scanf("%s", str1);
    scanf("%s", str2);

    a = &str1[0];
    b = &str2[0];

    while (*a != '\0')
    {
        b = &str2[0];

        while (*b != '\0')
        {
            if (*a == *b)
            {
                *a = '.';
                *b = '-';
                count++;
            }

            b++;
        }

        a++;
    }

    if (count == strlen(str1) && count == strlen(str2))
    {
        printf("Anagram!");
    }

    else
    {
        printf("Bukan Anagram!");
    }
}