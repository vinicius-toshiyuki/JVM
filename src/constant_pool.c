#include "../include/constant_pool.h"

info_t * get_constant_pool_entry(frame_t *frame, u2 index){
  cp_info *cp = frame->constant_pool;
  return cp[index - 1].info;
}

int get_constant_pool_tag(frame_t *frame, u2 index){
	return frame->constant_pool[index - 1].tag;
}
