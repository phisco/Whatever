#include <stdio.h>

#define DIM 3


void matrice_matricetrasposta(int m[DIM][DIM])
{
  int i,j,m_trasposta[DIM][DIM];
  for (i=0;i<DIM;i++)
  {
    for (j=0;j<DIM;j++)
    {
      m_trasposta[i][j]=m[j][i];
    }
  }
}
