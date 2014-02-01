#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(int argc, const char *argv[])
{
	char a[]={"ciao"};
	printf("%s\n",a);
	char b[]={"vaffanculo"};
	strcpy(b,a);
	printf("a=%s\n",a);
	printf("b=%s\n",b);
	return 0;
}
