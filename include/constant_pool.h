#ifndef constant_pool_h
#define constant_pool_h

#include "info.h"
#include "frame.h"

info_t * get_constant_pool_entry(frame_t *frame, u2 index);
int get_constant_pool_tag(frame_t *, u2);

#endif
