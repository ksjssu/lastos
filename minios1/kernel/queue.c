#include "queue.h"
#include <stdlib.h>

void init_queue(process_queue_t *q) {
    q->head = q->tail = NULL;
}

int is_queue_empty(process_queue_t *q) {
    return q->head == NULL;
}

void enqueue(process_queue_t *q, process_t *p) {
    queue_node_t *node = (queue_node_t *)malloc(sizeof(queue_node_t));
    if (node) {
        node->process = p;
        node->next = NULL;
        if (q->tail) {
            q->tail->next = node;
        } else {
            q->head = node;
        }
        q->tail = node;
    }
}

process_t *dequeue(process_queue_t *q) {
    if (is_queue_empty(q)) {
        return NULL;
    }
    queue_node_t *node = q->head;
    process_t *p = node->process;
    q->head = node->next;
    if (!q->head) {
        q->tail = NULL;
    }
    free(node);
    return p;
}

