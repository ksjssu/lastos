#ifndef QUEUE_H
#define QUEUE_H

#include "process.h"

typedef struct queue_node {
    process_t *process;
    struct queue_node *next;
} queue_node_t;

typedef struct {
    queue_node_t *head;
    queue_node_t *tail;
} process_queue_t;

void init_queue(process_queue_t *q);
int is_queue_empty(process_queue_t *q);
void enqueue(process_queue_t *q, process_t *p);
process_t* dequeue(process_queue_t *q);

#endif // QUEUE_H

