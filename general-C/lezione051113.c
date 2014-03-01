//sudoku
//matrice quadrato 9*9
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
#define ORDINE 2
#define DIM (ORDINE*ORDINE)
#include <stdio.h>
int riga_giusta(int m[DIM][DIM],int r)
{
  int cifre[DIM];
    int i;
    for (i=0;i<DIM;i++){
      cifre[i]=0;
    }
    //fa un array con posizione 0 le volte che incontra lo 0, cifre[1] volte che incontra l'uno ecc
    //così faccio un ciclo che aumenti il valore di 
    for (i=0;i<DIM;i++){
      if (m[r][i]>0)
        cifre[m[r][i]-1]++;

     }
    for (i=0;i<DIM;i++)
      if (cifre[i]>1)
        return 1;
    return 0;
}

int main(int argc, const char *argv[])
{
  int s[4][4]= {
    {1,2,0,0},
    {3,4,4,0},
    {3,2,1,4},
    {1,2,3,4}
    
  };

  if (riga_giusta(s,0)==1)
    printf("test 0 superato\n");
    else 
      printf("tu dici che la riga 0 non è giusta, ma a me sembra che lo sia\n");
  if (riga_giusta(s,0)==0)
    printf("tu dici che la riga 0 non è giusta, ma a me pare che lo sia");
  else
    printf("hai toppatola riga 1\n");

  return 0;
}
