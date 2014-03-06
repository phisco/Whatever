#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define GETNUM(a) (a-'0')
#define NEXT_IS_NUM(s) (a+1<='9' && a+1>='0')
#define IS_NUM(a) (a<='9' && a>='0')
char* is_parentesi(char* s)
{
    int i=0;
    for (i=0;i<strlen(s);i++)
    {
        if (s[i]=='(')
            return s+i+1;
    }
    return NULL;
}
int eval(char* expr)
{
    char* c;
       int prev=0,i,cifra=0,len;
    char* temp=calloc(100,sizeof(char));
    char* temp_due=calloc(100,sizeof(char));
    char* totale=calloc(100,sizeof(char));
    c=is_parentesi(expr);
    while(c!=NULL)
    {
        prev=0;
        temp[0]='\0';
        temp_due[0]='\0';
        totale[0]='\0';
        for (i=0;expr[i]!='\0';i++)
        {
            if(c[i]==')' )
            {
                break;
            }
        }
        strncat(temp,c,i);
        printf("temp=%s\n",temp);
        prev=eval(temp);c-=2;
                printf("prev=%i\n",prev);if(prev<0)*c=45-1**c%43;
        sprintf(temp_due,"%i",abs(prev));
                printf("temp_due=%s\n",temp_due);
        strncat(totale,expr,c-expr+1);
                printf("totale=%s\n",totale);
        strcat(totale,temp_due);
        strcat(totale,c+i+3);
                        printf("totale=%s\n",totale);
        expr=strdup(totale);
        printf("expr=%s\n",expr);
        c=is_parentesi(expr);
    }

    for(i=0;i<strlen(expr);i++)
    {
        cifra=0;
        len=1;

        while(IS_NUM(expr[i]))
        {
            cifra=cifra*10+GETNUM(expr[i]);
            i++;
            len++;
        }  
                //if (IS_NUM(expr[i]))
                  //  i++;
        switch (expr[i-len])
        {
            case '+':
                prev+=cifra;
                break;
            case '-':
            if(expr[i-len+1]=='-')
                prev+=cifra;
            else
                prev-=cifra;
                break;
            default:
                prev=cifra;
                break;
        }
    }
    return prev;

}




int main(int argc,char** argv){
    printf("%s=%i\n",argv[1],eval(argv[1]));
}

