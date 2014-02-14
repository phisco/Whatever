#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MIN(a,b) (a<b ? a : b)
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
 
int levenshtein(char *s1, char *s2) {
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int column[s1len+1];
    for (y = 1; y <= s1len; y++)
    {
        column[y] = y;
        printf("%i\n",y);
    }
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x-1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastdiag = olddiag;
        }
    } 
    for (y = 0; y <= s1len+1; y++)
    {
        printf("%i\n",column[y]);
    }

    return(column[s1len]);
}

int main(int argc, const char *argv[])
{
    /* char* parola1=strdup("cane"); */
    /* char* parola2=strdup("casa"); */
    /* printf("distanza tra %s e %s = %i",parola1,parola2,levenshtein(parola1,parola2)); */
    int a=atoi(argv[1]),b=atoi(argv[2]);
    printf("il minimo tra %i e %i è %i",a,b,MIN(a,b));
    return 0;
}
