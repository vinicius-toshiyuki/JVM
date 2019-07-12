/**
 * @file constant_pool.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain methods to get the constants from constant pool.
 */
#ifndef constant_pool_h
#define constant_pool_h

#include "info.h"
#include "frame.h"

info_t * get_constant_pool_entry(frame_t *frame, u2 index);
int get_constant_pool_tag(frame_t *, u2);

#endif
