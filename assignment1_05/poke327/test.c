#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdlib.h>

int main(void) {
    initscr();
    char check; 
    while(1)
    {
       check = getch();
       addch(check);
    }
}
