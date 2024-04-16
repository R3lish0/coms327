#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int queue_init(struct queue *q)
{
    //head and tail don't point to anything -> they point to NULL
    //Null is the NULL pointer. It is defined as:
    //(void *) 0
    q->head = q->tail = NULL;
    q->length = 0;
    

    return 0;
}
int queue_destroy(struct queue *q)
{
    struct queue_node *n;

    for (n = q->head; n; n = q->head) {
        q->head = q->head->next;
        free(n);
    }
    q->length = 0;
    q->tail = NULL;
      
    return 0;
}
int queue_enqueue(struct queue *q, int l[2], char c)
{
    struct queue_node *tmp;
    

    //sizeof is a compile-time (static operator). It gives the static size
    //the expression given as its parameter
    //Idiomatically: x = malloc(sizeof (*x)) returns enough bytes to store
    //whatever x is
    if(!(tmp = (class queue_node*)malloc(sizeof(*tmp))))
    {
        return 1;
    }

    tmp->val = c;
    tmp->location[0] = l[0];
    tmp->location[1] = l[1];
    tmp->next = NULL;

    if (!q->head) 
    { //queue is empty
        q->head = q->tail = tmp;
    }
    else
    {
        q->tail->next = tmp;
        q->tail = tmp;
    }
    q->length++;
    return 0;

}
int queue_dequeue(struct queue *q, int location[2], char *val)
{
    struct queue_node *n;
    if(!q->head)
    {
        return 1;
    }
    n = q->head;
    q->head = q->head->next;
    *val = n->val;
    free(n);

    if (!q->head)
    {
        q->tail = NULL;
    }

    q->length--;
    return 0;
}
int queue_length(struct queue *q)
{
    return q->length;
}
int queue_is_empty(struct queue *q)
{
    return !q->head;
}
