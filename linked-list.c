#include <stdio.h>
#include <stdlib.h>

struct node {
	int v;
	struct node *n;
};

int main(void)
{
	struct node l;
	struct node *a;
	l = *(struct node *)malloc(sizeof(struct node));
	a = (struct node *) malloc(sizeof(struct node));
	l.v = 0;
	l.n = a;
	for(int i = 1; i < 10; i++){
		a->v = i;
		a->n = (struct node *) malloc(sizeof(struct node));
		a = a->n;
		a->v = ++i;
		a->n = NULL;
	}
	printf("a l: %p l->v: %d \n", &l, l.v);
	a = l.n;
	while(a){
		printf("a l: %p l->v: %d \n", a, a->v);
		a = a->n;
	}
	return 0;
}
