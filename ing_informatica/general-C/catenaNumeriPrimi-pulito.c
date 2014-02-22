
#include <stdio.h>
#include <stdlib.h>
#define DIM 10


int controlla2(int x,int y)
{
	int i,c=0;
	int min=(x<y ? x : y);
	for (i = 2; i <= min; i++) {
	if (c>1)
			return 0;
		if (x%i==0 && y%i==0)
		{
			c++;
		}
	}
	if (c==1)return 1;
	else return 0;
}

int copia_array(int* temp, int *massima,int lunghezza)
{
	int i;
	for (i = 0; i < lunghezza; i++) {
		massima[i]=temp[i];
	}
	return 1;
}

//funzione che aggiunge un pezzo alla temp fino a finirla o non avere più possibilità
int concatena_add(int* a,int* acontrollo,int* temp, int* l_massima,int lunghezza,int *g_max,int *l_max)
{
	//a è l'array intero preso in input
	//acontrollo è quello su cui segno che numeri di a ho già usato
	//temp è l'array in cui scrivo i risultati
	//temp2 e l'array massimo loc
	//lunghezza la lunghezza dell'array di input
	//g_max è il massimo generale
	//l_max è il massimo locale che inizializzo ogni volta che cambio scelta iniziale

	int i,j;
	//ciclo per passare tutto 
	for (i = 1; i < lunghezza; i++) 
	{

		if (temp[i]==0 && lunghezza>1)
		{
			for (j=1;j<lunghezza;j++)
			{
				if (acontrollo[j]==0)
				{

					if (controlla2(temp[i-1],a[j]))
					{
						acontrollo[j]=1;
						temp[i]=a[j];
						*l_max=i+1;
						*l_max=concatena_add(a,acontrollo,temp,l_massima,lunghezza, g_max,l_max);
						if (*l_max>*g_max){
							copia_array(temp,l_massima,lunghezza);
							*g_max=*l_max;
						}
							int l;

						temp[i]=0;
						acontrollo[j]=0;
					}
				}
			}
		}
	}
	if(lunghezza==1)
	{
		copia_array(temp,l_massima,lunghezza);
		return 1;
	}
	
		return *l_max;
}

int concatena(int* a,int lunghezza,int *massima,int *g_max)
{ 
	//*max è l'indirizzo del massimo globale
	//*massima è l'arrey massimo globale
	int i,j;
	int c=0;
	
	int *acontrollo=calloc(lunghezza,sizeof(int));
	int *temp=calloc(lunghezza+1,sizeof(int));
	int *l_massima=calloc(lunghezza+1,sizeof(int));
	int l;
	int *l_max=calloc(1,sizeof(int));
	for (i = 0; i < lunghezza; i++) 
	{
		//gemp è il massimo locale al tentativo
		*l_max=1;
		if (a[i]!=0)
		{
			temp[0]=a[i];
			acontrollo[i]=1;
			printf("\n");

			//a è l'array intero preso in input
			//acontrollo è quello su cui segno che numeri di a ho già usato
			//temp è l'array in cui scrivo i risultati
			//temp2 è l'array massimo loc
			//lunghezza la lunghezza dell'array di input
			//max è il massimo generale
			//l_max è il massimo locale che inizializzo ogni volta
			*l_max=concatena_add(a,acontrollo,temp,massima,lunghezza,g_max,l_max);
			acontrollo[i]=0;
			temp[0]=0;
			
		}
	}
	return *g_max;
}	




int orig()
{
	printf("Quanto vuoi che sia lungo il tuo array?\n");
	int lunghezza;
	scanf("%i",&lunghezza);
	int *array=calloc(lunghezza+1,sizeof(int));
	int i;
	for (i = 0; i < lunghezza ; i++) {
		printf("Quale vuoi che sia la cifra nr. %i? \n", i+1);
		scanf("%i", &array[i]);
	}
	int *massima=calloc(lunghezza,sizeof(int));

	int maxx=0;
	int *max=&maxx;
	*max=concatena(array,lunghezza,massima,max);
	printf("la concatenazione maggiore, ottenibile seguendo le specifiche è di %i numeri\n", *max);
	for (i = 0; i < *max; i++) {
		printf("%i",massima[i]);
		if (i<*max-1)
			printf(",");
		else
			printf(".");
	}
	
	return *max;
}
int main(int argc, const char *argv[])
{
	int max=orig();
	return max;
}
