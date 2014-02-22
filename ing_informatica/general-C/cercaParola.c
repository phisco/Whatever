#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int cercaParola(char* parola, char *frase)
{
	char terminatore='\0';
	char spazio =' ';
	int i,l,j,contatore=0;
	int pos=0;
	for (i = 0;parola[i]!=terminatore; i++) 
	{
		if (parola[i+1]==',' || parola[i+1]==terminatore)
		{
			for (j = 0; frase[j]!=terminatore; j++) 
			{
				if (frase[j]==parola[pos])
				{
					for(l=1;(pos+l)<i+1;l++)
					{
						if (frase[j+l]!=parola[pos+l])
						{
							break;
						}
					}
					if (i+1-pos==l)
					{
						if ( !(('A'<=frase[j+l] && frase[j+l]<='Z') || ('a'<=frase[j+l] && frase[j+l]<='z' )) )
						{	
							contatore++;
						}
					}
				}

			}
				pos=i+2;
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
