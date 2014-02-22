#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int cercaParola(char* parola, char *frase)
{
	char terminatore='\0';
	char spazio =' ';
	int i,l,j,contatore=0;
	int pos=0;
	for (j = 0;parola[j]!=terminatore; j++) 
	{
		if (parola[j+1]==',' || parola[j+1]==terminatore)
		{
			for (i = 0; frase[i]!=terminatore; i++) 
			{
				if (frase[i]==parola[pos])
				{
					for(l=1;(pos+l)<j+1;l++)
					{
						if (frase[i+l]!=parola[pos+l])
						{
							break;
						}
					}
					if (j+1-pos==l)
					{
						if ( !(('A'<=frase[i+l] && frase[i+l]<='Z') || ('a'<=frase[i+l] && frase[i+l]<='z' )) )
						{	
							contatore++;
						}
					}
				}

			}
				pos=j+2;
		}
	}

	return contatore;    
}

//fscanf legge file come se fosse scritto da tastiera e lo salva in una variabile
//strdup duplica la stringa data e restituisce puntatore


int main(int argc, char *argv[])
{
	printf("%i\n", cercaParola(argv[1],argv[2]));
	return 0;
}
