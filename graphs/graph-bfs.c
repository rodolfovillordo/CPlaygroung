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
	int pV;
	int visited[g.nV] = { 0 };
	vertex *trav, *prev;
	queue aux;
	struct backtrack {
		int distance;
		int prev;
	} bt[g.nV] = { 0 };
	enqueue(aux, &g.v[sV]);

	visited[sV] = -1;
	bt[sV].distance = 0;
	bt[sV].prev = -1;

	while ( !empty(aux) ){
		prev = trav;
		trav =(vertex *) dequeue(aux);
		while ( trav != NULL ){
			if ( !visited[trav->id] ){
				enqueue(aux, trav);
				visited[trav->id] = 1;
			}
			trav = trav->next;
		}
	
	}
}
