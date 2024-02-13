#include <string.h>
#include <stdlib.h>
#include <stdio.h>



size_t strlen327(const char *s)
{
    int i;

    for (i = 0; s[i];i++)
        ;
    return i;
}

int strcmp_idiomatic(const char *s1, const char *s2)
{
    // *s1++: Dereference s1, then incerment s1
    while (*s1++ == *s2++)
        ;

    return *s1 - *s2;
}


int main()
{
    char *s= "hello world";
    char a[] = "hello world";

    printf("%lu\n", strlen327(s));
    printf("%lu\n", strlen327("Foo"));
    printf("%lu\n", strlen327(s));
    printf("%lu\n", strlen327(s));
return 0;
}
