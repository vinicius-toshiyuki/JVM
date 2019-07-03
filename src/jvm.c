#include "../include/jvm.h"
#include "../include/cstack.h"
#include "../include/method_area.h"
#include <stdlib.h>

void start_jvm(jvm_t *jvm){
	jvm = (jvm_t *) malloc(sizeof(jvm_t));
	jvm->heap = new_cstack();
	jvm->marea = new_method_area();
	return;
}
