#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	int * aEntero = NULL;
	int entero = 3;
	
	printf("%d\n", (int)aEntero);
	//printf("%d\n", (int)* aEntero);

	aEntero = &entero;

        printf("%d\n", (int)aEntero);
        printf("%d\n", (int)* aEntero);

	entero = 5;

        printf("%d\n", (int)aEntero);
        printf("%d\n", (int)* aEntero);

	int entero2 = 3;
	aEntero = &entero2;
	*aEntero = 7;

        printf("%d\n", (int)aEntero);
        printf("%d\n", (int)* aEntero);

	aEntero = 0;

        printf("%d\n", (int)aEntero);
        printf("%d\n", (int)* aEntero);

	return 0;
}
