#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ROTATE_LIMIT 3
#define MAX_ELEMENTS 10
#define INVALID_POINTER (void *)0xFFFFFFFFFFFFFFFF

struct h_node {
	char *k;
	void *v;
	struct h_node *next;
};

struct element {
	int v;
	char name[10];
};

int hash (const char *n);
void* h_lookup(struct h_node *ht[], const char *n);
void* h_delete(struct h_node *ht[], char *k);
int h_insert(struct h_node *ht[], char *k, void *v);

int main(void)
{
	struct element e1 = { .v = 10, .name = "el1" };
	struct element e2 = { .v = 10, .name = "el2" };
	struct element e3 = { .v = 10, .name = "el3" };
	//struct element tmp;
	struct h_node *h[MAX_ELEMENTS] = {NULL};

	h_insert(h,e1.name, &e1);
	h_insert(h,e2.name, &e2);
	h_insert(h,e3.name, &e3);
	h_insert(h,"dummy", (void *)123);
	h_insert(h,"wasItcoincidence", (void *)123);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
	printf(" dummy: %d \n", (int)h_lookup(h, "dummy"));
#pragma GCC diagnostic pop
/*	tmp = *(struct element *)h_delete(&h, e3.name);
	printf("deleted el3 = { name: %s, v: %d }\n", tmp.name, tmp.v);
	*/
	return 0;

}

int h_insert(struct h_node *ht[], char *k, void *v)
{
	struct h_node **cur, *prev;
	int li = 0;
	int i = hash(k);
	if (h_lookup(ht, k) != INVALID_POINTER)
		return 0;
	prev = NULL;
	cur = &ht[i];
	while((*cur) != NULL){
		prev = (*cur);
		(*cur) = prev->next;
		li++;
	}
	if(li < ROTATE_LIMIT){
		(*cur) = (struct h_node*) malloc(sizeof(struct h_node));	
		(*cur)->k = k;
		(*cur)->v = v;
		(*cur)->next = NULL;
		if (prev)
			prev->next = (*cur);
		return 1;
	}
	return 0;
}

int hash (const char *n)
{
	unsigned long long hash = 2048;
	char c;
	while ( c = *n++)
		hash = ( (hash << 5) + hash ) + c;

	return hash % MAX_ELEMENTS;
}


void* h_lookup(struct h_node *ht[], const char *n)
{
	int i = hash(n);
	struct h_node *el;
	el = ht[i];
	while (el)
	{
		if (strcmp(el->k, n) == 0){
			return el->v;
		}
		el = el->next;
	}
	return INVALID_POINTER;
}

void* h_delete(struct h_node *ht[], char *k)
{
	int i = hash(k);
	struct h_node **el;
	struct h_node *prev;
	void *tmp;

	el = &ht[i];
	prev = (*el);
	while (*el){
		if (strcmp((*el)->k, k) == 0){
			tmp = (*el)->v;
			if ((*el)->next && prev != (*el)){
				prev->next = (*el)->next;
				free(*el);
			}
			return tmp;
		}
	}

	return NULL;
}
