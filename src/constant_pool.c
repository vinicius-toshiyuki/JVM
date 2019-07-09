#include "../include/constant_pool.h"

info_t * getConstantPoolEntry(frame_t *frame, u2 index){
  cp_info *cp = frame->constant_pool;
  return cp[index - 1].info;
}