
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include <unistd.h>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
#define MAXLEN(a,b) (a<=b ? b : a)

typedef struct node
{
    struct node* prev;
    int distanza;
    char* word;
    struct node* next;
    char* p_dizionario;
    short int flag_presenza;

}node;
typedef struct prox
{
    struct prox* prev; 
    node* node;
    struct prox* next;
}prox;

node* rewind_list(node* head)
{
    while(head->prev!=NULL)
    {
        head=head->prev;
    }
    return head;
}
prox* append_prox(prox* head,node* parola)
{
    if(head!=NULL)
    {
        while (head->next!=NULL)
            head=head->next;
        head->next=calloc(1,sizeof(prox));
        head->next->prev=head;
        head=head->next;
    }
    else{
        printf("ci provo\n");
        head=calloc(1,sizeof(prox));
        head->prev=NULL;
    }
    head->node=parola;
    head->next=NULL;
    return head;
}

int levenshtein(char *s1, char *s2) {
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int column[s1len+1];
    for (y = 1; y <= s1len; y++)
    {
        column[y] = y;
    }
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x-1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastdiag = olddiag;
        }
    } 

    return(column[s1len]);
}



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


//
//
//FUNZIONI DI CONTROLLO;
//
//
//controlla se due parole sono una l'anagramma dell'altra
//return 1 se lo sono
// 0 se non lo sono

int anagramma(int len_parola, char *parola1,char *parola2)
{
    int i,l,cont=0;
    for (i=0; i<len_parola;i++)
    {
        for(l=0;l<len_parola;l++)
        {
            if(parola1[i]==parola2[l] && cont==i)
            {
                cont++;
            }
        }
    }
    return cont;
}

//controlla se due parole sono una uguali all'altra meno una lettera che è stata cambiata
//return 1 se lo sono
// 0 se non lo sono
int cambioLettera(int len_parola, char *parola1,char *parola2)
{
    int i,cont;
    cont=0;
    for (i = 0; i < len_parola; i++) {
        if (parola1[i]==parola2[i] && cont>=i-1)
        {
            cont++;
        }
    }
    return cont;
}

//controlla se due parole sono una uguali all'altra meno una lettera che è stata tolta
//return 1 se lo sono
// 0 se non lo sono
int letteraInMeno(int len_parola1,int len_parola2, char *parola1,char *parola2)
{
    int i, c,cont;
    c=0;
    cont=0;
    for (i = 0; i < (len_parola1>len_parola2? len_parola1 : len_parola2); i++) {
        if (parola1[(len_parola1>len_parola2 ? i : c )]==parola2[(len_parola1>len_parola2 ? c : i )])
        {
            cont++;
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

int controllo(char *p1,char *p2)
{
    if (strcmp(p1,p2)==0)
        return 0;
    char *parola1;
    char *parola2;
    int len_parola1,len_parola2,len_max,len_min;

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
        if (anagramma(len_parola1,parola1,parola2)==len_max)
            return 1;
        else
            if (cambioLettera(len_max,parola1,parola2)==len_max-1)
                return 1;
    }
    else
        if (len_min==len_max-1)
        {
            if (letteraInMeno(len_parola1,len_parola2,parola1,parola2)==len_min)
            {
                return 1;
            }
        }
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

node* append(node *head, char* string )
{
    if (head==(NULL))
        return NULL;
    while(head->next!=NULL)
        head=head->next;
    if (head->word==NULL)
    {
        head->prev=NULL; 
        head->word=strdup(string);
        head->next=NULL;
        return head;
    }
    else{
        head->next=(node*)malloc(sizeof(node));
        head->next->prev=head;
        head=head->next;
        head->word=strdup(string);
        head->next=NULL;
        return head;
    }
    return NULL;
}

void stampa_lista_prox(prox* head)
{
    while (head!=NULL)
    {

        printf("%s %i \n",head->node->word,head->node->distanza);
        head=head->next;
    }
}

void stampa_lista(node* head)
{
    while (head!=NULL)
    {
        printf("%s %i \n",head->word,head->distanza);
        head=head->next;
    }
}

int controlla_ultima_altra(node* prima_p,char* parola,int* a_controllo)
{
    if (prima_p==NULL)
        return -1;
    while(prima_p->next!=NULL)
    {
        prima_p=prima_p->next;
    }
    if( controllo(prima_p->word,parola))
        return 1;
    else return 0;
}

node* copia_lista(node* head)
{
    if (head!=NULL)
    {
        node* new_head=calloc(1,sizeof(node));
        while(head!=NULL)
        {
            append(new_head,head->word);
            new_head=new_head->next;
            head=head->next;
            if (head==NULL)
                break;
        }
        return new_head;
    }
    return NULL;
}


node* assimila_file(char* nome_file,char* last_word)
{
    FILE *file=fopen(nome_file,"r");
    node* head=calloc(1,sizeof(node));
    char* parola=calloc(40,sizeof(char));
    while (!feof(file))
    {
        fscanf(file,"%s",parola);
        if(feof(file))
            break;
        head=append(head,parola);
        head->distanza=levenshtein(head->word,last_word);
    }
    while(head->prev!=NULL)
        head=head->prev;
    return head;
}

prox* trova_possibilità(node* head,char* string)
{
    prox* possibil=NULL;
    while (head->next!=NULL)
    {
        if(controllo(head->word,string))
        {
            possibil=append_prox(possibil,head);
        }
        head=head->next;
    }
    while (possibil->prev!=NULL)
    {
        possibil=possibil->prev;
    }
    return possibil;
}
void svuota_sol(node* sol)
{
    node* tmp=sol;
    while (sol->next!=NULL)
    {
        sol=sol->next;
    }
    while (sol!=tmp)
    {
        sol=sol->prev;
        free(sol->next);
    }
}
void test(int argc,  char *argv)
{
    node* head=assimila_file(argv,"stocazzo");
    stampa_lista(head);
    prox* head_prox=trova_possibilità(head,"stocazzo");
    stampa_lista_prox(head_prox);
}
int risolvi(node* head,node* soluzione,char* last_w)
{
    if (controllo(last_w,soluzione->word))
    {
        printf("ho finito!\n");
        return 1; 
    }
    else {
        prox* possibil=trova_possibilità(head,soluzione->word);
        prox* probabil=possibil;
        while (possibil!=NULL)
        {
            
            if (possibil->node->distanza<probabil->node->distanza)
            {
                probabil=append_prox(probabil,possibil->node);
            }
            if (possibil->next==NULL)
                break;
            possibil=possibil->next;
        }  
        while (probabil==NULL){
            append(soluzione,probabil->node->word);
            if (risolvi(head,soluzione->next,last_w))
            {
                return 1;
            }
            else svuota_sol(soluzione);
            if (probabil->prev!=NULL)
                probabil=probabil->prev;
            else return 0;
        }
    }
}

int contr_tendenza(node*head)
{
    int cont;
    if (head->prev!=NULL)
        while (head!=NULL)
        {
            if (cont>=2)
                return 0;
            if (head->prev->distanza>head->distanza)
                cont++;
            if(head->prev!=NULL)
                head=head->prev;
            else return 1;
        }
    else return 1;
    return 0;
}
void risolvi_dizionario(int argc,char *argv[])
{
    node* head=assimila_file("dizionario.txt",argv[2]);
    node* first_w=calloc(1,sizeof(node));
    char* last_w=strdup(argv[2]);
    first_w->word=strdup(argv[1]);
    first_w->prev=NULL;
    first_w->next=NULL;
    first_w->distanza=levenshtein(first_w->word,last_w);
    if (first_w->distanza==0)
    {
        printf("le due parole sono uguali\n");
        return;
    }
    else if(controllo(first_w->word,last_w))
    {
        printf("le due parole vanno già bene\n");
        return;
    }
    else
    risolvi(head,first_w,last_w);
    
}
int main(int argc,char *argv[])
{
    test(argc,argv[1]);
    return 0;
}
