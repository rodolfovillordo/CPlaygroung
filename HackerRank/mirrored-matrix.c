#include <stdio.h>
#include <stdlib.h>

void p_mat(int **m, int l, int c){
	for(int i = 0; i < l; i++){
		for(int j = 0; j < c; j++){
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	for(int i = l-2; i >= 0; i--){
		for(int j = 0; j < c; j++){
			printf("%d ",m[i][j]);
		}
		printf("\n");
	}
}

int main() 
{

	int n;
	int **mat;
	scanf("%d", &n);
	mat = malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++) {
		mat[i] = malloc(sizeof(int) * ((2*n)-1) );
		mat[i][0] = n;
		for(int j = 1; j < n - 1; j++){
			if ( j < i)
				mat[i][j] =  n - j;
			else
				mat[i][j] =  n-i;
		}
		for(int j = n-1, k = n -1 ; j > 0; j--, k++) {
			if ( j > i )
				mat[i][k] = n-i;
			else
				mat[i][k] = n-j;
		}	       
		mat[i][(2*n)-2] = n;
	}
	p_mat(mat, n, (2*n)-1);
	return 0;
}


