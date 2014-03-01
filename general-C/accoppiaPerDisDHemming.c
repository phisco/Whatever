#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int contaParole(FILE *f)
{
	int i=0,contatoreParole=0;
	/* FILE *p; */
	/* p=fopen("f","r"); */
	char *temp;
	temp=calloc(80,sizeof(char));
	while(!feof(f))
	{
		i++;
		if (fscanf(f,"%s",temp)!=EOF)
		{
			contatoreParole++;
			/* printf("%s",temp); */
			/* printf(" %i\n",contatoreParole); */
		}

	}


	/* while (parole[i]!='\0') */
	/* { */
	/* 	if (parole[i]==',' && parole[i+1]!='\0') */
	/* 		contatoreParole++; */
	/* } */
	/* fclose(f); */
	return contatoreParole;
}

char **scorporaEsalva(FILE *p, int *dim)
{
	
	int i;
	char **arrayPuntatori;
	*dim=contaParole(p);
	/* printf("%i",*dim); */
	arrayPuntatori=calloc(*dim,sizeof (char*));
	/* FILE *p; */
	/* p=fopen("f","r"); */
	rewind(p);
	char *parola;
	int j;
	parola=calloc(80,sizeof(char));
	for (i=0;i<*dim; i++)
	{
		for (j = 0; j < 80; j++) {
			parola[j]=0;
		}
		fscanf(p,"%s\n",parola);
		arrayPuntatori[i]=strdup(parola);
	}
	/*  */
	/* while (parole[i]!='\0') */
	/* { */
	/* 	 */
	/* } */
	for (i = 0; i < *dim; i++) {
		printf("%i : %s\n",i+1,arrayPuntatori[i]);
	}
		return arrayPuntatori;

	
}
int compara(char p1[],char p2[])
{
	char *max, *min;
	int i;
	int cont_diff=0;
	int len_p1=strlen(p1),len_p2=strlen(p2);
	max=calloc(1,sizeof(int));
	min=calloc(1,sizeof(int));
	*max=(len_p1>=len_p2 ? len_p1 : len_p2);
	*min=(len_p1>=len_p2 ? len_p2 : len_p1);
	printf("%i\n",*max);
	for (i = 0; i < *min; i++) {
		if( p1[i]!=p2[i])
			cont_diff++;
	}
	return cont_diff+(*max-*min);
}


int f(char **arrayPuntatori,int dim,char *arrayFinale)
{
	int i,j,min_diff=100;
		for (i = 0; i < dim; i++) {
			for (j = 0; j < dim; j++) {
				if(j!=i)
				{
					int diff_loc=compara(arrayPuntatori[i],arrayPuntatori[j]);
					if (diff_loc<min_diff)
					{
						min_diff=diff_loc;
						*arrayFinale[i]=
					}
				}
			}
		}

	return 0;
}


int accoppiaPerDisdHemming()
{
	FILE *p;
	int *dim;
	dim=calloc(1,sizeof(int));
	p=fopen("testo.txt","r");	
	char **arrayPuntatori;
	arrayPuntatori=scorporaEsalva(p,dim);	
	char *arrayFinale;
	arrayFinale=calloc(ftell(p),sizeof(char));
	fclose(p);
	f(arrayPuntatori,*dim,arrayFinale);
	

	return 0;
}



int main()
{
	accoppiaPerDisdHemming();
	int a=compara("ciao", "ciaoooo");
	printf("%i",a);
	return 0;
}
