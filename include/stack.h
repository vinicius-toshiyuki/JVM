#ifndef stack_h
#define stack_h

#include <stdlib.h>

// Não garante que um push ou pop não vai estourar a pilha.

typedef void * stack_t;

stack_t * Stack(int max_size);
void push(stack_t *stack, void *value);
void * pop(stack_t *stack);

#endif

