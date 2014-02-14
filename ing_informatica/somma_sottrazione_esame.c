#include <stdio.h>
#include <string.h>
#define GETNUM(a) (a-'0')
#define NEXT_IS_NUM(a) (a+1<='9' && a+1>='0')
#define IS_NUM(a) (a<='9' && a>='0')

char* is_parentesi(char*s)
{
    int i=0;
    for (i=0;s[i+1]!='\0';i++)
    {
        
    }
    return NULL;
}

int eval(char* expr)
{
    int prev=0,i, cifra=0,len;
    for (i=0;expr[i+1]!='\0';i++)
    {
        cifra=0;
        len=1;
        while(IS_NUM(expr[i]))
            {
                cifra=cifra*10+GETNUM(expr[i]);
                i++;
                len++;
            }
        switch (expr[i-len]){
        case '+':
            printf("somma\n");
            prev+=cifra;
            break;
        case '-':
            printf("differenza\n");
            prev-=cifra;
            break;
        default:
            printf("prima cifra\n");
            prev=cifra;
            break;
        }
    }
    return prev;

}
int main(int argc, char** argv)
{
    printf("%i\n", eval("100+10+90"));
}
