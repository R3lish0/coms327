#include <unistd.h>
#include <stdio.h>
#include "../terrain/terrain.h"



int main()
{
    struct square sq;
    genMap(&sq);
    printf("%p", (&sq));
    return 0;
}
