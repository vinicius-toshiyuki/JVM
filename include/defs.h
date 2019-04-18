#ifndef defs_h
#define defs_h

#include <stdint.h>
#include "stack_t.h"

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u3;
typedef uint32_t u4;

typedef struct {
  stack_t *local_variables;
  stack_t *environmetn;
  stack_t *operands;
} stack_frame_t;

#endif
