#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct pqueueNode_t {
    char name[7];
    char sick[25];
    int data;
    struct pqueueNode_t *next;
} PQueueNode;

typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;

void pqueue_init(PriorityQueue *pqueue);
bool pqueue_isEmpty(PriorityQueue *pqueue);
void pqueue_anpush(PriorityQueue *pqueue, char* naming, char* sickness, int id);
void pqueue_rapush(PriorityQueue *pqueue, char* naming, char* sickness, int id);
void pqueue_pop(PriorityQueue *pqueue);
int  pqueue_top(PriorityQueue *pqueue);
char* pqueue_topname(PriorityQueue *pqueue);
char* pqueue_topsick(PriorityQueue *pqueue);

void pqueue_init(PriorityQueue *pqueue)
{
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) 
{
    return (pqueue->_top == NULL);
}

void pqueue_anpush(PriorityQueue *pqueue, char* naming, char* sickness, int id)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
        (PQueueNode*) malloc (sizeof(PQueueNode));
    strcpy(newNode->name, naming);
    strcpy(newNode->sick, sickness);
    newNode->data = id;
    newNode->next = NULL;
    
    pqueue->_size++;

    if (pqueue_isEmpty(pqueue)) 
    {
        pqueue->_top = newNode;
        return;
    }

    if (id > pqueue->_top->data) 
    {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
        return;
    }

    else if (id == pqueue->_top->data)
    {
        if (strcmp(pqueue->_top->name, naming) > 0)
        {
            newNode->next = pqueue->_top;
            pqueue->_top = newNode;
            return;
        }
    }
    
    while (temp->next != NULL && (temp->next->data > id || (temp->next->data == id && strcmp(temp->next->name, naming) < 0)))
    {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

void pqueue_rapush(PriorityQueue *pqueue, char* naming, char* sickness, int id)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
        (PQueueNode*) malloc (sizeof(PQueueNode));
    strcpy(newNode->name, naming);
    strcpy(newNode->sick, sickness);
    newNode->data = id;
    newNode->next = NULL;
    
    pqueue->_size++;

    if (pqueue_isEmpty(pqueue)) 
    {
        pqueue->_top = newNode;
        return;
    }
    
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

void pqueue_pop(PriorityQueue *pqueue)
{
    if (!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
        pqueue->_size--;
    }
}

int pqueue_top(PriorityQueue *pqueue) 
{
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->data;
    else return 0;
}

char* pqueue_topname(PriorityQueue *pqueue)
{
    return pqueue->_top->name;
}

char* pqueue_topsick(PriorityQueue *pqueue)
{
    return pqueue->_top->sick;
}

int
main()
{
    PriorityQueue ruangAntri;
    pqueue_init(&ruangAntri);

    PriorityQueue ruangRawat;
    pqueue_init(&ruangRawat);

    int command, doc, count1 = 0, count2 = 0, count3 = 0, count4 = 0, p = 0;
    scanf("%d", &doc);
    
    while (scanf("%d", &command) != EOF)
    {
        if (command == 1)
        {
            char patientName[7], patientDisease[25];

            scanf("%s", patientName);
            scanf("%s", patientDisease);

            printf("Pasien atas nama %s terdaftar ke database.\n", patientName);

            int s = 0;

            if (strcmp(patientDisease, "flu") == 0)
            {
                s = 1;
                count1++;
            }

            else if (strcmp(patientDisease, "maag") == 0)
            {
                s = 2;
                count2++;
            }

            else if (strcmp(patientDisease, "diare") == 0)
            {
                s = 3;
                count3++;
            }

            else if (strcmp(patientDisease, "pusingkebanyakantugas") == 0)
            {
                s = 4;
                count4++;
            }

            pqueue_anpush(&ruangAntri, patientName, patientDisease, s);

            if (ruangRawat._size < doc)
            {
                pqueue_rapush(&ruangRawat, patientName, patientDisease, s);
                printf("Pasien atas nama %s langsung masuk.\n", patientName);
                pqueue_pop(&ruangAntri);
            }

            else
            {
                printf("Pasien atas nama %s mengantri.\n", patientName);
            }
        }

        else if (command == 2)
        {
            if (!pqueue_isEmpty(&ruangRawat))
            {
                printf("Pasien atas nama %s sudah selesai konsultasi mengenai %s.\n", pqueue_topname(&ruangRawat), pqueue_topsick(&ruangRawat));
                pqueue_pop(&ruangRawat);
            }

            if (!pqueue_isEmpty(&ruangAntri) && ruangRawat._size < doc)
            {
                printf("Pasien atas nama %s masuk dari antrian.\n", pqueue_topname(&ruangAntri));
                pqueue_rapush(&ruangRawat, pqueue_topname(&ruangAntri), pqueue_topsick(&ruangAntri), pqueue_top(&ruangAntri));
                pqueue_pop(&ruangAntri);
            }
        }
    }

    printf("Data pasien hari ini:\n");
    
    if (count3 > 0)
    {
        printf("diare: %d.\n", count3);
    }

    if (count1 > 0)
    {
        printf("flu: %d.\n", count1);
    }

    if (count2 > 0)
    {
        printf("maag: %d.\n", count2);
    }

    if (count4 > 0)
    {
        printf("pusingkebanyakantugas: %d.\n", count4);
    }

    return 0;
}