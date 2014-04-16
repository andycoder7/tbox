#include <stdio.h>
#include <stdlib.h> 
#include <netdb.h> 

typedef struct {
	uint8_t c1;
	uint8_t c2;
	uint8_t c3;
	int c4[0];
} test;

struct line {
	int length;
	char contents[0];
};

int main()
{
	//这test的是对齐问题
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
	printf("sizeof sturct is: %d\n", sizeof(test));

	//这test的是柔性数组问题
	int this_length = 10, i;

	struct line *thisline = (struct line *)
		malloc (sizeof (struct line) + this_length);
	thisline->length = this_length;

	for (i = 0; i < (thisline->length - 1); i++) {
		thisline->contents[i] = 'a' + i%26;
	}
	thisline->contents[thisline->length - 1] = 0;
	//数组长10位，最后一位置为'\0'，所以应该只会输出9个字符
	puts(thisline->contents);

	free(thisline);
	return 0;
}
