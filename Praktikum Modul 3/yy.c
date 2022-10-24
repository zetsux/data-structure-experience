#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct avl_node_s {
	struct avl_node_s *left;
	struct avl_node_s *right;
	char* value;
};

typedef struct avl_node_s avl_node_t;

struct avl_tree_s {
	struct avl_node_s *root;
};

typedef struct avl_tree_s avl_tree_t;
char *strdup(const char *);


/* Create a new AVL tree. */
avl_tree_t *avl_create() {
	avl_tree_t *tree = NULL;

	if( ( tree = malloc( sizeof( avl_tree_t ) ) ) == NULL ) {
		return NULL;
	}

	tree->root = NULL;

	return tree;
}

/* Initialize a new node. */
avl_node_t *avl_create_node() {
	avl_node_t *node = NULL;
	
	if( ( node = malloc( sizeof( avl_node_t ) ) ) == NULL ) {
		return NULL;
	}

	node->left = NULL;
	node->right = NULL;
	node->value = malloc( sizeof(char*)*64 );

	return node;	
}

/* Find the height of an AVL node recursively */
int avl_node_height( avl_node_t *node ) {
	int height_left = 0;
	int height_right = 0;

	if( node->left ) height_left = avl_node_height( node->left );
	if( node->right ) height_right = avl_node_height( node->right );

	return height_right > height_left ? ++height_right : ++height_left;
}

/* Find the balance of an AVL node */
int avl_balance_factor( avl_node_t *node ) {
	int bf = 0;

	if( node->left  ) bf += avl_node_height( node->left );
	if( node->right ) bf -= avl_node_height( node->right );

	return bf ;
}

/* Left Left Rotate */
avl_node_t *avl_rotate_leftleft( avl_node_t *node ) {
 	avl_node_t *a = node;
	avl_node_t *b = a->left;
	
	a->left = b->right;
	b->right = a;

	return( b );
}

/* Left Right Rotate */
avl_node_t *avl_rotate_leftright( avl_node_t *node ) {
	avl_node_t *a = node;
	avl_node_t *b = a->left;
	avl_node_t *c = b->right;
	
	a->left = c->right;
	b->right = c->left; 
	c->left = b;
	c->right = a;

	return( c );
}

/* Right Left Rotate */
avl_node_t *avl_rotate_rightleft( avl_node_t *node ) {
	avl_node_t *a = node;
	avl_node_t *b = a->right;
	avl_node_t *c = b->left;
	
	a->right = c->left;
	b->left = c->right; 
	c->right = b;
	c->left = a;

	return( c );
}

/* Right Right Rotate */
avl_node_t *avl_rotate_rightright( avl_node_t *node ) {
	avl_node_t *a = node;
	avl_node_t *b = a->right;
	
	a->right = b->left;
	b->left = a; 

	return( b );
}

/* Balance a given node */
avl_node_t *avl_balance_node( avl_node_t *node ) {
	avl_node_t *newroot = NULL;

	/* Balance our children, if they exist. */
	if( node->left )
		node->left  = avl_balance_node( node->left  );
	if( node->right ) 
		node->right = avl_balance_node( node->right );

	int bf = avl_balance_factor( node );

	if( bf >= 2 ) {
		/* Left Heavy */	

		if( avl_balance_factor( node->left ) <= -1 ) 
			newroot = avl_rotate_leftright( node );
		else 
			newroot = avl_rotate_leftleft( node );

	} else if( bf <= -2 ) {
		/* Right Heavy */

		if( avl_balance_factor( node->right ) >= 1 )
			newroot = avl_rotate_rightleft( node );
		else 
			newroot = avl_rotate_rightright( node );

	} else {
		/* This node is balanced -- no change. */

		newroot = node;
	}

	return( newroot );	
}

/* Balance a given tree */
void avl_balance( avl_tree_t *tree ) {

	avl_node_t *newroot = NULL;

	newroot = avl_balance_node( tree->root );

	if( newroot != tree->root )  {
		tree->root = newroot; 
	}
}

/* Insert a new node. */
void avl_insert( avl_tree_t *tree, char* value ) {
	avl_node_t *node = NULL;
	avl_node_t *next = NULL;
	avl_node_t *last = NULL;

	/* Well, there must be a first case */ 	
	if( tree->root == NULL ) {
		node = avl_create_node();
		node->value = value;

		tree->root = node;

	/* Okay.  We have a root already.  Where do we put this? */
	} else {
		next = tree->root;

		while( next != NULL ) {
			last = next;

			if( strcmp(value,next->value) < 0 ) {
				next = next->left;

			} else if( strcmp(value,next->value) > 0 ) {
				next = next->right;

			/* Have we already inserted this node? */
			} else if( strcmp(value,next->value) == 0 ) {
				return;	
			}
		}

		node = avl_create_node();
		node->value = value;

		if( strcmp(value,last->value) < 0 ) last->left = node;
		if( strcmp(value,last->value) > 0 ) last->right = node;
		
	}

	avl_balance( tree );
}

/* Find the node containing a given value */
avl_node_t *avl_find( avl_tree_t *tree, char* value ) {
	avl_node_t *current = tree->root;

	while( current && (strcmp(current->value,value)!=0) ) {
		if( strcmp(value,current->value) > 0 )
			current = current->right;
		else
			current = current->left;
	}
	return current;
}

/* Do a depth first traverse of a node. */
void avl_traverse_node_dfs( avl_node_t *node, int depth ) {
	int i = 0;

	if( node->left ) avl_traverse_node_dfs( node->left, depth + 2 );

	for( i = 0; i < depth; i++ ) putchar( ' ' );
	printf( "%s: %d\n", node->value, avl_balance_factor( node ) );

	if( node->right ) avl_traverse_node_dfs( node->right, depth + 2 );
}

/* Do a depth first traverse of a tree. */
void avl_traverse_dfs( avl_tree_t *tree ) {
	avl_traverse_node_dfs( tree->root, 0 );
}

int avl_print_node( avl_node_t *node, int index, char *search) {
    int newPos;
    if(node != NULL){
        newPos = avl_print_node( node->left, index, search);
        newPos++;
        if(strcmp(node->value, search)==0){
           printf( "%d\n",  newPos % (1000000007) ); 
        }
	    newPos = avl_print_node( node->right, newPos, search);
    }else{
        return index;
    }
	return newPos;
}

void avl_print( avl_tree_t *tree, char *search) {
	avl_print_node( tree->root, 0, search);
}

void avl_count_node( avl_node_t *node, int* res ) {
	if( node->left ) avl_count_node( node->left, res);
	*res = *res+1;
	if( node->right ) avl_count_node( node->right, res);
}

void avl_count(avl_tree_t *tree, int* res) {
	avl_count_node(tree->root, res);
}

void swap(char *a, char *b) { char t = *a; *a = *b; *b = t; }

void permute(avl_tree_t *t, char *a, int i, int n) {
   // If we are at the last letter, print it
   if (i == (n-1)){
       char* aux; 
       aux = strdup(a);
       avl_insert( t, aux);
   }else {
     // Show all the permutations with the first i-1 letters fixed and 
     // swapping the i'th letter for each of the remaining ones.
     for (int j = i; j < n; j++) {
       swap((a+i), (a+j));
       permute(t, a, i+1, n);
       swap((a+i), (a+j));
     }
  }
}

char *numToStr(int N){
    int a[N];
    for(int j=0;j<N;j++){a[j]=j+1;}
    char * str = malloc (sizeof (char) * N+1);
    int i=0;
    int index = 0;
    for (i=0; i<N+1; i++){
        index += snprintf(&str[index], N+1-index, "%d", a[i]);  
    }
   
    return str;
}

char *strdup(const char *c)
{
    char *dup = malloc(strlen(c) + 1);

    if (dup != NULL)
       strcpy(dup, c);

    return dup;
}

int main( int argc, char **argv ) {
    int charLen, wordCount;
	avl_tree_t *tree = NULL;
	tree = avl_create();
	
    scanf("%d",&wordCount);
    scanf("%d",&charLen);
    
    permute(tree, numToStr(charLen), 0, charLen);
    char val[(charLen*wordCount)];
    char r[wordCount+1];
	char* aux; 
    
    for(int i=0;i<(charLen*wordCount);i++){
        scanf(" %c", &val[i]);
    }
    
    //loop per n of seqlen where n=wordCount
    for(int j =0;j<(charLen*wordCount);j+=charLen){
        //turn n to ni of array to string
        for(int k=0;k<charLen;k++){
            r[k]=val[k+j];
        }
        r[(charLen)]='\0';
        aux = strdup(r);
        avl_print(tree, aux);
    }
	return 0;
}