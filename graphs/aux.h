#include <stdio.h>
#include <stdlib.h>
#include "data-structures.h"

#ifndef	AUX_H
#define AUX_H

struct backtrack {
	int dist;
	int from;
};

path* gen_path(int sV, int dV, struct backtrack *bt);
void load_graph(graph *g);

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
#endif
