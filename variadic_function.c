#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void print_args(int i, ...)
{
	va_list ap;
	int n;
	int v;
	va_start(ap, i);
	n = va_arg(ap, int);

	printf("%d - ", i);
	for(i = 0; i < n; i++){
		v = va_arg(ap, int);
		printf("%d - ", v);
	}

}

int main(void)
{
	int i = 0;
	print_args(i, 3, 1, 2, 3);
	return 0;
}
