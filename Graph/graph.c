#include <stdio.h>
#include <stdlib.h>

typedef struct typeS {
    struct typeS *left;
    int info;
    struct typeS *right;
}typeS;

typedef struct typeS simpul;
simpul *p, *first, *last, *pvertex, *pedge, *q, *r, *s;
simpul *points[5];

int main()
{
    int arr[5][5] = {0, 7, 3, 0, 0,  5, 0, 0, 4, 2,  0, 0, 0, 0, 11,  0, 0, 10, 0, 6,  1, 19, 0, 0, 0};
    char nms[5] = "ABCDE";
    int i = 0, j = 0;

    p = (simpul*) malloc(sizeof(simpul));
    p->info = nms[0];
    first = last = p;
    p->left = p->right = NULL;
    points[0] = p;
    printf("%c ", p->info);
    printf("alamat %d\n", points[0]);

    for (i = 1; i <= 4 ; i++)
    {
        p = (simpul*) malloc(sizeof(simpul));
        p->info = nms[i];
        last->left = p;
        last = last->left;
        p->left = p->right = NULL;
        points[i] = p;
        printf("%c ", p->info);
        printf("alamat %d\n", points[i]);
    }

    q = first;
    for (i = 0; i <= 4 ; i++)
    {
        r = q;
        printf("Vertex %c .... ", q->info);

        for (j = 0; j <= 4 ; j++)
        {
            if (arr[i][j] != 0)
            {
                p = (simpul*) malloc(sizeof(simpul));
                p->info = arr[i][j];
                r->right = p;
                p->left = points[j];
                printf("berhubungan dengan %c : bobot %d; ", p->left->info, p->info);
                p->right = NULL;
                r = p;
            }
        }

        printf("\n");
        q = q->left;
    }
}