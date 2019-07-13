#ifndef string_h
#define string_h

#include "types.h"

typedef struct String{
	short tag;
	void *data;
} String;

typedef enum{
  STR_Builder = -2,
	STR_Null = -1,
	STR_String,
	STR_Double,
	STR_Float,
	STR_Char,
	STR_Integer,
	STR_Short,
	STR_Byte,
	STR_Long,
	STR_Boolean
} STRING_Tag;

String * new_string(void);
void string_of(String *str, int tag, void *data);
#define CSTRING_TAG -1

#endif
