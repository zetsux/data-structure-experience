#include <stdio.h>

int
cekprima(int n)
{
    if (n==2)
	{
		return 1;
	}
	    
	else if (n==1 || n%2==0)
    {
        return 0;
    }
    
    for (int i=3 ; i*i<=n ; i+=2)
    {
        if (n%i==0 && n/i!=1)
        {
            return 0;
        }
    }

    return 1;
}

int
main()
{
    int num;
    scanf("%d", &num);

    for (int i=0 ; i<num ; i++)
    {
        if (cekprima(i) == 1)
        {
            printf("%d ", i);
        }
    }
}