#include <stdio.h>

/* GCC Variable attributes:
 * https://gcc.gnu.org/onlinedocs/gcc/Variable-Attributes.html#Variable-Attributes
 */
#define __unused __attribute__ ((__unused__))

/* GCC Function attributesL
 * https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 */
#define __deprecated __attribute__ ((__deprecated__))

int power(int x, int y) __deprecated;

int main(int argc, char *argv[]){
	int __unused a; //will not alert unused warning compiling with -Wall
	int b; //WARNING: unused variable
	
	printf("arg: %s\n", argv[1]);
	printf("power(2,3): %d\n", power(2,3));//WARNING: deprecated

}

int power(int x, int y)
{
	int pow = x;
	for (int i = 1; i < y; i++)
		pow *= x;
	return pow;
}
