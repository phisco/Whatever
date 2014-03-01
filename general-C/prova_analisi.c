
#include <stdio.h>
#include <stdlib.h>


char* y(char* s, int a, int b) {
    char* x= (char*) malloc(b-a+1); int i;
    for(i=0; b>a; i++, a++) x[i] = s[a];
    x[i] = '\0'; return x;
}

int f (char c, char* cs){
    if(*cs == '\0') return 0; if(*cs==c) return 1;
    return f(c, cs+1);
}

char* d(char*s, char* dls)
{
    if(f(*s, dls) || *s=='\0') return s;
    return d(s+1, dls);
}

char* nd(char*s, char* dls)
{
    if(!f(*s, dls) || *s=='\0') return s;
    return nd(s+1, dls);
}

char* h(char**b, char**c, char*a, char*dls)
{
    int m1 = d(a, dls)-a, m2 = nd(a+m1, dls)-a;
    *b = y(a, 0, m1); *c = y(a, m1, m2);
    return nd(d(a, dls), dls);
}

void j ( char*s, char*dls) {
    char *w, *d;
    for(s=h(&w, &d, s, dls); *s !='\0'; s= h(&w, &d, s, dls))
        printf("(%s),(%s)\n", w, d);
    printf("(%s),(%s)\n", w, d);
}


void primo()
{
    char *s = "il mattino ha l'oro in bocca";
    printf("%s\n", y(s, 0, d(s, "odore")-s));
    printf("%s\n", y(s, d(s, "odore")-s, d(d(s, "odore"), "ummm...")-s));
}

void secondo ()
{
    char *w, *d, *s="before indi post";
    h(&w, &d, s, "din ");
    printf("%s -> %s\n", w, d);

}


int main(int argc, const char *argv[])
{
    /* primo(); */
    secondo ();
    return 0;
}
