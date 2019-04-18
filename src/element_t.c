#include "../include/element_t.h"
#include <stdlib.h>

element_t * element(void *value){
  element_t *new = (element_t *) malloc(sizeof(element_t));
  new->value = value;
  new->next = NULL;
  return new;
}

void * _element_(element_t *element){
  void *value = element->value;
  free(element);
  return value;
}
