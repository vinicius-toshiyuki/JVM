#ifndef array_h
#define array_h

#include "clist.h"
#include <stdlib.h>
#include "types.h"
#include "objectref.h"

/**
 *  Defines the array structure, which is a encapsulation of clist structure
 */
typedef struct array_t{
    int32_t length;
    u2 type;
    int32_t max_length;
    clist_t *items;
} array_t;

/**
 *  Definition of array types
 */
typedef enum{
    ARR_Null = -1,
    ARR_RefInstance = REF_Instance,
    ARR_RefArray = REF_Array,
    ARR_RefFieldref = REF_Fieldref,
    ARR_RefMethodref = REF_Methodref,
    ARR_RefClass = REF_Class,
    ARR_Char,
    ARR_Boolean,
    ARR_Byte,
    ARR_Short,
    ARR_Integer,
    ARR_Float,
    ARR_Double,
    ARR_Long
} ARR;

/**
 *  Creates a new array_t
 */
array_t * new_array(void);

/**
 *  Defines the type of an array and it's max length
 */
void array_of(array_t *array, int type, int max_length);

/**
 *  Destroys an array_t
 */
void destroy_array(array_t *array);

/**
 *  Returns element at index if exists, else, returns NULL
 */
void * at(array_t *array, int index);

/**
 *  If possible, puts value in array at index
 */
void put(array_t *array, int index, void *value);

/**
 *  Removes and get element in array at index, if possible
 */
void * get(array_t *array, int index);

#endif