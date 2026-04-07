#include "doubly_circular_queue.h"

#include <stdlib.h>

// 头尾哨兵
static struct node tailsentinel;
static struct node headsentinel = {0, NULL, &tailsentinel};
static struct node tailsentinel = {0, &headsentinel, NULL};

static link head = &headsentinel;
static link tail = &tailsentinel;

link make_node(int data) {
    link p = (link)malloc(sizeof(struct node));

    if (p == NULL) {
        return NULL;
    }

    p->data = data;
    p->prev = NULL;
    p->next = NULL;

    return p;
}

void free_node(link p) {
    free(p);
}

link search(int key) {
    link p;

    for (p = head->next; p != tail; p = p->next) {
        if (p->data == key) {
            return p;
        }
    }

    return NULL;
}

void insert(link p) {
    link first;

    if (p == NULL) {
        return;
    }

    first = head->next;
    p->prev = head;
    p->next = first;
    head->next = p;
    first->prev = p;
}

void delete(link p) {
    if (p == NULL || p == head || p == tail) {
        return;
    }

    p->prev->next = p->next;
    p->next->prev = p->prev;
    p->prev = NULL;
    p->next = NULL;
}

void traverse(void (*visit)(link)) {
    link p;

    if (visit == NULL) {
        return;
    }

    for (p = head->next; p != tail; p = p->next) {
        visit(p);
    }
}

void destroy(void) {
    link p = head->next;

    while (p != tail) {
        link next = p->next;
        delete(p);
        free_node(p);
        p = next;
    }

    head->next = tail;
    tail->prev = head;
}
