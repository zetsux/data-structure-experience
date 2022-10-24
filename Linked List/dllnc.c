#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct d_node {
    int data;
    struct d_node      \
        *next,
        *prev;
} DoublyListNode;

typedef struct d_list {
    DoublyListNode *head;
    DoublyListNode *tail;
} DoublyList;

void init(DoublyList *dList)
{
    dList->head = dList->tail = NULL;
}

int isEmpty(DoublyList *dList)
{
	if (dList->tail == NULL) return 1;
	else return 0;
}

void insertDepan(DoublyList *dList, int newData)
{
    DoublyListNode *new = (DoublyListNode*) malloc(sizeof(DoublyListNode));
    new->data = newData;
    new->next = NULL;
    new->prev = NULL;

    if (isEmpty(dList) == 1)
    {
        dList->head = dList->tail = new;
    }

    else 
    {
        new->next = dList->head;
        dList->head->prev = new;
        dList->head = new;
    }

    printf("Data %d masuk di depan\n", newData);
}

void insertBelakang(DoublyList *dList, int newData)
{
    DoublyListNode *new = (DoublyListNode*) malloc(sizeof(DoublyListNode));
    new->data = newData;
    new->next = NULL;
    new->prev = NULL;

    if (isEmpty(dList) == 1)
    {
        dList->head = dList->tail = new;
    }

    else 
    {
        dList->tail->next = new;
        new->prev = dList->tail;
        dList->tail = new;
    }

    printf("Data %d masuk di belakang\n", newData);
}

void tampilDepan(DoublyList *dList)
{
    DoublyListNode *temp;
    temp = dList->head;

    if (isEmpty(dList) == 1)
    {
        printf("Masih kosong\n");
        return;
    } 
    
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

void tampilBelakang(DoublyList *dList)
{
    DoublyListNode *temp;
    temp = dList->tail;

    if (isEmpty(dList) == 1)
    {
        printf("Masih kosong\n");
        return;
    } 
    
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->prev;
    }

    printf("\n");
}

void hapusDepan(DoublyList *dList)
{
	DoublyListNode *del;
	int d;

	if (isEmpty(dList) == 1)
    {
        printf("Masih kosong\n");
        return;
	} 

    if (dList->head != dList->tail)
    {
        del = dList->head;
        d = del->data;
        dList->head = dList->head->next;
        dList->head->prev = NULL;
        free(del);
    } 
    
    else 
    {
        d = dList->tail->data;
        dList->head = dList->tail = NULL;
    }

    printf("%d terhapus dari depan\n", d);
}

void hapusBelakang(DoublyList *dList)
{
	DoublyListNode *del;
	int d;

	if (isEmpty(dList) == 1)
    {
        printf("Masih kosong\n");
        return;
	} 

    if (dList->head != dList->tail)
    {
        del = dList->tail;
        d = del->data;
        dList->tail = dList->tail->prev;
        dList->tail->next = NULL;
        free(del);
	 } 
     
     else 
     {
		del = dList->head;
        d = del->data;
        dList->head = dList->tail = NULL;
        free(del);
	 }
     
	 printf("%d terhapus dari belakang\n", d);
}

void clear(DoublyList *dList)
{
	DoublyListNode *temp, *del;
	temp = dList->head;
    
	while (temp != NULL)
    {
		del = temp;
		temp = temp->next;
		free(del);
	}

	dList->head = NULL;	
    dList->tail = NULL;	
}

void getFrom(DoublyList *dList, int dataIndex)
{
    if (isEmpty(dList) == 1)
    {
        printf("Masih kosong\n");
    }

    DoublyListNode *temp = dList->head;
    int i = 0;

    while (temp->next != NULL && i < dataIndex)
    {
        temp = temp->next;
        i++;
    }

    printf("Data pada index %d : %d\n", i, temp->data);
}

void removeData(DoublyList *dList, int data)
{
    if (isEmpty(dList) == 1)
    {
        printf("Masih kosong\n");
        return;
    } 

    DoublyListNode *temp, *before;
    temp = dList->tail;

    if (temp->data == data)
    {
        hapusBelakang(dList);
        printf("Data %d berhasil dihapus!\n", data);
        return;
    }

    temp = dList->head;

    if (temp->data == data)
    {
        hapusDepan(dList);
        printf("Data %d berhasil dihapus!\n", data);
        return;
    }

    while (temp != NULL && temp->data != data)
    {
        before = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Data tidak ditemukan\n");
        return;
    }

    before->next = temp->next;
    temp->next->prev = before;
    free(temp);
    printf("Data %d berhasil dihapus!\n", data);
}

void insertAfter(DoublyList *dList, int point, int newData)
{
    if (point == dList->tail->data)
    {
        insertBelakang(dList, newData);
        printf("Data %d masuk sebelum %d\n", newData, point);
        return;
    }

    DoublyListNode *temp = dList->head;

    while (temp->next != NULL && temp->data != point) 
    {
        temp = temp->next;
    }

    if (temp->next == NULL && temp->data != point)
    {
        printf("Data tidak ditemukan!\n");
    }

    DoublyListNode *new = (DoublyListNode*) malloc(sizeof(DoublyListNode));
    new->data = newData;
    new->next = temp->next;
    temp->next->prev = new;
    new->prev = temp;
    temp->next = new;
    printf("Data %d masuk sesudah %d\n", newData, point);
}

void insertBefore(DoublyList *dList, int point, int newData)
{
    if (point == dList->head->data)
    {
        insertDepan(dList, newData);
        printf("Data %d masuk sebelum %d\n", newData, point);
        return;
    }

    DoublyListNode *temp = dList->head;

    while (temp->next != NULL) 
    {
        if (temp->next->data == point)
        {
            break;
        }

        temp = temp->next;
    }

    if (temp->next == NULL)
    {
        printf("Data tidak ditemukan!\n");
    }

    DoublyListNode *new = (DoublyListNode*) malloc(sizeof(DoublyListNode));
    new->data = newData;
    new->next = temp->next;
    temp->next->prev = new;
    temp->next = new;
    new->prev = temp;
    printf("Data %d masuk sebelum %d\n", newData, point);
}

int main()
{
    DoublyList dlist;
    init(&dlist);

    tampilDepan(&dlist);
    tampilBelakang(&dlist);

    insertDepan(&dlist, 10);
    insertDepan(&dlist, 30);
    insertDepan(&dlist, 40);

    removeData(&dlist, 30);
    removeData(&dlist, 20);

    tampilDepan(&dlist);
    tampilBelakang(&dlist);

    insertBelakang(&dlist, 20);
    insertBelakang(&dlist, 50);
    insertAfter(&dlist, 20, 100);
    insertBefore(&dlist, 10, 200);

    tampilDepan(&dlist);
    tampilBelakang(&dlist);

    getFrom(&dlist, 2);
    getFrom(&dlist, 3);

    hapusBelakang(&dlist);
    hapusDepan(&dlist);

    clear(&dlist);

    tampilDepan(&dlist);
    tampilBelakang(&dlist);
}