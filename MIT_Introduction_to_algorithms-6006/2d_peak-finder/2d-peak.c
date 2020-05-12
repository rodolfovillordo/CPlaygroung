#include <stdlib.h>
#include <stdio.h>

#define ROWS 3
#define COLS 3

int peak(int **mat, int nr, int nc);
int global_max(int *row, int size);
int r_global_max(int **mat, int rows);
int find_peak(int **mat, int nc, int r_ini, int r_end);

int main(void)
{
	int **mat;

	mat = (int **)malloc(ROWS*sizeof(int *));
	for (int i = 0; i < 3; i++)
		mat[i] = (int *)malloc(COLS*sizeof(int));
	for(int i = 0; i < ROWS; i++)
		for( int j = 0; j < COLS; j++)
			scanf("%d", &mat[i][j]);

	printf("%d\n", peak(mat, ROWS, COLS));
	return 0;
}

int peak(int **mat, int nr, int nc)
{
	return find_peak(mat, nc, 0, nr-1);
}

int find_peak(int **mat, int nc, int r_ini, int r_end)
{
	int mid_r = (r_end - r_ini) / 2; /*Pick a middle column */
	int g_max = 0;
	if (nc == 1)
		return mat[r_global_max(mat, r_end + 1)][0];
	if ( r_ini == r_end )
		return mat[r_ini][global_max(mat[r_ini], nc)];
	/* find the global maximum on column j; */
	g_max = global_max(mat[mid_r], nc);
	if (mat[mid_r][g_max] >= mat[mid_r-1][g_max] && mat[mid_r][g_max] >=
			mat[mid_r+1][g_max])
		return mat[mid_r][g_max];
	if (mat[mid_r][g_max] <= mat[mid_r-1][g_max])
		return find_peak(mat,nc, r_ini, mid_r-1);
	
	return find_peak(mat, nc, mid_r+1, r_end);	
}

int global_max(int *row, int size)
{
	int bigger = 0;
	for (int i = 1; i < size; i++){
		if (row[i] > row[bigger])
			bigger = i;
	}
	return bigger;
}

int r_global_max(int **mat, int rows)
{
	int bigger = 0;
	for(int i = 1; i < rows; i++){
		if (mat[i][0] > mat[bigger][0])
			bigger = i;
	}
	return bigger;
}
