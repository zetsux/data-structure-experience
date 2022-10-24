#include <stdio.h>
#include <stdlib.h>
	
#define RED 0
#define BLACK 1
 
struct node {
    int data;
    int color;
    struct node* parent;
    struct node* right;
    struct node* left;
};

struct node *root = NULL;
struct node *nill = NULL;

void left_rotate(struct node *x)
{
	struct node *y;
	
	y = x->right;
	x->right = y->left;

	if(y->left != nill)
    {
		y->left->parent = x;
	}

	y->parent = x->parent;

	if(y->parent == nill)
    {
		root = y;
	}

	else if(x == x->parent->left)
    {
		x->parent->left = y;
	}

	else
    {
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

void right_rotate(struct node *x)
{
	struct node *y;
	y = x->left;
	x->left = y->right;

	if(y->right != nill)
    {
		y->right->parent = x;
	}

	y->parent = x->parent;

	if(y->parent == nill)
    {
		root = y;
	}

	else if(x == x->parent->left)
    {
		x->parent->left = y;	
	}

	else
    {
		x->parent->right = y;
	}

	y->right = x;
	x->parent = y;
}

void redblack_insert_arrange(struct node *z)
{
	while(z->parent->color == RED)
    {
		if(z->parent == z->parent->parent->left)
        {
			if(z->parent->parent->right->color == RED){
				z->parent->color = BLACK;
				z->parent->parent->right->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}

			else
            {
				if(z == z->parent->right)
                {
					z = z->parent;
					left_rotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(z->parent->parent);
			}
		}

		else
        {
			if(z->parent->parent->left->color == RED)
            {
				z->parent->color = BLACK;
				z->parent->parent->left->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}

			else
            {
				if(z == z->parent->left)
                {
					z = z->parent;
					right_rotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(z->parent->parent);
			}
		}
	}

	root->color = BLACK;
}
 
void redblack_insert(int d, struct node *ch)
{
	if (ch != nill)
	{
		printf("Data %d sudah ada di dalam tree..\n", d);
		return;
	}

	struct node *z, *x, *y;
	z = malloc(sizeof(struct node));

	z->data = d;
	z->color = RED;
	z->left = nill;
	z->right = nill;

	x = root;
	y = nill;

	while(x != nill)
    {
		y = x;

		if(z->data <= x->data)
        {
			x = x->left;
		}

		else
        {
			x = x->right;
		}
	}

	if(y == nill)
    {
		root = z;
	}

	else if(z->data <= y->data)
    {
		y->left = z;
	}

	else
    {
		y->right = z;
	}

	z->parent = y;

	redblack_insert_arrange(z);
	printf("Data %d Berhasil Dimasukkan!\n", d);
}

struct node *search(int d)
{
	struct node *x;

	x = root;
	while(x != nill && x->data != d)
    {
		if(d < x->data){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}

	return x;
}

struct node *minimum(struct node *x)
{
	while(x->left != nill){
		x = x->left;
	}
	return x;
}
 
void redblack_delete_arrange(struct node *x)
{
	struct node *w;	

	while(x != root && x->color == BLACK)
    {
		
		if(x == x->parent->left)
        {
			w = x->parent->right;

			if(w->color == RED)
            {
				w->color = BLACK;
				x->parent->color = RED;
				left_rotate(x->parent);
				w = x->parent->right;
			}

			if(w->left->color == BLACK && w->right->color == BLACK)
            {
				w->color = RED;
				x->parent->color = BLACK;
				x = x->parent;
			}

			else
            {
				if(w->right->color == BLACK)
                {
					w->color = RED;
					w->left->color = BLACK;
					right_rotate(w);
					w = x->parent->right;
				}

				w->color = x->parent->color;
				x->parent->color = BLACK;
				x->right->color = BLACK;
				left_rotate(x->parent);
				x = root;		
			}

		}

		else
        {
			w = x->parent->left;

			if(w->color == RED)
            {
				w->color = BLACK;
				x->parent->color = BLACK;
				right_rotate(x->parent);
				w = x->parent->left;
			}

			if(w->left->color == BLACK && w->right->color == BLACK)
            {
				w->color = RED;
				x->parent->color = BLACK;
				x = x->parent;
			}

			else
            {

				if(w->left->color == BLACK)
                {
					w->color = RED;
					w->right->color = BLACK;
					left_rotate(w);
					w = x->parent->left;
				}

				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				right_rotate(x->parent);
				x = root;

			}
		}
	}

	x->color = BLACK;
}

void redblack_transplant(struct node *u, struct node *v)
{
	if(u->parent == nill)
    {
		root = v;
	}

	else if(u == u->parent->left)
    {
		u->parent->left = v;
	}
    
	else
    {
		u->parent->right = v;
	}

	v->parent = u->parent;
}

void redblack_delete(int d, struct node *z)
{
	if (z == nill)
	{
		printf("Data %d tidak ditemukan pada tree..\n", d);
		return;
	}

	struct node *y, *x;
	int yOriColor;

	y = z;
	yOriColor = y->color;

	if(z->left == nill)
    {
		x = z->right;
		redblack_transplant(z, z->right);
	}

	else if(z->right == nill)
    {
		x = z->left;
		redblack_transplant(z, z->left);
	}

	else
    {
		y = minimum(z->right);
		yOriColor = y->color;

		x = y->right;

		if(y->parent == z)
        {
			x->parent = y;
		}

		else
        {
			redblack_transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		redblack_transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	if(yOriColor == BLACK)
    {
		redblack_delete_arrange(x);
	}

	printf("Penghapusan Data %d Berhasil!\n", d);
}

void insert(int input)
{
    redblack_insert(input, search(input));
}

void delete(int input)
{
    redblack_delete(input, search(input));
}

void inorder(struct node *x)
{
	if(x != nill)
    {
		inorder(x->left);
		printf("%d ", x->data);
		inorder(x->right);
	}
}

void init()
{
    nill = malloc(sizeof(struct node));
    nill->color = BLACK;
    root = nill;
}

int main()
{
    init();
    int i;
    for (i = 1 ; i <= 100 ; i++)
    {
    	insert(i);
	}

    inorder(root);
    puts("");
    
    for (i = 5 ; i <= 100 ; i += 5)
    {
    	delete(i);
	}

    inorder(root);
    puts("");
 
    return 0;
}
