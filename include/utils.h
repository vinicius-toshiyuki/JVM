/**
 * @file utils.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain utils methods.
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"

extern int VERBOSE;

/**
 * Compare two chars.
 */
int comp(const void *a, const void *b);
int charcmp(const void *a, const void *b);
#define printv(...) if(VERBOSE) printf(__VA_ARGS__);
void print_utf8(info_t *string_utf8);

#endif /* __UTILS_H__ */
