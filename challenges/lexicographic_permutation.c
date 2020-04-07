#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// https://www.quora.com/How-would-you-explain-an-algorithm-that-generates-permutations-using-lexicographic-ordering
void swap(char **s, int first, int second)
{
	char *aux;
	aux = s[first];
	s[first] = s[second];
	s[second] = aux;
}
void reverse(char **s, int from, int till)
{
	while(from < till){
		swap(s, from, till);
		from++;
		till--;
	}
}
int next_permutation(int n, char **s)
{
	int i;
	/* largest elements on array, initialized with invalid index */
	int x = -1, y = -1; 
	int size_a = n - 1;/* array size is n-1 */

	/* run till the last but one element and check s[i] < s[i+1] */
	for(i = 0; i < size_a; i++){
		if (strcmp(s[i], s[i+1]) < 0)
			x = i;
	}
	if (x == -1)
		return 0;

	/* find the largest y where s[x] < s[i] */
	for (i = 0; i <= size_a; i++){
		if(strcmp(s[x], s[i]) < 0)
			y = i;
	}
	swap(s, x, y); /* swap x and y positions */
	reverse(s, x+1, size_a); /* reverse the suffix order of of elements */
	return 1;

}
int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char *));
	for (int i = 0; i < n; i++) {
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do {
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}
