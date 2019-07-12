/**
 * @file jvm.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contains the struct of the java machine and the methods to create and start the jvm.
 */
#ifndef jvm_h
#define jvm_h

#include "cstack.h"
#include "method_area.h"
#include "classfile.h"

/**
 * \struct jvm_t
 * Struct of the JVM.
 */
typedef struct jvm_t {
	cstack_t *heap;	/**< Heap */
	method_area_t *marea; /**< Method area */
	cstack_t *frame_stack; /**< Frame Stack */
} jvm_t;

/**
 * Create an instance of the jvm.
 */
jvm_t* new_jvm(void);

/**
 * Initialize the JVM with ClassFile.
 */
void start_jvm(jvm_t **, ClassFile *);

#endif /* jvm_h */
