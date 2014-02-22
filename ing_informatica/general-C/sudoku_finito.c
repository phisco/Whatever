//matrice quadrato 9*9
//sudoku
//tutti problemi simili, esempio la fattorizzazione di un numero(scomposizione in numeri primi
//di un numero), problema del commesso viaggiatore che deve trovare strada più breve per passare per tutte le città, poi aggiungedo un solo elemento e il numero di
//combinazioni esplode fattorialmente 3 città 3! 4=>4! ecc quindi potremmo metterci millegni
//Tutti i problemi si possono ascrivere a una categoria, che può, datogli un problema del commesso , restituisce un sudoku da risolvere, che risolto permette di 
//risolvere il problema iniziale in tempi utili
//quindi abbassare a un tempo che aumenta invece che fattorialmente o esponenzialmente, almeno a polinomiale, va benissimo! sarebbe lo scopo
//
//dobbiamo fare una f risolvi che preso un sudoku lo risolva.
//
//approccio bottomup, inizio ad aggirare il problema: faccio una funzione che controlli se matrice di sudoku è giusta o sbagliata
//
//facessi una funzione mossa_giusta che datogli un sudoku, una casella e un numero da metterci, dice se la mossa è giusta o meno=>avrei risolto il sudoku
//=>partiamo da più smplice, mossa è sbagliata se non rispetta una delle regole del sudoku, quindi uguale a dare uno schema e vedere se è giusto o meno
//=> riga corretta se non c'è due volte lo stesso numero;
//colonna idem;
//sottosudoku(riquadro 3x3) corretto se non c'è due volte lo stesso numero;
//a meno che non sia 0 ripetuto, che è equivalente allo spazio vuoto
//
//    matrice sudoku funziona se i lati sono quadrati perfetti 3*3 4*4 ecc
//    quindi inizializzo con un define le misure del sudoku, quindi troviamo soluzione per sudoku generico di lato n^2=> andiamo al caso più semplice possibile
//
//quindi facciamo prima una funzione che controlla una riga e dice se giusta
//
#define ORDINE 3
#define DIM (ORDINE*ORDINE)
#include <stdio.h>
//facciamo funzione che restituisca la riga dell'n-esimo elemento del quadro x,y
//suddivide la matrice in quattro quadri, le coordinate degli elementi ad essi appartenenti ???
//n è l'elemnto del quadro, x e y le coordinate del quadrato => 0,0 alto sx; 0,1 alto dx; 1,0 basso sx; 1,1 basso dx
int cella_quadro_x(int x, int y,int n)
{
  return x*ORDINE+n/ORDINE;
}

int cella_quadro_y(int x, int y,int n)
{
  return y*ORDINE+n%ORDINE;
}

//da mettere una codifica dei due parametri in uno solo da passare a giusta per cordinate quadro
int giusta(int m[DIM][DIM], int x,int y, int crq)
    //rendo parametrico l'accesso alla matrice=>con espressione condizionoale (condizione ? se_vero :se_falso)prende un valore o l'altro se è giusta o meno
    //m[cr==0 ? i : n][cr==0 ? i : n]
{
    int cifre[DIM];
    int i;
    for (i=0;i<DIM;i++){
      cifre[i]=0;
   //printf("%d\n",cifre[i]);
    }
    //fa un array con posizione 0 le volte che incontra lo 0, cifre[1] volte che incontra l'uno ecc
    //così faccio un ciclo che aumenti il valore di
    //valori di crq
    //0 colonna m[i][fermo]
    //1 riga m[fermo][i]
    //2 quadro m[cella_quadro_x][cella_quadro_y]
   // printf("%d\n",m[cella_quadro_x(x,y,8)][cella_quadro_y(x,y,8)]);
    for (i=0;i<DIM;i++)
    {
      if (m[crq==0 ? i : (crq==1 ? y : cella_quadro_x(x,y,i))][crq==0 ? y : (crq==1 ? i : cella_quadro_y(x,y,i))]>0)
      {   
        // printf("il numero %d compare %d volte \n",m[crq==0 ? i : (crq==1 ? y : cella_quadro_x(x,y,i))][crq==0 ? y : (crq==1 ? i : cella_quadro_y(x,y,i))],cifre[m[crq==0 ? i : (crq==1 ? y : cella_quadro_x(x,y,i))][crq==0 ? y : (crq==1 ? i : cella_quadro_y(x,y,i))]]);
        //printf("%d,%d,1\n",crq==0 ? i : (crq==1 ? y : cella_quadro_x(x,y,i)),crq==0 ? y : (crq==1 ? i : cella_quadro_y(x,y,i)));
        if (cifre[m[crq==0 ? i : (crq==1 ? y : cella_quadro_x(x,y,i))][crq==0 ? y : (crq==1 ? i : cella_quadro_y(x,y,i))]-1]>=1)
        {
          //in base a cosa gli ho chiesto (se riga colonna o quadro), mi prende le coordinate giuste e se non è già presente quella cifra nel controllo,
          //mi aumenta il contatore della cifra per quel dato controllo.
          //se c'è una cifra che mi
          //
          //
          //printf("il numero %d compare %d volte \n",m[crq==0 ? i : (crq==1 ? y : cella_quadro_x(x,y,i))][crq==0 ? y : (crq==1 ? i : cella_quadro_y(x,y,i))],cifre[m[crq==0 ? i : (crq==1 ? y : cella_quadro_x(x,y,i))][crq==0 ? y : (crq==1 ? i : cella_quadro_y(x,y,i))]-1]);


          //printf("%d,%d,2a\n",crq==0 ? i : (crq==1 ? y : cella_quadro_x(x,y,i)),crq==0 ? y : (crq==1 ? i : cella_quadro_y(x,y,i)));
          return 0;
        }
        else
        {
          //  printf("%d,%d,2b\n",crq==0 ? i : (crq==1 ? y : cella_quadro_x(x,y,i)),crq==0 ? y : (crq==1 ? i : cella_quadro_y(x,y,i)));
          cifre[(m[crq==0 ? i : (crq==1 ? y : cella_quadro_x(x,y,i))][crq==0 ? y : (crq==1 ? i : cella_quadro_y(x,y,i))])-1]++;
          //printf("il numero %d compare %d volte \n",m[crq==0 ? i : (crq==1 ? y : cella_quadro_x(x,y,i))][crq==0 ? y : (crq==1 ? i : cella_quadro_y(x,y,i))],cifre[m[crq==0 ? i : (crq==1 ? y : cella_quadro_x(x,y,i))][crq==0 ? y : (crq==1 ? i : cella_quadro_y(x,y,i))]-1]);

          // if ( cifre[m[crq==0 ? i : (crq==1 ? n : cella_quadro_x(x,n,i))][crq==0 ? n : (crq==1 ? i : cella_quadro_y(x,n,i))]]>1)
          // return 0;
        }
      }
    }
  // printf("ha finito il ciclo\n");
return 1;
}

int riga_giusta(int m[DIM][DIM],int r)
{
  return giusta(m,0,r,1);
}

int colonna_giusta(int m[DIM][DIM],int c)
{
  return giusta(m,0,c,0);
}

int quadro_giusto2(int m[DIM][DIM], int x, int y)
{
  return giusta(m,x,y,2);
}

//per evitare di fare due funzioni, ne faccio una sola che racchiuda le altre due, a seconda che io voglia riga o colonna


int quadro_giusto(int m[DIM][DIM],int x, int y)
{
    int cifre[DIM];
    int i;
  
    for (i=0;i<DIM;i++)
      cifre[i]=0;
    for (i=0;i<DIM;i++)
    {
      if (m[cella_quadro_x(x,y,i)][cella_quadro_y(x,y,i)]>0)
      {
        if (cifre[m[cella_quadro_x(x,y,i)][cella_quadro_y(x,y,i)]-1]>0)
        {
          return 0;
        }
        else
        {
          cifre[m[cella_quadro_x(x,y,i)][cella_quadro_y(x,y,i)]]++;
        }
      }
    }
return 1;
}

int controlla_tutto(int m[DIM][DIM])
{
  int i;
  for (i=0;i<DIM; i++)
  {
    if (riga_giusta(m,i)==0)
      return 0;
    if (colonna_giusta(m,i)==0)
       return 0;
    if (quadro_giusto2(m,i/ORDINE,i%ORDINE)==0)
      return 0;

  }
  return 1;
}

int risolvi(int m[DIM][DIM])
{
  if (controlla_tutto(m)==0)
  {
    return 0;
  }
  int i,j,k;
  for (i=0;i<DIM;i++)
  {
    for (j=0; j<DIM; j++)
    {
      if (m[i][j]==0)
      {
        for (k=1;k<=DIM;k++)
        {
          m[i][j]=k;
          if (risolvi(m)==1)
            return 1;
        }
        m[i][j]=0;
        return 0;

      }
    }
  }
  return 1;
}

int stampa_sudoku(int m[DIM][DIM])
{
  int i,j;
  for (i=0;i<DIM;i++)
  {
    for (j=0;j<DIM;j++)
    {
      printf("| %i |",m[i][j]);
    }
    printf("\n---------------------------------------------------------\n");

  }

  printf("\n----------------------------------------------------------\n");
  printf("\n----------------------------------------------------------\n");
  return 0;
}

int svuota_sudoku(int m[DIM][DIM])
{
  int i,j;
  for (i=0;i<DIM;i++)
  {
    for (j=0;j<DIM;j++)
    {
      m[i][j]=0;
    }
  }
return 0;
}

int test()
{
  int s[DIM][DIM]=
  {

    { 1, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

  stampa_sudoku(s);
  switch (risolvi(s))
  {
    case 1:
      printf("lo schema è risolvibile\n");
      break;
    case 0:
      printf("lo schema non è risolvibile\n");
      break;
    default:
      printf("errore!!!\n");
      break;
  }
  stampa_sudoku(s);
  return 0;
}


int main(int argc, const char *argv[])
{
  test();
}
