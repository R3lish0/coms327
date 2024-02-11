#include <stdio.h>

#include <ctype.h>

char *words[] = {
    "avacado",
    "bacon",
    "canada",
    "detriment",
    "elephant",
    "five",
    "guerilla",
    "hueristic",
    "iguana",
    "jaguar",
    "kilometer",
    "lizard",
    "malding",
    "newspaper",
    "octagon",
    "pentagon",
    "quail",
    "ricin",
    "sheaffer",
    "transatlantic",
    "unambiguous",
    "vector",
    "worctsterchire",
    "x-ray",
    "yachtsmanship",
    "zed",
};

int main(int argc, char *argv[])
{
    /*
    printf("%c\n", 0101);
    printf("%c\n", 0x41);
    printf("%c\n", 65);
    printf("%c\n", 'A');
   */ 

    printf("%c is for %s\n", argv[1][0], words[toupper(argv[1][0]) - 'A']);
    



    return 0;

}

