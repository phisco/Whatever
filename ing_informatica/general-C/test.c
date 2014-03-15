#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test()
{
	int c=0;
	int *d;
	int *a;
	a=&c;
	*a=9;
	d=malloc(sizeof(int)*10);
	int i;
	for (i=0;i<10;i++)
	{
		d[i]=i;
		printf("%i\n",d[i]);
		printf("%i\n",*(d+i));
	}
	
	printf("*a=%i\n", *a);
	printf("c=%i \n", c);

}

int main(int argc, const char *argv[])
{
	test();
	return 0;
}
