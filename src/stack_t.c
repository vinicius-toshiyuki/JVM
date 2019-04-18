#include "../include/stack_t.h"
#include <stdio.h>
#include <stdlib.h>

stack_t * stack(void){
  stack_t *new = (stack_t *) malloc(sizeof(stack_t));
  new->top = NULL;
  new->size = 0;
  new->pop = pop;
  new->push = push;
  return new;
}

void _stack_(stack_t *stack){
  while(stack->size > 0){
    free(_element_(stack->pop(stack)));
  }
  free(stack);
  return;
}

void push(void *value, stack_t *stack){
  element_t *new_element = element(value);
  new_element->next = stack->top;
  stack->top = new_element;
  stack->size++;
  return;
}

void * pop(stack_t *stack){
  if(stack->size == 0){
    fprintf(stderr, "Pop attempt on zero-sized stack\n");
    return NULL;
  }
  void *ret = stack->top->value;
  stack->top = stack->top->next;
  stack->size--;
  ret->next = NULL;
  return ret;
}
