#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int is_vowel(char c) {
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
		return 1;
	return 0;
}

char* findSubstring(char* s, int k) {
	char *ret;
	int j = 0;
	int bigger = 0;
	int vowels = 0;
	int *count = calloc (100000, sizeof(int));
	ret = (char *)malloc(20 * sizeof(char));
	strcpy(ret, "Not found!");
	while (s[j] != '\0'){
		if(is_vowel(s[j])){
			vowels++;
		}
		if ( (j - k) >= 0 && is_vowel(s[j-k]))
			vowels--;
		count[j] = vowels;
		if ( vowels > count[bigger] )
			bigger = j;
		j++;
	}
	count = realloc(count, j * sizeof(int));
	if (vowels > 0){
		ret = (char *)malloc((k + 1)*sizeof(char));
		s += bigger - (k -1);
		strncpy(ret, s, k);
	}
	return ret;
}

int main(void)
{
	int size;
	char *str;
	scanf("%s", str);
	scanf("%d", &size);
	printf("%s\n", findSubstring(str,size));
}
