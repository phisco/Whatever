

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include <unistd.h>

typedef struct node
{
	struct node* prev;
	char* word;
	struct node* next;
} node;

typedef struct indice{
	struct indice* prev;
	char lettera;
	node* punto_lista;
	struct indice* next;
} indice;



void convertToLow(int len_parola,char *parola);


//dice se una parola "s_o_s"(sopra o sotto) va sopra o sotto rispetto a un'altra ("p_fermo")
// 1 va sopra
// 0 va sotto
int sopra_o_sotto(char* s_o_s,char* p_fermo)
{int c=strcmp(s_o_s,p_fermo);
		return (c>0?0:1);
	/* int i,l,c; */
	/* int len_s_o_s=strlen(s_o_s),len_p_fermo=strlen(p_fermo); */
	/* int len_min=(len_s_o_s>len_p_fermo?len_p_fermo:len_s_o_s ); */
	/* char* p1=strdup(s_o_s),*p2=strdup(p_fermo); */
	/* char lettera_dopo; */
	/* convertToLow(len_s_o_s,p1); */
	/* convertToLow(len_p_fermo,p2); */
	/* for (i = 0; i < len_min; i++) { */
	/* 	if (p1[i]<p2[i]) */
	/* 	{ */
	/* 		free(p1); */
	/* 		free(p2); */
	/* 		return 1; */
	/* 	} */
	/* 	if(p1[i]>p2[i]) */
	/* 	{ */
	/* 		free(p1); */
	/* 		free(p2); */
	/* 		return 0; */
	/* 	} */
	/* } */
	/* lettera_dopo=(len_s_o_s>len_p_fermo? p1:p2)[i]; */
	/* if (lettera_dopo>='a' && lettera_dopo<='z') */
	/* 	{ */
	/* 		if (lettera_dopo==p1[i]) */
	/* 		{ */
	/* 			free(p1); */
	/* 			free(p2); */
	/* 			return 0; */
	/* 		} */
	/* 		else { */
	/* 			free(p1); */
	/* 			free(p2); */
	/* 			return 1; */
	/* 		} */
	/* 	} */

	/* return 0; */
}


//head qua sta per la head dell'indice
//string per il puntatore al nodo che ha i dati da appendere all'indice;
//duplice scopo se mi string==NULL crea la lista con tutte le lettere e basta, senza posizione nel dizionario
//quindi se invece string!=NULL scrive solo la parola data nel posto giusto dell'indice
int append_indice(indice* alfabeto, node* string)
{
	if (string==NULL)
	{
		/* printf("string= %p\n",string); */
		if(alfabeto->lettera=='z')
			return 1;
		if (alfabeto->next==NULL)
		{
			/* printf("sono alla lettera: %c\n",alfabeto->lettera); */
			alfabeto->next=calloc(1,sizeof(indice));
			alfabeto->next->lettera=alfabeto->lettera+1;
			alfabeto->next->next=NULL;

			alfabeto->next->punto_lista=NULL;
			/* printf("creata la voce per la lettera: %c\n",alfabeto->next->lettera); */
			return append_indice(alfabeto->next,NULL); 
		}
	}
	else
	{
		if(alfabeto->lettera==tolower(string->word[0]))
		{
			if (alfabeto->punto_lista!=NULL)
			{
				alfabeto->punto_lista=string;
				return 1;
			}
		}
		else
		return append_indice(alfabeto->next,string);
	}
	return 0;
}



//Aggiorna l'indice datagli la testa dell'indice
//ritorna 1 se arriva alla z
//ritorna 0 in caso di errore
int aggiorna_indice(indice* alfabeto)
{
	if (alfabeto->lettera=='z')
		if(tolower(alfabeto->punto_lista->prev->word[0])<'z')
			return 1;
	if(tolower(alfabeto->punto_lista->prev->word[0])==alfabeto->lettera)
	{
		alfabeto->punto_lista=alfabeto->punto_lista->prev;
		return aggiorna_indice(alfabeto);
	}
	else
		return aggiorna_indice(alfabeto->next);
	return 0;
}

int crea_indice_int(node* head, indice* alfabeto)
{
	if(head->next==NULL)
	{
		if(alfabeto->lettera==tolower(head->word[0]) || alfabeto->punto_lista==head )
		{
			return 1;
		}
		else {
			append_indice(alfabeto,head);
			return 1;
		}
	}
	
	if(head->prev==NULL)
	{	
		alfabeto->punto_lista=head;
		return crea_indice_int(head->next,alfabeto);
	}
	else
	{
		if (tolower(head->word[0])>tolower(head->prev->word[0])) {
			append_indice(alfabeto,head);
		}
		return crea_indice_int(head->next,alfabeto);

		}
return 0;
}

//ricorda che per aggiornare il dizionario basta che ogni volta veda se va sopra o sotto la prima parola della lettera
//con cui inizia la parola, se va sopra cambia la "pagina" di riferimento nell'indice in quella della parola nuova! fine!
indice* indicizza(node* head,int controllo,indice* alfabeto_dato)
{
	int i;
	if(controllo==1)
	{
	indice* alfabeto=calloc(1,sizeof(indice));
	alfabeto->lettera='a';
	alfabeto->punto_lista=NULL;
	alfabeto->next=NULL;
	/* printf("creata la voce per la lettera : %c\n",alfabeto->lettera); */
	append_indice(alfabeto,NULL);
	return alfabeto;
	}
	else{
	if(crea_indice_int(head,alfabeto_dato))
		return alfabeto_dato;
	else return NULL;
	}
}

//torna alla testa della lista
//e restituisce il nuovo indirizzo della testa
node* rewind_list(node* head)
{
	
	/* printf("mi è stato passato %s \n", head->word); */
	/* printf("la precedente di %s è : %s \n",head->word,head->prev->word); */
	if (head->prev==NULL)
	{
	/* printf("ritornato alla testa della lista cioè la parola %s\n",head->word); */
		return head;
	}
	else return rewind_list(head->prev);
}

//converte tutta la parola in lettere minuscole
void convertToLow(int len_parola,char *parola)
{
	int i;
	for(i=0; i<len_parola; i++)
	{
		parola[i] = tolower(parola[i]);
	}
}

//appende la parola alla lista
//e se lista è del tutto vuota mette in testa la parola data
//ma comunque gli deve essere dato un puntatore a testa pieno, non alloca da solo lo spazio se non c'è una testa
//ritorna -1 se gli è data una head vuota
// 				1 se è andata a buon fine
// 				0 se ha terminato senza andare a buon fine (gestione errore)
int append(node *head, char* string )
{
	if (head==(NULL))
		return -1;

	if(head->next==NULL)
	{
		if (head->word!=NULL)
		{
		head->next=(node*)malloc(sizeof(node));
		(head->next)->word=strdup(string);
		(head->next)->next=NULL;
		head->next->prev=head;
		return 1;
		}
		else 
		{
			head->prev=NULL;
			head->word=strdup(string);
			return 1;
		}
	}
	else
		append(head->next,string);
	return 0;
}

//scrive la lista "head" nel file "f"
int scrivi_lista(node* head,FILE* f)
{
	/* printf("scrivi_lista ok\n"); */
	
	fwrite(head->word,strlen(head->word),sizeof(char),f);
	fwrite("\n",1,sizeof(char),f);
	if (head->next!=NULL)
		scrivi_lista(head->next,f);
	return 1;
}

//stampa la lista a schermo
int stampa_lista(node* head)
{
	if(head->prev==NULL)
		printf("---------------\nquesta è la lista stampata:\n");
	printf("%s\n",head->word);
	if (head->next!=NULL)
		stampa_lista(head->next);
	return 1;
}


//Dice se due parole sono uguali o meno
//per il controllo della presenza 
// 1 sono uguali
// 0 sono diverse
int sono_uguali(char* p1,char* p2)
{
	if (strcmp(p1,p2)==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	/* int i, l_p=strlen(p1),l_l=strlen(p2); */
	/* if (l_p==l_l) */
	/* { */
	/* 		for(i=0;i<l_l;i++) */
	/* 		{ */
	/* 						 */
	/* 			if(p1[i]!=p2[i]) */
	/* 			{ */
	/* 				return 0; */
	/* 			} */
	/* 		} */
	/* 		if(p1[i]==p2[i]) */
	/* 		return 1; */
	/* } */
	/* else return 0; */
	/* return 0; */
}

//controlla in tutta la lista "head" se la "parola" è presente
//o meno
//ritorna 1 se non c'è
//   0 se c'è già
int controllo_presenza(node* head, char* parola,indice* alfabeto)
{
	printf("ok\n");
	printf("%s =? %c\n",parola, alfabeto->lettera);
	if(alfabeto->lettera==tolower(parola[0]))
	{
		printf("si\n");
		if(alfabeto->punto_lista==NULL)
			return 1;
		if(!sono_uguali(head->word,parola))
		{
			/* if(!sopra_o_sotto(head->word,parola)) */
				/* return 1; */
			if (head->next==NULL)
				return 1;
			else
				return controllo_presenza(head->next,parola,alfabeto);
		}
		else
			return 0;
	}
	else
	{
		printf("no\n");
		return controllo_presenza(alfabeto->next->punto_lista,parola,alfabeto->next);
	}
}
//infila una parola al di sotto della head (posizione giusta data da trova punto )
//facendo slittare la successiva

node* infila(node* head,char* parola,indice* alfabeto)
{
	printf("%p,%s,%p\n",head,parola,alfabeto);
	/* printf("ok provo a infilare la parola %s tra %s e %s\n",parola,head->word,head->next->word); */
	if(head->next!=NULL){
		node* scalpello=calloc(1,sizeof(node));
		if (head==NULL)
			return 0;
		scalpello->next=head->next;
		scalpello->prev=head;
		scalpello->word=strdup(parola);
		head->next->prev=scalpello;
		head->next=scalpello;
		return rewind_list(head);
	}
	else{
		printf("non ci sono parole dopo\n");
		append(head,parola);
		return rewind_list(head);
	}
}


//trova il punto giusto dove attaccare la parola in ordine alfabetico
//ritorna la nuova testa della lista,
//dato che può anche attaccare come primo elemento della lista
node* trova_punto(node* head, char* string,indice* alfabeto)
{
	/* printf("ora vedo dove va la parola %s \n",string); */
	if(alfabeto->lettera==tolower(string[0]))
	{
		
		if(alfabeto->punto_lista==NULL)
		{
			printf("l'alfabeto è vuoto!!\n");
			head=infila(head,string,alfabeto);
			alfabeto->punto_lista=head;
			printf("ok ho infilato la parola\n");
			return rewind_list(head);
		}
		/* else */
		/* { */
			
			/* head=alfabeto->punto_lista; */
		/* } */

		if (!sopra_o_sotto(string,head->word) )
		{
			/* printf("ok sta sotto a %s\n",head->word); */
			if(head->next!=NULL)
			{
				if(sopra_o_sotto(string,head->next->word))
				{
					/* printf("ok sta sopra a %s\n",head->next->word); */
					/* printf("quindi dico a infila di infilare la parola %s tra %s e %s\n",string,head->word,head->next->word); */
					/* printf("ok provo a infilare la parola %s tra %s e %s\n",string,head->word,head->next->word); */
					head=infila(head,string,alfabeto);
					return head;

				}
				else return trova_punto(head->next,string,alfabeto);
			}
			else 
			{
				append(head,string);
					if(sopra_o_sotto(alfabeto->punto_lista->word,head->next->word))
					{
						alfabeto->punto_lista=head;
					}
				return rewind_list(head);
			}
		}
		else
		{
			if(head->prev!=NULL)
			{
				if(alfabeto->lettera==tolower(head->prev->word[0]))
				{
					alfabeto->punto_lista=head->prev;
				}
				return trova_punto(head->prev,string,alfabeto);
			}
			else
			{
				//attacco prima un pezzo se deve stare prima della testa della lista
				head->prev=calloc(1,sizeof(node));
				alfabeto->punto_lista=head->prev;
				head->prev->word=strdup(string);
				head->prev->prev=NULL;
				head->prev->next=head;
				if(alfabeto->lettera==tolower(head->prev->word[0]))
				{
					alfabeto->punto_lista=head->prev;
				}
				return rewind_list(head);
			}
		}
		return head;
	}
	else {
		if(alfabeto->next->punto_lista!=NULL)
		return trova_punto(alfabeto->next->punto_lista, string, alfabeto->next);
		else{
			return trova_punto(head->next,string,alfabeto->next);
		}
	}
}
// vera funzione che crea presi come argomenti da passare alla chiamata del programma
// prima il nome del dizionario già creato, poi i nomi di tutti i file da aggiungere
int final(int argc,const char *argv[])
{
	FILE* f;
	FILE* dizionario_omnia;
	int i;
	char* buffer= calloc(30, sizeof(char));
	indice* alfabeto=calloc(1,sizeof(indice));
	node* head=calloc(1,sizeof(node));

	head->word=strdup("ciao");
	head->prev=NULL;
	dizionario_omnia=fopen(argv[1],"r");

	alfabeto=indicizza(head,1,NULL);

	printf("ok ho creato l'indice alfabetico\n");
	while (!feof(dizionario_omnia))
	{
		fscanf(dizionario_omnia,"%s",buffer);
		/* printf("salvo %s\n",buffer); */
		if(controllo_presenza(head,buffer,alfabeto)) {
			head=trova_punto(head,buffer,alfabeto);
	printf("ok\n");}
	}
	printf("ok ho assimilato il dizionario di base\n");
	fclose(dizionario_omnia);
	
	alfabeto=indicizza(head,2,alfabeto);
	
	/* stampa_lista(head); */
	for(i=2;i<argc;i++)
	{
		printf("ora assimilo %s\n",argv[i]);
		f=fopen(argv[i],"r");
		while(!feof(f))
		{
			fscanf(f,"%s",buffer);
			if(controllo_presenza(head,buffer,alfabeto))
			{
				/* printf("ok la parola %s non c'è\n",buffer); */
				head=trova_punto(head,buffer,alfabeto);
			
			}
			else
			{
				/* printf("la parola %s è già presente!\n",buffer); */
			}
		}
		fclose(f);
	}
	printf("ok ho inserito tutte le parole mancanti\n");
	/* stampa_lista(head); */
	f=fopen(argv[1],"w");
	scrivi_lista(head,f);
	fclose(f);
	return 0;
}
void stampa_indice(indice* alfabeto)
{
	/* printf("ci sono\n"); */
	/* printf("%c=  \n", alfabeto->lettera); */
	if(alfabeto->punto_lista==NULL)
	printf("%c= %p\n", alfabeto->lettera,alfabeto->punto_lista);
	/* else */
	/* { */
	/* 	printf("%c= vuoto\n", alfabeto->lettera); */
	/* } */
	/* sleep(2); */
	if (alfabeto->next!=NULL)
		stampa_indice(alfabeto->next);
}

void test2(int argc,const char *argv[])
{
	FILE* f;
	FILE* dizionario_omnia;
	int i;
	char* buffer= calloc(30, sizeof(char));
	node* head=calloc(1,sizeof(node));
	indice* alfabeto=indicizza(NULL,1,NULL);

	head->word=strdup("albero");
	head->prev=NULL;
	/* dizionario_omnia=fopen(argv[1],"r"); */
	/* alfabeto->punto_lista=head; */
	printf("ok ho creato l'indice alfabetico\n");

	stampa_indice(alfabeto);

	/* while (!feof(dizionario_omnia)) */
	/* { */
	/* 	fscanf(dizionario_omnia,"%s",buffer); */
	/* 	#<{(| printf("salvo %s\n",buffer); |)}># */
	/* 	if(controllo_presenza(head,buffer,alfabeto)) head=trova_punto(head,buffer,alfabeto); */
	/* } */
	/* printf("ok ho assimilato il dizionario di base\n"); */
	/* fclose(dizionario_omnia); */
	/*  */
	/* alfabeto=indicizza(head,2,alfabeto); */
	
}
void test1(int argc, const char *argv[])
{
	int i;
	/* printf("%i\n",sopra_o_sotto((char*)argv[1],(char*)argv[2])); */
	/* printf("%i",argc); */
	/* printf("%i",sono_uguali((char*)argv[1],(char*)argv[2])); */
	char* string=calloc(30,sizeof(char));
	node* head=calloc(1,sizeof(node));
	head->word=strdup(argv[1]);
	for (i = 0; i < 5; i++) {
		scanf("%s",string);
		/* trova_punto(head,string,alfabeto); */
	}
	
	head=rewind_list(head);
	stampa_lista(head);
	while (1)
	{
	printf("ok ora dimmi una parola che vuoi controllare nella lista\n");
	scanf("%s",string);
	/* if(controllo_presenza(head,string)) */
		/* printf("non c'è!\n"); */
	/* else printf("c'è!\n"); */
	}
}
int main(int argc, const char *argv[])
{
	/* test1(argc,argv); */
	/* test2(argc,argv); */
	final(argc,argv);
}
