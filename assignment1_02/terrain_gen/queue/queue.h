#ifndef QUEUE_H
#define QUEUE_H



typedef struct queue_node {
    struct queue_node *next;
    int location[2];
    char val;

} queue_node;


typedef struct queue {
    struct queue_node *head, *tail;
    int length;
}queue;

int queue_init(queue *q);
int queue_destroy(queue *q);
int queue_enqueue(queue *q, int location[2], char val);
int queue_dequeue(queue *q, int location[2], char *val);
int queue_length(queue *q);
int queue_is_empty(queue *q);


#endif
