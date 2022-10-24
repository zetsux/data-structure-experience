#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct pqueueNode_t {
    int data;
    int data2;
    int num;
    struct pqueueNode_t *next;
} PQueueNode;

typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;

void pqueue_init(PriorityQueue *pqueue);
bool pqueue_isEmpty(PriorityQueue *pqueue);
void pqueue_push(PriorityQueue *pqueue, int value, int value2, int id);
void pqueue_pop(PriorityQueue *pqueue);
int  pqueue_top(PriorityQueue *pqueue);

void pqueue_init(PriorityQueue *pqueue)
{
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) 
{
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, int value, int value2, int id)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
        (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->data = value;
    newNode->data2 = value2;
    newNode->num = id;
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) 
    {
        pqueue->_top = newNode;
        return;
    }

    if (value > pqueue->_top->data) 
    {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
        return;
    }

    else if (value == pqueue->_top->data)
    {
        if (value2 > pqueue->_top->data2)
        {
            newNode->next = pqueue->_top;
            pqueue->_top = newNode;
            return;
        }
    }
    
    while (temp->next != NULL && (temp->next->data > value || (temp->next->data == value && temp->next->data2 > value2)))
    {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

void pqueue_pop(PriorityQueue *pqueue)
{
    if (!pqueue_isEmpty(pqueue)) 
    {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
    
    
}

int pqueue_top(PriorityQueue *pqueue) 
{
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->num;
    else return 0;
}

int
main()
{
    PriorityQueue myPque;
    pqueue_init(&myPque);
    
    int x;
    scanf("%d", &x);
    getchar();
    
    for (int i=0 ; i<x ; i++)
    {
        char command[7];
        scanf("%s", command);
        
        if (strcmp(command, "BELI") == 0)
        {
            int n;
            scanf("%d", &n);
            getchar();

            for (int j=0 ; j<n ; j++)
            {
                if (!pqueue_isEmpty(&myPque))
                {
                    pqueue_pop(&myPque);
                }

                else
                {
                    break;
                }
            }
        }
        
        else if (strcmp(command, "DAFTAR") == 0)
        {
            int id, usia, massa;
            scanf("%d%d%d", &id, &usia, &massa);
            getchar();
            
            pqueue_push(&myPque, usia, massa, id);
        }
    }
    
    while (!pqueue_isEmpty(&myPque)) {
        printf("%d ", pqueue_top(&myPque));
        pqueue_pop(&myPque);
    }
}
