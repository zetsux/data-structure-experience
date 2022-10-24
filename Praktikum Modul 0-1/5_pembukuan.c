#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int code = 1;

typedef struct dnode_t {
    int data;
    struct dnode_t      \
        *next,
        *prev;
} DListNode;

typedef struct deque_t {
    DListNode           \
        *_head, 
        *_tail;
    unsigned _size;
} Deque;

DListNode* __dlist_createNode(int value);
void deq_init(Deque *deque);
bool deq_isEmpty(Deque *deque);
void deq_pushFront(Deque *deque, int value);
void deq_pushBack(Deque *deque, int value);
int  deq_front(Deque *deque);
int  deq_back(Deque *deque);
void deq_popFront(Deque *deque);
void deq_popBack(Deque *deque);

DListNode* __dlist_createNode(int value)
{
    DListNode *newNode = \
        (DListNode*) malloc (sizeof(DListNode));
    
    if (!newNode) return NULL;
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    return (DListNode*) newNode;
}

void deq_init(Deque *deque)
{
    deque->_head = deque->_tail = NULL;
    deque->_size = (unsigned) 0;
}

bool deq_isEmpty(Deque *deque) {
    return (deque->_head == NULL && \
            deque->_tail == NULL);
}

void deq_pushFront(Deque *deque, int value)
{
    DListNode *newNode = __dlist_createNode(value);
    if (newNode) {
        deque->_size++;
        if (deq_isEmpty(deque)) {
            deque->_head = newNode;
            deque->_tail = newNode;
            return;
        }

        newNode->next = deque->_head;
        deque->_head->prev = newNode;
        deque->_head = newNode;
    }
}

void deq_pushBack(Deque *deque, int value)
{
    DListNode *newNode = __dlist_createNode(value);
    if (newNode) {
        deque->_size++;
        if (deq_isEmpty(deque)) {
            deque->_head = newNode;
            deque->_tail = newNode;
            return;
        }

        deque->_tail->next = newNode;
        newNode->prev = deque->_tail;
        deque->_tail = newNode;
    }
}

int deq_front(Deque *deque) {
    if (!deq_isEmpty(deque)) {
        return (deque->_head->data);
    }
    return 0;
}

int deq_back(Deque *deque) {
    if (!deq_isEmpty(deque)) {
        return (deque->_tail->data);
    }
    return 0;
}

void deq_popFront(Deque *deque)
{
    if (!deq_isEmpty(deque)) {
        DListNode *temp = deque->_head;
        if (deque->_head == deque->_tail) {
            deque->_head = NULL;
            deque->_tail = NULL;
            free(temp);
        }
        else {
            deque->_head = deque->_head->next;
            deque->_head->prev = NULL;
            free(temp);
        }
        deque->_size--;
    }
}

void deq_popBack(Deque *deque)
{
    if (!deq_isEmpty(deque)) {
        DListNode *temp;
        if (deque->_head == deque->_tail) {
            temp = deque->_head;
            deque->_head = NULL;
            deque->_tail = NULL;
            free(temp);
        }
        else {
            temp = deque->_tail;
            deque->_tail = deque->_tail->prev;
            deque->_tail->next = NULL;
            free(temp);
        }
        deque->_size--;
    }
}


int 
main()
{
    Deque tumpuk1;
    deq_init(&tumpuk1);

    Deque tumpuk2;
    deq_init(&tumpuk2);

    Deque tumpuk3;
    deq_init(&tumpuk3);

    int n;
    scanf("%d", &n);
    getchar();

    for (int i=0 ; i<n ; i++)
    {
        char command[10];
        scanf("%s", command);

        int x;
        scanf("%d", &x);
        getchar();

        if (strcmp(command, "CETAK") == 0)
        {
            for (int j=0 ; j<x ; j++)
            {
                deq_pushBack(&tumpuk1, code++);
            }

        }

        else if (strcmp(command, "TTD") == 0)
        {       
            for (int j=0 ; j<x ; j++)
            {
                if (!deq_isEmpty(&tumpuk1))
                {
                    deq_pushFront(&tumpuk2, deq_back(&tumpuk1));
                    deq_popBack(&tumpuk1);
                }

                else
                {
                    break;
                }
            }
        }

        else if (strcmp(command, "SAMPUL") == 0)
        {
            for (int j=0 ; j<x ; j++)
            {
                if (!deq_isEmpty(&tumpuk2))
                {
                    deq_pushBack(&tumpuk3, deq_front(&tumpuk2));
                    deq_popFront(&tumpuk2);
                }

                else
                {
                    break;
                }
            }
        }
    }

    printf("tumpukan 1: ");
    while (!deq_isEmpty(&tumpuk1)) {
        printf("%d ", deq_front(&tumpuk1));
        deq_popFront(&tumpuk1);
    }

    printf("\ntumpukan 2: ");
    while (!deq_isEmpty(&tumpuk2)) {
        printf("%d ", deq_back(&tumpuk2));
        deq_popBack(&tumpuk2);
    }

    printf("\ntumpukan 3: ");
    while (!deq_isEmpty(&tumpuk3)) {
        printf("%d ", deq_front(&tumpuk3));
        deq_popFront(&tumpuk3);
    }

    return 0;
}