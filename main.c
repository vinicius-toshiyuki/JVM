#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "info.h"
#include "classfile.h"
#include "types.h"

#define u1_read(buffer, file) { fread(&buffer, sizeof(u1), 1, file); }
#define u4_read(buffer, file) { fread(&buffer, sizeof(u4), 1, file); }
#define u2_read(buffer, file) { int i; for(i = 0; i < 2; i++){u1 byte; u1_read(byte, file); buffer <<= i == 0 ? 0 : 8; buffer |= byte;} }
#define magic_read(buffer, file) { int i; for(i = 0; i < 4; i++){u1 byte; u1_read(byte, file); buffer <<= i == 0 ? 0 : 8; buffer |= byte;} }

int main(int argc, char **argv){
  if(argc < 2){
    fprintf(stderr, "Faltou o arquivo\n");
    exit(-1);
  }
  char *filename = argv[1];
  FILE *classfile = fopen(filename, "rb");

  ClassFile *class = (ClassFile *) malloc(sizeof(ClassFile));

  magic_read(class->magic, classfile);
  u2_read(class->minor_version, classfile);
  u2_read(class->major_version, classfile);
  u2_read(class->const_pool_count, classfile);
  printf(
    "Cafe: 0x%x\n"
    "Minor: 0x%x\n"
    "Major: 0x%x\n"
    "CPC: 0x%x\n",
    class->magic,
    class->minor_version,
    class->major_version,
    class->const_pool_count
  );
  class->constant_pool = (cp_info *) malloc(sizeof(cp_info) * class->const_pool_count);
  //return 0;
  int i;
  for(i = 0; i < class->const_pool_count - 1; i++){
    cp_info *cp = &(class->constant_pool[i]);
  //for(cp_info *cp = class->constant_pool; cp < cp + class->const_pool_count; cp++){
    u1_read(cp->tag, classfile);
    printf("\e[48;5;221mTag %d: %d\e[0m\n", i, cp->tag);
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
            "\Name and type index: %d\n",
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
            cp->info->Float.bytes
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
  for(i = 0; i < class->fields_count; i++){
    u2_read(class->fields[i].access_flags, classfile);
    u2_read(class->fields[i].name_index, classfile);
    u2_read(class->fields[i].descriptor_index, classfile);
    u2_read(class->fields[i].attributes_count, classfile);
    class->fields[i].attributes = (attribute_info *) malloc(sizeof(attribute_info) * class->fields[i].attributes_count);
    int j;
    for(j = 0; j < class->fields[i].attributes_count; j++){
      attribute_info *att = &(class->fields[i].attributes[j]);
      u2_read(att->attribute_name_index, classfile);
      u4_read(att->attribute_length, classfile);
      int k;
      att->info = (u1 *) malloc(sizeof(u1) * att->attribute_length);
      for(k = 0; k < att->attribute_length; k++){
        u1_read(att->info[k], classfile);
      }
    }
  }
  u2_read(class->methods_count, classfile);


  return 0;
}
