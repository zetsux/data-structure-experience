#include <stdio.h>

int
faktorial(int n)
{
    if (n == 0)
    {
        return 1;
    }

    return n*faktorial(n-1);
}

int
main()
{
    int num;
    scanf("%d", &num);

    printf("%d", faktorial(num));
}