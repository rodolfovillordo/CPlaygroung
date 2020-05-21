#include <stdlib.h>

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct vertex {
	int id;
	struct vertex *next;
} vertex;

typedef struct graph {
	int nV;
	vertex *v;
}graph;

struct element {
	void *el;
	struct element *next;
};
typedef struct queue {
	int size;
	struct element *first;
	struct element *last;
} queue;
void init_graph(graph *g, int nv);
int add_vertex(vertex* prev, int id);
int add_edge(graph *g, int vO, int vD);
int empty(queue *q) { return !q->size; }
int enqueue(queue *q, void *el);
void* dequeue(queue *q);
void gen_svg(graph *g, char *filename);
void collor_path(char *filename, graph *path);

void init_graph(graph *g, int nv)
{
	g->nV = nv;
	g->v = malloc(nv*sizeof(vertex));
	for (int i = 0; i < nv; i++){
		g->v[i].id = -1;
		g->v[i].next = NULL;
	}
}

int add_vertex(vertex* prev, int id)
{
	prev->next = (vertex *)malloc(sizeof(vertex));
	prev->next->id = id;
	prev->next->next = NULL;
}

int add_edge(graph *g, int vO, int vD)
{
	vertex *trav;

	if (vO < 0 || vO > (g->nV - 1))
		return 0;
	if (vD < 0 || vD > (g->nV -1))
		return 0;
	if (g->v[vO].id == -1){
		g->v[vO].id = vO;
		add_vertex(&(g->v[vO]), vD);
		return 1;
	}
	trav = &g->v[vO];
	while (trav->next != NULL)
		trav = trav->next;

	add_vertex(trav, vD);
}

void gen_svg(graph *g, char *filename)
{
	FILE *fd;
	vertex *trav;
	fd = fopen(filename, "w+");
	if (fd == NULL){
		perror("fopen: ");
	}
	fprintf(fd,"strict graph %s\n{\n", filename);
	for (int i = 0; i < g->nV; i++){
		fprintf(fd, "\t %d -- { ", i);
		trav = g->v[i].next;
		while (trav != NULL){
			fprintf(fd, "%d ", trav->id);
			trav = trav->next;
		}
		fprintf(fd, "}\n");
	}
	fprintf(fd, "}\n");

	fclose(fd);
	free(trav);
}

void collor_path(char *filename, graph *path)
{
	FILE *fd;

	fd = fopen(filename, "r+");
	if (fd == NULL)
		perror("fopen: ");
	fseek(fd, -2, SEEK_END);
	for (int i = 0; i < path->nV; i++){
		fprintf(fd, "\t%d: [collor=red]\n", path->v[i].id);
	}

	fprintf(fd, "}\n");
	fclose(fd);
}

int enqueue(queue *q, void *el)
{
	struct element *aux = (struct element *)malloc(sizeof(struct element)); 
	aux->el = el;
	if (q->size == 0)
		q->first = aux;
	else
		q->last->next = aux;
	q->last = aux;
	q->size++;

	return q->size;
}

void* dequeue(queue *q)
{
	void *aux;
	struct element *f;
	if (q->size < 1)
		return NULL;
	aux = q->first->el;
	f = q->first;
	if (q->size == 1)
		q->first = q->last = NULL;
	else
		q->first = q->first->next;
	q->size--;
	free(f);
	return aux;
}
			
#endif
