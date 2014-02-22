#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//funzione che presa una stringa ne restituisca la lunghezza
int stringLen(char x[])
{
		int i;
		for (i=0;x[i]!='\0';i++)
		{
		}
		return i;
}

int strEq(char x[],char y[])
{
		int i;
		for (i = 0; i < stringLen(x); i++) 
		{
				if (x[i]!=y[i])
						return 0;
		}
		if (y[i]=='\0') return 1;
		return 0;
}
int contaChar(char l,char word[])
{
		int i,c=0;

		for (i = 0; i < stringLen(word); i++) 
		{
				if (word[i]==l)
						c++;
		}
		return c;
}

int subStr(char x[],char y[])
{
		int i, l;
		for (i = 0; y[i]!='\0'; i++) 
		{
				if (y[i]==x[0])
				{

						for (l = 0;x[l]!='\0'; l++) 
						{
								if (y[i+l]!=x[l])
										break;
						}
						if (x[l]=='\0')
								return i;
				}
		}
		return 0;
}
int main()
{
		printf("%i\n", subStr("ciao", "come stai ciao ciao"));
}
