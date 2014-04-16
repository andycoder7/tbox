#include <stdio.h>
#include <netdb.h> 

typedef struct {
	uint8_t c1;
	uint8_t c2;
	uint8_t c3;
	int c4[0];
//	uint32_t c5[0];
} test;

int main()
{
	uint32_t a[0];
	printf("%d\n", sizeof(a));
    test c = {.c1 = 1, .c2 = 2, .c3 = 3};
	printf("address of c: %d\n", &c);
	printf("address of c1: %d\n", &(c.c1));
	printf("context of c1: %d\n", (c.c1));
	printf("address of c2: %d\n", &(c.c2));
	printf("context of c2: %d\n", (c.c2));
	printf("address of c3: %d\n", &(c.c3));
	printf("context of c3: %d\n", (c.c3));
	printf("address of c4: %d\n", &(c.c4));
	printf("context of c4: %d\n", (c.c4));
//	printf("address of c5: %ld\n", (uint32_t)&(c.c5));
//	printf("context of c5: %ld\n", (uint32_t)(c.c5));
	printf("sizeof sturct is: %d\n", sizeof(test));
	return 0;
}
