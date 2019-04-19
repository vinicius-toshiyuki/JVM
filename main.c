#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "info.h"
#include "classfile.h"
#include "types.h"
#include <unistd.h>

#define u1_read(buffer, file) { fread(&buffer, sizeof(u1), 1, file); }
/* #define u4_read(buffer, file) { fread(&buffer, sizeof(u4), 1, file); } antigo u4_read */
/* Por algum motivo não funciona com um for em algum caso: zera o valor de buffer ao final ou até deu segmentation fault */
#define u2_read(buffer, file) \
{ \
  buffer = 0x0000; \
  u1 byte; \
  u1_read(byte, file); \
  buffer |= byte; \
  u1_read(byte, file); \
  buffer = (buffer << 8) | byte; \
}
#define u4_read(buffer, file) { int __i; for(__i = 0; __i < 4; __i++){u1 byte; u1_read(byte, file); buffer <<= __i == 0 ? 0 : 8; buffer |= byte;} }

int main(int argc, char **argv){
  if(argc < 2){
    fprintf(stderr, "Faltou o arquivo\n");
    exit(-1);
  }
  char *filename = argv[1];
  FILE *classfile = fopen(filename, "rb");

  ClassFile *class = (ClassFile *) malloc(sizeof(ClassFile));

  u4_read(class->magic, classfile);
  u2_read(class->minor_version, classfile);
  u2_read(class->major_version, classfile);
  u2_read(class->const_pool_count, classfile);
  printf(
    "Magic: 0x%x\n"
    "Minor: 0x%x\n"
    "Major: 0x%x\n"
    "CPC: %d\n",
    class->magic,
    class->minor_version,
    class->major_version,
    class->const_pool_count
  );
  class->constant_pool = (cp_info *) malloc(sizeof(cp_info) * (class->const_pool_count - 1));
  //return 0;
  int i;
  for(i = 0; i < class->const_pool_count - 1; i++){
    cp_info *cp = &(class->constant_pool[i]);
  //for(cp_info *cp = class->constant_pool; cp < cp + class->const_pool_count; cp++){
    u1_read(cp->tag, classfile);
    printf("\e[48;5;221mTag %d: %d\e[0m\n", i + 1, cp->tag);
    switch(cp->tag){
      case CONSTANT_Class:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Class.tag, classfile);
        u2_read(cp->info->Class.name_index, classfile);
        printf(
            "\tName index: %d\n",
            cp->info->Class.name_index
        );
        break;
      case CONSTANT_Fieldref:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Fieldref.tag, classfile);
        u2_read(cp->info->Fieldref.class_index, classfile);
        u2_read(cp->info->Fieldref.name_and_type_index, classfile);
        printf(
            "\tClass index: %d\n"
            "\tName and type index: %d\n",
            cp->info->Fieldref.class_index,
            cp->info->Fieldref.name_and_type_index
        );
        break;
      case CONSTANT_Methodref:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Methodref.tag, classfile);
        u2_read(cp->info->Methodref.class_index, classfile);
        u2_read(cp->info->Methodref.name_and_type_index, classfile);
        printf(
            "\tTag: %d\n"
            "\tClass index: %d\n"
            "\tName and type index: %d\n",
            cp->info->Methodref.tag,
            cp->info->Methodref.class_index,
            cp->info->Methodref.name_and_type_index
        );
        break;
      case CONSTANT_InterfaceMethodref:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->InterfaceMethodref.tag, classfile);
        u2_read(cp->info->InterfaceMethodref.class_index, classfile);
        u2_read(cp->info->InterfaceMethodref.name_and_type_index, classfile);
        printf(
            "\tClass index: %d\n"
            "\tName and type index: %d\n",
            cp->info->InterfaceMethodref.class_index,
            cp->info->InterfaceMethodref.name_and_type_index
        );
        break;
      case CONSTANT_String:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->String.tag, classfile);
        u2_read(cp->info->String.string_index, classfile);
        printf(
            "\tString index: %d\t",
            cp->info->String.string_index
        );
        break;
      case CONSTANT_Integer:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Integer.tag, classfile);
        u4_read(cp->info->Integer.bytes, classfile);
        printf(
            "\tBytes: %d\n",
            cp->info->Integer.bytes
        );
        break;
      case CONSTANT_Float:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Float.tag, classfile);
        u4_read(cp->info->Float.bytes, classfile);
        printf(
            "\tBytes: %f\n",
            (float) cp->info->Float.bytes
        );
        break;
      case CONSTANT_Long:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Long.tag, classfile);
        u4_read(cp->info->Long.high_bytes, classfile);
        u4_read(cp->info->Long.low_bytes, classfile);
        printf(
            "\tHigh bytes: 0x%x\n"
            "\tLow bytes: 0x%x\n",
            cp->info->Long.high_bytes,
            cp->info->Long.low_bytes
        );
        break;
      case CONSTANT_Double:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Double.tag, classfile);
        u4_read(cp->info->Double.high_bytes, classfile);
        u4_read(cp->info->Double.low_bytes, classfile);
        printf(
            "\tHigh bytes: 0x%x\n"
            "\tLow bytes: 0x%x\n",
            cp->info->Double.high_bytes,
            cp->info->Double.low_bytes
        );
        break;
      case CONSTANT_NameAndType:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->NameAndType.tag, classfile);
        u2_read(cp->info->NameAndType.name_index, classfile);
        u2_read(cp->info->NameAndType.descriptor_index, classfile);
        printf(
            "\tName index: %d\n"
            "\tDescriptor index: %d\n",
            cp->info->NameAndType.name_index,
            cp->info->NameAndType.descriptor_index
        );
        break;
      case CONSTANT_Utf8:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Utf8.tag, classfile);
        u2_read(cp->info->Utf8.length, classfile);
        printf("\tLength: %d\n\tBytes: \"", cp->info->Utf8.length);
        cp->info->Utf8.bytes = (u1 *) malloc(sizeof(u1) * cp->info->Utf8.length);
        int i;
        for(i = 0; i < cp->info->Utf8.length; i++){
          u1_read(cp->info->Utf8.bytes[i], classfile);
          printf("%c", cp->info->Utf8.bytes[i]);
        }
        printf("\"\n");
        break;
      }
  }
  u2_read(class->access_flags, classfile);
  u2_read(class->this_class, classfile);
  u2_read(class->super_class, classfile);
  u2_read(class->interfaces_count, classfile);
  printf(
      "Access flags: 0x%x\n"
      "This class: %d\n"
      "Super class: %d\n"
      "Interfaces count: %d\n",
      class->access_flags,
      class->this_class,
      class->super_class,
      class->interfaces_count
  );
  class->interfaces = (u2 *) malloc(sizeof(u2) * class->interfaces_count);
  for(i = 0; i < class->interfaces_count; i++){
    u2_read(class->interfaces[i], classfile);
    printf(
        "\e[48;5;189mInterface %d:\n"
        "\tClass index: %d\n",
        i, class->interfaces[i]
    );
  }
  u2_read(class->fields_count, classfile);
  printf("Fields count: %d\n", class->fields_count);
  class->fields = (field_info *) malloc(sizeof(field_info) * class->fields_count);
 /* while(!feof(classfile)){
    u2 byte;
    u2_read(byte, classfile);
    printf("%x ", byte);
  }
  printf("\b\n");
  return 0;*/
  for(i = 0; i < class->fields_count; i++){
    u2_read(class->fields[i].access_flags, classfile);
    u2_read(class->fields[i].name_index, classfile);
    u2_read(class->fields[i].descriptor_index, classfile);
    u2_read(class->fields[i].attributes_count, classfile);
    printf(
        "\e[48;5;189mField %d:\e[0m\n"
        "\tAccess flags: 0x%x\n"
        "\tName index: %d\n"
        "\tDescriptor index: %d\n"
        "\tAttributes count: %d\n",
        i,
        class->fields[i].access_flags,
        class->fields[i].name_index,
        class->fields[i].descriptor_index,
        class->fields[i].attributes_count
    );
    class->fields[i].attributes = (attribute_info *) malloc(sizeof(attribute_info) * class->fields[i].attributes_count);
    int j;
    for(j = 0; j < class->fields[i].attributes_count; j++){
      attribute_info *att = &(class->fields[i].attributes[j]);
      u2_read(att->attribute_name_index, classfile);
      u4_read(att->attribute_length, classfile);
      printf(
          "\tAttribute %d:\n"
          "\t\tAttribute name index: %d\n"
          "\t\tAttribute length: %d\n\t\tInfo: \"",
          j,
          att->attribute_name_index,
          att->attribute_length
      );
      int k;
      att->info = (u1 *) malloc(sizeof(u1) * att->attribute_length);
      for(k = 0; k < att->attribute_length; k++){
        u1_read(att->info[k], classfile);
        printf("%c", att->info[k]);
      }
      printf("\"\n");
    }
  }

  /* Methods */
  u2_read(class->methods_count, classfile);
  printf("Methods count: %d\n", class->methods_count);
  class->methods = (method_info *) malloc(sizeof(method_info) * class->methods_count);
  for(i = 0; i < class->methods_count; i++){
    u2_read(class->methods[i].access_flags, classfile);
    u2_read(class->methods[i].name_index, classfile);
    u2_read(class->methods[i].descriptor_index, classfile);
    u2_read(class->methods[i].attributes_count, classfile);
    printf(
        "Method %d:\n"
        "\tAccess flags: 0x%x\n"
        "\tName index: %d\n"
        "\tDescriptor index: %d\n"
        "\tAttributes count: %d\n",
        i,
        class->methods[i].access_flags,
        class->methods[i].name_index,
        class->methods[i].descriptor_index,
        class->methods[i].attributes_count
    );
    class->methods[i].attributes = (attribute_info *) malloc(sizeof(attribute_info) * class->methods[i].attributes_count);
    int j;
    for(j = 0; j < class->methods[i].attributes_count; j++){
      u2_read(class->methods[i].attributes[j].attribute_name_index, classfile);
      u4_read(class->methods[i].attributes[j].attribute_length, classfile);
      printf(
          "\tAttribute %d:\n"
          "\t\tAttribute name index: %d\n"
          "\t\tAttribute length: %d\n"
          "\t\tInfo: \"",
          j,
          class->methods[i].attributes[j].attribute_name_index,
          class->methods[i].attributes[j].attribute_length
      );
      class->methods[i].attributes[j].info = (u1 *) malloc(sizeof(u1) * class->methods[i].attributes[j].attribute_length);
      int k;
      for(k = 0; k < class->methods[i].attributes[j].attribute_length; k++){
        u1_read(class->methods[i].attributes[j].info[k], classfile);
        printf("%02x ", class->methods[i].attributes[j].info[k]);
      }
      printf("\b\"\n");
    }
  }

  /* Attributes */
  u2_read(class->attributes_count, classfile);
  printf("Attributes count: %d\n", class->attributes_count);
  class->attributes = (attribute_info *) malloc(sizeof(attribute_info) * class->attributes_count);
  for(i = 0; i < class->attributes_count; i++){
    u2_read(class->attributes[i].attribute_name_index, classfile);
    u4_read(class->attributes[i].attribute_length, classfile);
    printf(
        "Attribute %d:\n"
        "\tAttribute name index: %d\n"
        "\tAttribute length: %d\n"
        "\tInfo: \"",
        i,
        class->attributes[i].attribute_name_index,
        class->attributes[i].attribute_length
    );
    class->attributes[i].info = (u1 *) malloc(sizeof(u1) * class->attributes[i].attribute_length);
    int j;
    for(j = 0; j < class->attributes[i].attribute_length; j++){
      u1_read(class->attributes[i].info[j], classfile);
      printf("%02x ", class->attributes[i].info[j]);
    }
    printf("\b\"\n");
  }
  return 0;
}











