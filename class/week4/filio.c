#include <stdio.h>

typedef enum {
    read_text,  // 0
    write_text, // 1
    read_binary,// 2
    write_binary,// 3
    invalid_action
} action_t;

int main(int argc, char *argv[])
{
    action_t a = invalid_action;

    if (argc == 2 && argv[1][0] == '-')
    {
        if (argv[1][1] == 'r') {
            if (argv[1][2] == 't') {
                a = read_text;
            } else if (argv[1][2] == 'b') {
                a = read_binary;
            }
        }   
        else if (argv[1][1] == 'w') {
            if (argv[1][2] == 't') {
                a = write_text;
            } else if (argv[1][2] == 'b') {
                a = write_binary; 
            }
        }
    }

    if(a == invalid_action) {
        fprintf(stderr, "Usage: %s [-wt|-wb|-rt|-rb]\n", argv[0]);

        return -1;
    }


    switch(a) {
        case read_text:
            
            break;
        case read_binary:
            break;
        case write_binary:
            break;
        case write_text:
            break;
        default:
            break;
    }

    return 0;
}
