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

#endif
