#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STRSIZE 10

void fizzBuzz(int n) 
{
	char output[STRSIZE] = {""};
	for(int i = 1; i <= n; i++){
		strcpy(output, "");
		if (i % 3 == 0)
			strcat(output, "Fizz");
		if (i % 5 == 0)
			strcat(output, "Buzz");
		if (strcmp(output, "") == 0)
			sprintf(output, "%d", i);
		printf("%s\n", output);
	}
}

int main (void)
{
	int n;
	scanf("%d", n);
	fizzBuzz(n);
}
