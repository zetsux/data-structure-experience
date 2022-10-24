#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int incr = 1;

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

int dArray_front(DynamicArray *darray) 
{
    if (!dArray_isEmpty(darray))
        return darray->_arr[0];
    else return 0;
}

void dArray_insertAt(DynamicArray *darray, unsigned index, int value)
{
    if (index == darray->_size)
    {
        dArray_pushBack(darray, value);
    }

    else if (index >= 0 && index <= darray->_capacity)
    {
        if (darray->_size + 1 > darray->_capacity)
        {
            unsigned it;
            darray->_capacity *= 2;
            int *newArr = (int*) malloc(sizeof(int) * darray->_capacity);

            for (it=0; it < darray->_size; ++it)
                newArr[it] = darray->_arr[it];
            
            int *oldArray = darray->_arr;
            darray->_arr = newArr;
            free(oldArray);
        }

        int i, temp, new, x = darray->_size - index;

        for (i=0 ; i<=x+1 ; i++)
        {
            if (i==0)
            {
                temp = darray->_arr[index+i];
                darray->_arr[index+i] = value;
            }
            
            else
            {
                new = darray->_arr[index+i];
                darray->_arr[index+i] = temp;
                temp = new;
            }
        }
        
        darray->_size++;
    }
    
    else
    {
        printf("\nPlease check your index..\n");
    }
}

void dArray_removeAt(DynamicArray *darray, unsigned index)
{
    if (!dArray_isEmpty(darray))
    {
        if (index >= darray->_size)
        { 
            dArray_popBack(darray);
        }

        int i, x = darray->_size - index;

        for (i=0 ; i<x ; i++)
        {
            darray->_arr[index+i] = darray->_arr[index+i+1];
        }

        darray->_size--;
    }
    
}

void viceFunction(DynamicArray *darray, int n)
{
    int x = 0;

    while (x<darray->_size - 1)
    {
        if (darray->_arr[x] % n == 0)
        {
            if (darray->_arr[x]+incr == darray->_arr[x+1])
            {
                incr = 1;
                return;
            }

            else
            {
                dArray_insertAt(darray, x+1, darray->_arr[x]+incr);
            }
            
            incr++;
        }

        x++;
    }
}

void printElement(DynamicArray *darray)
{
    int i;

    for(i=0 ; i<darray->_size ; i++)
    {
        printf("%d ", darray->_arr[i]);
    }

    printf("\n");
    
    return;
}

int
main()
{
    DynamicArray myArray;
    dArray_init(&myArray);

    int b, n;
    scanf("%d", &b);

    for (int i = 0 ; i<b ; i++)
    {
        int num;
        scanf("%d", &num);

        dArray_pushBack(&myArray, num);
    }

    scanf("%d", &n);
    viceFunction(&myArray, n);

    if (incr == 1)
    {
        printf("VICE!!!\n");
        return 0;
    }

    else if (incr-1 > n)
    {
        printf("#NICEVICE\n");
        dArray_popBack(&myArray);
        dArray_removeAt(&myArray, 0);
    }

    else if (incr-1 <= n)
    {
        printf(":(\n");
    }

    while (!dArray_isEmpty(&myArray)) {
        printf("%d ", dArray_front(&myArray));
        dArray_removeAt(&myArray, 0);
    }
}