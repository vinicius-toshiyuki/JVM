/**
 * @file attributes.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the definition of an attribute.
 */
#ifndef attributes_h
#define attributes_h

#include "types.h"
#include <stdio.h>
#include "classfile.h"

#define ATT_C 7
#define ATT_M_S 20

/**
 * \enum NUMBERS
 * Number of the attribute.
 */
typedef enum {
  NUMBER_Invalid = -1,
  NUMBER_Code = 0,
  NUMBER_ConstantValue,
  NUMBER_Deprecated,
  NUMBER_Exceptions,
  NUMBER_LineNumberTable,
  NUMBER_LocalVariableTable,
  NUMBER_SourceFile
} NUMBERS;

/**
 * \struct exceptions_info
 * Exception entry.
 */
typedef struct {
  u2 start_pc;
  u2 end_pc;
  u2 handler_pc;
  u2 catch_type;
} exceptions_info;

/**
 * \struct line_number_table_info
 * Line Number Table entry.
 */
typedef struct {
  u2 start_pc;
  u2 line_number;
} line_number_table_info;

/**
 * \struct local_variable_table_info
 * Local Variable Table entry.
 */
typedef struct {
  u2 start_pc;
  u2 length;
  u2 name_index;
  u2 descriptor_index;
  u2 index;
} local_variable_table_info;

/**
 * \struct ConstantValue_attribute
 * ConstantValue attribute.
 */
typedef struct {
  u2 constantvalue_index;
} ConstantValue_attribute;

/**
 * \struct Code_attribute
 * Code attribute.
 */
typedef struct {
  u2 max_stack;
  u2 max_locals;
  u4 code_length;
  u1 *code;
  u2 exception_table_length;
  exceptions_info *exception_table;
  u2 attributes_count;
  attribute_info *attributes;
} Code_attribute;

/**
 * \struct Exceptions_attribute
 * Exceptions attribute.
 */
typedef struct {
  u2 attribute_name_index;
  u4 attribute_length;
  u2 number_of_exceptions;
  u2 *exception_index_table;
} Exceptions_attribute;

/**
 * \struct SourceFile_attribute
 * SourceFile attribute.
 */
typedef struct {
  u2 sourcefile_index;
} SourceFile_attribute;

/**
 * \struct LineNumberTable_attribute
 * Line Number Table attribute.
 */
typedef struct {
  u2 line_number_table_length;
  line_number_table_info *line_number_table;
} LineNumberTable_attribute;

/**
 * \struct LocalVariableTable_attribute
 * Local Variable Table attribute.
 */
typedef struct {
  u2 local_variable_table_length;
  local_variable_table_info *local_variable_table;
} LocalVariableTable_attribute;

// typedef struct {} Deprecated_attribute;

/**
 * \union Attributes
 * Union of all attributes structs.
 */
typedef union {
  ConstantValue_attribute ConstantValue;
  Code_attribute Code;
  Exceptions_attribute Exceptions;
  SourceFile_attribute SourceFile;
  LineNumberTable_attribute LineNumberTable;
  LocalVariableTable_attribute LocalVariableTable;
} Attributes;

/**
 * Return the attribute by passing his entry.
 */
void get_attribute_from_info(u1 *, Attributes *, u2, ClassFile *);

#define u2_flip(__bytes) __bytes = (__bytes << 8) | (__bytes >> 8)

#define u4_flip(__bytes) \
{ \
  u2 __a = __bytes; u2_flip(__a); \
  u2 __b = __bytes >> 16; u2_flip(__b); \
  __bytes = (__a << 16) | __b; \
}

#define u1_to_Code(__code, __u1_stream) \
{ \
  u1 *__stream = __u1_stream; \
  /* u2 max_stack, u2 max_locals, u4 code_length */ \
  memcpy(&__code, __stream, 8), __stream += 8; \
  u2_flip(__code.max_stack); \
  u2_flip(__code.max_locals); \
  u4_flip(__code.code_length); \
  /* u1 code[code_length] */ \
  __code.code = (u1 *) malloc(sizeof(u1) * __code.code_length); \
  memcpy(__code.code, __stream, __code.code_length), __stream += __code.code_length; \
  /* u2 exception_table_length */ \
  memcpy(&__code.exception_table_length, __stream, 2), __stream += 2; \
  u2_flip(__code.exception_table_length); \
  /* exceptions_info exception_table[exception_table_length] */ \
  /* TODO: flip exception_table fields */ \
  __code.exception_table = (exceptions_info *) malloc(sizeof(exceptions_info) * __code.exception_table_length); \
  for(int i = 0; i < __code.exception_table_length; i++) \
    memcpy(&__code.exception_table[i], __stream, 8), __stream += 8; \
  /* u2 attributes_count */ \
  memcpy(&__code.attributes_count, __stream, 2), __stream += 2; \
  u2_flip(__code.attributes_count); \
  /* attribute_info attributes[attributes_count] */ \
  __code.attributes = (attribute_info *) malloc(sizeof(attribute_info) * __code.attributes_count); \
  for(int i = 0; i < __code.attributes_count; i++){ \
    memcpy(&__code.attributes[i].attribute_name_index, __stream, 2), __stream += 2; \
    memcpy(&__code.attributes[i].attribute_length, __stream, 4), __stream += 4; \
    u2_flip(__code.attributes[i].attribute_name_index); \
    u4_flip(__code.attributes[i].attribute_length); \
    /* TODO: flip attribute info bytes (ou talvez não) */ \
    __code.attributes[i].info = (u1 *) malloc(sizeof(u1) * __code.attributes[i].attribute_length); \
    memcpy(__code.attributes[i].info, __stream, __code.attributes[i].attribute_length), __stream += __code.attributes[i].attribute_length; \
  } \
}

#define u1_to_ConstantValue(__constantvalue, __u1_stream) memcpy(&__constantvalue, __u1_stream, 2), u2_flip(__constantvalue.constantvalue_index)

#define u1_to_Exceptions(__exceptions, __u1_stream) \
{ \
  u1 *__stream = __u1_stream; \
  memcpy(&__exceptions.number_of_exceptions, __stream, 2), __stream += 2; \
  u2_flip(__exceptions.number_of_exceptions); \
	__exceptions.exception_index_table =  (u2 *) malloc(sizeof(u2) * __exceptions.number_of_exceptions);\
  for(int i = 0; i < __exceptions.number_of_exceptions; i++){ \
    memcpy(&__exceptions.exception_index_table[i], __stream, 2), __stream += 2; \
    u2_flip(__exceptions.exception_index_table[i]); \
  } \
}

#define u1_to_LineNumberTable(__linenumbertable, __u1_stream) \
{ \
  u1 *__stream = __u1_stream; \
  memcpy(&__linenumbertable.line_number_table_length, __stream, 2), __stream += 2; \
  u2_flip(__linenumbertable.line_number_table_length); \
  __linenumbertable.line_number_table = (line_number_table_info *) malloc(sizeof(line_number_table_info) * __linenumbertable.line_number_table_length); \
  for(int i = 0; i < __linenumbertable.line_number_table_length; i++){ \
    memcpy(&__linenumbertable.line_number_table[i].start_pc, __stream, 2), __stream += 2; \
    memcpy(&__linenumbertable.line_number_table[i].line_number, __stream, 2), __stream += 2; \
    u2_flip(__linenumbertable.line_number_table[i].start_pc); \
    u2_flip(__linenumbertable.line_number_table[i].line_number); \
  } \
}

#define u1_to_LocalVariableTable(__localvariabletable, __u1_stream) \
{ \
  u1 *__stream = __u1_stream; \
  memcpy(&__localvariabletable.local_variable_table_length, __stream, 2), __stream += 2; \
  u2_flip(__localvariabletable.local_variable_table_length); \
  __localvariabletable.local_variable_table = (local_variable_table_info *) malloc(sizeof(local_variable_table_info) * __localvariabletable.local_variable_table_length); \
  for(int i = 0; i < __localvariabletable.local_variable_table_length; i++){ \
    memcpy(&__localvariabletable.local_variable_table[i].start_pc, __stream, 2), __stream += 2; \
    u2_flip(__localvariabletable.local_variable_table[i].start_pc); \
    memcpy(&__localvariabletable.local_variable_table[i].length, __stream, 2), __stream += 2; \
    u2_flip(__localvariabletable.local_variable_table[i].length); \
    memcpy(&__localvariabletable.local_variable_table[i].name_index, __stream, 2), __stream += 2; \
    u2_flip(__localvariabletable.local_variable_table[i].name_index); \
    memcpy(&__localvariabletable.local_variable_table[i].descriptor_index, __stream, 2), __stream += 2; \
    u2_flip(__localvariabletable.local_variable_table[i].descriptor_index); \
    memcpy(&__localvariabletable.local_variable_table[i].index, __stream, 2), __stream += 2; \
    u2_flip(__localvariabletable.local_variable_table[i].index); \
  } \
}

#define u1_to_SourceFile(__sourcefile, __u1_stream) memcpy(&__sourcefile.sourcefile_index, __u1_stream, 2), u2_flip(__sourcefile.sourcefile_index);

#define bprint_numeral(tag) \
{ \
	switch(tag){ \
		case CONSTANT_Integer: \
      printf("%sBytes: %d\n", prefix, cp->info->Integer.bytes); \
      break; \
		case CONSTANT_Float:; \
      u4 __value_f = cp->info->Float.bytes; \
      float __f; \
      memcpy(&__f, &__value_f, 4); \
      printf("%sValue: %f\n", prefix, __f); \
      break; \
		case CONSTANT_Long: \
      printf( \
          "%sValue: %ld\n", \
          prefix, ((u8) cp->info->Long.high_bytes << 32 | cp->info->Long.low_bytes) \
      ); \
      break; \
		case CONSTANT_Double:; \
      u8 v = (((u8) cp->info->Double.high_bytes) << 32 | cp->info->Double.low_bytes); \
      double d; \
      memcpy(&d, &v, 8); \
      printf( \
          "%sValue: %lf\n", \
          prefix, d \
      ); \
      break; \
	} \
}
#endif
