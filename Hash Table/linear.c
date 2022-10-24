#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int key;
    char name[1000];
} Peoples;

int 
main ()
{
    Peoples person[701] = {0};

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

            int pos = num % 701;
            int cap = pos;

            while (person[pos].key != 0 && person[pos].key != -1 && pos <= 700)
            {
                pos++;
            }

            if (pos >= 701)
            {
                pos = 0;

                while (person[pos].key != 0 && person[pos].key != -1 && pos <= cap)
                {
                    pos++;
                }
            }

            if (person[pos].key > 0)
            {
                printf("Linear Hash Database is full, please delete some data\n");
                continue;
            }

            person[pos].key = num;
            strcpy(person[pos].name, name);
            printf("ID %d with the name %s is successfully inserted into index %d\n", num, name, pos);
        }

        else if (command == 2)
        {
            int num;
            printf("Insert ID to search for : ");
            scanf("%d", &num);

            int pos = num % 701;
            int cap = 701, posawal = pos;

            while (pos <= 700)
            {
                if (person[pos].key == num)
                {
                    printf("The ID %d with the name %s is located in index %d\n", num, person[pos].name, pos);
                    break;
                }

                else if (person[pos].key == 0 || pos >= cap)
                {
                    printf("The ID %d is not found in database\n", num);
                    break;
                }

                pos++;
                if (pos >= 701 && cap == 701)
                {
                    cap = posawal;
                    pos = 0;
                }
            }
        }

        else if (command == 3)
        {
            int num;
            printf("Insert ID to delete : ");
            scanf("%d", &num);

            int pos = num % 701;
            int cap = 701, posawal = pos;

            while (pos <= 700)
            {
                if (person[pos].key == num)
                {
                    person[pos].key = -1;
                    printf("The ID %d with the name %s is sucessfully deleted\n", num, person[pos].name, pos);
                    break;
                }

                else if (person[pos].key == 0 || pos >= 701)
                {
                    printf("The ID %d is not found in database\n", num);
                    break;
                }

                pos++;
                if (pos >= 701 && cap == 701)
                {
                    cap = posawal;
                    pos = 0;
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