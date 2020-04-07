#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int lexicographic_sort(const char* a, const char* b) {
    unsigned int size_a = -1, size_b = -1;
    size_a = strlen(a);
    size_b = strlen(b);
    for (int i = 0; i < size_a && i < size_b; i++){
        if(a[i] > b[i])
            return 1;
        if (a[i] < b[i]) {
            return -1;
        }
    }
    return size_a - size_b ;
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    unsigned int size_a = -1, size_b = -1;
    size_a = strlen(a);
    size_b = strlen(b);
    for (int i = 0; i < size_a && i < size_b; i++){
        if(a[i] > b[i])
            return -1;
        if (a[i] < b[i]) {
            return 1;
        }
    }
    return size_b - size_a;
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    int count_a[26] = {0};
    int count_b[26] = {0};
    int size_a = 0, size_b = 0;
    /* counting characters on str a */
    for (int i = 0; i < strlen(a); i++){
        /* This will increment the arry index based on the letter ascii value - 97
         * doing it I can relativize the letter value on the array index
         * ASCII lowercar a = 97; b = 98; c = 99;
         * string abc will increment count_a[0], count_a[1] and count_a[2]
         */
        count_a[a[i]-'a']++;
    }
    /* counting characters on str b */
    for (int i = 0; i < strlen(b); i++){
        count_b[b[i]-'a']++;
    }

    /* Count distinct carachters: 
     * For each index != 0, incriease 1 on the distinct character count
     */
    for(int i = 0; i < 26; i++){
        if (count_a[i] > 0)
            size_a++;
        if (count_b[i] > 0)
            size_b++;
    }
    if(size_a == size_b){
        if (lexicographic_sort(a, b) > 0)
            size_a++;
        else 
            size_b++;
    }

    return size_a - size_b;
}

int sort_by_length(const char* a, const char* b) {
    unsigned int size_a = -1, size_b = -1;
    size_a = strlen(a);
    size_b = strlen(b);
    if(size_b == size_a){
        if(lexicographic_sort(a, b) > 0)
            size_a++;
        else
            size_b++;
    }
    return size_a - size_b;
}

void merge(char **a, char **aux, int ini, int end, int (*cmp)(const char *a, const char *b))
{
        int l, end_l, r, end_r, a_index;
        l = ini;
        end_l = (ini + end) / 2;
        r = end_l + 1;
        end_r = end;
	a_index = ini;

        while ((l <= end_l) && (r <= end_r)){
            if(cmp(a[l], a[r]) <= 0){
                aux[a_index] = a[l];
                l++;
            } else {
                aux[a_index] = a[r];
                r++;
            }
            a_index++;
        }

        while (l <= end_l) {
            aux[a_index] = a[l];
            l++;
            a_index++;
        }

        while (r <= end_r) {
            aux[a_index] = a[r];
            r++;
            a_index++;
        }

        for (int i = ini; i <= end; i++)
            a[i] = aux[i];

}

void merge_sort(char **a, char **aux, int ini, int end, int (*cmp)(const char *a, const char *b))
{
        int mid;
        if(end > ini){
            mid = (ini+end)/2;
            merge_sort(a, aux, ini, mid, cmp);
            merge_sort(a, aux, mid+1, end, cmp);
            merge(a, aux, ini, end, cmp);
        }
}


void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
    char **aux;
    aux = (char **)calloc(len, sizeof(char*));
    for(int i = 0; i < len; i++)
        aux[i] = (char *) calloc(1,sizeof(char));

    merge_sort(arr, aux, 0, len-1, cmp_func);
    
    
}


int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}
