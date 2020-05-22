#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data-structures.h"
#include "aux.h"


path* bfs(graph *g, int sV, int dV);

int main (void)
{
	graph g1;
	path *p;

	load_graph(&g1);
	p = bfs(&g1,7,3);
	gen_svg(&g1, "color.neato");
	if ( p )
		color_path("color.neato", p);
}

path* bfs(graph *g, int sV, int dV)
{
	int visited[g->nV]; 
	vertex *trav, *lvl;
	queue *aux = (queue *)calloc(1, sizeof(queue));
	struct backtrack  bt[g->nV];
	/* if sV or dV are isolated return NULL (no possible path) */
	if ( g->v[sV].next == NULL || g->v[dV].next == NULL )
		return NULL;
	/* Initialize visited array with 0 and, distances with "infinit" */
	for (int i = 0; i < g->nV; i++){
		bt[i].dist = g->nV + 1;
		visited[i] = 0;
	}
	enqueue(aux, &g->v[sV]);

	visited[sV] = 1;
	bt[sV].dist = 0;
	bt[sV].from = sV;

	while ( !empty(aux) ){
		trav =(vertex *) dequeue(aux);
		lvl = trav;

		while ( trav != NULL ){
			if ( !visited[trav->id] ){
				enqueue(aux, &g->v[trav->id]);
				visited[trav->id] = 1;
			}
			if (bt[trav->id].dist > bt[lvl->id].dist + 1){
				bt[trav->id].dist = bt[lvl->id].dist + 1;
				bt[trav->id].from = lvl->id;
			}
			if (trav->id == dV)
				return gen_path(sV, dV, bt);
			trav = trav->next;
		}
	
	}
	return NULL;
}
