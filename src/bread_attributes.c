#include "../include/bread_attributes.h"
#include "../include/bprint_classfile.h"

extern int VERBOSE;

void bread_attributes(attribute_info *atts, int atts_count, FILE *classfile, ClassFile *class){
  for(int i = 0; i < atts_count; i++){
      u2_read(atts[i].attribute_name_index, classfile);
      u4_read(atts[i].attribute_length, classfile);

      atts[i].info = (u1 *) malloc(sizeof(u1) * atts[i].attribute_length);
      for(int j = 0; j < atts[i].attribute_length; j++)
         u1_read(atts[i].info[j], classfile);
			bread_att_info(atts[i].info[i], atts[i].attribute_name_index, class);
  }
  return;
}

void bread_att_info(u1 *u1_stream, int name_index, ClassFile *class){
  static char attributes_types[ATT_C][ATT_M_S] = {
		"Code",
		"ConstantValue",
		"Deprecated",
		"Exceptions",
		"LineNumberTable",
		"LocalVariableTable",
		"SourceFile"
	}, att_type_value_assign = 1;

  static int lookup = 0;

  if(att_type_value_assign){
    att_type_value_assign = 0;
    /* A enum NUMBERS tem que estar de acordo com essa numeração */
    for(int i = 0; i < ATT_C; i++)
      attributes_types[i][ATT_M_S - 1] = i;
    if(VERBOSE) printf(BGC(127) FGC(83) "%sSetting attributes array" CLEARN, prefix);
  }
  
	/* Pega o nome do atributo e vê qual é*/
  char *str_name = (char *) calloc(ATT_M_S - 1, sizeof(char));
  memcpy(str_name, class->constant_pool[name_index - 1].info->Utf8.bytes, class->constant_pool[name_index - 1].info->Utf8.length);
  void *bsearch_result = bsearch(str_name, attributes_types, ATT_C, ATT_M_S, (int (*)(const void *, const void *)) strcmp);
  int number_code = bsearch_result != NULL ? ((char *) bsearch_result)[ATT_M_S - 1] : NUMBER_Invalid;
  free(str_name);

  Attributes att_info;
  switch(number_code){
    case NUMBER_Code:
      u1_to_Code(att_info.Code, u1_stream);
      break;
    case NUMBER_ConstantValue:
      u1_to_ConstantValue(att_info.ConstantValue, u1_stream);
      break;
    case NUMBER_Deprecated: /* Tem nada */
      break;
    case NUMBER_Exceptions:
      u1_to_Exceptions(att_info.Exceptions, u1_stream);
    case NUMBER_LineNumberTable:
      u1_to_LineNumberTable(att_info.LineNumberTable, u1_stream);
      break;
    case NUMBER_LocalVariableTable:
      u1_to_LocalVariableTable(att_info.LocalVariableTable, u1_stream);
      break;
    case NUMBER_SourceFile:
      u1_to_SourceFile(att_info.SourceFile, u1_stream);
      break;
    default:
      break;
  }
  return;
}
