#include <stdlib.h>
#include <stdio.h>

#define DEBUG 0

struct node {
	int v;
	struct node *l;
	struct node *r;
};

int add(struct node **tree, int v);
int del(struct node **tree, int v);
int search(struct node *tree, int v);
void print_inorder(struct node *tree);
void print_preorder(struct node *tree);
void print_postorder(struct node *tree);
void init_node(struct node **node);

int main(void) {
	struct node *tree;
	int n;
	int v;

	init_node(&tree);
#if DEBUG	
	printf("tree: %p, tree->v: %d, tree->l: %p, tree-r: %p\n", tree, tree->v,
			tree->l, tree->r);
#endif

	scanf("%d", &n);
	scanf("%d",&v);
	tree->v = v;

	while (n > 1){
		scanf("%d",&v);
		add(&tree, v);
		n--;
	}

	printf("del(6): %d\n", del(&tree, 6));
	printf(" Inorder:\n");
	print_inorder(tree);

}

void init_node(struct node **node)
{
	struct node **ref = node;
	*ref = malloc(sizeof(struct node));
	(*ref)->v = 0;
	(*ref)->l = NULL;
	(*ref)->r = NULL;
}

int add (struct node **tree, int v)
{
	struct node **trav = tree;
	if ( v > (*trav)->v ){
		if ( (*trav)->r != NULL ){
			trav = &(*trav)->r;
			add(trav, v);
		} else {
			init_node(&(*trav)->r);
			(*trav)->r->v = v;
		}
	} else {
		if ( (*trav)->l != NULL ){
			trav = &(*trav)->l;
			add(trav, v);
		} else {
			init_node(&(*trav)->l);
			(*trav)->l->v = v;
		}
	}
}
int del (struct node **tree, int v)
{
	struct node **trav = tree;
	struct node *aux;

	if ( *trav == NULL )
		return 0;

	if ( (*trav)->l->v == v ){
		aux = (*trav)->l;
		if ( (*trav)->l->r != NULL )
			(*trav)->l = (*trav)->l->r;
		else
			(*trav)->l = (*trav)->l->l;
		free(aux);
		return 1;
	}
	if ( (*trav)->r->v == v ){
		aux = (*trav)->r;
		if ( (*trav)->r->r != NULL )
			(*trav)->r = (*trav)->r->r;
		else
			(*trav)->r = (*trav)->r->l;
		free(aux);
		return 1;
	}
	if ( (*trav)->v > v )
		del(&(*trav)->l, v);
	else
		del(&(*trav)->r, v);

	return 1;
}

void print_inorder(struct node *tree)
{
	struct node *trav = tree;

	if (trav == NULL )
		return;
	if (trav->l != NULL)
		print_inorder(trav->l);

	printf("%d ", trav->v);

	if (trav->r != NULL)
		print_inorder(trav->r);
}

void print_preorder(struct node *tree)
{
	struct node *trav = tree;

	if ( trav == NULL )
		return;

	printf("%d ", trav->v);

	if ( trav->l != NULL )
		print_preorder(trav->l);

	if ( trav->r != NULL )
		print_preorder(trav->r);
}

void print_postorder (struct node *tree)
{
	struct node *trav = tree;

	if ( trav == NULL )
		return;

	if ( trav->l != NULL )
		print_postorder(trav->l);
	if ( trav->r != NULL )
		print_postorder(trav->r);

	printf("%d ", trav->v);
}

int search(struct node *tree, int v)
{
	struct node *trav = tree;

	if ( trav == NULL )
		return 0;
	if ( v == trav->v )
		return v;

	if ( v > trav->v )
		search(trav->r, v);
	else
		search(trav->l, v);
}

