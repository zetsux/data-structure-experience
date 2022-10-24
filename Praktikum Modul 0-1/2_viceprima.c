#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct dynamicarr_t {
    int *_arr;
    unsigned _size, _capacity;
} DynamicArray;

void dArray_init(DynamicArray *darray)
{
    darray->_capacity = 2u;
    darray->_size = 0u;
    darray->_arr = (int*) malloc(sizeof(int) * 2);
}

bool dArray_isEmpty(DynamicArray *darray) 
{
    return (darray->_size == 0);
}

void dArray_pushBack(DynamicArray *darray, int value)
{
    if (darray->_size + 1 > darray->_capacity) {
        unsigned it;
        darray->_capacity *= 2;
        int *newArr = (int*) malloc(sizeof(int) * darray->_capacity);

        for (it=0; it < darray->_size; ++it)
            newArr[it] = darray->_arr[it];
        
        int *oldArray = darray->_arr;
        darray->_arr = newArr;
        free(oldArray);
    }
    darray->_arr[darray->_size++] = value;
}

void dArray_popBack(DynamicArray *darray) 
{
    if (!dArray_isEmpty(darray)) darray->_size--;
    else return;
}

int dArray_back(DynamicArray *darray) 
{
    if (!dArray_isEmpty(darray))
        return darray->_arr[darray->_size-1];
    else return 0;
}

int 
check_prime (int x)
{
    int flag = 0;

    if (x==2 || x==3)
	{
		return 0;
	}
	    
	else if (x==1 || x%2==0)
	{
		return 1;
	}
    
    for (int i=3 ; i<=97 ; i+=2)
	{
		if (x%i==0 && x/i!=1)
		{
			flag = 1;
			break;
		}
	}
  
    return flag;
}

void printElement(DynamicArray *darray)
{
    for (int j = darray->_size - 1 ; j>=0 ; j--)
    {
        if (check_prime(darray->_arr[j]) == 0)
        {
            printf("%d\n", darray->_arr[j]);
            darray->_arr[j] = -1;
        }
    }

    while (!dArray_isEmpty(darray))
    {
        if (dArray_back(darray) != -1)
        {
            printf("%d\n", dArray_back(darray));
        }

        dArray_popBack(darray);
    }
    
    return;
}

int
main()
{
    DynamicArray myArray;
    dArray_init(&myArray);
    
    int n;
    scanf("%d", &n);

    for (int i=0 ; i<n ; i++)
    {
        int num;
        scanf("%d", &num);

        dArray_pushBack(&myArray, num);
    }
    
    printElement(&myArray);
}