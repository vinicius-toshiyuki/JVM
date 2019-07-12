/**
 * @file celement.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the definition of an stack or list element.
 */
#ifndef celement_h
#define celement_h

/**
 * \struct celement_t
 * Struct of an stack or list element.
 */
typedef struct celement_t {
	struct celement_t *next; /**< Next element. */
	void *value; /**< Value. */
} celement_t;

/**
 * Create a new element.
 */
celement_t * new_celement(void *);

/**
 * Destroy the passed element.
 */
void destroy_celement(celement_t *);
#endif /* celement_h */
