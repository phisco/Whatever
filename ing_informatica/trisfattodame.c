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
void errore()
{
	printf("\nc'è qualcosa che non è andato come ci aspettavamo\nPOI VEDI TU!!!\n");
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


// vede mosse possibili dell'avversario e salva su array come 1 se posizione 
// perdente per ai.
int mossevincentiavv(int m[DIM][DIM],int g,int acv[DIM][DIM])
{   int avv=g%2+1;
    int k, l,c=0;
    for (k=0;k<DIM;k++)
    {
        for (l=0;l<DIM;l++)
        {
            if ( acv[k][l]==0)
            {
              int preb=m[k][l];
              if(mossab(m,avv,k,l)==avv)
              {
                acv[k][l]=1;
                /* printf("c è %i, potrebbe vincere giocando in %i,%i",c,k,l); */
                c++;
              }
              m[k][l]=preb;
            }
        }
    }
    return c;
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
              acv[p][q]=2;
        }
    }
    return 0;
}
//controlla se c'è una posizione vincente per l'avversario su array di controllo e gioca,
int controllaetappa(int m[DIM][DIM],int acv[DIM][DIM],int g)
{
    int o,n;
    for (o=0;o<DIM;o++)
    {
        for (n=0;n<DIM;n++)
        {
            if (acv[o][n]==1)
            {
                mossab(m,g,o,n);
                return 0;
            }
        }
    }
    return g;
}

/* int mospattare(int m[DIM][DIM],int g,int acv[DIM][DIM]) */
/* { */
/*   int o,n; */
/*     for (o=0;o<DIM;o++) */
/*     { */
/*         for (n=0;n<DIM;n++) */
/*         { */
/*             if (acv[o][n]==3) */
/*             { */
/*                 mossab(m,g,o,n); */
/*                 return 0; */
/*             } */
/*         } */
/*     } */
/*     return 0; */
/* } */
//gioca per vincere avendo solo mosse possibili, prova tutte le possibilità, e le annulla, se una è vincente
//la tiene
int mosvincente(int m[DIM][DIM],int g,int acv[DIM][DIM])
{
  int i, j;
  for (i=0;i<DIM;i++)
  {
    for (j=0;j<DIM;j++)
    {
      if (acv[i][j]!=2)
      {
        int pre=m[i][j];
        if (mossab(m,g,i,j)==g)
        {
          return g;
        }
        else
          m[i][j]=pre;
      }
    }
  }
  return 0;
}

/* int mosspossvittoria(int m[DIM][DIM],int g, int acv[DIM][DIM]) */
/* { */
/*   int i, j; */
/*   for(i=0;i<DIM;i++) */
/*   { */
/*     for (j=0;j<DIM;j++) */
/*     { */
/*       if (acv[i][j]==4) */
/*       { */
/*         mossab(m,g,i,j); */
/*         return g; */
/*       } */
/*     } */
/*   } */
/*   return 0; */
/* } */




//mossa generica AI

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


int f2(int m[DIM][DIM],int g)
{
	mostra_aggiornata(m);
	int h=g%2+1, acv[DIM][DIM];
	if (controllatutto(m,h)==h) 
		return h; 	
	int k,j, m_da_passare[DIM][DIM];
	for (k = 0; k < DIM; k++) {
		for (j = 0; j < DIM; j++) {
			m_da_passare[k][j]=m[k][j];
		}
	}

	arraymossepossibili(m,acv);
	// devo fottere l'avversario! EUREKA!
	if (mosvincente(m,g,acv)==g)
	{
		return g;	
	}
	/* int c=array_mossevincenti_per_g(m_da_passare,g,acv); */
	/* if (c==1) */
	/* { */
	/* 	mosvincente(m,g,acv); */
	/* 	return g; */
	/* } */
	int cont=mossevincentiavv(m,g,acv);
	/* printf("ha %i possibilità di vittoria",cont); */
	mostra_aggiornata_acv(acv);
	if (cont>=1)
	{
		if (cont>1) 
		{
			controllaetappa(m,acv,g);
			/* printf("finqua ci arrivo\n"); */
			return h;
		}
		else
		{
			controllaetappa(m,acv,g);
			return 0;
		}
	}

	/* if (!controllaetappa(m,acv,g)) */
	/* 		return 0; */
	/* if (c>=2) */
	/* { */
	/* 	return g; */
	/* } */
	
	/* mostra_aggiornata_acv(acv); */
	int i,l;
	/* printf("qua"); */
	for (i = 0; i < DIM; i++) 
	{
		for (l = 0; l < DIM; l++) 
		{
			if (acv[i][l]!=2)
			{
					/* m_da_passare[i][l]=g; */
					m[i][l]=g;
					/* printf("qua"); */

					/* if (f2(m_da_passare,h)==g) */
					if (f2(m,h)==g)
					{
							/* mostra_aggiornata(m_da_passare); */
							/* m[i][l]=g; */
							/* printf("qui"); */
							return g;
					}
					/* printf("qu1"); */
					m[i][l]=0;
					/* m_da_passare[i][l]=0; */
			}
		}
	}
	/* printf("la"); */
	/* for (k = 0; k < DIM; k++) */
	/* { */
	/* 	for (j = 0; j < DIM; j++) */
	/* 	{ */
	/* 		m[k][j]=m_da_passare[k][j]; */
	/* 	} */
	/* } */
	return 0;
}
int f(int m[DIM][DIM],int g)
{
	int h=g%2+1, acv[DIM][DIM];
	if (controllatutto(m,h)==h) 
		return h; 	
	int k,j,i,l, m_da_passare[DIM][DIM];
	for (k = 0; k < DIM; k++) {
		for (j = 0; j < DIM; j++) {
			m_da_passare[k][j]=m[k][j];
		}
	}

	arraymossepossibili(m,acv);
	// devo fottere l'avversario! EUREKA!
	if (mosvincente(m,g,acv)==g)
	{
		return g;
	}
	/* int c=array_mossevincenti_per_g(m_da_passare,g,acv); */
	/* if (c==1) */
	/* { */
	/* 	mosvincente(m,g,acv); */
	/* 	return g; */
	/* } */
	int cont=mossevincentiavv(m,g,acv);
	/* mostra_aggiornata_acv(acv); */
		
	/* mostra_aggiornata_acv(acv); */
	printf("finqua ci arrivo\n");
	if (!controllaetappa(m,acv,g))
	{
		if (cont>=1)
			return h;
		else
			return g;
	}
	/* if (c>=2) */
	/* { */
	/* 	return g; */
	/* } */
	
	/* mostra_aggiornata_acv(acv); */
	for (i = 0; i < DIM; i++) 
	{
		for (l = 0; l < DIM; l++) 
		{
			if (acv[i][l]!=2)
			{
					m_da_passare[i][l]=g;
					/* printf("qua"); */
					if (f(m_da_passare,h)==g)
					{
							/* mostra_aggiornata(m_da_passare); */
							m[i][l]=g;
							printf("qui");
							return g;
					}
					/* printf("qu1"); */
					m_da_passare[i][l]=0;
			}
		}
	}
	printf("la");
	/* for (k = 0; k < DIM; k++) */
	/* { */
	/* 	for (j = 0; j < DIM; j++) */
	/* 	{ */
	/* 		m[k][j]=m_da_passare[k][j]; */
	/* 	} */
	/* } */
	return 0;
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
			}

			switch (giocatore)
			{
					case 1:c=1;
						   break;
					case 2: c=1;
							break;
					default: c=0;
			}
			if (c==1)
					return giocatore;
			if (c!=1)
			{
					printf("Non hai immesso un valore valido! Riprova!\n");
					scanf("%i", &giocatore);

			}
	} 	while (c!=1);
	return 0;
}



int partita()
{
	int gioco=1;
	int m[DIM][DIM],turni=(DIM*DIM-1),giocatore;
	do
	{
		//inizializzo matrice e matrice di controllo
		if (turni==(DIM*DIM-1))
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
			case 2:f2(m,giocatore);
						 break;
			default:
						 errore();
		}
		turni--;
		giocatore=giocatore%2+1;

		int c=0;
		if (controllatutto(m,giocatore))
		{
			gioco=vittoria(giocatore);
			c++;
		}
		if(!turni)
		{
			gioco=patta();
			c++;
		}
		if (c>=1)
			turni=DIM*DIM;
	}while (gioco==1);
	return 0;
}

int test()
{
	int m[DIM][DIM]=
	{
		{1,0,0},
		{0,0,0},
		{0,0,0},
	};
	mostra_aggiornata(m);
	int a=0;
	int *c=&a;
	f2(m,1);
	printf("ho scelto\n");
	mostra_aggiornata(m);
	return 0;
}
int main()
{
	test();
	/* partita(); */
}


