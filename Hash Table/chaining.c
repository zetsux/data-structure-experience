#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define hashSize 7

typedef struct s_node {
    int key;
    char name[1000];
    struct s_node *next;
} SinglyListNode;

typedef struct s_list {
    SinglyListNode *head;
    SinglyListNode *tail;
} SinglyList;

void init(SinglyList *sList) 
{
    sList->head = NULL;
    sList->tail = NULL;
}

int isEmpty(SinglyList *sList)
{
	if (sList->tail == NULL) return 1;
	else return 0;
}

void insert(SinglyList *sList, int newData, char str[])
{
    SinglyListNode *new = (SinglyListNode*) malloc(sizeof(SinglyListNode));
    new->key = newData;
    strcpy(new->name, str);
    new->next = NULL;

    if (isEmpty(sList) == 1)
    {
        sList->head = sList->tail = new;
        sList->tail->next = NULL;
    }

    else 
    {
        sList->tail->next = new;
        sList->tail = new;
    }
}

void hapusDepan(SinglyList *sList)
{
	SinglyListNode *del;

	if (isEmpty(sList) == 1)
    {
        return;
	} 

    if (sList->head != sList->tail)
    {
        del = sList->head;
        sList->head = sList->head->next;
        free(del);
    } 
    
    else 
    {
        sList->head = sList->tail = NULL;
    }
}

void deleteData(SinglyList *sList, int data, int index)
{
    if (isEmpty(sList) == 1)
    {
        printf("The ID %d is not found in database\n", data);
        return;
    } 

    SinglyListNode *temp, *before;
    temp = sList->head;

    if (temp->key == data)
    {
        printf("The ID %d with the name %s is sucessfully deleted from index %d, position 0\n", data, temp->name, index);
        hapusDepan(sList);
        return;
    }

    int count = 0;

    while (temp != NULL && temp->key != data)
    {
        before = temp;
        temp = temp->next;
        count++;
    }

    if (temp == NULL)
    {
        printf("The ID %d is not found in database\n", data);
        return;
    }

    printf("The ID %d with the name %s is sucessfully deleted from index %d, position %d\n", data, temp->name, index, count);
    before->next = temp->next;
    free(temp);
}

void findData(SinglyList *sList, int data, int index)
{
    if (isEmpty(sList) == 1)
    {
        printf("The ID %d is not found in database\n", data);
        return;
    } 

    SinglyListNode *temp;
    temp = sList->head;

    if (temp->key == data)
    {
        printf("The ID %d with the name %s is located in index %d, position 0\n", data, temp->name, index);
        return;
    }

    int count = 0;

    while (temp != NULL && temp->key != data)
    {
        temp = temp->next;
        count++;
    }

    if (temp == NULL)
    {
        printf("The ID %d is not found in database\n", data);
        return;
    }

    printf("The ID %d with the name %s is located in index %d, position %d\n", data, temp->name, index, count);
    return;
}

int 
main ()
{
    SinglyList person[hashSize];
    for (int i = 0; i < hashSize; i++)
    {
        init(&person[i]);
    }

    while(1)
    {
        int command;
        printf("\t- Command List -\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Exit\n");
        printf("Enter the index of the command you want to do : ");
        scanf("%d", &command);

        if (command == 1)
        {
            int num;
            char name[1000];
            printf("Insert your ID : ");
            scanf("%d", &num);
            getchar();
            printf("Insert your name : ");
            gets(name);

            int pos = num % hashSize;
            insert(&person[pos], num, name);
            printf("ID %d with the name %s is successfully inserted into index %d\n", num, name, pos);
        }

        else if (command == 2)
        {
            int num;
            printf("Insert ID to search for : ");
            scanf("%d", &num);

            int pos = num % hashSize;
            findData(&person[pos], num, pos);            
        }

        else if (command == 3)
        {
            int num;
            printf("Insert ID to delete : ");
            scanf("%d", &num);

            int pos = num % hashSize;
            deleteData(&person[pos], num, pos);
        }

        else if (command == 4)
        {
            printf("Thank you for using Hash Database!\n");
            return 0;
        }

        else
        {
            printf("Please enter the correct index according to the command list!\n");
        }
    }
}