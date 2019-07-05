#ifndef bprint_classfile_h
#define bprint_classfile_h

#include "breads.h"
#include "colors.h"
#include "attributes.h"
#include <string.h>

void bprint_classfile(ClassFile *class);
int bprint_info(ClassFile *class, int index, const char *prefix, int inner);
void bprint_att_info(u1 *u1_stream, int name_index, ClassFile *class, const char prefix[]);
int charcmp(const void *a, const void *b);

enum {
	ACC_PUBLIC     = 0x0001,
	ACC_PRIVATE    = 0x0002,
	ACC_PROTECTED  = 0x0004,
	ACC_STATIC     = 0x0008,
	ACC_FINAL      = 0x0010,
	ACC_SUPER      = 0x0020,
	ACC_VOLATILE   = 0x0040,
	ACC_TRANSIENT  = 0x0080,
	ACC_INTERFACE  = 0x0200,
	ACC_ABSTRACT   = 0x0400,
	ACC_SYNTHETIC  = 0x1000,
	ACC_ANNOTATION = 0x2000,
	ACC_ENUM       = 0x4000
} ACCESS_FLAGS;

#define ATT_C 7
#define ATT_M_S 20

#define u2_flip(__bytes) __bytes = (__bytes << 8) | (__bytes >> 8)

#define u4_flip(__bytes) \
{ \
  u2 __a = __bytes; u2_flip(__a); \
  u2 __b = __bytes >> 16; u2_flip(__b); \
  __bytes = (__a << 16) | __b; \
}

#define bprint_magic(__class) printf("Magic number: 0x%x\n", __class->magic)

#define bprint_versions(__class) printf("Minor version: %d\nMajor version: %d\nJava version: %s\n", __class->minor_version, __class->major_version, java_version[__class->major_version])

#define bprint_const_pool_count(__class) printf(BGC(226) FGC(88) "Constant pool count: %d" CLEARN, __class->const_pool_count)

#define bprint_constant_pool(__class) \
{ \
  printf(BGC(226) FGC(88) "Constant pool:" CLEARN); \
  for(int i = 0; i < __class->const_pool_count - 1; i++){ \
		printf(BGC(10) FGC(1) "Tag %d: ", i + 1); \
    bprint_info(__class, i, "\t", 0); \
  } \
}

static inline void bprint_access_flags(u2 af){
	printf("Access flags: 0x%04x (", af);

	if(af & ACC_PUBLIC)     printf ("Public ");
	if(af & ACC_PRIVATE)    printf ("Private ");
	if(af & ACC_PROTECTED)  printf ("Protected ");
	if(af & ACC_STATIC)     printf ("Static ");
	if(af & ACC_FINAL)      printf ("Final ");
	if(af & ACC_SUPER)      printf ("Super ");
	if(af & ACC_VOLATILE)   printf ("Volatile ");
	if(af & ACC_TRANSIENT)  printf ("Transient ");
	if(af & ACC_INTERFACE)  printf ("Interface ");
	if(af & ACC_ABSTRACT)   printf ("Abstract ");
	if(af & ACC_SYNTHETIC)  printf ("Synthetic ");
	if(af & ACC_ANNOTATION) printf ("Annotation ");
	if(af & ACC_ENUM)       printf ("Enum ");

	printf("\b)\n");
	return;
}

#define bprint_this_class(__class) printf("This class: %d ", __class->this_class); bprint_info(__class, __class->this_class - 1, "\t", 0)

#define bprint_super_class(__class) printf("Super class: %d ", __class->super_class); bprint_info(__class, __class->super_class - 1, "\t", 0)

#define bprint_interfaces_count(__class) printf("Interfaces count: %d\n", __class->interfaces_count)

#define bprint_interfaces(__class) \
{ \
  printf("Interfaces:\n"); \
  for(int i = 0; i < __class->interfaces_count; i++){ \
    printf("\tInterface %d: %d ", i, __class->interfaces[i]); \
		bprint_info(__class, __class->interfaces[i] - 1, "\t", 0); \
	} \
}

#define bprint_fields_count(__class) printf(BGC(211) FGC(51) "Fields count: %d" CLEARN, __class->fields_count)
  
#define bprint_fields(__class) \
{ \
  printf(BGC(210) FGC(51) "Fields:" CLEARN); \
  for(int i = 0; i < __class->fields_count; i++){ \
    printf("\t" BGC(218) FGC(51) "Field %d:" CLEARN "\t", i); \
		bprint_access_flags(__class->fields[i].access_flags); \
		printf("\tName index: %d ", __class->fields[i].name_index); \
		bprint_info(__class, __class->fields[i].name_index - 1, "\t\t", 0); \
		printf("\tDescriptor index: %d ", __class->fields[i].descriptor_index); \
		bprint_info(__class, __class->fields[i].descriptor_index - 1, "\t\t", 0); \
		printf("\tAttributes count: %d\n", __class->fields[i].attributes_count); \
    bprint_attributes(__class->fields[i].attributes, __class->fields[i].attributes_count, "\t"); \
  } \
}

#define bprint_methods_count(__class) printf(BGC(148) FGC(166) "Methods count: %d" CLEARN, __class->methods_count)

#define bprint_methods(__class) \
{ \
  printf(BGC(156) FGC(166) "Methods:" CLEARN); \
  for(int i = 0; i < __class->methods_count; i++){ \
    printf("\t" BGC(157) FGC(166) "Method %d:" CLEARN "\t", i); \
		bprint_access_flags(__class->methods[i].access_flags); \
		printf("\tName index: %d ", __class->methods[i].name_index); \
		bprint_info(__class, __class->methods[i].name_index - 1, "\t\t", 0); \
    printf("\tDescriptor index: %d ", __class->methods[i].descriptor_index); \
		bprint_info(__class, __class->methods[i].descriptor_index - 1, "\t\t", 0); \
    printf("\tAttributes count: %d\n", __class->methods[i].attributes_count);\
    bprint_attributes(__class->methods[i].attributes, __class->methods[i].attributes_count, "\t"); \
  } \
}

#define bprint_attributes_count(__class) printf(BGC(30) FGC(47) "Attributes count: %d" CLEARN, __class->attributes_count)

#define bprint_attributes(__attributes, __attributes_count, __prefix) \
{ \
  printf(__prefix BGC(38) FGC(22) "Attributes:" CLEARN); \
  for(int j = 0; j < __attributes_count; j++){ \
    printf( \
        __prefix "\t" BGC(45) FGC(29) "Attribute %d:" CLEARN \
        __prefix "\tAttribute name index: %d ", \
        j, __attributes[j].attribute_name_index \
		); \
		bprint_info(class, __attributes[j].attribute_name_index - 1, __prefix "\t\t", 0); \
		printf( \
        __prefix "\tAttribute length: %d\n", \
        __attributes[j].attribute_length \
    ); \
    /* Procurar o tipo do atributo com o name_index na constant_pool */ \
    /* Escolher o elemento certo da union Attributes */ \
    /* Imprimir os elementos */ \
    /* E quando o elemento for um attribute_info? */ \
    /* {"Code", "ConstantValue", "Deprecated", "Exceptions", "LineNumberTable", "LocalVariableTable", "SourceFile"}; */ \
    bprint_att_info(__attributes[j].info, __attributes[j].attribute_name_index, class, __prefix "\t"); \
  } \
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
	printf("Parado antes do memcpy\n");\
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
		case CONSTANT_Float: \
      printf("%sBytes: %d\n", prefix, cp->info->Integer.bytes); \
      break; \
		case CONSTANT_Long: \
      printf( \
          "%sHigh bytes: 0x%08x\n%sLow bytes: 0x%08x\n", \
          prefix, cp->info->Long.high_bytes, \
          prefix, cp->info->Long.low_bytes \
      ); \
      break; \
		case CONSTANT_Double: \
      printf( \
          "%sHigh bytes: 0x%08x\n%sLow bytes: 0x%08x\n", \
          prefix, cp->info->Long.high_bytes, \
          prefix, cp->info->Long.low_bytes \
      ); \
      break; \
	} \
}
#endif
