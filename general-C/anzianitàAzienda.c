
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node{
    struct node *prev;
    char *nome;
    char *cognome;
    int età;
    struct node *next;
} node;

node* rewind_list(node* head){
    while(head->prev!=NULL)
    { 
        head=head->prev;
    }
    return head;
}

void stampaLista(node *head)
{
    while (head!=NULL)
    {
        printf("%s %s %i\n",head->nome, head->cognome,head->età);
        head=head->next;
    }
}


node* append(node* head,char *nome, char *cognome, int età)
{
    if(head==NULL)
    {
        head=calloc(1,sizeof(node));
        head->next=NULL;
        head->prev=NULL;
        head->nome=strdup(nome);
        head->cognome=strdup(cognome);
        head->età=età;
        return head;
    }
    
    while (head->next!=NULL)
    {
        head= head->next;
    }
    head->next=calloc(1,sizeof(node));
    head->next->prev=head;
    head=head->next;
    head->nome=strdup(nome);
    head->cognome=strdup(cognome);
    head->età=età;
    head->next=NULL;
   return rewind_list(head);
}

float contaDipendenti(node*head){
    int contatore=0;
    while(head!=NULL)
    {
        head=head->next;
        contatore++;
    }
    return contatore;
}

node* screma(node* head)
{
    node* punto;
    while(head!=NULL)
    {
        if(head->età<15)
        {
            if(head->prev!=NULL)
            {
                head->prev->next=head->next;
            }
            if(head->next!=NULL)
                head->next->prev=head->prev;
        }
        if(head->next==NULL)
            punto=head;
        head=head->next;
    }
    return rewind_list(punto);
}

int controlla(node *head,char* nome,char* cognome, int età)
{
    while(head!=NULL)
    {
        if(strcmp(head->nome,nome)==0)
            if(strcmp(head->cognome,cognome)==0)
                if(head->età==età)
                    return 0;
        head=head->next;
    }
    return 1;
}

node* acquisizione()
{
    char *nome=malloc(30*sizeof(char)), *cognome=malloc(30*sizeof(char));
    int età=0;
    node* head=NULL;
    int status=0;
    int numeroDatiDaImmettere=3;
    printf("Digita \"exit\" quando hai inserito tutti i dipendenti.\n");
    do
    {
        printf("\n\nInserisci il nome, il cognome e l'età pensionabile del dipendente separati da \"spazi\":\n");
        status=0;
        età=0;
        /* status=scanf("%s %s %i",nome,cognome,&età); */
        status+=scanf(" %s",nome);
        if(strcmp(nome, "exit")==0)
        {
            printf("\n\n");
            printf("Hai finito i nomi da immettere? rispondi no se vuoi continuare\n");
            scanf(" %s",nome);
            if (strcmp(nome,"no")!=0)
                return head;
            else
            {
                status=numeroDatiDaImmettere;
                continue;
            }
        }
        status+=scanf(" %s",cognome);
        status+=scanf(" %i",&età);
        if(status!=numeroDatiDaImmettere)
        {
            continue;
        }
        if(controlla(head,nome,cognome,età))
            head=append(head,nome,cognome,età);
        else
            continue;
    } while (status==numeroDatiDaImmettere);
    if(status!=numeroDatiDaImmettere)
        printf("errore hai inserito dei dati sbagliati, ci devono essere solo: il nome, il cognome e l'età separate da spazi\n");
    printf("head= %p \n", head);
    return head; 
}

node* scambia(node* parola1, node* parola2)
{
    if(parola1->prev!=NULL)
        parola1->prev->next=parola2;
    parola2->prev=parola1->prev;
    parola1->prev=parola2;
    parola1->next=parola2->next;
    parola2->next=parola1;
    return parola1;
}


node* riordina(node *head)
{
    node* punto, *testa=head;
    int cmp;
    while (testa!=NULL)
    {
        punto=head;

        while (punto!=NULL)
        {
            if(punto->next!=NULL){
                cmp=strcmp(punto->nome,punto->next->nome);
                if (cmp>0)
                {
                    punto=scambia(punto,punto->next);
                }
                else
                    if (cmp==0)
                        if(strcmp(punto->cognome,punto->next->cognome)>0)
                            punto=scambia(punto,punto->next);
            }
            punto=punto->next;
        }
        if(testa->next!=NULL)
            testa=testa->next;
        else break;
    }
    return rewind_list(testa);
}

int main(int argc, const char *argv[])
{
    node* head=acquisizione();
    if (head==NULL)
    {
        printf("non hai immesso dipendenti\nFINE\n");
        return 0;
    }
    float totale=contaDipendenti(head);
    printf("\nHai inserito questi dipendenti:\n");
    stampaLista(head);
    printf("I dipendenti in totale sono= %i\n",(int)totale);
    head=screma(head);
    float subTotale=contaDipendenti(head);
    printf("I dipendenti con anzianità minore di 15 anni sono in totale = %i\n",(int)subTotale);
    head=riordina(head);
    printf("La lista in ordine alfabetico dei dipendenti è:\n");
    stampaLista(head);
    printf("la percentuale di dipendenti con età pensionabile maggiore di 15 anni è %i / %i = %f %% \n",(int)subTotale,(int)totale,(subTotale/totale)*100);
    return 1;
}

