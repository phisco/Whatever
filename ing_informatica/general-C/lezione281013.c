#include<stdio.h>

int vincente(int n)
{
  int i;
  if (n<3) return 1;
  if (n<6) return 0;
  for (i=n/2;i<0;i--)
  {
  // printf(" %d (%d) = %d + %d\n",n,k,i,n-i);
   if (vincente(i)==0 && vincente(n-i)==0)
      return 1;
  }
  return 0;
}

int main(int argc,const char * argv [])
{
  int num;
  for(num=0;num<10000;num++)
    if(vincente(num)==1)
        printf("il numero %d è vincente! ^_^\n", num);
    else
        printf("il numero %d è perdente! :(\n", num);
        return 0;
}
