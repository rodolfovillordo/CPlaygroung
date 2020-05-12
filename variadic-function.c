#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/*
 * https://gcc.gnu.org/onlinedocs/gcc/Variadic-Pointer-Args.html#Variadic-Pointer-Args
 * https://linux.die.net/man/3/va_start
 */

void print_args(int i, ...)
{
	va_list ap; /* access pointer to variadic arguments */
	int n;
	int v;
	/* initialize the pointer (after the last function argument) */
	va_start(ap, i);
	/* 
	 * Get first argument; argument type is int (by developer definition)
	 * The first argument is the number of variadic arguments;
	 */
	n = va_arg(ap, int); 

	printf("%d - ", i);
	for(i = 0; i < n; i++){
		v = va_arg(ap, int); /* get next variadic argument from list */
		printf("%d - ", v);
	}

}

int main(void)
{
	int i = 0;
	/* int i (fix argument)
	 * 3: number of variadic arguments;
	 * 1, 2, 3: variadic arguments;
	 */
	print_args(i, 3, 1, 2, 3);
	return 0;
}
