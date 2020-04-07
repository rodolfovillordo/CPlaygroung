#include <stdio.h>
#include <stdlib.h>

void s(int *i, int v){
	*i = v;
}

void f(int **i)
{
	*i = malloc(2 * sizeof(int));
	s(&(*i)[0], 3);
	s(&(*i)[1], 4);
}

int main (void)
{
	int **i;
	i = (int **) malloc(2 * sizeof(int *));
	f(&(i[0]));
	f(&(i[1]));
	printf("%d", i[1][0]);
	return 0;
}
