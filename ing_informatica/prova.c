#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
    /* int x=0; */
    /* char *parola1=malloc(30*sizeof(char)); */
    /* char *parola2=malloc(30*sizeof(char)); */
    /* char *parola3=malloc(30*sizeof(char)); */
    /* while(x<10) */
    /* { */
    /*     scanf("%s %s %s",parola1,parola2,parola3); */
    /*     if(strcmp(parola1,"exit")==0) */
    /*         printf("funziona\n"); */
    /*     printf("%s %s %s\n",parola1,parola2,parola3); */
    /*     x++; */
    /* } */
    char* parola=malloc(100*sizeof(char));
    int status;
    while(1){
        status=scanf("%s",parola);
        printf("%s %i\n",parola,status);
    }
}
