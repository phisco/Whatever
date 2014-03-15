#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>


char *strdup(const char *s1)
{
	int i=0;
	char *s2 =(char *) calloc(strlen(s1), sizeof(char));
	for (i = 0; i < strlen(s1); i++)
		s2[i] = s1[i];
	s2[i] = '\0';

	return s2;
}

void convertToLow(int len_parola,char *parola)
{
	int i;
	for(i=0; i<len_parola; i++)
	{
		parola[i] = tolower(parola[i]);
	}
}

int anagramma(int len_parola, char *parola1,char *parola2)
{
	int i,l,cont=0;
	for (i=0; i<len_parola;i++)
		{
			for(l=0;l<len_parola;l++)
			{
				if(parola1[i]==parola2[l] && cont==i)
				{
					cont++;
				}
			}
		}
	return cont;
}
int cambioLettera(int len_parola, char *parola1,char *parola2)
{
	int i,cont;
	cont=0;
	for (i = 0; i < len_parola; i++) {
			if (parola1[i]==parola2[i] && cont>=i-1)
			{
				cont++;
			}
		}
	return cont;
}


int letteraInMeno(int len_parola1,int len_parola2, char *parola1,char *parola2)
{
	int i, c,cont;
	c=0;
	cont=0;
	for (i = 0; i < (len_parola1>len_parola2? len_parola1 : len_parola2); i++) {
		if (parola1[(len_parola1>len_parola2 ? i : c )]==parola2[(len_parola1>len_parola2 ? c : i )])
		{
			cont++;
			c++;
		}
		else
		{
			c=i;
		}
	}
	return cont;
}

int controllo(char *p1,char *p2)
{
	char *parola1;
	char *parola2;
	int len_parola1,len_parola2,len_max,len_min;
	
	parola1=strdup(p1);
	parola2=strdup(p2);

	len_parola1=strlen(parola1);
	len_parola2=strlen(parola2);
	len_max=(len_parola1>=len_parola2 ? len_parola1 : len_parola2);
	len_min=(len_parola1>=len_parola2 ? len_parola2 : len_parola1);
	
	/*conversione da maiuscole a minuscole*/
	convertToLow(len_parola1,parola1);
	convertToLow(len_parola2,parola2);

	if(len_parola1==len_parola2)
	{
		if (anagramma(len_parola1,parola1,parola2)==len_max)
			return 1;
		else
			if (cambioLettera(len_max,parola1,parola2)==len_max-1)
				return 1;
	}
	else
		if (len_min==len_max-1)	
		{
			if (letteraInMeno(len_parola1,len_parola2,parola1,parola2)==len_min)
			{
				return 1;
			}
		}
	return 0;
}


int cicla(char **parole, int numero_p, char **temp,int *a_contr,int *cont_p)
{
	int l;
	if (*cont_p+2==numero_p){
		if(controllo(temp[*cont_p],temp[numero_p-1]))
		{
			return 1;
		}
	}
	for (l=0;l<numero_p-1;l++)
	{
		if(a_contr[l]==0)
		{
			if (controllo(temp[*cont_p],parole[l]))
			{
				temp[*cont_p+1]=parole[l];
				a_contr[l]=1;
				*cont_p=*cont_p+1;
				if(cicla(parole,numero_p,temp,a_contr,cont_p))
					return 1;
				a_contr[l]=0;
				*cont_p=*cont_p-1;
			}
		}
	}
	return 0;

}

void risolvi(char **parole,int numero_p,char **temp)
{
	int *a_contr=calloc(numero_p,sizeof(int));
	int *cont_p=calloc(1,sizeof(int));
	*cont_p=0;
	a_contr[0]=1;
	a_contr[numero_p-1]=1;
	temp[0]=parole[0];
	temp[numero_p-1]=parole[numero_p-1];
	cicla(parole,numero_p,temp,a_contr,cont_p);
}


int contaParole(char *nomeFile)
{
	FILE *f;
	int cont;
	char buffer[30];
	int vuota=0;
	vuota++;

	f=fopen(nomeFile,"r");
	
		cont=0;
	
    while(!feof(f))
    {
        vuota=fscanf(f,"%s",buffer);
        cont++;
    }
    cont--;
    
    fclose(f);
    return cont;
}

int main(int argc,char *argv[])
{
	FILE *f;	
	int i=0;
	char parola[30];
	char **parole;						/*array di puntatori*/
	char **temp;
	int numeroParole ;	/*numero di parole*/
	char *nome_f;
	int vuota=0;
	vuota++;
	nome_f=calloc(50,sizeof(char));
	vuota=scanf("%s",nome_f);
	f=fopen(nome_f,"r");
	numeroParole= contaParole(nome_f);
	parole = malloc(sizeof(char *)*numeroParole);
	temp = calloc(numeroParole,sizeof(char*));
	
	while(!feof(f))
    {
        vuota=fscanf(f,"%s",parola);
        parole[i]=strdup(parola);
        i++;
    }
    	
    risolvi(parole,numeroParole,temp);	

		for(i=0;i<numeroParole;i++)
		{

			printf("%s",temp[i]);
			if(i!=numeroParole-1)
				printf(" ");
		}
		printf("\n");
		return 0; 	
}
