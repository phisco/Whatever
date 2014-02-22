
#include<stdio.h>
int controlriga(int x[3][3], int riga)
{
  if (x[riga][0] ==1 && x[riga][1]==1 && x[riga][2]==1)
    return 1;
  else return 0;
}

int controlgioco(int x[2][2],int riga,int colonna)
{
  int r,c,d,i;
  for ( i=0; i<riga; i++)
  {
    int a;
    for (a=0; a<colonna;a++)
    {
    if ( x[a][i]==1)
      d+=1;
    }
  }
}

int main(int argc,const char * argv [])
{
  
}
