			//funzioni somma pari
int sommapari(int n) 
{
	int i,s;
	s=0;	for (i=2;i<n;i++)
	{
		if (i%2==0) s=s+i;
	}
	return s;
}

int sommapari2(int n) 
//risparmio il 30% dei calcoli
{
	int i,s;
	s=0;	for (i=2;i<n;i=i+2)
	{
		s=s+i;
	}
	return s;
}




			//gioco 21/10/13

		

// funzione che rappresenta la mossa del primo giocatore
int p1(int numero)
{
    return numero-1;
}

// funzione che rappresenta la mossa del secondo giocatore
int p2(int numero)
{
    return numero-1;
}

	
// funzione che rappresenta una generica mossa di una partita di un gioco multigiocatore
int mossa(int stato, int giocatore)
{
    int risultato;
    
    if(giocatore==1)
   risultato = p1(stato);
    else
        risultato = p2(stato);
    
    giocatore=3-giocatore;
    
    if(risultato==1 || risultato!=stato-1)
        return giocatore;
    
    return mossa(risultato,giocatore);
}


			//gioco modificato per fare gioco che prende un numero di due e restituisce due numeri la cui somma da' il primo
//funzione che codifica il numero
int codifica(int numero1, int numero2)
	{	
		int numero3;
		numero3= (numero1*1000)+numero2;
	}


//funzione che decodifica il numero uno sarà il risultato e l'altro il resto della divisione intera di numero3 per 1000

int decodifica1(int numero3) 
	{
		numero1= numero3/1000;
		return numero1;
	}

int decodifica2(int numero3) 
	{
		int numero1
		numero2= numero3%1000;
		return numero2;
	}
	
//oppure funzione singola con if

int decodifica(int numero, int param)
	{
		if(param==1)
			return numero/1000;
		return numero%1000;
	}	

// funzione che rappresenta la mossa del primo giocatore
int p1(int numero1, int numero2)
{
	numero3= numero1
    return numero3;
}

// funzione che rappresenta la mossa del secondo giocatore
int p2(int numero)
{
    return numero-1;
}


int p1a(int numero1,int numero2)
{
	return numero 1;
}
int p1b(int numero)
{
	return codifica(numero-3,3)
}
int p2a(int numero1,int numero2)
{
	return numero 1;
}
int p2b(int numero)
{
	return codifica(numero-4,4)
}


// funzione che rappresenta una generica mossa di una partita di un gioco multigiocatore
int mossa(int stato, int giocatore)
{
    int risultato;
    
    if(giocatore==1)
   risultato = p1(stato);
    else
        risultato = p2(stato);
    
    giocatore=3-giocatore;
    
    if(risultato==1 || risultato!=stato-1)
        return giocatore;
    
    return mossa(risultato,giocatore);
}

// funzione che rappresenta una generica mossa di una partita di un gioco multigiocatore
int mossa(int numero1, int numero2, int giocatore)
{
    int risultato;
    
    if(giocatore==1)	
    {
   		risultato = p1a(numero1, numero2);
   		risultato= p1b(risultato);
   	}
    else
    {
        risultato = p2a(numero1, numero2);
   		risultato = p2b(risultato);
	}
    	
    giocatore=3-giocatore;
    
    if(decodifica1(risultato)<3 || decodifica2(risultato)<3)
    //bisogna implementare i controlli per vedere se numero inserito giusto, divisto giusto ecc.
    
        return giocatore;
    
    return mossa(decodifica1(risultato),decodifica2(risultato),giocatore);
}


//funzione che dice se numero vince o no
//numero vincente se posso scomporlo in due numeri perdenti per l'avversario
int vincente(int n)
{
	int i;
	if(n<3) return 1;
	if(n<5)return 0;
	for(i=0;i<n;i++)
		if (vincente(i)==0 && vincente(n-i)==0)
			return 1;
			
	return 0;
}


			//vincente a gioco per n come numero massimo perdente.cioè tutti i numeri fino a n sono perdenti
int vincenten(int n, int p)
{
	int i;
	if (n<p) return 1;
	if (n%(p+1)==0) return 0;
	for(i=0;i<n;i++)
		if (vincente(i)==0 && vincente(n-i)==0)
			return 1;
	return 0;
}

//22/10/13 funzione che ritorni dato un numero, risponde quale è la cifra più presente in quel numero

int sommacifre(int n)
{
	int s=0; //ho creato una variabile, s, su cui accumulo i valori di c, e sarà una variabile globale
	for(;n>0;n=n/10) //non c'è l'inizializzazione del ciclo, la regola di permanenza nel ciclo è che n sia minore di 0;
	{	int c; //variabile locale circoscritta al blocco, regola di shadowing: dichiarando all'interno di un blocco, una variabile presente anche all'esterno del blocco, quella interna scherma quella esterna, perciò è come se non ci fosse.
	//ciclo while(condizione) {comando}
	//ciclo do 			while( ){} fa un giro e poi valuta il while
		c=n%10;
		s=s+c;
	}
}


int cifrapiùcomune(int n)
{
	int i,numcar;
	numcar=
	for(i=0;i=numerocaratteri;i++)
	{
		
		
	}
}

