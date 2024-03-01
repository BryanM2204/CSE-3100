
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

//TODO:
void push(stack *s, node *new_node)
{
    if (s != NULL) {
        while (s->top != NULL)
            s->top = s->top->next;
    }

    node *last = s->top;

    new_node->next = NULL;

    last->next = new_node;
}

//TODO:
node* pop(stack *s)
{
    node *current = s->top;
    node *previous = NULL;

    while(current->next != NULL){
        previous = current;
        current = current->next;
    }

    previous->next = NULL;

    node *temp = current;

    free(current);

    return temp;
}

//TODO:
int empty(stack *s)
{
    if(s->top ==NULL){
        return 0;
    } else {
        return 1;
    }
}

//TODO:
void clear_stack(stack *s)
{
    while(s->top != NULL){
        node *current = s->top->next;
        free(s->top);
        s->top = current;
    }
}