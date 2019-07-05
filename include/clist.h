#ifndef clist_h
#define clist_h

#include "celement.h"

typedef struct clist_t {
	int size;
	celement_t *head;
	celement_t *tail;
} clist_t;

clist_t * new_clist(void);
void destroy_clist(clist_t *);
void cinsert(clist_t *, int, void *);
void cappend(clist_t *, void *);
void * cremove(clist_t *, int);
void * cat(clist_t *, int);

#endif
