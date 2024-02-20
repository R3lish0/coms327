#include <stdio.h>

//value-type macro
#define FOO 42

//function-type macro
#define min(x,y) (x < y ? x : y)





int main(int argc, char argv[])
{
    printf("%d\n", FOO);

    min(10,7) + 5;

    min(function_with_side_effects() < really_expensive_function() ? function_with_side_effects() : really_expensive_function());
    return 0;

}

