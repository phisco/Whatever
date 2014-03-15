int cercaParola(char* parola, char *frase)
{
	int i,l,c=0;
	for (i = 0; frase[i]!='\0'; i++) {
		if (frase[i]==*parola)
		{
			for(l=0;parola[l]!='\0';l++)
			{
				if (frase[i+l]!=parola[l])
					break;
			}
			if (strlen(parola)==l )
				if (frase[i+l]==' ' || frase[i+l]=='\0')
					c++;
		}
	}
	return c;
}
