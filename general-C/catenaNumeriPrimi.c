#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
			/* printf("c=%i, %i e %i sono divisibili per %i\n",c,x,y,i); */
		}
	}
	if (c==1)return 1;
	else return 0;
}
int controlla(int x,int y)
{
	int *x_p, *y_p;
	x_p=calloc(x,sizeof(char));
	y_p=calloc(y,sizeof(char));
	int i;
	int c_x=0,c_y=0;
	printf("y_p[2]= %i\n", y_p[2]);
	for (i = 2; i<=x;i++ ) {
		if (x%i==0)
		{
			if(x!=i)
			{
				x_p[i-1]=1;
				c_x++;
			}
			else
				if(c_x==0)
				{
					x_p[i-1]=1;
				}
		}
		printf("x_p[%i]=%i\n",i,x_p[i]);
	}
	for (i = 1; i<=y; i++) {
		if (y%i==0)
		{
			printf("aiuto\n");
			if(y!=i)
			{
				y_p[i-1]=1;
				c_y++;
			}
			else
			{
				if(c_y==0)
				{
					y_p[i-1]=1;
				}
			}
		}
		printf("y_p[%i]=%i\n",i,y_p[i]);
	}
	int cont=0;
	for (i = 2; i <= (x>y ? x : y); i++) {
		if(x_p[i]==y_p[i] && x_p[i]==1)
		{
			printf("x_p[%i] è uguale a y_p[%i]\n",i,i);
			cont++;
		}
	}
	printf("%i",cont);

	if (cont==1)
	return 1;
return 0;
}


int f(int cifre[DIM])
{
		//presuppongo mi vengano dati dei numeri, il modo vedo dopo
		//mi interessa quanti numeri sono immessi e poi le cifre
		/* int cifre[DIM]={10,22,43,52,67,89,12,15,37,40}; */
		int controllo[DIM];
		int cifre_p[DIM];
		int più_lungo[DIM];
		int i, j;
		for (i = 0; i < DIM; i++) {
			controllo[i]=0;
			cifre_p[i]=0;
		}
		int c=0;
		for (i = 0; i < DIM; ) {
			cifre_p[0]=cifre[i];
			controllo[i]=1;
			for (j = 0; j < DIM; j++) {
				if (controlla2(cifre[j],cifre[j-1]) && controllo[j]==0)
				{
					controllo[j]=1;
					/* cifre_p[] */

						}
					/* int h=f2(cifre,cifre_p,controllo); */
				/* if(h>c) */
				/* { */
				/* 	c=h; */
				/* 	for (i = 0; i < DIM; i++) { */

				/* 	} */
				}
			}

		/* } */
		return 0;
}

//funzione che 
int* a_controllata(int a[DIM],int acontrollo[DIM])
{
	int i,j,c=0;
	int *temp=calloc(DIM,sizeof(int));
	for (i = 0; i < DIM; i++) {
		if (acontrollo[i]!=0)
		{
			c++;
			temp[i]=a[i];
		}
	}
	return temp;

}

int copia_array(int* temp, int *massima,int lunghezza)
{
	int i;
	for (i = 0; i < lunghezza; i++) {
		massima[i]=temp[i];
	}
	return 1;
}



/* int concatena_gen(int *a,int *acontrollo,int lunghezza, int *massima, int *g_max) */
/* { */
/* 	int z,i; */
/* 	int *l_max=calloc(1,sizeof(int)); */
/* 	int *temp=calloc(lunghezza+1,sizeof(int)); */
/*  */
/* 	 */
/* 	for (z = 0; z < lunghezza; z++) */
/* 	{ */
/* 		if (!acontrollo[z] ) */
/* 			for (i = 0; i < lunghezza; i++) { */
/* 				if (controlla2(temp[z],)) */
/* 			} */
/* 	} */
/*  */
/* 	 */
/* 	for (z = 0; z < lunghezza; z++)  */
/* 	{ */
/* 		*l_max=1; */
/* 		temp[0]=a[z]; */
/* 		acontrollo[z]=1; */
/* 		int i,j; */
/* 		for (i = 1; i < lunghezza; i++)  */
/* 		{ */
/*  */
/* 			if (temp[i]==0 && lunghezza>1) */
/* 			{ */
/* 				printf("\ntemp[%i]= %i -->",i,temp[i]); */
/* 				for (j=1;j<lunghezza;j++) */
/* 				{ */
/* 					if (acontrollo[j]==0) */
/* 					{ */
/*  */
/* 						if (controlla2(temp[i-1],a[j])) */
/* 						{ */
/* 							printf("matchano %i e %i --> ",temp[i-1],a[j]); */
/* 							acontrollo[j]=1; */
/* 							temp[i]=a[j]; */
/* 							printf("%i\n",temp[i]); */
/*  */
/* 							*l_max=i+1; */
/* 							#<{(| *max=i+1; |)}># */
/* 							*l_max=concatena_add(a,acontrollo,temp,massima,lunghezza, g_max,l_max); */
/* 							if (*l_max>*g_max){ */
/* 								copia_array(temp,massima,lunghezza); */
/* 								*g_max=*l_max */
/* 								#<{(| l_max=gemp; |)}># */
/* 							} */
/* 							int l; */
/* 							printf("l'array massimo locale iniziando con %i  è:",temp[0]); */
/* 							for (l=0;l<*l_max;l++) */
/* 							{ */
/* 								printf("%i",temp[l]); */
/* 							} */
/* 							printf("\n"); */
/*  */
/* 							temp[i]=0; */
/* 							acontrollo[j]=0; */
/* 						} */
/* 					} */
/* 				} */
/* 				#<{(| printf("%i\n",temp[i]); |)}># */
/* 			} */
/* 			else if(lunghezza<=1)  */
/* 			{ */
/* 				copia_array(temp,massima,lunghezza); */
/* 				return lunghezza; */
/* 			} */
/* 		} */
/* 		 */
/* 		acontrollo[z]=1; */
/*  */
/*  */
/*  */
/*  */
/*  */
/* 	} */
/* } */
/*  */



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
			printf("\ntemp[%i]= %i -->",i,temp[i]);
			for (j=1;j<lunghezza;j++)
			{
				if (acontrollo[j]==0)
				{

					if (controlla2(temp[i-1],a[j]))
					{
						printf("matchano %i e %i --> ",temp[i-1],a[j]);
						acontrollo[j]=1;
						temp[i]=a[j];
						printf("%i\n",temp[i]);

						*l_max=i+1;
						/* *max=i+1; */
						*l_max=concatena_add(a,acontrollo,temp,l_massima,lunghezza, g_max,l_max);
						if (*l_max>*g_max){
							copia_array(temp,l_massima,lunghezza);
							*g_max=*l_max;
							/* l_max=gemp; */
						}
							int l;
							printf("l'array massimo locale iniziando con %i  è:",temp[0]);

							for (l=0;l<*l_max;l++)
							{
								printf("%i",temp[l]);
							}
							printf("\n");

						temp[i]=0;
						acontrollo[j]=0;
					}
				}
			}
			/* printf("%i\n",temp[i]); */
		}
	}
	if(lunghezza==1)
	{
		copia_array(temp,l_massima,lunghezza);
		return 1;
	}
	printf("\n");
	printf("-----------------------------------");
	printf("\n");
	printf("il massimo locale provando con %i è %i \n",temp[0],*l_max);
	printf("il massimo globale è invece %i \n",*g_max);
	printf("invece l'array massimo  al momento è:");
	for (i = 0; i < *g_max; i++) {
		printf("%i",l_massima[i]);
	}

	/* printf("il massimo è: %i \n",*max); */
	printf("\n");
	/* printf("l'array massimo locale è:"); */
	/* for (i = 0; i < *max; i++) { */
	/* for (i = 0; i < gemp; i++) { */
		/* printf("%i,",temp[i]); */
	/* } */
	/* printf("\n"); */
	/* printf("il massimo è: %i \n",*max); */
	/* printf("il massimo è: %i \n",*max); */
	return *l_max;
}

int concatena(int* a,int lunghezza,int *massima,int *g_max)
{ 
	//*max è l'indirizzo del massimo globale
	//*massima è l'arrey massimo globale
	int i,j;
	int c=0;
	printf("le cifre date sono :\n");
	for (i = 0; i < lunghezza; i++) {
		printf("%i",a[i]);
	}
	printf("\n");
	printf("lunghezza: %i\n",lunghezza);
	
	int *acontrollo=calloc(lunghezza,sizeof(int));
	int *temp=calloc(lunghezza+1,sizeof(int));
	int *l_massima=calloc(lunghezza+1,sizeof(int));
	int l;
	printf("temp è all'inizio è:\n");
	for (l=0;l<lunghezza;l++)
	{
		printf("%i",temp[l]);
	}
	printf("\n");
	printf("-----------------------------------");
	printf("\n");
	int *l_max=calloc(1,sizeof(int));
	for (i = 0; i < lunghezza; i++) 
	{
		//gemp è il massimo locale al tentativo
		*l_max=1;
		if (a[i]!=0)
		{
			temp[0]=a[i];
			acontrollo[i]=1;
			printf("temp dopo un tentativo è:\n");
			for (l=0;l<lunghezza;l++)
			{
				printf("%i",temp[l]);
			}
			printf("\n");

			printf("Proviamo ad iniziare con: %i\n",temp[0]);
			//a è l'array intero preso in input
			//acontrollo è quello su cui segno che numeri di a ho già usato
			//temp è l'array in cui scrivo i risultati
			//temp2 è l'array massimo loc
			//lunghezza la lunghezza dell'array di input
			//max è il massimo generale
			//l_max è il massimo locale che inizializzo ogni volta
			*l_max=concatena_add(a,acontrollo,temp,massima,lunghezza,g_max,l_max);
			/* if (*l_max>*g_max) */
			/* { */
			/* 	printf("dato che l_max è maggiore di g_max(%i >%i) ho preso l_max come g_max\n",*l_max,*g_max); */
			/* 	copia_array(l_massima,massima,lunghezza); */
			/* 		*g_max=*l_max; */
			/* } */
			acontrollo[i]=0;
			temp[0]=0;
			
		}
	}
	return *g_max;
}	
/* for (i = 0; i < DIM; i++) { */
/* 	if (acontrollo[i]!=0) */
	/* 	{ */
	/* 		c++; */
	/* 		temp[i]=a[i]; */
	/* 	} */
	/* } */
	/* int *temp=a_controllata(a,acontrollo); */
	
	/* if (c==DIM) */
		/* return DIM; */
	/* for (i = 0; i < DIM; i++) { */
	/* 	if (acontrollo[i]==0) */
	/* 	{ */
	/* 		a[i] */
	/* 		for (j = 0; j < count; j++) { */
	/* 			if (controlla2(a[i],))	 */
	/* 		} */
	/* 	} */
	/* } */

	/* for (i = 0; i < DIM; i++) { */
	/* 	if(acontrollo[i]==0) */
	/* 	{ */
	/* 		if(c==0) */
	/* 		{ */
	/* 			temp[0]=a[i]; */
	/* 			acontrollo[i]=1; */
	/* 			max=concatena_più(temp,acontrollo); */
	/* 		} */
	/* 		else */
	/* 			for (j = 0; j < DIM; j++)  */
	/* 			{ */
	/* 				if (acontrollo[j]==0 && controlla2(a[j],temp[i-1])) */
	/* 				{ */
	/* 					temp[i]=a[j]; */
	/* 					acontrollo[j]=1; */
	/* 					max=concatena_più(temp,acontrollo); */
	/* 				} */
	/* 				#<{(| if (concatena_più(temp,acontrollo)) |)}># */
	/* 			} */
	/* 	} */
	/* } */
/* } */
/* { */
/*  */
/* 	int i,j; */
/* 	int *temp=calloc(DIM,sizeof(int)); */
/* 	for (i = 0; i < DIM; i++)  */
/* 	{ */
/* 		temp[0]=a[i]; */
/* 		acontrollo[i]=1; */
/* 		for (j = 0; j < DIM; j++)  */
/* 		{ */
/* 			if (acontrollo[j]==0) */
/* 			{ */
/* 				if (controlla2(a[],a[j-1])) */
/* 				if (concatena_più(temp,acontrollo)==1) */
/*  */
/* 			} */
/* 		} */
/* 	} */
/* 	return 0; */
/* } */


void test()
{
	int *a=calloc(4,sizeof(int));
	int *b=calloc(4,sizeof(int));
	int i;
	for (i = 0; i < 4; i++) {
		a[i]=i;
		b[i]=4+i;
	}
	printf("a è :\n");
	for (i = 0; i < 4; i++) {
		printf("%i,",a[i]);
	}
	printf("\n");
	printf("b è :\n");
	for (i = 0; i < 4; i++) {
		printf("%i,",b[i]);
	}

	copia_array(a,b,4);
	printf("ora invece:\n");
printf("a è :\n");
	for (i = 0; i < 4; i++) {
		printf("%i,",a[i]);
	}
	printf("\n");
	printf("b è :\n");
	for (i = 0; i < 4; i++) {
		printf("%i,",b[i]);
	}

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


	/* printf("Quanto vuoi che sia lungo il tuo array?\n"); */
	/* int lunghezza=4; */
	/* int *array=calloc(lunghezza+1,sizeof(int)); */
	/* array[0]=2; */
	/* array[1]=4; */
	/* array[2]=6; */
	/* array[3]=3; */

	int maxx=0;
	int *max=&maxx;
	*max=concatena(array,lunghezza,massima,max);
	printf("la concatenazione maggiore, ottenibile seguendo le specifiche è di %i numeri\n", *max);
	/* printf("%i\n",massima[*max]); */
	for (i = 0; i < *max; i++) {
		printf("%i",massima[i]);
		if (i<*max-1)
			printf(",");
		else
			printf(".");
	}
	
	return 0;
}

void test2()
{
	int a=controlla2(2,6);
	printf("%i\n",a);
	a=controlla2(3,6);
	printf("%i\n",a);
	a=controlla2(4,6);
	printf("%i\n",a);
	a=controlla2(5,6);
	printf("%i\n",a);
	a=controlla2(5,5);
	printf("%i\n",a);
	a=controlla2(7,6);
	printf("%i\n",a);
}
int main(int argc, const char *argv[])
{
	/* test2(); */
	orig();
	/* test(); */
	return 0;
}
