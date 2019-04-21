#ifndef classfile_h
#define classfile_h

#include "types.h"
#include "info.h"

typedef struct attribute_info attribute_info;

typedef enum {
  NUMBER_Code = 0,
  NUMBER_ConstantValue,
  NUMBER_Exceptions,
  NUMBER_Deprecated,
  NUMBER_SourceFile,
  NUMBER_LineNumberTable,
  NUMBER_LocalVariableTable
} NUMBERS;

typedef struct {
  u2 start_pc;
  u2 end_pc;
  u2 handler_pc;
  u2 catch_type;
} exceptions_info;

typedef struct {
  u2 start_pc;
  u2 line_number;
} line_number_table_info;

typedef struct {
  u2 start_pc;
  u2 length;
  u2 name_index;
  u2 descriptor_index;
  u2 index;
} local_variable_table_info;

typedef struct {
  u2 constantvalue_index;
} ConstantValue_attribute;

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

typedef struct {
  u2 attribute_name_index;
  u4 attribute_length;
  u2 number_of_exceptions;
  u2 *exception_index_table;
} Exceptions_attribute;

typedef struct {
  u2 sourcefile_index;
} SourceFile_attribute;

typedef struct {
  u2 line_number_table_length;
  line_number_table_info *line_number_table;
} LineNumberTable_attribute;

typedef struct {
  u2 local_variable_table_length;
  local_variable_table_info *local_variable_table;
} LocalVariableTable_attribute;

typedef struct {} Deprecated_attribute;

typedef union {
  ConstantValue_attribute ConstantValue;
  Code_attribute Code;
  Exceptions_attribute Exceptions;
  SourceFile_attribute SourceFile;
  LineNumberTable_attribute LineNumberTable;
  LocalVariableTable_attribute LocalVariableTable;
} Attributes;

typedef struct {
  u1 tag;
  info_t *info;
} cp_info;

struct attribute_info{
  u2 attribute_name_index;
  u4 attribute_length;
  u1 *info;
  Attributes *att_info;
};

typedef struct {
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  attribute_info *attributes;
} field_info;

typedef struct {
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  attribute_info *attributes;
} method_info;

typedef struct {
  u4 magic;
  u2 minor_version;
  u2 major_version;
  u2 const_pool_count;
  cp_info *constant_pool;
  u2 access_flags;
  u2 this_class;
  u2 super_class;
  u2 interfaces_count;
  u2 *interfaces;
  u2 fields_count;
  field_info *fields;
  u2 methods_count;
  method_info *methods;
  u2 attributes_count;
  attribute_info *attributes;
} ClassFile;

#endif

