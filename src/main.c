#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wchar.h>
#include <locale.h>

#include "../include/info.h"
#include "../include/classfile.h"
#include "../include/types.h"
#include "../include/breads.h"
#include "../include/errcodes.h"

int main(int argc, char **argv){
  if(argc < 2){
    fprintf(stderr, "Usage:\n\t%s <.class file name>\n", argv[0]);
    exit(ERR_NOFILE);
  }

  char *filename = argv[1];
  FILE *classfile = fopen(filename, "rb");

  ClassFile *class = (ClassFile *) malloc(sizeof(ClassFile));

  if(bread_magic(class, classfile)){
    free(class);
    fprintf(stderr, "Invalid .class file. Magic number \"0xcafebabe\" does not check.\n");
    exit(ERR_MAGIC);
  }

  bread_minor(class, classfile);
  bread_major(class, classfile);

  bread_constant_pool(class, classfile);

  int i;

  bread_access_flags(class, classfile);
  //bread_this_class(class, classfile);
  //bread_super_class(class, classfile);
  //bread_interfaces_count(class, classfile);

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
          "\t\tAttribute length: %d\n"
          "\t\tInfo: \"",
          j,
          att->attribute_name_index,
          att->attribute_length
      );
      int k;
      att->info = (u1 *) malloc(sizeof(u1) * att->attribute_length);
      for(k = 0; k < att->attribute_length; k++){
        u1_read(att->info[k], classfile);
        printf("%02x ", att->info[k]);
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











