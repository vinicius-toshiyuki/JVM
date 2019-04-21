#ifndef bprint_classfile_h
#define bprint_classfile_h

#include "breads.h"
#include "colors.h"
#include "attributes.h"
#include <string.h>

void bprint_classfile(ClassFile *class);
void bprint_info(cp_info *cp, const char *prefix);

#define bprint_magic(__class) printf("Magic number: 0x%x\n", __class->magic)

#define bprint_versions(__class) printf("Minor version: 0x%02x\nMajor version: 0x%02x\n", __class->minor_version, __class->major_version)

#define bprint_const_pool_count(__class) printf(BGC(182) "Constant pool count: %d" CLEARN, __class->const_pool_count)

#define bprint_constant_pool(__class) \
{ \
  printf(BGC(183) "Constant pool:" CLEARN); \
  for(int i = 0; i < __class->const_pool_count - 1; i++){ \
    printf("\t" BGC(189) "Tag %d: %d" CLEARN, i + 1, __class->constant_pool[i].tag); \
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

#define bprint_fields_count(__class) printf(BGC(211) "Fields count: %d" CLEARN, __class->fields_count)
  
#define bprint_fields(__class) \
{ \
  printf(BGC(210) "Fields:" CLEARN); \
  for(int i = 0; i < __class->fields_count; i++){ \
    printf( \
        "\t" BGC(218) "Field %d:" CLEARN \
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

#define bprint_methods_count(__class) printf(BGC(148) "Methods count: %d" CLEARN, __class->methods_count)

#define bprint_methods(__class) \
{ \
  printf(BGC(156) "Methods:" CLEARN); \
  for(int i = 0; i < __class->methods_count; i++){ \
    printf( \
        "\t" BGC(157) "Method %d:" CLEARN \
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

#define bprint_attributes_count(__class) printf(BGC(30) "Attributes count: %d" CLEARN, __class->attributes_count)

#define bprint_attributes(__attributes, __attributes_count, __prefix) \
{ \
  printf(__prefix BGC(38) "Attributes:" CLEARN); \
  for(int i = 0; i < __attributes_count; i++){ \
    printf( \
        __prefix "\t" BGC(45) "Attribute %d:" CLEARN \
        __prefix "\tAttribute name index: %d\n" \
        __prefix "\tAttribute length: %d\n" \
        __prefix "\tInfo: \"", \
        i, __attributes[i].attribute_name_index, \
        __attributes[i].attribute_length \
    ); \
    for(int j = 0; j < __attributes[i].attribute_length; j++){ \
      printf("%02x ", __attributes[i].info[j]); \
    } \
    printf("\b\"\n"); \
  } \
}
//bprint_attribute_info((&attibutes[i])) \



#define bprint_attribute_info(__attribute) \
{ 
  #ifndef ATT_C
  #define ATT_C 7
  #define MAX_ATT_S 20
  #endif
  // A atribuição tem que estar de acordo com a enum em attibutes.h
  char attributes_names[ATT_C][MAX_ATT_S] = {"Code", "ConstantValue", "Exceptions", "Deprecated", "SourceFile", "LineNumberTable", "LocalVariableTable"};
  for(int i = 0; i < ATT_C; i++)
    attributes_names[i][MAX_ATT_S - 1] = i;
  qsort(attributes_names, ATT_C, sizeof(char) * MAX_ATT_S, strcmp);

  // Pega o nome do attributo na constant pool como um vetor de u1
  u1 *att_name_bytes = class->constant_pool[__attribute->attribute_name_index - 1].info->Utf8->bytes;

  // Cria uma string a partir da stream de bytes com o nome do atributo
  char *att_name = (char *) calloc(__attribute_length + 1, sizeof(char));
  for(int i = 0; i < __attribute->attribute_length; i++)
    att_name[i] = (char) att_name_bytes[i];

  // Checa qual é o atributo
  int att_number = (int) (bsearch(att_name, attributes_names, ATT_C, sizeof(char) * MAX_ATT_S, strcmp))[MAX_ATT_S - 1];
  __attribute->att_info = (Attributes *) malloc(sizeof(Attributes)); // Union Attributes
  u1 *info = __attribute->info;
  switch(att_number){
    case NUMBER_Code:
      Code_attribute *__code = &__attribute->att_info->Code;
      __code->max_stack = (info[0] << 8) | info[1], info+= 2;
      __code->max_locals = (info[0] << 8) | info[1], info+= 2;
      __code->code_length = (info[0] << 24) | (info[1] << 16) | (info[2] << 8) | info[3], info += 4;
      __code->code = (u1 *) malloc(sizeof(u1) * __code->code_length);
      // Termina de ler o Code
      break;
    case NUMBER_ConstantValue:
      break;
    case NUMBER_Exceptions:
      break;
    case NUMBER_Deprecated:
      break;
    case NUMBER_SourceFile:
      break;
    case NUMBER_LineNumberTable:
      break;
    case LocalVariableTable:
      break;
  } 

  // Libera a string alocada
  free(att_name);
}


#endif
