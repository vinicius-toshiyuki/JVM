#ifndef info_h
#define info_h
#include "types.h"
enum {
  CONSTANT_Class = 7,
  CONSTANT_Fieldref = 9,
  CONSTANT_Methodref = 10,
  CONSTANT_InterfaceMethodref = 11,
  CONSTANT_String = 8,
  CONSTANT_Integer = 3,
  CONSTANT_Float = 4,
  CONSTANT_Long = 5,
  CONSTANT_Double = 6,
  CONSTANT_NameAndType = 12,
  CONSTANT_Utf8 = 1
} CONSTANTS;
typedef struct {
  u1 tag;
  u2 name_index;
} CONSTANT_Class_info;
typedef struct {
  u1 tag;
  u2 class_index;
  u2 name_and_type_index;
} CONSTANT_Fieldref_info;
typedef struct {
  u1 tag;
  u2 class_index;
  u2 name_and_type_index;
} CONSTANT_Methodref_info;
typedef struct {
  u1 tag;
  u2 class_index;
  u2 name_and_type_index;
} CONSTANT_InterfaceMethodref_info;
typedef struct {
  u1 tag;
  u2 string_index;
} CONSTANT_String_info;
typedef struct {
  u1 tag;
  u4 bytes;
} CONSTANT_Integer_info;
typedef struct {
  u1 tag;
  u4 bytes;
} CONSTANT_Float_info;
typedef struct {
  u1 tag;
  u4 high_bytes;
  u4 low_bytes;
} CONSTANT_Long_info;
typedef struct {
  u1 tag;
  u4 high_bytes;
  u4 low_bytes;
} CONSTANT_Double_info;
typedef struct {
  u1 tag;
  u2 name_index;
  u2 descriptor_index;
} CONSTANT_NameAndType_info;
typedef struct {
  u1 tag;
  u2 length;
  u1 *bytes;
} CONSTANT_Utf8_info;
typedef union {
  CONSTANT_Class_info Class;
  CONSTANT_Fieldref_info Fieldref;
  CONSTANT_Methodref_info Methodref;
  CONSTANT_InterfaceMethodref_info InterfaceMethodref;
  CONSTANT_String_info String;
  CONSTANT_Integer_info Integer;
  CONSTANT_Float_info Float;
  CONSTANT_Long_info Long;
  CONSTANT_Double_info Double;
  CONSTANT_NameAndType_info NameAndType;
  CONSTANT_Utf8_info Utf8;
} info_t;
#endif

