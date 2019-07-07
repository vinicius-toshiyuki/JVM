#include "../include/attributes.h"
#include "../include/classfile.h"
#include <stdlib.h>
#include <string.h>

void get_attribute_from_info(u1 *info, Attributes *att_info, u2 name_index, ClassFile *class){
  static char attributes_types[ATT_C][ATT_M_S] = {
		"Code",
		"ConstantValue",
		"Deprecated",
		"Exceptions",
		"LineNumberTable",
		"LocalVariableTable",
		"SourceFile"
	}, att_type_value_assign = 1;

  if(att_type_value_assign){
    att_type_value_assign = 0;
    for(int i = 0; i < ATT_C; i++)
      attributes_types[i][ATT_M_S - 1] = i;
  }
  
	/* Pega o nome do atributo e vê qual é*/
  char *str_name = (char *) calloc(ATT_M_S - 1, sizeof(char));
  memcpy(str_name, class->constant_pool[name_index - 1].info->Utf8.bytes, class->constant_pool[name_index - 1].info->Utf8.length);
  void *bsearch_result = bsearch(str_name, attributes_types, ATT_C, ATT_M_S, (int (*)(const void *, const void *)) strcmp);
  int number_code = bsearch_result != NULL ? ((char *) bsearch_result)[ATT_M_S - 1] : NUMBER_Invalid;
  free(str_name);

  switch(number_code){
    case NUMBER_Code:
      u1_to_Code(att_info->Code, info);
      break;
    case NUMBER_ConstantValue:
      u1_to_ConstantValue(att_info->ConstantValue, info);
      break;
    case NUMBER_Deprecated: /* Tem nada */
      break;
    case NUMBER_Exceptions:
      u1_to_Exceptions(att_info->Exceptions, info);
			break;
    case NUMBER_LineNumberTable:
      u1_to_LineNumberTable(att_info->LineNumberTable, info);
      break;
    case NUMBER_LocalVariableTable:
      u1_to_LocalVariableTable(att_info->LocalVariableTable, info);
      break;
    case NUMBER_SourceFile:
      u1_to_SourceFile(att_info->SourceFile, info);
      break;
    default:
      break;
  }
	return;
}
