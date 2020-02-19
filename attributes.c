#include <stdio.h>

#define __unused __attribute__ ((__unused__))

int main(int argc, char *argv[]){
	int __unused a; //will not alert unused warning compiling with -Wall
	int b; //will allert unused variable
	printf("arg: %s\n", argv[1]);

}
