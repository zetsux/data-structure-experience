#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct dynamicarr_t {
    int *_arr;
    int *_arr2;
    unsigned _size, _capacity;
} DynamicArray;

typedef struct stackNode_t {
    int data;
    int data2;
    struct stackNode_t *next;
} StackNode;

typedef struct stack_t {
    StackNode *_top;
    unsigned _size;
} Stack;

int dArray_back(DynamicArray *darray);
int dArray_back2(DynamicArray *darray);
void dArray_init(DynamicArray *darray);
bool dArray_isEmpty(DynamicArray *darray);
void dArray_pushBack(DynamicArray *darray, int value, int value2);
void dArray_popBack(DynamicArray *darray);
void stack_init(Stack *stack);
bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, int value, int value2);
void stack_pop(Stack *stack);
int stack_top(Stack *stack);
int stack_top2(Stack *stack);
bool keboFunction(DynamicArray *darray, Stack *stack, int n, int m);

int dArray_back(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return darray->_arr[darray->_size-1];
    else return 0;
}

int dArray_back2(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return darray->_arr2[darray->_size-1];
    else return 0;
}

void dArray_init(DynamicArray *darray)
{
    darray->_capacity = 2u;
    darray->_size = 0u;
    darray->_arr = (int*) malloc(sizeof(int) * 2);
    darray->_arr2 = (int*) malloc(sizeof(int) * 2);
}

bool dArray_isEmpty(DynamicArray *darray) {
    return (darray->_size == 0);
}

void dArray_pushBack(DynamicArray *darray, int value, int value2)
{
    if (darray->_size + 1 > darray->_capacity) {
        unsigned it;
        darray->_capacity *= 2;
        int *newArr = (int*) malloc(sizeof(int) * darray->_capacity);
        int *newArr2 = (int*) malloc(sizeof(int) * darray->_capacity);

        for (it=0; it < darray->_size; ++it)
        {
            newArr[it] = darray->_arr[it];
            newArr2[it] = darray->_arr2[it];
        }
        
        int *oldArray = darray->_arr;
        int *oldArray2 = darray->_arr2;
        darray->_arr = newArr;
        darray->_arr2 = newArr2;
        free(oldArray);
        free(oldArray2);
    }
    darray->_arr[darray->_size] = value;
    darray->_arr2[darray->_size++] = value2;
}

void dArray_popBack(DynamicArray *darray) {
    if (!dArray_isEmpty(darray)) darray->_size--;
    else return;
}

void stack_init(Stack *stack) 
{
    stack->_size = 0;
    stack->_top = NULL;
}

bool stack_isEmpty(Stack *stack) {
    return (stack->_top == NULL);
}

void stack_push(Stack *stack, int value, int value2) 
{
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        newNode->data = value;
        newNode->data2 = value2;
        
        if (stack_isEmpty(stack)) newNode->next = NULL;
        else newNode->next = stack->_top;

        stack->_top = newNode;
    }
}

void stack_pop(Stack *stack) 
{
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        free(temp);
        stack->_size--;
    }
}

int stack_top(Stack *stack) 
{
    if (!stack_isEmpty(stack)) 
        return stack->_top->data;
    return 0;
}

int stack_top2(Stack *stack) 
{
    if (!stack_isEmpty(stack)) 
        return stack->_top->data2;
    return 0;
}

bool keboFunction(DynamicArray *darray, Stack *stack, int n, int m)
{
    if (n == 1 && m > 1)
    {
        return true;
    }

    int highest = 0;

    for (int i = 0; i < n; i++)
    {
        if (darray->_arr[i] >= darray->_arr2[i])
        {
            return false;
        }

        if (darray->_arr2[i] > highest)
        {
            highest = darray->_arr2[i];
        }
        
        for (int k = i + 1; k < n; k++)
        {
            if (darray->_arr[i] == darray->_arr[k])
            {
                return false;
            }

            if (darray->_arr2[i] == darray->_arr2[k])
            {
                return false;
            }
            
        }
    }

    for (int i = 1 ; i<highest ; i++)
    {
        for (int j = 0 ; j<darray->_size ; j++)
        {
            if (darray->_arr[j] == i)
            {
                stack_push(stack, darray->_arr[j], darray->_arr2[j]);
            }

            if (stack->_size > m)
            {
                return false;
            }

            if (darray->_arr2[j] == i)
            {
                if (stack_top(stack) != darray->_arr[j] || stack_top2(stack) != darray->_arr2[j])
                {
                    return false;
                }
                
                stack_pop(stack);
            }
        }
    }

    return true;
}

int
main()
{
    DynamicArray myArray;
    dArray_init(&myArray);

    Stack myStack;
    stack_init(&myStack);
    
    int n, m;

    scanf("%d%d", &n, &m);

    while (n != 0 && m != 0)
    {
        for (int i = 0 ; i<n ; i++)
        {
            int p, q;
            scanf("%d%d", &p, &q);

            dArray_pushBack(&myArray, p, q);
        }

        if (keboFunction(&myArray, &myStack, n, m))
        {
            printf("Bagusla\n");
        }

        else
        {
            printf("Dah lah\n");
        }

        while (!dArray_isEmpty(&myArray)) 
        {
            dArray_popBack(&myArray);
        }

        while (!stack_isEmpty(&myStack))
        {
            stack_pop(&myStack);
        }

        scanf("%d%d", &n, &m);
    }
}