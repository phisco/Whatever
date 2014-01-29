#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int permutazione (char x[],char y[])
{
	int sy=strlen(y);
	int i, l, c=0;
	int sx=strlen(x);
	if (sx!=sy)
		return 0;
	int *a=calloc(sy,sizeof(char)); 
	for (i = 0; i < sx; i++) {
		c=0;
		for(l=0;l<sy; l++)
		{
			if (x[i]==y[l] && *(a+l)==0 )
			{
				c=1;
				*(a+l)=1;
				break;
			}
		}
		if (c!=1) return 0;
	}
return 1;
}

int main(int argc, const char *argv[])
{
	printf("%i\n",permutazione("ciao","coia"));
	printf("%i\n",permutazione("coso","cosa"));
	printf("%i\n",permutazione("c","cosa"));
	return 0;
}
