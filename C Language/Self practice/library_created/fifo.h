#ifndef FIFO
#define FIFO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Pour les fifo
struct cell {
    int donnee;
    struct cell *suivant;
};

// Paire de pointeurs vers des cellules chainables
struct s_fifo {
    struct cell *first;
    struct cell *last;
};
typedef struct s_fifo fifo;

// LA FILE VIDE
fifo new_fifo(void)
{
    fifo r;
    r.first = NULL;
    r.last = NULL;

    return r;
}
// Reconnaitre une file vide
int is_empty(fifo xs)
{
    return (xs.first == NULL && xs.last == NULL);
}
fifo add(int x, fifo xs)
{
    struct cell *c = malloc(sizeof(struct cell));
    c->donnee = x;
    c->suivant = NULL;

    if (is_empty(xs) == 1)
    {
        xs.first = c;
        xs.last = c;
    }
    else 
    {
        xs.last->suivant = c;
        xs.last = c;
    }
    return xs;
}
int peek(fifo xs)
{
    return xs.first->donnee;
}
fifo pop(fifo xs)
{
    if (is_empty(xs) == 0)
    {
        xs.first = xs.first->suivant;
        if (xs.first == NULL) xs.last = NULL;
    }
    return xs;
}
void print_fifo(fifo xs)
{
    struct cell *c = xs.first;
    printf("[");

    while (c != NULL)
    {
        printf("(%d)",c->donnee);
        c = c->suivant;
    }
    printf("]\n");
}
#endif