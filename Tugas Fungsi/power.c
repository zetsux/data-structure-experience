#include <stdio.h>

int
power(int x, int y)
{
    if (y == 0)
    {
        return 1;
    }

    return x*power(x,y-1);
}

int
main()
{
    int num, pangkat;
    scanf("%d%d", &num, &pangkat);

    printf("%d", power(num, pangkat));
}