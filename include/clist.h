/**
 * @file clist.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the definition of a list struct.
 */
#ifndef clist_h
#define clist_h

#include "celement.h"

/**
 * \struct clist_t
 */
typedef struct clist_t {
	int size;
	celement_t *head; /**< First element. */
	celement_t *tail; /**< Last element. */
} clist_t;

/**
 * Create a new list.
 */
clist_t * new_clist(void);

/**
 * Destroy the passed list.
 */
void destroy_clist(clist_t *);

/**
 * Insert in the position an element into the list.
 */
void cinsert(clist_t *, int, void *);

/**
 * Append an elemento into the list
 */
void cappend(clist_t *, void *);

/**
 * Remove an element from the following position.
 */
void * cremove(clist_t *, int);

/**
 * Get a element from the following position.
 */
void * cat(clist_t *, int);

#endif /* clist_h */
