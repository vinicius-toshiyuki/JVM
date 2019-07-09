#ifndef constant_pool_h
#define constant_pool_h

#include "info.h"
#include "frame.h"

info_t * getConstantPoolEntry(frame_t *frame, u2 index);

#endif