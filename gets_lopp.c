#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct t {
	int a;
	int b;
}
int main(void)
{
	struct t t1;
	char *buff= malloc(100*sizeof(char));
	memcpy(buff, "spam", 10);
	while(strlen(buff)>0){
		puts(buff);
		memset(buff, 0, 100);
		fgets(buff, 100, stdin);
	}

	return 0;
}
