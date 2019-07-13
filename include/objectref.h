/**
 * @file objectref.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the definition of an object reference on operand stack or local variable array.
 */
#ifndef objectref_h
#define objectref_h

#include "types.h"

/**
 * \struct objectref_t
 *  Defines the objectref_t structure to be used as an object reference in operand stack and local variable array.
 */
typedef struct objectref_t{
    u1 tag;
    void *object;
} objectref_t;

/**
 * \enum REF
 *  Defines enum REF of reference types.
 */
typedef enum {
    REF_Null = -1,
    REF_Instance = 0,
    REF_Array = 1,
    REF_Fieldref,
    REF_Methodref,
    REF_Class,
		REF_String
} REF;

/**
 *  Creates a new objectref.
 */
objectref_t * new_objectref(void);

/**
 *  Destroys an objectref.
 */
void destroy_objectref(objectref_t *ref);

/**
 *  Initializes objectref acording to reference type.
 */
void reference_of(objectref_t *ref, int type, void *refvalue);

#endif /* objectref_h */
