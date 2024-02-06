#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t mystrlen(const char *s)
{
    int i;
    for (i = 0; s[i]; i++)
        ;

    return i;
}



int main(int argc, char *argcv[])
{
    char *s = "Hello World!";
    char a[] = "Hello World!";
    printf("%d\n", sizeof (a));
    printf("%d\n", mystrlen(a));printf("%d\n", mystrlen(s));
    printf("%d\n", mystrlen(a));



    printf("%c\n", s[0]);

    
}
