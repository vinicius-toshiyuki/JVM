/**
 * @file utils.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain utils methods.
 */
#ifndef __UTILS_H__
#define __UTILS_H__

extern int VERBOSE;

/**
 * Compare two strings.
 */
int comp(const void *a, const void *b);
#define printv(...) if(VERBOSE) printf(__VA_ARGS__);

#endif /* __UTILS_H__ */
