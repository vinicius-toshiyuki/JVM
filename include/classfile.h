#ifndef classfile_h
#define classfile_h

#include "types.h"
#include "info.h"
//#include "attributes.h"

typedef struct {
  u1 tag;
  info_t *info;
} cp_info;

typedef struct {
  u2 attribute_name_index;
  u4 attribute_length;
  u1 *info;
//  Attributes *att_info;
} attribute_info;

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

