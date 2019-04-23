#include "../include/bprint_classfile.h"
#include "../include/mnemonic.h"

extern char * opcode_to_mnemonic[0x100];

void bprint_classfile(ClassFile *class){
  bprint_magic(class);
  bprint_versions(class);
  bprint_const_pool_count(class);
  bprint_constant_pool(class);
  bprint_access_flags(class);
  bprint_this_class(class);
  bprint_super_class(class);
  bprint_interfaces_count(class);
  bprint_interfaces(class);
  bprint_fields_count(class);
  bprint_fields(class);
  bprint_methods_count(class);
  bprint_methods(class);
  bprint_attributes_count(class);
  bprint_attributes(class->attributes, class->attributes_count, "");
  return;
}

void bprint_info(cp_info *cp, const char *prefix){
  switch(cp->tag){
    case CONSTANT_Class:
      printf("%sName index: %d\n", prefix, cp->info->Class.name_index);
      break;
    case CONSTANT_Fieldref:
    case CONSTANT_Methodref:
    case CONSTANT_InterfaceMethodref:
      printf(
          "%sClass index: %d\n%sName and type index: %d\n",
          prefix, cp->info->Fieldref.class_index,
          prefix, cp->info->Fieldref.name_and_type_index
      );
      break;
    case CONSTANT_String:
      printf("%sString index: %d\n", prefix, cp->info->String.string_index);
      break;
    case CONSTANT_Integer:
    case CONSTANT_Float:
      printf("%sBytes: %d\n", prefix, cp->info->Integer.bytes);
      break;
    case CONSTANT_Long:
    case CONSTANT_Double:
      printf(
          "%sHigh bytes: 0x%08x\n%sLow bytes: 0x%08x\n",
          prefix, cp->info->Long.high_bytes,
          prefix, cp->info->Long.low_bytes
      );
      break;
    case CONSTANT_NameAndType:
      printf(
          "%sName index: %d\n%sDescripitor index: %d\n",
          prefix, cp->info->NameAndType.name_index,
          prefix, cp->info->NameAndType.descriptor_index
      );
      break;
    case CONSTANT_Utf8:
      printf("%sLength: %d\n%sBytes: \"", prefix, cp->info->Utf8.length, prefix);
      for(int i = 0; i < cp->info->Utf8.length; i++)
        printf("%c", cp->info->Utf8.bytes[i]);
      printf("\"\n");
      /*  printf("%02x ", cp->info->Utf8.bytes[i]);
      printf("\b\"\n");*/
      break;
  }
  return;
}

void bprint_att_info(u1 *u1_stream, int name_index, ClassFile *class, const char prefix[]){
  static char attributes_types[ATT_C][ATT_M_S] = {"Code", "ConstantValue", "Deprecated", "Exceptions", "LineNumberTable", "LocalVariableTable", "SourceFile"};
  #ifndef att_type_value_assign
  #define att_type_value_assign
    // A enum NUMBERS tem que estar de acordo com essa numeração
    for(int i = 0; i < ATT_C; i++)
      attributes_types[i][ATT_M_S - 1] = i;
  #endif
  // Busca nome do atributo com o name_index na constant_pool
  
  char str_name[ATT_M_S] = {[0 ... ATT_M_S - 1] = '\0'};
  memcpy(str_name, class->constant_pool[name_index - 1].info->Utf8.bytes  /*Bytes do nome do atributo*/, class->constant_pool[name_index - 1].info->Utf8.length);
  int number_code = ((char *) (bsearch(str_name, attributes_types, ATT_C, ATT_M_S, (int (*)(const void *, const void *)) strcmp)))[ATT_M_S - 1];

  printf(BGC(27) "%s%s attribute:" CLEARN, prefix, str_name);

  Attributes att_info;
  switch(number_code){ // Vou para o código correto para imprimir o atributo
    case NUMBER_Code:
      u1_to_Code(att_info.Code, u1_stream);
      printf(
          "%s\tMax stack: %d\n"
          "%s\tMax locals: %d\n"
          "%s\tCode length: %d\n"
          "%s\tCode: \"",
          prefix, att_info.Code.max_stack,
          prefix, att_info.Code.max_locals,
          prefix, att_info.Code.code_length, prefix
      );
      for(int i = 0; i < att_info.Code.code_length; i++)
        printf("%02x ", att_info.Code.code[i]);
      printf("\b\"\n");
      printf("%s\n", opcode_to_mnemonic[att_info.Code.code[0]]);
      printf(
          "%s\tException table length: %d\n"
          "%s\tException table:\n",
          prefix, att_info.Code.exception_table_length, prefix
      );
      for(int i = 0; i < att_info.Code.exception_table_length; i++)
          printf(
              "%s\t\tException %d:\n"
              "%s\t\tStart PC: 0x%08x\n"
              "%s\t\tEnd PC: 0x%08x\n"
              "%s\t\tHandler PC: 0x%08x\n"
              "%s\t\tCatch type: %d\n",
              prefix, i,
              prefix, att_info.Code.exception_table[i].start_pc,
              prefix, att_info.Code.exception_table[i].end_pc,
              prefix, att_info.Code.exception_table[i].handler_pc,
              prefix, att_info.Code.exception_table[i].catch_type
          );
      printf(
          "%s\tAttributes count: %d\n",
          prefix, att_info.Code.attributes_count
      );
      char *att_prefix = (char *) calloc(strlen(prefix) + 3, sizeof(char));
      att_prefix[0] = '\t', att_prefix[1] = '\t';
      strcat(att_prefix, prefix);
      for(int i = 0; i < att_info.Code.attributes_count; i++)
        bprint_att_info(att_info.Code.attributes[i].info, att_info.Code.attributes[i].attribute_name_index, class, att_prefix);
      break;
    case NUMBER_ConstantValue:
      u1_to_ConstantValue(att_info.ConstantValue, u1_stream);
      printf("%s\tConstant value index: %d\n", prefix, att_info.ConstantValue.constantvalue_index);
      break;
    case NUMBER_Deprecated: /* Tem nada */
      break;
    case NUMBER_Exceptions:
      u1_to_Exceptions(att_info.Exceptions, u1_stream);
      printf(
          "%s\tNumber of exceptions: %d\n"
          "%s\tException index table:\n",
          prefix, att_info.Exceptions.number_of_exceptions, prefix
      );
      for(int i = 0; i < att_info.Exceptions.number_of_exceptions; i++)
        printf(
            "%s\t\tException %d: %d\n",
            prefix, i, att_info.Exceptions.exception_index_table[i]
        );
      break;
    case NUMBER_LineNumberTable:
      u1_to_LineNumberTable(att_info.LineNumberTable, u1_stream);
      printf(
          "%s\tLine number table length: %d\n"
          "%s\tLine number table:\n",
          prefix, att_info.LineNumberTable.line_number_table_length, prefix
      );
      for(int i = 0; i < att_info.LineNumberTable.line_number_table_length; i++)
        printf(
            "%s\t\tLine number %d:\n"
            "%s\t\tStart PC: 0x%04x\n"
            "%s\t\tLine number: %d\n",
            prefix, i,
            prefix, att_info.LineNumberTable.line_number_table[i].start_pc,
            prefix, att_info.LineNumberTable.line_number_table[i].line_number
        );
      break;
    case NUMBER_LocalVariableTable:
      u1_to_LocalVariableTable(att_info.LocalVariableTable, u1_stream);
      printf(
          "%s\tLocal variable table length: %d\n"
          "%s\tLocal variable table:\n",
          prefix, att_info.LocalVariableTable.local_variable_table_length, prefix
      );
      for(int i = 0; i < att_info.LocalVariableTable.local_variable_table_length; i++)
        printf(
            "%s\t\tLocal variable %d:\n"
            "%s\t\tStart PC: 0x%04x\n"
            "%s\t\tLength: %d\n"
            "%s\t\tName index: %d\n"
            "%s\t\tDescriptor index: %d\n"
            "%s\t\tIndex: %d\n",
            prefix, i,
            prefix, att_info.LocalVariableTable.local_variable_table[i].start_pc,
            prefix, att_info.LocalVariableTable.local_variable_table[i].length,
            prefix, att_info.LocalVariableTable.local_variable_table[i].name_index,
            prefix, att_info.LocalVariableTable.local_variable_table[i].descriptor_index,
            prefix, att_info.LocalVariableTable.local_variable_table[i].index
        );
      break;
    case NUMBER_SourceFile:
      u1_to_SourceFile(att_info.SourceFile, u1_stream);
      printf("%s\tSource file index: %d\n", prefix, att_info.SourceFile.sourcefile_index);
      break;
    default:
      break;
  }

  return;
}
