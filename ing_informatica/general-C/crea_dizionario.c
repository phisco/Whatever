

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

//
//
//FUNZIONI BASE
//
//
//converte tutta la parola in lettere minuscole
void convertToLow(int len_parola,char *parola)
{
    int i;
    for(i=0; i<len_parola; i++)
    {
         parola[i] = tolower(parola[i]);
    }
}

void stampa_indice(indice* alfabeto)
{
    if(alfabeto->punto_lista==NULL)
        printf("%c= %p\n", alfabeto->lettera,alfabeto->punto_lista);
    if (alfabeto->next!=NULL)
        stampa_indice(alfabeto->next);
}

//appende la parola alla lista
//e se lista è del tutto vuota mette in testa la parola data
//ma comunque gli deve essere dato un puntatore a testa pieno, non alloca da solo lo spazio se non c'è una testa
//ritorna -1 se gli è data una head vuota
//              1 se è andata a buon fine
//              0 se ha terminato senza andare a buon fine (gestione errore)
int append(node *head, char* string )
{
    if (head==NULL)
        return -1;
    while(head->next!=NULL)
        head=head->next;
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
    return 0;
}

//torna alla testa della lista
//e restituisce il nuovo indirizzo della testa
node* rewind_list(node* head)
{ if (head->prev==NULL) { return head; } else return rewind_list(head->prev); }

indice* rewind_alfabeto(indice* alfabeto)
{ if (alfabeto->prev==NULL) { return alfabeto; } else return rewind_alfabeto(alfabeto->prev); }

//infila una parola al di sotto della head (posizione giusta data da trova punto )
//facendo slittare la successiv
int infila(node* head,char* parola)
{
    if (head==NULL)
            return -1;
    if(head->next!=NULL){
        node* scalpello=calloc(1,sizeof(node));
        scalpello->next=head->next;
        scalpello->prev=head;
        scalpello->word=strdup(parola);
        head->next->prev=scalpello;
        head->next=scalpello;
        return 1;
    }
    else{
        append(head,parola);
        return 1;
    }
    return 0;
}


//dice se una parola "s_o_s"(sopra o sotto) va sopra o sotto rispetto a un'altra ("p_fermo")
// 1 va sopra
// 0 va sotto
/* int sopra_o_sotto(char* s_o_s,char* p_fermo) */
/* { */
/*     int c=strcmp(s_o_s,p_fermo);  */
/*     return (c>0 ? 0 : 1); */
/* }  */

//Dice se due parole sono uguali o meno
//per il controllo della presenza 
// 1 sono uguali
// 0 sono diverse
/* int sono_uguali(char* p1,char* p2) */
/* { if (strcmp(p1,p2)==0) { return 1; } else { return 0; } }  */


//stampa la lista a schermo
int stampa_lista(node* head)
{
    if(head!=NULL){
    if(head->prev==NULL)
        printf("---------------\nquesta è la lista stampata:\n");
    printf("%s\n",head->word);
    if (head->next!=NULL)
        return(stampa_lista(head->next));
    else
        return 1;
    }
    else return -1;
}


//alfabeto sta per la head dell'indice
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


//due funzioni che creano l'indice vuoto
indice* crea_indice_uno(char lettera, indice* alfabeto);
indice* crea_indice_zero()
{
    indice* alfabeto=calloc(1,sizeof(indice));
    alfabeto->prev=NULL;
    alfabeto->lettera='a';
    alfabeto->punto_lista=NULL;
    alfabeto->next=crea_indice_uno('a',alfabeto);
    return alfabeto;
}
indice* crea_indice_uno(char lettera, indice* alfabeto)
{
    alfabeto->next=calloc(1,sizeof(indice));
    alfabeto->next->prev=alfabeto;
    alfabeto->next->lettera=lettera+1;
    alfabeto->next->punto_lista=NULL;
    if( lettera!='z')
        alfabeto->next->next=crea_indice_uno(lettera+1,alfabeto->next);
    return alfabeto->next;
}

//scrive la lista "head" nel file "f"
int scrivi_lista(indice* alfabeto,FILE* f)
{
    node* head=alfabeto->punto_lista;
    static int c=strlen("\n");
    while (head!=NULL)
    {
        fwrite(head->word,strlen(head->word),sizeof(char),f);
        fwrite("\n",c,sizeof(char),f);
        head=head->next;
    }
    if (head==NULL)
    {
        if(alfabeto->next!=NULL)
            return scrivi_lista(alfabeto->next,f);
        else 
            return 1;
    }
    else
        return 0;

}


//controlla in tutta la lista "head" se la "parola" è presente
//o meno
//ritorna 1 se non c'è
//   0 se c'è già
int controllo_presenza(char* parola,indice* alfabeto)
{
    char prima_l=parola[0];
    node *head;
    while(alfabeto->lettera!=prima_l )
    {
        if(alfabeto->next!=NULL)
            alfabeto=alfabeto->next;
        else
            return -1;
    }
    if(alfabeto->lettera==prima_l)
    {
        if (alfabeto->punto_lista!=NULL)
            head=alfabeto->punto_lista;
        else 
            return 1;
        while (strcmp(head->word,parola)!=0)
        {
            if(head->next!=NULL)
                head=head->next;
            else
                return 1;
        }
        return 0;
    }
    else
        return 0;
}


//trova il punto giusto dove attaccare la parola in ordine alfabetico
//ritorna la nuova testa della lista,
//dato che può anche attaccare come primo elemento della lista
int trova_punto(char* string,indice* alfabeto)
{
    char prima_l=string[0];
    node *punto_dizionario;
    while (prima_l!=alfabeto->lettera && alfabeto->next!=NULL)
        alfabeto=alfabeto->next;
    if (alfabeto->lettera==prima_l)
    {
        if(alfabeto->punto_lista==NULL)
        {
            alfabeto->punto_lista=calloc(1,sizeof(node));
            infila(alfabeto->punto_lista,string);
        }
        else
        {
            punto_dizionario=alfabeto->punto_lista;
            if(strcmp(string,punto_dizionario->word)<0)
            {
                punto_dizionario->prev=calloc(1,sizeof(indice));
                punto_dizionario->prev->next=punto_dizionario;
                punto_dizionario=punto_dizionario->prev;
                punto_dizionario->prev=NULL;
                punto_dizionario->word=strdup(string);
                alfabeto->punto_lista=punto_dizionario;
            }
            else
            {
                while(strcmp(string,punto_dizionario->word)>0 && punto_dizionario->next!=NULL)
                {
                    punto_dizionario=punto_dizionario->next;
                }
                infila(punto_dizionario,string);
            }
        }
        return 1;
    }
    return -1;
}

// vera funzione che crea presi come argomenti da passare alla chiamata del programma
// prima il nome del dizionario già creato, poi i nomi di tutti i file da aggiungere
int main(int argc, const char *argv[])
{
    if(argc<2)
    { 
        printf("devi passare almeno 2 argomenti alla chiamata,\n il primo sarà il file di base da assimilare, che può anche non esistere,\n\t e su cui poi verrà scritto il nuovo dizionario riordinato, \ntutti gli argomenti successivi saranno i file che verranno assimilati\n");
        return -1;
    }
    FILE* f;
    FILE* dizionario_omnia;
    int i;
    char* buffer= calloc(30, sizeof(char));
    indice* alfabeto=crea_indice_zero();
    dizionario_omnia=fopen(argv[1],"r");
    if(dizionario_omnia!=NULL)
    while (!feof(dizionario_omnia))
    {
        fscanf(dizionario_omnia,"%s",buffer);
        /* printf("controllo %s\n",buffer); */
        if(controllo_presenza(buffer,alfabeto))
        {
            if(!trova_punto(buffer,alfabeto))
                return -1;
        }
    }
    printf("ok ho assimilato il dizionario di base\n");
    fclose(dizionario_omnia);
    for(i=2;i<argc;i++)
    {
        printf("ora assimilo %s\n",argv[i]);
        f=fopen(argv[i],"r");
        while(!feof(f))
        {
            fscanf(f,"%s",buffer);
            if(controllo_presenza(buffer,alfabeto))
            {
                /* printf("ok la parola %s non c'è\n",buffer); */
                if(!trova_punto(buffer,alfabeto))
                    return -1;
            
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
    printf("ora scrivo la nuova lista in %s\n",argv[1]);
    scrivi_lista(alfabeto,f);
    fclose(f);
    return 1;
}


