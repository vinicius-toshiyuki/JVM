#ifndef celement_h
#define celement_h

typedef struct celement_t {
	struct celement_t *next;
	void *value;
} celement_t;

celement_t * new_celement(void *);
void destroy_celement(celement_t *);
#endif
