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

void init_graph(graph *g, int nv);
int add_vertex(vertex* prev, int id);
int add_edge(graph *g, int vO, int vD);

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

void gen_svg(graph g, char *filename)
{
	FILE *fd;
	vertex *trav;
	fd = fopen(filename, "w+");
	if (fd == NULL){
		printf("unable to open file %s. exit(1)\n", filename);
	}
	fprintf(fd,"strict graph %s\n{\n", filename);
	for (int i = 0; i < g.nV; i++){
		fprintf(fd, "\t %d -- { ", i);
		trav = g.v[i].next;
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

			
#endif
