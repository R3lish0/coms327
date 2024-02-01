#ifndef QUEUE_H
#define QUEUE_H



typedef struct queue_node queue_node_t;

struct queue_node {
    queue_node_t *next;
    int data;
} ;


typedef struct queue {
    struct queue_node *head, *tail;
    int length;
} queue_t;

int queue_init(queue_t *q);
int queue_destroy(queue_t *q);
int queue_enqueue(queue_t *q, int d);
int queue_dequeue(queue_t *q, int *d);
int queue_length(queue_t *q);
int queue_is_empty(queue_t *q);


#endif
