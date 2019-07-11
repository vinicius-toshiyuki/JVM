#ifndef engine_h
#define engine_h

#include "types.h"
#include "classfile.h"
#include "frame.h"
#include "jvm.h"
#include "array.h"

typedef struct Method {
    u2 length;
    u1 *code;
} Method;

Method get_method_by_name(ClassFile *, char *);
void run_method(frame_t *, Method *, jvm_t *);

/* Store @arguments in local variable array on @frame from @old_frame. @arguments is a char array of descriptors */
void store_arguments(frame_t *frame, frame_t *old_frame, char *arguments);

/**
 *  Pop a java integer from the frame operands stack top
 */
integer pop_integer(frame_t *frame);

/**
 * Push a java integer into frame operands stack top
 */
void push_integer(frame_t *frame, integer ivalue);

/**
 *  Pop a java byte from the frame operands stack top
 */
byte pop_byte(frame_t *frame);

/**
 * Push a java byte into frame operands stack top
 */
void push_byte(frame_t *frame, byte bvalue);

/**
 *  Pop a java char from the frame operands stack top
 */
#define pop_char(frame) pop_byte(frame)

/**
 * Push a java char into frame operands stack top
 */
#define push_char(frame, bvalue) push_byte(frame, bvalue)

/**
 *  Pop a java boolean from the frame operands stack top
 */
#define pop_boolean(frame) pop_byte(frame)

/**
 * Push a java boolean into frame operands stack top
 */
#define push_boolean(frame, bvalue) push_byte(frame, bvalue)

/**
 *  Pop a java array reference from the frame operands stack top
 */
array_t * pop_array(frame_t *frame);

/**
 *  Pop a java double from the frame operands stack top
 */
double pop_double(frame_t *frame);

/**
 *  Push a java double into frame operands stack top
 */
void push_double(frame_t *frame, double dvalue);

/**
 * Transform high and low bytes into a java double
 */
double high_low_to_double(u4 *value_low, u4* value_high);

/**
 * Pop a java long from the frame operand stack top
 */
long pop_long(frame_t *frame);

/**
 * Push a java long into frame operands stack top
 */
void push_long(frame_t *frame, long lvalue);

/**
 * Transform high and low bytes into a java long
 */
long high_low_to_long(u4 *value_low, u4* value_high);

/**
 * Pop a java float from the frame operand stack top
 */
float pop_float(frame_t *frame);

/**
 * Push a java float into frame operands stack top
 */
void push_float(frame_t *frame, float fvalue);

/**
 *  Pop a java short from the frame operands stack top
 */
short pop_short(frame_t *frame);

/**
 *  Push a java short into frame operands stack top
 */
void push_short(frame_t *frame, short svalue);
#endif
