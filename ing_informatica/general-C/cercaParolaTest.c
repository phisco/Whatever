int cercaParola(char* parola, char *frase)
{
	char terminatore='\0';
	char spazio =' ';
	int i,l,contatore=0,pos=0,j;
	for (j = 0;parola[j]!=terminatore; j++){if (parola[j+1]==',' || parola[j+1]==terminatore)
		{
		for (i = 0; frase[i]!=terminatore; i++) {
			if (frase[i]==parola[pos])
			{
				for(l=1;pos+l<j+1;l++)
				{
					if (frase[i+l]!=parola[pos+l])
					{
						break;
					}
				}
				if (j+1-pos==l )
				{
					char t_frase=frase[i+l];
					if ( !(('A'<=frase[i+l] && frase[i+l]<='Z') || ('a'<=frase[i+l] && frase[i+l]<='z' )))
						/* if ( frase[i+l]==' ' || frase[i+l]=='\0') */
						contatore++;
				}
			}
		}
	}pos=j+2;}
return contatore;
}
