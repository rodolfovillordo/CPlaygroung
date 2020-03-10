#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char *buff= malloc(100*sizeof(char));
	memcpy(buff, "spam", 10);
	while(strlen(buff)>0){
		puts(buff);
		memset(buff, 0, 100);
		fgets(buff, 100, stdin);
	}

	return 0;
}
