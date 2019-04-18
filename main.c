#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

#define u1_read(buffer, file) { fread(&buffer, sizeof(u1), 1, file); }
//#define u2_read(buffer, file) { fread(&buffer, sizeof(u2), 1, file); }
#define u4_read(buffer, file) { fread(&buffer, sizeof(u4), 1, file); }
#define magic_read(buffer, file) { int i; for(i = 0; i < 4; i++){u1 byte; u1_read(byte, file); buffer <<= i == 0 ? 0 : 8; buffer |= byte;} }
#define u2_read(buffer, file) { int i; for(i = 0; i < 2; i++){u1 byte; u1_read(byte, file); buffer <<= i == 0 ? 0 : 8; buffer |= byte;} }

typedef struct {
  u1 tag;
  u1 *info;
} cp_info;

typedef struct {

} field_info;

typedef struct {

} method_info;

typedef struct {

} attribute_info;

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
  class->constant_pool = (cp_info *) malloc(sizeof(cp_info) * class->const_pool_count);
  for(int i = 0; i < class->const_pool_count; i++){

  }

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

  return 0;
}
