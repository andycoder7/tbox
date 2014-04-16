#include <stdio.h>

struct A {
	int  a, b;
	char data[0];
	/* do not write fields below */
};

int main()
{
	struct A *p;
	int n = 100, i;
	p = malloc(sizeof(struct A) + n);
	for (i = 0; i < n; i++) {
		p->data[i] = 1;
	}
	free(p);
	return 0;
}
