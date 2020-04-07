#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ROTATE_LIMIT 3
#define MAX_ELEMENTS 10

struct h_node {
	char *k;
	void *obj;
	struct h_node *next;
};

struct element {
	int v;
	char name[10];
};

int hash (const char *n);
void* h_lookup(const struct h_node *ht, char *n);
void* h_delete(struct h_node *ht, char *n);
int h_insert(struct h_node ht[], char *k, void *v);

int main(void)
{
	struct element e1 = { .v = 10, .name = "el1" };
	struct element e2 = { .v = 10, .name = "el2" };
	struct element e3 = { .v = 10, .name = "el3" };
	//struct element tmp;
	struct h_node *h[MAX_ELEMENTS] = {{.v = -1}};

	h_insert(h,e1.name, &e1);
	h_insert(h,e2.name, &e2);
	h_insert(h,e3.name, &e3);
	//h_insert(h,"dummy", (void *)123);


/*	printf("dummy = %d\n", *(int *)h_lookup(&h, "dummy"));
	tmp = *(struct element *)h_delete(&h, e3.name);
	printf("deleted el3 = { name: %s, v: %d }\n", tmp.name, tmp.v);
	*/
	return 0;

}

int h_insert(struct h_node ht[MAX_ELEMENTS], char *k, void *v)
{
	struct h_node *cur, *prev;
	int li = 0;
	int i = hash(k);
	printf("%d\n", i);
	cur = &ht[i];
	while(cur != NULL){
		prev = cur;
		cur = prev->next;
		li++;
	}
	if(li < ROTATE_LIMIT){
		cur = (struct h_node*) malloc(sizeof(struct h_node));	
		cur->k = k;
		cur->obj = v;
		cur->next = NULL;
		prev->next = cur;
		return 1;
	}
	return 0;
}

int hash (const char *n)
{
	unsigned long long hash = 2048;
	int c;
	while ( c = *n++)
		hash = ( (hash << 3) + hash ) + c;

	return hash % MAX_ELEMENTS;
}



