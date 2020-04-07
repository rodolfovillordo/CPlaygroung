#include <stdio.h>
#include <stdlib.h>

void printv(int *a)
{
	printf("---");
	for (int i = 0; i < 4; i++)
		printf(" a[%d]: %d ", i, a[i]);
	printf("\n--\n");
}

void merge(int *a, int *aux, int ini, int end)
{
	int m = (ini + end) / 2;
	int i = ini;
	int end_i = m;
	int j = end_i + 1;
	int end_j = end;
	int aux_i = ini;

	while ((i <= end_i) && (j <= end_j)) {
		if (a[i] < a[j]) {
			aux[aux_i] = a[i];
			i++;
		} else {
			aux[aux_i] = a[j];
			j++;
		}
		aux_i++;
	}
	while (i <= end_i) {
		aux[aux_i] = a[i];
		i++;
		aux_i++;
	}
	while (j <= end_j) {
		aux[aux_i] = a[j];
		j++;
		aux_i++;
	}
	i = ini;
	while (i <= end) {
		a[i] = aux[i];
		i++;
	}

}

void merge_sort(int *a, int *aux, int ini, int end)
{
	int mid;
	if (ini < end) {

		mid = (ini + end) / 2;
		merge_sort(a, aux, ini, mid);
		merge_sort(a, aux, mid + 1, end);
		merge(a, aux, ini, end);
	}
}

int main(void)
{
	int n;
	int *a, *aux;

	scanf("%d", &n);
	a = (int *) calloc(n - 1, sizeof(int));
	aux = (int *) calloc(n - 1, sizeof(int));
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	merge_sort(a, aux, 0, n - 1);
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	return 0;
}
