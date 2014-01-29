
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include <unistd.h>

typedef struct node
{
	char* word;
	struct node* next;
	char* p_dizionario;
}node;

//converte parola in minuscole
//data la lunghezza della parola e il puntatore alla parola
void convertToLow(int len_parola,char *parola)
{
	int i;
	for(i=0; i<len_parola; i++)
	{
		parola[i] = tolower(parola[i]);
	}
}

//controlla se due parole sono una l'anagramma dell'altra
//return 1 se lo sono
// 0 se non lo sono
int anagramma(int len_parola, char *parola1,char *parola2,int* a_controllo)
{
	int i,l,cont=0;
	int* a_controllo_anagramma=calloc(len_parola,sizeof(short int));
	for (i=0; i<len_parola && (cont==i || cont==i-1);i++)
		{
			for(l=0;l<len_parola && cont==i;l++)
			{
				if(parola1[i]==parola2[l] && a_controllo_anagramma[l]==0 && a_controllo[i])
				{
					a_controllo_anagramma[l]=1;
					cont++;
				}
			}
		}
	free(a_controllo_anagramma);
	return cont;
}

//controlla se due parole sono una uguali all'altra meno una lettera che è stata cambiata
//return 1 se lo sono
// 0 se non lo sono

int cambioLettera(int len_parola, char *parola1,char *parola2,int *a_controllo)
{
	int i,cont;
	cont=0;
	for (i = 0; i < len_parola; i++) {
			if (parola1[i]==parola2[i] && cont>=i-1)
			{
				cont++;
			}
			else
				if (parola1[i]!=parola2[i] && a_controllo[i])
					return 0;
		}
	return cont;
}


//controlla se due parole sono una uguali all'altra meno una lettera che è stata tolta
//return 1 se lo sono
// 0 se non lo sono
int letteraInMeno(int len_parola1,int len_parola2, char *parola1,char *parola2,int* a_controllo)
{
	int i, c,cont;
	c=0;
	cont=0;
	for (i = 0; i < (len_parola1>len_parola2? len_parola1 : len_parola2); i++) {
		if (parola1[(len_parola1>len_parola2 ? i : c )]==parola2[(len_parola1>len_parola2 ? c : i )])
		{
			if(!a_controllo[(len_parola1>len_parola2? i : c)])cont++;
			c++;
		}
		else
		{
			c=i;
		}
	}
	return cont;
}

//controlla se due parole 
//return 1 se lo sono
// 0 se non lo sono
int controllo(char *p1,char *p2,int *a_controllo)
{
	char *parola1;
	char *parola2;
	int len_parola1,len_parola2,len_max,len_min;
	int c=0;
	parola1=strdup(p1);
	parola2=strdup(p2);

	len_parola1=strlen(parola1);
	len_parola2=strlen(parola2);
	len_max=(len_parola1>=len_parola2 ? len_parola1 : len_parola2);
	len_min=(len_parola1>=len_parola2 ? len_parola2 : len_parola1);
	
	/*conversione da maiuscole a minuscole*/
	convertToLow(len_parola1,parola1);
	convertToLow(len_parola2,parola2);
	
	if(len_parola1==len_parola2)
	{
		if (anagramma(len_parola1,parola1,parola2,a_controllo)==len_max)
			c=1;
		else
			if (cambioLettera(len_max,parola1,parola2,a_controllo)==len_max-1)
				c=1;
	}
	else
		if (len_min==len_max-1)	
		{
			if (letteraInMeno(len_parola1,len_parola2,parola1,parola2,a_controllo)==len_min)
		c=1;	

		}
	if (c==1)
		{
			/* sleep(1); */
			printf("%s e %s ok\n",parola1,parola2);
			free(parola1);
			free(parola2);
			return 1;
		}
	else
		return 0;
}


int contaParole(char *nomeFile)
{
	FILE *f;
	int cont;
	char buffer[30];
	int vuota=0;
	vuota++;

	f=fopen(nomeFile,"r");
	
		cont=0;
	
    while(!feof(f))
    {
        vuota=fscanf(f,"%s",buffer);
        cont++;
    }
    cont--;
    
    fclose(f);
    return cont;
}

int append(node *head, char* string )
{
	if (head==(NULL))
		return -1;
	if(head->next==NULL)
		{
			head->next=(node*)malloc(sizeof(node));
			(head->next)->word=strdup(string);
			(head->next)->next=NULL;
			(head->next)->p_dizionario=string;
			return 1;
		}
	else
	append(head->next,string);
	return 0;
}

int stampa_lista(node* head)
{
	printf("%s\n",head->word);
	if (head->next!=NULL)
		stampa_lista(head->next);
	return 1;
}

int controlla_ultima_altra(node* prima_p,char* parola,int* a_controllo)
{
	int propag=0;
	if (prima_p==NULL)
		return-1;
	if (prima_p->next!=NULL)
	{
		/* printf("scalo\n"); */
		propag=controlla_ultima_altra(prima_p->next,parola,a_controllo);
	}
	else
	{
		/* printf("ok ora vedo se %s e %s vanno bene\n",prima_p->word,parola); */
		return (controllo(prima_p->word,parola,a_controllo) && prima_p->p_dizionario!=parola);
	}
	if (propag==0)
		return 0;
	else return(prima_p->p_dizionario!=parola);
}

int copia_lista_interno(node* head,node* new_head)
{
	if(head!=NULL){
		/* printf("ora copio %s\n",head->word); */
	new_head->word=strdup(head->word);
	/* printf("ok la parola %s è stata copiata,vedi? %s \n",head->word,new_head->word); */
	new_head->p_dizionario=head->p_dizionario;
	/* printf("ok ora sono qui!\n"); */
	if(head->next!=NULL)new_head->next=calloc(1,sizeof(node));
	
	/* new_head->word=strdup(head->word); */
	/* append2CopyList(head,new_head); */
	/* new_head->next=calloc(1,sizeof(node)); */
	if(head->next!=NULL)
	{

	/* printf("ok arrivo fin qui!!\n"); */
		copia_lista_interno(head->next,new_head->next);
	}
	/* else printf("ok la lista madre è finita\n") ; */
	return 1;
	}
	return 0;
}

node* copia_lista(node* head)
{
	
	if (head!=NULL)
	{
		node* new_head=calloc(1,sizeof(node));

		if (new_head!=NULL)
		{
			copia_lista_interno(head,new_head);
		}
		return new_head;
	}
	return NULL;
}




int risolvi_lista(char** parole,node* prima_p, char* final_p,int numeroParole,int* a_controllo)
{
	/* printf("ok mo ci provo\n"); */
	int i=0;
	if (controlla_ultima_altra(prima_p,final_p,a_controllo))
	{
		/* printf("ok l'ultima parola immessa va bene con la finale!\n"); */
		append(prima_p,final_p);
		printf("questa lista porta da dove vuoi partire a dove vuoi andare:\n");
		stampa_lista(prima_p);
		printf("----------------\n");
		return 1;
	}
	for (i=0;i<numeroParole;i++)
	{
		if (controlla_ultima_altra(prima_p,parole[i],a_controllo))
		{
			/* printf("va bene l'ultima parola trovata con %s\n",parole[i]); */
			/* printf("ora la lista è:\n"); */
			/* stampa_lista(prima_p); */
			node* new_list=copia_lista(prima_p);
			append(new_list,parole[i]);
			/* printf("ora la lista copiata è:\n"); */
			/* stampa_lista(new_list); */
			risolvi_lista(parole,new_list,final_p,numeroParole,a_controllo);
		}
	}
	printf("non go trova' un cazzo!\n");
	return 0;
	
}


int seek_n_save(char** parole, node* prima_p,int numeroParole)
{
	int i,l;
	char *parola1;
	int c=0;
	parola1=strdup(prima_p->word);

	int len_parola1=strlen(parola1);
	/*conversione da maiuscole a minuscole*/
	convertToLow(len_parola1,parola1);
	

	for (i=0;i<numeroParole;i++)
	{
		if(parole[i][0]==parola1[0])
		{
			c=1;
			for(l=1;l<len_parola1;l++)
			{
				if(parole[i][l]==parola1[l])
					c++;
			}
			if (c!=len_parola1)
				c=0;
			else{
				printf("ho trovato la parola nel dizionario!\n %s = %s \n",prima_p->word,parole[i]);
				prima_p->p_dizionario=parole[i];
				return 1;
			}
		}
	}
	return 0;
}


int test(int argc,const char *argv[])
{
	int i,dim;
	char* buffer=calloc(30,sizeof(char));
	node* lista_orig=calloc(1,sizeof(node));
	printf("quanto vuoi che sia lunga la tua lista?\n");
	scanf("%i",&dim);
	printf("con cosa vuoi che inizi?\n");
	scanf("%s",buffer);
	lista_orig->word=strdup(buffer);
	printf("ok\n");
	for (i = 0; i < dim-1; i++) {
		printf("e poi?\n");
		scanf("%s",buffer);
		append(lista_orig,buffer);
	}
	stampa_lista(lista_orig);
	printf("e la copia è\n");
	stampa_lista(copia_lista(lista_orig));
	return 1;
}

int main(int argc, const char *argv[])
{
	/* char *file="dizionario.txt"; */
	FILE* f;
	int i=0;
	char parola[30];
	char **parole;						/*array di puntatori*/
	char* final_p=(char*)argv[2];
	int numeroParole=contaParole("dizionario.txt");
	node* prima_p=(node*)calloc(1,sizeof(node));
	f=fopen("dizionario.txt","r");
	
	parole = malloc(sizeof(char *)*numeroParole);
	if (f==NULL)
		printf("------\n");
	while(!feof(f))
    {
			fscanf(f,"%s",parola);
			parole[i]=strdup(parola);
			i++;
    }
	prima_p->word=(char*)argv[1];
	prima_p->next=NULL;
	int *a_controllo=malloc(strlen(prima_p->word)*sizeof(int));
	for(i=0;i<strlen(prima_p->word);i++)
	{
		if (prima_p->word[i]==final_p[i])
			a_controllo[i]=1;
	}

	seek_n_save(parole, prima_p,numeroParole);
	risolvi_lista(parole,prima_p,final_p,numeroParole,a_controllo);
	fclose(f);
	return 0;
}
