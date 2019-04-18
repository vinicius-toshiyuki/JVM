#ifndef element_t_h
#define element_t_h

typedef struct _element_t {
  void *value;
  struct _element_t *next;
} element_t;

element_t * element(void *value);
void * _element_(element_t *element);

#endif
