#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data-structures.h"

void load_graph(graph *g);
graph* bfs(graph g, int sV, int dV);

int main (void)
{
	graph g1;
	load_graph(&g1);
	gen_svg(g1, "cgraph.neato");

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

vertex* bfs(graph g, int sV, int dV)
{
	int visited[g.nV] = { 0 };
	vertex *trav, *lvl;
	queue aux;
	struct backtrack {
		int dist;
		int from;
	} bt[g.nV] = { };
	enqueue(aux, &g.v[sV]);

	visited[sV] = 1;

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
			trav = trav->next;
		}
	
	}
}
