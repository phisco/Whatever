//Esempio di esercizio sull'utilizzo degli array
//Tris.c

//1 cerchio primo giocatore
//2 x secondo giocatore
//
//
#define DIM 3
#include <stdio.h>

//
//
//FUNZIONI GENERICHE PER PARTITA
//
//
//

//patta
int patta()
{
	printf("\nPATTA!\nVolete rigiocare?\n Digitare 1 per si, 0 per no.\n");
	int x;
	scanf("%i",&x);
	return x;
}
//funzione vittoria
int vittoria(int g)
{
	printf("\nGiocatore %i, HAI VINTO!!\n", g);
	printf("\nVolete rigiocare?\n Digitare 1 per si, 0 per no.\n");
	int x;
	scanf("%i",&x);
	return x;

}


int mostra_aggiornata_acv(int m[DIM][DIM])
{
	int i, j;
	printf("\n");
	for (i=0; i<DIM; i++) {
		for (j=0; j<DIM; j++) {
			printf("[ %i ]",m[i][j]);
		}
		printf("\n");
	}
	return 0;
}


int mostra_aggiornata(int m[DIM][DIM])
{
	int i, j;
	printf("\n");
	for (i=0; i<DIM; i++) {
		for (j=0; j<DIM; j++) {
			if (m[i][j]==1)
				printf("[ O ]");
			if (m[i][j]==2)
				printf("[ X ]");
			if (m[i][j]==0)
				printf("[   ]");

		}
		printf("\n");
	}
	return 0;
}
int inizializza(int m[DIM][DIM])
{
	int i, j;
	for (i=0; i<DIM; i++) {
		for (j=0; j<DIM; j++) {
			m[i][j]=0;
		}
	}
	return 0;
}

//controllo mossa
int controllocoord(int m[DIM][DIM],int x,int y)
{
	int c=0;

	do
	{
		if (x<1 || x>3 ||y<1 || y>3 || m[x-1][y-1]==2 || m[x-1][y-1]==1)
			c=0;
		else c=1;
		switch (c) {
			case 1:
				break;
			default:
				printf("\nHai sbagliato coordinate, ritenta.\n");
				scanf("%d,%d",&x,&y);
				break;

		}
	}while (c!=1);

	int cod;
	cod=x*10+y;
	return cod;
}

//funzione di controllo totale
int controllatutto(int m[DIM][DIM],int g)
{
	int i, p;

	for (i=0;i<DIM;i++)
	{
		int c=0;
		int d=0;
		int r=0;
		int d2=0;
		//controllo 1 colonna
		for (p=0;p<DIM;p++)
		{
			if (m[p][i]==g)
				c++;
			//controllo 1 riga
			if (m[i][p]==g)
				r++;
			//controllo le diagonali
			if (i==0)
			{
				int j=DIM-1-p;
				if (m[p][p]==g)
					d++;
				if(m[p][j]==g)
					d2++;
			}
		}
		//controllo se vinto
		if (c==3 || d==3 || r==3 || d2==3 )
		{
			return g;
		}
	}
	return 0;
}

void errore()
{
	printf("\nc'è qualcosa che non è andato come ci aspettavamo\nPOI VEDI TU!!!\n");
}

int richiestagiocatore() 
{
	int c=2;
	int giocatore=0;
	do
	{
		if (c==2)
		{
			printf("Che giocatore vuoi essere?\nDigita:\t 1 per cominciare per primo.\n      2 per cominciare per secondo.\n");
			scanf("%i", &giocatore);
			switch (giocatore){
				case 1:c=1;
					   break;
				case 2: c=1;
						break;
				default: c=0;
			}
		}
		if (c!=1)
		{
			printf("Non hai immesso un valore valido! Riprova!\n");
			scanf("%i", &giocatore);
		}
	} 	while (c!=1);
	return giocatore;
}

//
//
//MOSSA PER GIOCATORE VIVENTE
//
//

//richiesta coordinate
int coordinate(int m[DIM][DIM])
{
	int x,y;
	printf("\nDove vuoi giocare? Dammi delle coordinate in forma x,y.\n");
	scanf("%d,%d",&x,&y);
	int cod=controllocoord(m,x,y);
	return cod;

}

//funzione decodifica x
int dex(int cod)
{
	int x;
	x=cod/10;
	return x;
}
//funzione decodifica y
int dey(int cod)
{
	int y;
	y=cod%10;
	return y;
}

//mossa giocatore vivente
void mossavivente(int m[DIM][DIM],int g)
{
	int x,y,cod;
	cod=coordinate(m);
	x=dex(cod);
	y=dey(cod);
	m[x-1][y-1]=g;
}

void mossav(int m[DIM][DIM],int g,int x, int y)
{
	m[x-1][y-1]=g;
}



//
//
//
//STUDIO AI
//
//
//

//in pratica vorrei avere una funzione che ad ogni giro duplichi la funzione 
//datale e sulla doppia gioca nel primo spazio vuoto, richiamando se stessa poi
//così da riapplicare gli stessi criteri precedenti 
//(1- gioca per vincere se puoifarlo in una mossa 
//2- gioca per tappare l'avversario se può farlo lui
//3- gioca dove c'è possibilità di intrappolare l'avversario
//4- gioca dove hai la maggior possibilità di vittorie nel minor numero 
//di mosse possibili


//mossa base ai da poter ciclare
int mossab(int m[DIM][DIM],int g,int x, int y)
{
	mossav(m,g,x+1,y+1);
	return controllatutto(m,g);
}


//array di controllo mosse possibili, i posti dove posso mettere mossa sono quelli con 0, quelli già usati, sono i 2, poi quelli dove vince l'altro saranno gli 1.
int arraymossepossibili(int m[DIM][DIM], int acv[DIM][DIM])
{
	int p,q;
	for (p=0;p<DIM;p++)
	{
		for (q=0;q<DIM;q++)
		{
			if (m[p][q]!=2 && m[p][q]!=1)
				acv[p][q]=0;
			else
				acv[p][q]=9;
		}
	}
	return 0;
}

// vede mosse possibili del giocatore  e salva su array come g(numero del giocatore)
// se posizione vincente in una mossa
//controlla se può vincere in una mossa e se può lo fa
int giocapervincere(int m[DIM][DIM],int g, int acv[DIM][DIM])
{
	int k, l;
	for (k=0;k<DIM;k++)
	{
		for (l=0;l<DIM;l++)
		{
			if ( acv[k][l]==g)
			{
				m[k][l]=g;
				return g;
			}
		}
	}
	return 0;
}
//controlla se c'è una posizione vincente per l'avversario
//su array di controllo e gioca
int controllaetappa(int m[DIM][DIM],int acv[DIM][DIM],int g)
{
	int o,n;
	for (o=0;o<DIM;o++)
	{
		for (n=0;n<DIM;n++)
		{
			if (acv[o][n]==g%2+1)
			{
				m[o][n]=g;
				return 0;
			}
		}
	}
	return g+100;
}
int giocapervincere_o_nonperdere(int m[DIM][DIM],int g, int acv[DIM][DIM])
{
	int k, l,c;
	for( c=0; c<2; c++)
	{
		for (k=0;k<DIM;k++)
		{
			for (l=0;l<DIM;l++)
			{
				switch (c) 
				{
					case 0:
						if ( acv[k][l]==g )
						{
							m[k][l]=g;

							return g;
						}
						break;
					case 1:
						if ( acv[k][l]==g%2+1 )
						{
							m[k][l]=g;
							return g+100;
						}
						break;

					default:
						errore();
				}
			}
		}
	}
	return 0;
}
//gioca per vincere + GIOCA PER NON PERDERE 
//DEVO AGGIUNGERE IN MEZZO DA QUALCHE PARTE CHE SE HO 2 POSSIBILITà DI VITTORIA UN CONTATORE
//ME LO DIMOSTRI!!!!!!!!!
//
int mossevincenti(int m[DIM][DIM],int g,int acv[DIM][DIM])
{   
	int avv=g%2+1;
	int k, l,cg,cavv;
	for (k=0;k<DIM;k++)
	{
		for (l=0;l<DIM;l++)
		{
			if ( acv[k][l]==0)
			{
				int preb=m[k][l];
				/* switch (mossab(m,g,k,l))  */
				/* { */
				/* 	case g: */
				/* 		acv[k][l]=g; */
				/* 		cg++; */
				/* 		break; */
				/* 	case g%2+1: */
				/* 		acv[k][l]=g%2+1; */
				/* 		break; */
				/* 	default: */
				/* 		errore(); */
				/* 		break; */
				/* } */
				if (mossab(m,g,k,l)==g)
				{
					acv[k][l]=g;
					cg++;
				}
				if (mossab(m,avv,k,l)==avv)
				{
					acv[k][l]=avv;
					cavv++;
				}
				m[k][l]=preb;
			}
		}
	}
	/* c=(c>=1 ? 1 : 0); */
	return cg*10+cavv;;
	/* if (c) */
	/* { */
	/* 	return giocapervincere_o_nonperdere(m,g,acv); */
	/* } */
	/* else return 0; */
}

int mossa_n(int m[DIM][DIM],int g)
{
	int acv[DIM][DIM];
	inizializza(acv);
	arraymossepossibili(m,acv);
	int c=mossevincenti(m,g,acv);
	int cg,cavv;
	cg=c/10;
	cavv=c%10;
	if (c)
	{
		if (cg>=1)
		{
			if (cg>=2)
			return 100+giocapervincere_o_nonperdere(m,g,acv);
			return giocapervincere_o_nonperdere(m,g,acv);
		}

	}
	int i,j;
	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			if (acv[i][j]==0)
			{
				m[i][j]=g;
				if (mossa_n() )
			}
			
		}
	}
/*  */
/* 	switch (cg) { */
/* 		case 1: */
/* 			return giocapervincere_o_nonperdere(m,g,acv); */
/* 			break; */
/* 		case 2: */
/* 			return giocapervincere_o_nonperdere(m,g,acv)+100; */
/* 			break; */
/* 		case 0: */
/* 		default: */
/* 			errore(); */
/* 			break; */
/* 			 */
/* 			 */
	}
}

int mospattare(int m[DIM][DIM],int g,int acv[DIM][DIM])
{
	int o,n;
	for (o=0;o<DIM;o++)
	{
		for (n=0;n<DIM;n++)
		{
			if (acv[o][n]==3)
			{
				mossab(m,g,o,n);
				return 0;
			}
		}
	}
	return 0;
}


int mosspossvittoria(int m[DIM][DIM],int g, int acv[DIM][DIM])
{
	int i, j;
	for(i=0;i<DIM;i++)
	{
		for (j=0;j<DIM;j++)
		{
			if (acv[i][j]==4)
			{
				mossab(m,g,i,j);
				return g;
			}
		}
	}
	return 0;
}




//mossa generica AI
int mossa(int m[DIM][DIM],int g)
{

	int i,j,h,acv[DIM][DIM];
	h=g%2+1;
	//array di controllo mosse possibili, i posti dove posso mettere mossa sono quelli con 0, quelli già usati, sono i 2, poi quelli dove vince l'altro saranno gli 1.
	arraymossepossibili(m,acv);
	// vede mosse possibili dell'avversario e salva su array come 1 se posizione perdente per ai.
	/* mossevincentiavv(m,g,acv); */

	//gioca per vincere avendo solo mosse possibili, prova tutte le possibilità, e le annulla, se una è vincente
	//la tiene
	if (mosvincente(m,g,acv)==g)
	{
		return g;
	}
	//vede se può bloccare la mossa dell'avversario
	if (controllaetappa(m, acv, g)==g)
	{
		return g;
	}
	//gioca random
	else
	{
		int o,n;
		o=0;
		n=0;
		for (o=0;o<DIM;o++)
		{
			for (n=0;n<DIM;n++)
			{
				if (acv[o][n]==0)
				{
					mossab(m,g,o,n);
					printf("\nIl computer ha giocato nella casella %i,%i\n",o+1,n+1);
					return g;
				}
			}
		}
	}

	return 0;
}

int mossaai5(int m[DIM][DIM],int g)
{
	int h=g%2+1;
	if (controllatutto(m,h)==h)
		return h;
	int i, j;
	for (i=0;i<DIM;i++)
	{
		for (j=0;j<DIM;j++)
		{
			if  (m[i][j]==8)
			{
				m[i][j]=g;
				if (mossaai5(m,h)==g)

					m[i][j]=8;
			}
		}
	}
	return 1;
}
int mossaai4(int m[DIM][DIM],int g, int v, int acv[DIM][DIM])
{
	int i,j,h,z,w,a_avv[DIM][DIM],acv_avv[DIM][DIM];
	v--;
	h=g%2+1;
	if (v==0)
		return 0;
	if (controllatutto(m,g)==g)
		return h;

	//arraymossepossibili(m,acv);

	//mossevincentiavv(m,g,acv);

	mostra_aggiornata_acv(acv);
	if (mosvincente(m,g,acv)==g)
	{
		return g;
	}
	else
		if (controllaetappa(m,acv,g)==0)
		{
			for (z=0;z<DIM;z++)
			{
				for (w=0;w<DIM;w++)
				{
					acv_avv[z][w]=acv[z][w];
					a_avv[z][w]=m[z][w];
				}
			}

			mossaai4(a_avv,h,v,acv_avv);
		}
		else
		{
			for (z=0;z<DIM;z++)
			{
				for (w=0;w<DIM;w++)
				{
					a_avv[z][w]=m[z][w];
					acv_avv[z][w]=acv[z][w];
				}
			}

			int o,n;
			for (o=0;o<DIM;o++)
			{
				for (n=0;n<DIM;n++)
				{
					if (acv[o][n]==0)
					{
						int preb=a_avv[o][n];
						a_avv[o][n]=g;
						int tc=mossaai4(a_avv,h,v,acv_avv);
						if (tc==h)
						{
							a_avv[o][n]=preb;
							acv_avv[o][n]=4;
						}
						if (tc==g)
						{

							acv_avv[o][n]=4;
						}
						if (tc==0)
						{
							a_avv[o][n]=preb;
						}
					}
				}
			}
		}
	return 0;

}

int mossaai3(int m[DIM][DIM], int g,int v)
{
	v--;
	if (controllatutto(m,g)==g)
	{
		return g;
	}

	if (v==0)
		return 0;
	int i,j,h,acv[DIM][DIM];
	h=g%2+1;
	//array di controllo mosse possibili, i posti dove posso mettere mossa sono quelli con 0, quelli già usati, sono i 2, poi quelli dove vince l'altro saranno gli 1 e 3 dove potrà vincere in due mosse.
	arraymossepossibili(m,acv);
	//gioca per vincere avendo solo mosse possibili, prova tutte le possibilità, e le annulla, se una è vincente
	//la tiene
	// vede mosse possibili dell'avversario e salva su array come 1 se posizione perdente per ai.
	/* mossevincentiavv(m,g,acv); */
	mostra_aggiornata_acv(acv);
	if (mosvincente(m,g,acv)==g)
	{
		return g;
	}

	int o,n,z,w,a_avv[DIM][DIM];
	for (o=0;o<DIM;o++)
	{
		for (n=0;n<DIM;n++)
		{
			if (acv[o][n]!=2)
			{
				for (z=0;z<DIM;z++)
				{
					for (w=0;w<DIM;w++)
					{
						a_avv[z][w]=m[z][w];
					}
				}

				a_avv[o][n]=g;
				int tc=mossaai3(a_avv,h,v);
				if (tc==h)
				{
					acv[o][n]=4;
				}
				if (tc==g)
				{
					mossab(m,g,o,n);
					return g;
				}
				if (tc==0)
				{
					acv[o][n]=3;
				}
			}
		}
	}
	mospattare(m,g,acv);
	return 0;
}

int mossaai2(int m[DIM][DIM], int g)
{

	int i,j,h,acv[DIM][DIM];
	h=g%2+1;
	//array di controllo mosse possibili, i posti dove posso mettere mossa sono quelli con 0, quelli già usati, sono i 2, poi quelli dove vince l'altro saranno gli 1 e 3 dove potrà vincere in due mosse.
	arraymossepossibili(m,acv);
	// vede mosse possibili dell'avversario e salva su array come 1 se posizione perdente per ai.
	/* mossevincentiavv(m,g,acv); */
	mostra_aggiornata_acv(acv);
	//gioca per vincere avendo solo mosse possibili, prova tutte le possibilità, e le annulla, se una è vincente
	//la tiene
	if (mosvincente(m,g,acv)==g)
	{
		return g;
	}
	//copia l'array del tris in un altro array e dallo al giocatore avversario, così da non dover ripristinare la sua mossa!!!
	//vede se può bloccare la mossa dell'avversario
	if (controllaetappa(m, acv, g)==g)
	{
		return g;
	}
	//gioca random
	else
	{
		int o,n,z,w,a_avv[DIM][DIM];
		for (o=0;o<DIM;o++)
		{
			for (n=0;n<DIM;n++)
			{

				if (acv[o][n]==0)
				{
					for (z=0;z<DIM;z++)
					{
						for (w=0;w<DIM;w++)
						{
							a_avv[z][w]=m[z][w];
						}
					}
					a_avv[o][n]=g;

					if (mossaai2(a_avv,h)==h)
					{
						mossab(m,g,o,n);
						return h;
					}
					a_avv[o][n]=0;

				}
			}
		}
	}


	return 0;

}

int array_mossevincenti_per_g(int m[DIM][DIM],int g,int acv [DIM][DIM])
{
	int i,j,c=0;
	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) 
		{
			if (acv[i][j]!=2)	
			{
				m[i][j]=g;
				if (controllatutto(m,g)==g)
				{
					c++;
				}
				m[i][j]=0;
			}
		}
	}
	return c;
}
int f(int m[DIM][DIM],int g)
{
	int h=g%2+1, acv[DIM][DIM];

	int k,j, m_da_passare[DIM][DIM];
	for (k = 0; k < DIM; k++) {
		for (j = 0; j < DIM; j++) {
			m_da_passare[k][j]=m[k][j];
		}
	}
	if (controllatutto(m,h)==h) 
		return h; 
	arraymossepossibili(m,acv);
	// devo fottere l'avversario! EUREKA!
	/* if (mosvincente(m_da_passare,g,acv)==g) */
	/* { */
	/* 	mosvincente(m,g,acv); */
	/* 	return g; */
	/* } */
	int c=array_mossevincenti_per_g(m_da_passare,g,acv);
	printf("%i",c);
	if (c==1)
	{
		mosvincente(m,g,acv);
		return g;
	}
	/* if (mossevincentiavv(m,g,acv)) */
	{
		controllaetappa(m,acv,g);
		return 0;
	}
	/* if (c>=2) */
	/* { */
	/* 	return g; */
	/* } */
	int i,l;
	for (i = 0; i < DIM; i++) 
	{
		for (l = 0; l < DIM; l++) 
		{
			if (acv[i][l]!=2)
			{
				m_da_passare[i][l]=g;
				if (f(m_da_passare,h)==g)
				{
					m[i][l]=g;
					return g;
				}
				else m_da_passare[i][l]=0;
			}
		}
	}
	/* for (k = 0; k < DIM; k++) */
	/* { */
	/* 	for (j = 0; j < DIM; j++) */
	/* 	{ */
	/* 		m[k][j]=m_da_passare[k][j]; */
	/* 	} */
	/* } */
	return 0;
}

int test(int argc, const char *argv[])
{
	int m[DIM][DIM]=
	{
		{2,2,0},
		{0,0,0},
		{0,0,0},	
	};
	mostra_aggiornata(m);

	int acv[DIM][DIM];
	f(m,1);
	mostra_aggiornata(m);
	return 0;
}

int main(int argc, const char *argv[])
{
	int gioco=0;
	int m[DIM][DIM],turni=(DIM*DIM),giocatore;
	do
	{
		//inizializzo matrice e matrice di controllo
		if (turni==(DIM*DIM))
		{
			printf("\n######### TRIS #########\n");
			inizializza(m);
			mostra_aggiornata(m);
			//finchè ho mosse da fare che sono al massimo DIM*DIM
			giocatore=richiestagiocatore();
		}
		else {
			mostra_aggiornata(m);
			printf("\nGiocatore %i tocca a te\n",giocatore);
		}
		int cod,x,y;
		switch (giocatore)
		{
			case 1:mossavivente(m,giocatore);
				   break;
			case 2:f(m,giocatore);
				   break;
			default:
				   errore();
		}
		int c=0;
		if (controllatutto(m,giocatore)==giocatore)
		{
			gioco=vittoria(giocatore);
			c++;
		}
		else
			if(!turni)
			{
				gioco=patta();
				c++;
			}
		if (c>=1)
			turni=DIM*DIM;
	}while (gioco==1);

}
