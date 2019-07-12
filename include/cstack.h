/**
 * @file cstack.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the struct of the stack.
 */
#ifndef cstack_h
#define cstack_h

#include "../include/celement.h"

/**
 * \struct cstack_t
 * Struct of the stack.
 */
typedef struct cstack_t {
	int size;
	celement_t *top;
} cstack_t;

/**
 * Create a new stack.
 */
cstack_t * new_cstack(void);

/**
 * Destroy the passed stack.
 */
void destroy_cstack(cstack_t *);

/**
 * Push an element into the stack.
 */
void cpush(cstack_t *, void *);

/**
 * Pop an element from the stack.
 */
void * cpop(cstack_t *);
#endif /* cstack_h */
