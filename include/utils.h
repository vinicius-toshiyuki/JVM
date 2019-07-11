#ifndef __UTILS_H__
#define __UTILS_H__

extern int VERBOSE;

int comp(const void *a, const void *b);
#define printv(...) if(VERBOSE) printf(__VA_ARGS__);

#endif
