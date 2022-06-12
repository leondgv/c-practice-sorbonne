#include <stdio.h>
#include "library_created/fifo.h"

int main(void) 
{
    fifo xs = new_fifo();
    print_fifo(xs);
    
    int i;
    for(i = 1; i < 6; i++) 
    {
        printf("Ajout de %d à ", i); print_fifo(xs);
        printf("\n");
        xs = add(i,xs); print_fifo(xs); 
    }
    for(i = 0; i < 5; i++) 
    {
        printf("Valeur de tête: %d\n", peek(xs));
        printf("Suppression: "); xs = pop(xs); print_fifo(xs); 
        printf("\n");
    }
    return 0;
}