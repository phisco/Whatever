#include <stdio.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
    const char *pre=argv[1];
    printf("%c\n",*pre);
    char *post=malloc(1);
    *post=45-1*((*pre)%43);
    printf("%c\n",*post);
    return 0;
}
