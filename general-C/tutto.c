#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int i;
    char* buffer=malloc(sizeof(char)*500);
    FILE* tutto=fopen("tutto.txt","w+");
    printf("ciao\n");
    for (i=1;i<=argc;i++)
    {
        FILE* file=fopen(argv[i],"r");
        fwrite("\0",1,2,tutto);
        fwrite("\0",1,2,tutto);
        fwrite("\0",1,2,tutto);
        fwrite(argv[i],1,100,tutto);
        fwrite("\0",1,2,tutto);
        fwrite("\0",1,2,tutto);
        fwrite("\0",1,2,tutto);
        /* while (!feof(file)) */
        /* { */
        /*     if(fgets(buffer, 500, file)!=NULL) */
        /*     { */
        /*         fputs(buffer,tutto); */
        /*     } */
        /*     else fwrite("\0",1,2,tutto); */
        /*     if (feof(file)) */
        /*         break; */
        /* } */
        fclose(file);
    }
    fclose(tutto);
    return 0;
}
