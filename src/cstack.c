#include "cstack.h"
#include <stdlib.h>

cstack_t * new_cstack(void){
	cstack_t *new = (cstack_t *) malloc(sizeof(cstack_t));
	new->size = 0;
	new->top = NULL;
	return new;
}

void destroy_cstack(cstack_t *stack){
	while(stack->size)
		cpop(stack);
	free(stack);
	return;
}

void cpush(cstack_t *stack, void *value){
	celement_t *element = new_celement(value);
	element->next = stack->top;
	stack->top = element;
	stack->size++;
	return;
}

void * cpop(cstack_t *stack){
	void *value = NULL;
	if(stack->size){
		value = stack->top->value;
		celement_t *new_top = stack->top->next;
		destroy_celement(stack->top);
		stack->top = new_top;
		stack->size--;
	}
	return value;
}

celement_t * new_celement(void *value){
	celement_t *new = (celement_t *) malloc(sizeof(celement_t));
	new->next = NULL;
	new->value = value;
	return new;
}

void destroy_celement(celement_t *element){
	free(element);
	return;
}
