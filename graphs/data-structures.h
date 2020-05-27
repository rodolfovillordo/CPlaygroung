#include <stdlib.h>
#include <string.h>

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

typedef struct path {
	int nV;
	int *p;
} path;

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
void gen_svg(graph *g, char *filename, int directed);
void color_path(char *filename, path *p);

void init_graph(graph *g, int nv)
{
	g->nV = nv;
	g->v = malloc(nv*sizeof(vertex));
	for (int i = 0; i < nv; i++){
		g->v[i].id = i;
		g->v[i].next = NULL;
	}
}

int add_vertex(vertex* prev, int id)
{
	prev->next = (vertex *)malloc(sizeof(vertex));
	if ( ! prev->next )
		return 0;
	prev->next->id = id;
	prev->next->next = NULL;
	return 1;
}

int add_edge(graph *g, int vO, int vD)
{
	vertex *trav;

	if (vO < 0 || vO > (g->nV - 1))
		return 0;
	if (vD < 0 || vD > (g->nV -1))
		return 0;

	trav = &g->v[vO];
	while (trav->next != NULL)
		trav = trav->next;

	return add_vertex(trav, vD);
}

/* Generate graph description file in DOT language.
 * http://www.graphviz.org/doc/info/lang.html
 */
void gen_svg(graph *g, char *filename, int directed)
{
	FILE *fd;
	vertex *trav;
	char edge[3];

	if (directed)
		strcpy(edge,"->");
	else
		strcpy(edge,"--");

	fd = fopen(filename, "w+");
	if (fd == NULL){
		perror("fopen: ");
	}

	if ( directed )
		fprintf(fd,"digraph \n{\n");
	else
		fprintf(fd,"strict graph \n{\n");

	for (int i = 0; i < g->nV; i++){
		fprintf(fd, "\t%d %s { ", i, edge);
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

/* Edit graph visialization to color the vertext of a path */
void color_path(char *filename, path *p)
{
	FILE *fd;

	fd = fopen(filename, "r+");
	if (fd == NULL)
		perror("fopen: ");
	fseek(fd, -2, SEEK_END);
	for (int i = 0; i < p->nV; i++){
		fprintf(fd, "\t%d [color=\"darkolivegreen1\",style=\"filled\"];\n", p->p[i]);
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
