#include <stdlib.h>
#include <stdio.h>
int main(){
    int risultato=0;
    long long int i;
    printf("ci provo\n");
    for (i = 1; i < 50; i++) {
        risultato=45%i-47%i-2;
        printf("%i\n",risultato);
        if (risultato==0)
        {
            printf("%lli\n",i);
            break;
        }
    }
    printf("%lli",i);
    return i;
}

