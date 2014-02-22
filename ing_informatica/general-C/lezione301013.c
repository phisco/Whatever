

#include<stdio.h>

//con # parlo con processore
#define DIM 1000

int main(int argc,const char * argv [])
{
  //DRY!!! DON'T REPEAT YOURSELF
  //inizializza matrice m
  //ANSI C PROIBISCE PERò DI DARE ARRAY SENZA COSTANTI=> TRUCCO
  //trucco= preprocessore a cui possiamo passare il nostro codice prima di compilarlo,
  //perciò possiamo dirgli di sostituire variabile con valore dato
  int m[DIM][DIM],i,a;
  for(a=0;a<=DIM-1;a++)
  {
    for(i=0;i<=DIM-1;i++)
      m[a][i]=0;
  }
  //faccio matrice unità
  for(i=0;i<=DIM-1;i++)
   m[i][i]=1;
}

//controllare se matrice uguale matrice unità
int isunita(int m[DIM][DIM])
{
  //ritorniamo 1 se matrice è unitaria, 0 altrimenti
  int i,j;
  for (i=0;i<DIM;i++)
  {
   for (j=0;j<DIM;j++)
    {
       if (i==j)
       { 
         if(m[i][j]!=1) return 0;
       }
       else 
         if(m[i][j]!=0) return 0;
    }
  }
  return 1;
}

//scriviamo un funzione che ritorni 1se c'è una riga di tutti 1 nella matrice
int is_there_riga_uni(int m[DIM][DIM])
{
  int i,j;
  for (i=0;i<DIM;i++)
  {
    int r=0;
    for(j=0;j<DIM;j++)
    {
      if (m[i][j]==1)
        r+=1;
    }
    if (r==DIM)
      return 1;
  }
  return 0;
}
