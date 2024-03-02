#include <stdio.h>


int main()
{
    for(int i = 0; i <= 10; i++)
    {
        printf("\n\n%d -- i\n", i); 
        printf("%d -- mod2\n", i%2);
        printf("%d -- mod3\n", i%3);
        printf("%d -- mod4\n", i%4);
        printf("%d -- mod5\n", i%5);
    }

return 0;
}

