#ifndef field_object_h
#define field_object_h

#include "info.h"
#include "types.h"
#include "objectref.h"

/**
 *  Defines a field object reference structure
 */
typedef struct field_object_t {
	info_t *ref;
	u1 tag;
	union {
		float Float;
		integer Integer;
		byte Byte;
		character Char;
		long int Long;
		double Double;
		boolean Boolean;
		short Short;
		objectref_t *ObjectRef;
		objectref_t *ArrayRef;
	} value;
} field_object_t;

/**
 *  Define an enum of field tags
 */
typedef enum {
	FIELD_Null = -1,
	FIELD_Float = 0,
	FIELD_Integer,
	FIELD_Char,
	FIELD_Byte,
	FIELD_Boolean,
	FIELD_Short,
	FIELD_Double,
	FIELD_Long,
	FIELD_ArrayRef,
	FIELD_ObjectRef
} FIELD;
/**
 *  Create a new field_object_t
 */
field_object_t * new_field_object(void);

/**
 *  Destroys a field_object_t
 */
void destroy_field_object(field_object_t *field_object);

#endif
