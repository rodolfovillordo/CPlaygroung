#include <stdlib.h>
#include <stdio.h>
#include "data-structures.h"
#include "aux.h"

int* topsort(graph *g);
int dfs(graph *g, int at, int *ordering, int i, int *visited);

int main(void)
{
	graph g;
	int *order;
	load_graph(&g);
	order = topsort(&g);
	gen_svg(&g, "directed.dot", 1);
	for (int i = 0; i < g.nV; i++)
		printf("%d, ", order[i]);
	printf("\n");

	return 0;
}

int* topsort(graph *g)
{
	int *visited;
	int i;
	int *ordering;
	
	ordering = calloc(g->nV, sizeof(int));
	visited = calloc(g->nV, sizeof(int));
	i = g->nV - 1;

	for (int at = 0; at < g->nV; at++){
		if (!visited[at])
			i = dfs(g, at, ordering, i, visited);
	}
	return ordering;
}

int dfs(graph *g, int at, int *ordering, int i, int *visited)
{
	vertex *trav = &g->v[at];
	vertex *prev;
	visited[at] = 1;	

	while( trav ){
		if ( !visited[trav->id] )
			i = dfs(g, trav->id, ordering, i, visited);
		prev = trav;
		trav = trav->next;
	}
	ordering[i] = prev->id;
	return i - 1;
}
