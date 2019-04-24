#include "../include/stack.h"

stack_t * Stack(int max_size){
  return (stack_t *) calloc(max_size + 1, sizeof(void *));
}
void push(stack_t *stack, void *value){
  int *index = (int *) stack;
  void **pos = stack + ++(*index);
  *pos = value;
  return;
}
void * pop(stack_t *stack){
  int *index = (int *) stack;
  void **pos = stack + (*index)--;
  return *pos;
}
