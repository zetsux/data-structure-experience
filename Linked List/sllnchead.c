#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct s_node {
    int data;
    struct s_node *next;
} SinglyListNode;

typedef struct s_list {
    SinglyListNode *head;
} SinglyList;

void init(SinglyList *sList) 
{
    sList->head = NULL;
}

int isEmpty(SinglyList *sList)
{
	if (sList->head == NULL) return 1;
	else return 0;
}

void insertDepan(SinglyList *sList, int newData)
{
    SinglyListNode *new = (SinglyListNode*) malloc(sizeof(SinglyListNode));
    new->data = newData;
    new->next = NULL;

    if (isEmpty(sList) == 1)
    {
        sList->head = new;
        sList->head->next = NULL;
    }

    else 
    {
        new->next = sList->head;
        sList->head = new;
    }

    printf("Data %d masuk di depan\n", newData);
} 

void insertBelakang(SinglyList *sList, int newData)
{
    SinglyListNode *new = (SinglyListNode*) malloc(sizeof(SinglyListNode));
    new->data = newData;
    new->next = NULL;

    if (isEmpty(sList) == 1)
    {
        sList->head = new;
        sList->head->next = NULL;
    }

    else 
    {
        SinglyListNode *temp = sList->head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = new;
    }

    printf("Data %d masuk di belakang\n", newData);
}

void tampil(SinglyList *sList)
{
    SinglyListNode *temp;
    temp = sList->head;

    if (isEmpty(sList) == 1)
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

void hapusDepan(SinglyList *sList)
{
	SinglyListNode *del;
	int d;

	if (isEmpty(sList) == 1)
    {
        printf("Masih kosong\n");
        return;
	} 

    if (sList->head->next != NULL)
    {
        del = sList->head;
        d = del->data;
        sList->head = sList->head->next;
        free(del);
    } 
    
    else 
    {
        d = sList->head->data;
        sList->head = NULL;
    }

    printf("%d terhapus\n", d);
}

void hapusBelakang(SinglyList *sList)
{
	SinglyListNode *del, *temp;
	int d;

	if (isEmpty(sList) == 1)
    {
        printf("Masih kosong\n");
        return;
	} 

    if(sList->head->next != NULL)
    {
		temp = sList->head;

		while (temp->next->next != NULL)
        {		  
		    temp = temp->next;
		}

		del = temp->next;
		d = del->data;
      	temp->next = NULL;
		free(del);
	 } 
     
     else 
     {
		d = sList->head->data;
		sList->head = NULL;
	 }
     
	 printf("%d terhapus\n", d);
}

void clear(SinglyList *sList)
{
	SinglyListNode *temp, *del;
	temp = sList->head;
    
	while (temp != NULL)
    {
		del = temp;
		temp = temp->next;
		free(del);
	}

	sList->head = NULL;	
}

void getFrom(SinglyList *sList, int dataIndex)
{
    if (isEmpty(sList) == 1)
    {
        printf("Masih kosong\n");
        return;
    }

    SinglyListNode *temp = sList->head;
    int i = 0;

    while (temp->next != NULL && i < dataIndex)
    {
        temp = temp->next;
        i++;
    }

    printf("Data pada index %d : %d\n", i, temp->data);
}

void removeData(SinglyList *sList, int data)
{
    if (isEmpty(sList) == 1)
    {
        printf("Masih kosong\n");
        return;
    } 

    SinglyListNode *temp, *before;
    temp = sList->head;

    if (temp->data == data)
    {
        hapusDepan(sList);
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
    free(temp);
    printf("Berhasil menghapus data %d!\n", data);
}

void insertAfter(SinglyList *sList, int point, int newData)
{
    SinglyListNode *temp = sList->head;

    while (temp->next != NULL && temp->data != point) 
    {
        temp = temp->next;
    }

    if (temp->next == NULL && temp->data != point)
    {
        printf("Data tidak ditemukan!\n");
    }

    SinglyListNode *new = (SinglyListNode*) malloc(sizeof(SinglyListNode));
    new->data = newData;
    new->next = temp->next;
    temp->next = new;
    printf("Data %d masuk sesudah %d\n", newData, point);
}

void insertBefore(SinglyList *sList, int point, int newData)
{
    if (point == sList->head->data)
    {
        insertDepan(sList, newData);
        printf("Data %d masuk sebelum %d\n", newData, point);
        return;
    }

    SinglyListNode *temp = sList->head;

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

    SinglyListNode *new = (SinglyListNode*) malloc(sizeof(SinglyListNode));
    new->data = newData;
    new->next = temp->next;
    temp->next = new;
    printf("Data %d masuk sebelum %d\n", newData, point);
}

int main()
{
    SinglyList slist;
    init(&slist);

    tampil(&slist);

    insertDepan(&slist, 10);
    insertDepan(&slist, 30);
    insertDepan(&slist, 40);

    removeData(&slist, 30);
    removeData(&slist, 20);
    tampil(&slist);

    insertBelakang(&slist, 20);
    insertBelakang(&slist, 50);
    insertAfter(&slist, 20, 100);
    insertBefore(&slist, 10, 200);

    tampil(&slist);
    getFrom(&slist, 2);
    getFrom(&slist, 3);

    hapusBelakang(&slist);
    hapusDepan(&slist);

    clear(&slist);

    tampil(&slist);
}





