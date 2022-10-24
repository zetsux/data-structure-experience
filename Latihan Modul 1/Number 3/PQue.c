#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct pqueueNode_t {
    char* data;
    struct pqueueNode_t *next;
} PQueueNode;

typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;


void  pqueue_init(PriorityQueue *pqueue);
bool  pqueue_isEmpty(PriorityQueue *pqueue);
void  pqueue_push(PriorityQueue *pqueue, char* txt);
void  pqueue_pop(PriorityQueue *pqueue);
char* pqueue_top(PriorityQueue *pqueue);

void pqueue_init(PriorityQueue *pqueue)
{
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, char* txt)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
        (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->data = txt;
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }

    if (strlen(txt) < strlen(pqueue->_top->data)) {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else {
        while ( temp->next != NULL && 
                strlen(temp->next->data) < strlen(txt))
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void pqueue_pop(PriorityQueue *pqueue)
{
    if (!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
}

char* pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->data;
    else return 0;
}

int main(int argc, char const *argv[])
{
    PriorityQueue myPque;

    pqueue_init(&myPque);

    pqueue_push(&myPque, "pendek");
    pqueue_push(&myPque, "panjang");
    pqueue_push(&myPque, "sangat panjang");

    while (!pqueue_isEmpty(&myPque)) {
        printf("%s\n", pqueue_top(&myPque));
        pqueue_pop(&myPque);
    }

    return 0;
}
