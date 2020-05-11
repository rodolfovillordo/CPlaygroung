#include <stdio.h>
#include <stdlib.h>

void s(int *i, int v){
	*i = v;
}


/* Need to receive a reference for the original pointer, otherwise the 
 * scope of the memory alocated will end with the end of the function and
 */
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
