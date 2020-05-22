#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data-structures.h"

struct backtrack {
	int dist;
	int from;
};

path* gen_path(int sV, int dV, struct backtrack *bt);
void load_graph(graph *g);
path* bfs(graph *g, int sV, int dV);

int main (void)
{
	graph g1;
	path *p;

	load_graph(&g1);
	p = bfs(&g1,7,3);
	gen_svg(&g1, "color.neato", 0);
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

void load_graph(graph *g)
{
	int v;
	char buff[100];
	char *token;
	scanf("%d%*c", &v);
	init_graph(g, v);
	for (int i = 0; i < v; i++){
		scanf("%[^\n]%*c", buff);
		token = strtok(buff, " ");
		while (token != NULL){
			if (atoi(token) == -1){
				token = strtok(NULL, " ");
				continue;
			}
			add_edge(g, i, atoi(token));
			token = strtok(NULL, " ");
		}
	}
}

path* gen_path(int sV, int dV, struct backtrack *bt)
{
	path *p = malloc(sizeof(p));
	int j = dV;

	p->nV = bt[dV].dist + 1;
	p->p = (int *)calloc(p->nV, sizeof(int));
	p->p[bt[dV].dist] = dV;
	for (int i = p->nV - 2; i >= 0; i--){
		p->p[i] = bt[j].from;
		j = bt[j].from;
	}
	return p;
}
