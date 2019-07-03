#ifndef method_area
#define method_area

/* TODO: colocar o include do cp_info */

typedef cp_info * constant_pool;

typedef struct method_area {
	int count;
	constant_pool *cpools;
} method_area;

method_area * new_method_area(void);
void destroy_method_area(method_area *);

#endif
