#ifndef stack_t_h
#define stack_t_h

#include "element_t.h"

typedef struct _stack_t {
  element_t *top;
  int size;
  void * (*pop)(struct _stack_t *stack);
  void (*push)(void *value, struct _stack_t *stack);
} stack_t;

void * pop(stack_t *stack);
void push(void *value, stack_t *stack_t);
stack_t * stack(void);
void _stack_(stack_t *stack);

#endif
