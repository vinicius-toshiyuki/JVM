/**
 * @file frame.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the definition of a frame struct.
 */
#ifndef frame_h
#define frame_h

#include "clist.h"
#include "cstack.h"
#include "classfile.h"

/**
 * \struct frame_t
 * Struct of an JVM frame.
 */
typedef struct frame_t {
	int size;	/**< Frame size. */
	clist_t *local_variables; /**< Frame local variables. */
	cstack_t *operands_stack; /**< Frame operand stack. */
	cp_info *constant_pool; /**< Frame constant pool */
	u1 *pc;	/**< Frame pc. */
} frame_t;

/**
 * Create a new frame.
 */
frame_t * new_frame(void);

/**
 * Destroy the passed frame;
 */
void destroy_frame(frame_t *);

#endif /* frame_h */
