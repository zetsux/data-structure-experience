#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define hashSize 701

int hashMem = 0;
int imax = 0;

typedef struct {
    int key;
    char name[1000];
} Peoples;

int hash1 (int key)
{
    return key%hashSize;
}

int hash2 (int key)
{
    return 7-(key%7);
}

int doubleHash (int h1, int h2, int i)
{
    return (h1 + (i*h2))%hashSize;
}

int 
main ()
{
    Peoples person[hashSize] = {0};

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
            int num, i = 1;
            char name[1000];
            printf("Insert your ID : ");
            scanf("%d", &num);
            getchar();
            printf("Insert your name : ");
            gets(name);

            int pos = hash1(num);
            int h1 = pos, h2 = hash2(num);

            if (hashMem >= hashSize)
            {
                printf("Linear Hash Database is full, please delete some data\n");
                continue;
            }

            while (person[pos].key != 0 && person[pos].key != -1)
            {
                pos = doubleHash(h1, h2, i++);
            }

            if (i > imax)
            {
                imax = i;
            }
            person[pos].key = num;
            strcpy(person[pos].name, name);
            hashMem++;
            printf("ID %d with the name %s is successfully inserted into index %d\n", num, name, pos);
        }

        else if (command == 2)
        {
            int num, i = 1;
            printf("Insert ID to search for : ");
            scanf("%d", &num);

            int pos = hash1(num);
            int h1 = pos, h2 = hash2(num);

            while (i <= imax)
            {
                if (person[pos].key == num)
                {
                    printf("The ID %d with the name %s is located in index %d\n", num, person[pos].name, pos);
                    break;
                }

                else if (person[pos].key == 0)
                {
                    printf("The ID %d is not found in database\n", num);
                    break;
                }

                pos = doubleHash(h1, h2, i++);
            }

            if (i > imax)
            {
                if (person[pos].key != num)
                {
                    printf("The ID %d is not found in database\n", num);
                }

                else
                {
                    printf("The ID %d with the name %s is located in index %d\n", num, person[pos].name, pos);
                }
            }
        }

        else if (command == 3)
        {
            int num, i = 1;
            printf("Insert ID to delete : ");
            scanf("%d", &num);

            int pos = hash1(num);
            int h1 = pos, h2 = hash2(num);

            while (i <= imax)
            {
                if (person[pos].key == num)
                {
                    person[pos].key = -1;
                    hashMem--;
                    printf("The ID %d with the name %s is successfully deleted from index %d\n", num, person[pos].name, pos);
                    break;
                }

                else if (person[pos].key == 0)
                {
                    printf("The ID %d is not found in database\n", num);
                    break;
                }

                pos = doubleHash(h1, h2, i++);
            }

            if (i > imax)
            {
                if (person[pos].key != num)
                {
                    printf("The ID %d is not found in database\n", num);
                }

                else if (person[pos].key == num && i >= imax)
                {
                    person[pos].key = -1;
                    hashMem--;
                    printf("The ID %d with the name %s is successfully deleted from index %d\n", num, person[pos].name, pos);
                    break;
                }
            }
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