#include "../include/celement.h"
#include <stdlib.h>

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
