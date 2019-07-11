#ifndef engine_h
#define engine_h

#include "types.h"
#include "classfile.h"
#include "frame.h"
#include "jvm.h"

typedef struct Method {
    u2 length;
    u1 *code;
} Method;

Method get_method_by_name(ClassFile *, char *);
void run_method(frame_t *, Method *, jvm_t *);

/* Store @arguments in local variable array on @frame from @old_frame. @arguments is a char array of descriptors */
void store_arguments(frame_t *frame, frame_t *old_frame, char *arguments);

#endif
