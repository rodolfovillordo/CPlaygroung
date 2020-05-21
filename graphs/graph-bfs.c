#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data-structures.h"

struct backtrack {
	int dist;
	int from;
};

void load_graph(graph *g);
graph* gen_path(int sV, int dV, struct backtrack *bt);
graph* bfs(graph *g, int sV, int dV);

int main (void)
{
	graph g1;
	graph *path;
	int *t = malloc(sizeof(int));
	load_graph(&g1);
	path = bfs(&g1,7,3);
	gen_svg(&g1, "color.neato");
	collor_path("color.neato", path);
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

graph* bfs(graph *g, int sV, int dV)
{
	int visited[g->nV]; 
	vertex *trav, *lvl;
	queue *aux = (queue *)calloc(1, sizeof(queue));
	struct backtrack  bt[g->nV];
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
				enqueue(aux, trav);
				visited[trav->id] = 1;
			}
			if (bt[trav->id].dist > bt[lvl->id].dist + 1){
				bt[trav->id].dist = bt[lvl->id].dist + 1;
				bt[trav->id].from = bt[lvl->id].from;
			}
			if (trav->id == dV)
				return gen_path(sV, dV, bt);
			trav = trav->next;
		}
	
	}
	return NULL;
}

graph* gen_path(int sV, int dV, struct backtrack *bt)
{
	graph *path;
	int i = dV;
	init_graph(path, bt[dV].dist + 1);
	while ( i != sV ){
		add_edge(path, i, bt[i].from);
		i = bt[i].from;
	}
	return path;
}
