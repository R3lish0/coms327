#include <stdio.h>
#include "queue.h"


int main(int argc, char *argv[])
{
    queue_t q;
    int i;
    queue_init(&q);

    for (i = 0; i < 10; i++) {
        queue_enqueue(&q, i);
    }

    printf("%d\n", queue_length(&q));

    while (!queue_is_empty(&q)) {
        if (queue_dequeue(&q, &i)) {
            fprintf(stderr, "Attempt to dequeue an empty queue\n");
            return 1;// stdin, stdout, stderr
        }
        printf("%d\n", i);
    }

    printf("%d\n", queue_dequeue(&q,&i));

    queue_destroy(&q);

    return 0;


}
