#ifndef QUEUE_H
#define QUEUE_H



struct queue_node {
    struct queue_node *next;
    int data;
};


struct queue {
    struct queue_node *head, *tail;
    int length;
};

int queue_init(struct queue *q);
int queue_destroy(struct queue *q);
int queue_enqueue(struct queue *q, int d);
int queue_dequeue(struct queue *q, int *d);
int queue_length(struct queue *q);
int queue_is_empty(struct queue *q);


#endif
