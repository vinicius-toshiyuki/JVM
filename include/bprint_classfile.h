#ifndef bprint_classfile_h
#define bprint_classfile_h

#include "breads.h"

void bprint_classfile(ClassFile *class);
void bprint_info(cp_info *cp, const char *prefix);

#define bprint_magic(__class) printf("Magic number: 0x%x\n", __class->magic)

#define bprint_versions(__class) printf("Minor version: 0x%02x\nMajor version: 0x%02x\n", __class->minor_version, __class->major_version)

#define bprint_const_pool_count(__class) printf("Constant pool count: %d\n", __class->const_pool_count)

#define bprint_constant_pool(__class) \
{ \
  printf("Constant pool:\n"); \
  for(int i = 0; i < __class->const_pool_count - 1; i++){ \
    printf("\tTag %d: %d\n", i + 1, __class->constant_pool[i].tag); \
    bprint_info(&__class->constant_pool[i], "\t"); \
  } \
}

#define bprint_access_flags(__class) printf("Access flags: 0x%04x\n", __class->access_flags)

#define bprint_this_class(__class) printf("This class: %d\n", __class->this_class)

#define bprint_super_class(__class) printf("Super class: %d\n", __class->super_class)

#define bprint_interfaces_count(__class) printf("Interfaces count: %d\n", __class->interfaces_count)

#define bprint_interfaces(__class) \
{ \
  printf("Interfaces:\n"); \
  for(int i = 0; i < __class->interfaces_count; i++) \
    printf("\tInterface %d: %d\n", i, __class->interfaces[i]); \
}

#define bprint_fields_count(__class) printf("Fields count: %d\n", __class->fields_count)
  
#define bprint_fields(__class) \
{ \
  printf("Fields:\n"); \
  for(int i = 0; i < __class->fields_count; i++){ \
    printf( \
        "\tField %d:\n" \
        "\tAccess flags: 0x%04x\n" \
        "\tName index: %d\n" \
        "\tDescriptor index: %d\n" \
        "\tAttributes count: %d\n", \
        i, __class->fields[i].access_flags, \
        __class->fields[i].name_index, \
        __class->fields[i].descriptor_index, \
        __class->fields[i].attributes_count \
    ); \
    bprint_attributes(__class->fields[i].attributes, __class->fields[i].attributes_count, "\t"); \
  } \
}

#define bprint_methods_count(__class) printf("Methods count: %d\n", __class->methods_count)

#define bprint_methods(__class) \
{ \
  printf("Methods:\n"); \
  for(int i = 0; i < __class->methods_count; i++){ \
    printf( \
        "\tMethod %d:\n" \
        "\tAccess flags: 0x%04x\n" \
        "\tName index: %d\n" \
        "\tDescriptor index: %d\n" \
        "\tAttributes count: %d\n", \
        i, __class->methods[i].access_flags, \
        __class->methods[i].name_index, \
        __class->methods[i].descriptor_index, \
        __class->methods[i].attributes_count \
    ); \
    bprint_attributes(__class->methods[i].attributes, __class->methods[i].attributes_count, "\t"); \
  } \
}

#define bprint_attributes_count(__class) printf("Attributes count: %d\n", __class->attributes_count)

#define bprint_attributes(__attributes, __attributes_count, __prefix) \
{ \
  printf(__prefix "Attributes:\n"); \
  for(int i = 0; i < __attributes_count; i++){ \
    printf( \
        __prefix "\tAttribute %d:\n" \
        __prefix "\tAttribute name index: %d\n" \
        __prefix "\tAttribute length: %d\n" \
        __prefix "\tInfo: \"", \
        i, __attributes[i].attribute_name_index, \
        __attributes[i].attribute_length \
    ); \
    for(int j = 0; j < __attributes[i].attribute_length; j++) \
      printf("%02x ", __attributes[i].info[j]); \
    printf("\b\"\n"); \
  } \
}


#endif
