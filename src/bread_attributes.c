#include "../include/bread_attributes.h"
#include "../include/bprint_classfile.h"

extern int verbose;

void bread_attributes(attribute_info *atts, int atts_count, FILE *classfile){

  for(int i = 0; i < atts_count; i++){
      u2_read(atts[i].attribute_name_index, classfile);
      u4_read(atts[i].attribute_length, classfile);

      atts[i].info = (u1 *) malloc(sizeof(u1) * atts[i].attribute_length);
      for(int j = 0; j < atts[i].attribute_length; j++)
        u1_read(atts[i].info[j], classfile);
  }

  return;
}
/*
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
      for(int i = 0; i < __code->code_length; i++)
        __code->code[i] = info[0], info++;
      __code->exception_table_length = (info[0] << 8) | info[1], info += 2;
      __code->exception_table = (exceptions_info *) malloc(sizeof(exceptions_info) * __code->exception_table_length);
      for(int i = 0; i < __code->exception_table_length; i++){
        __code->exception_table[i].start_pc = (info[0] << 8) | info[1], info +=2;
        __code->exception_table[i].end_pc = (info[0] << 8) | info[1], info +=2;
        __code->exception_table[i].handler_pc = (info[0] << 8) | info[1], info +=2;
        __code->exception_table[i].catch_type = (info[0] << 8) | info[1], info +=2;
      }
      __code->attributes_count = (info[0] << 8) | info[1], info += 2;
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


*/
