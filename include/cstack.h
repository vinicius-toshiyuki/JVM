#ifndef cstack
#define cstack

typedef struct celement_t {
	struct celement_t *next;
	void *value;
} celement_t;

typedef struct cstack_t {
	int size;
	celement_t *top;
} cstack_t;

cstack_t * new_cstack(void);
void destroy_cstack(cstack_t *);
void cpush(cstack_t *, void *);
void * cpop(cstack_t *);

celement_t * new_celement(void *);
void destroy_celement(celement_t *);
#endif
