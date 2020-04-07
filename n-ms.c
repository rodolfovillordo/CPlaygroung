#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void ms(int *a, int ini, int end);
void merge(int *a, int ini, int mid, int end);

int main(void)
{
	int n;
	int *a;

	scanf("%d", &n);
	a = (int *)malloc(n*sizeof(int));

	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	ms(a,0,n);

	printf("\n\n");
	for(int i = 0; i < n; i++)
		printf("%d ", a[i]);
}

void ms(int *a, int ini, int end)
{
	int mid;
	if (ini < end) {
		mid = floor((ini + end)/2);
		ms(a, ini, mid);
		ms(a, mid + 1, end);
		merge(a, ini, mid, end);
	}
}

void merge(int *a, int ini, int mid, int end)
{
	int *tmp, p1, p2, size, i, j, k;
	int end1 = 0, end2 = 0;

	size = end - ini;
	p1 = ini;
	p2 = mid +1;
	tmp = (int *) malloc(size*sizeof(int));

	if (tmp != NULL){
		for (i = 0; i < size; i++){
			if (!end1 && !end2){
				if (a[p1] < a[p2])
					tmp[i] = a[p1++];
				else
					tmp[i] = a[p2++];
				if (p1 > mid)
					end1 = 1;
				if (p2 > end)
					end2 = 1;
			} else {
				if(!end1)
					tmp[i] = a[p1++];
				else
					tmp[i] = a[p2++];
			}
		}
		for (j = 0, k = ini; j < size; j++, k++)
			a[k] = tmp[j];
	}
	free(tmp);
}
