#include "../include/bprint_classfile.h"
#include "../include/mnemonic.h"

#include <wchar.h>

extern int verbose, print_pool;
extern void * opcode_handlers[];
extern char * opcode_to_mnemonic[0x100];

char *constant_name[] = {
  [CONSTANT_Class]              = "Class",
  [CONSTANT_Fieldref]           = "Fieldref",
  [CONSTANT_Methodref]          = "Methodref",
  [CONSTANT_InterfaceMethodref] = "InterfaceMethodref",
  [CONSTANT_String]             = "String",
  [CONSTANT_Integer]            = "Integer",
  [CONSTANT_Float]              = "Float",
  [CONSTANT_Long]               = "Long",
  [CONSTANT_Double]             = "Double",
  [CONSTANT_NameAndType]        = "NameAndType",
  [CONSTANT_Utf8]               = "Utf8"
};

char *java_version[] = {
  [0x39] = "Java SE 13",
  [0x38] = "Java SE 12",
  [0x37] = "Java SE 11",
  [0x36] = "Java SE 10",
  [0x35] = "Java SE 9",
  [0x34] = "Java SE 8",
  [0x33] = "Java SE 7",
  [0x32] = "Java SE 6.0",
  [0x31] = "Java SE 5.0",
  [0x30] = "JDK 1.4",
  [0x2F] = "JDK 1.3",
  [0x2E] = "JDK 1.2",
  [0x2D] = "JDK 1.1",
};

void bprint_classfile(ClassFile *class){
  bprint_magic(class);
  bprint_versions(class);
  bprint_const_pool_count(class);
  if(print_pool) bprint_constant_pool(class);
  bprint_access_flags(class->access_flags);
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

int charcmp(const void *a, const void *b){
	return *((char *) a) - *((char *) b);
}

int bprint_info(ClassFile *class, int index, const char *prefix, int inner){
	cp_info *cp = &class->constant_pool[index];
	char *new_prefix = (char *) calloc(sizeof(prefix) + 1, sizeof(char));
	strcpy(new_prefix, prefix); strcat(new_prefix, "\t");
	
	if(!inner){
  if(cp->tag) printf(
			"(%d %s)",
			cp->tag,
			constant_name[cp->tag]
	); else printf(
		"(%d %s)",
		cp->tag,
		constant_name[(cp-1)->tag]
	);
	printf(CLEARN);}
  switch(cp->tag){
    case CONSTANT_Class:
      if(!inner) printf("%sName index: %d\n", prefix, cp->info->Class.name_index);
			bprint_info(class, cp->info->Class.name_index - 1, new_prefix, 1);
      break;
    case CONSTANT_Fieldref:
    case CONSTANT_Methodref:
    case CONSTANT_InterfaceMethodref:
      if(!inner) printf("%sClass index: %d\n", prefix, cp->info->Fieldref.class_index);
			bprint_info(class, cp->info->Fieldref.class_index - 1, new_prefix, 1);
			if(!inner) printf("%sName and type index: %d\n",	prefix, cp->info->Fieldref.name_and_type_index);
			bprint_info(class, cp->info->Fieldref.name_and_type_index - 1, new_prefix, 1);			
			break;
		case CONSTANT_String:
			if(!inner) printf("%sString index: %d\n",	prefix, cp->info->String.string_index);
			bprint_info(class, cp->info->String.string_index - 1, new_prefix, 1);
      break;
    case CONSTANT_Integer:
      printf("%sBytes: 0x%04x\n%sValue: %d\n", prefix, cp->info->Integer.bytes, prefix, cp->info->Integer.bytes);
      break;
    case CONSTANT_Float:
    case CONSTANT_Long:
    case CONSTANT_Double:
			bprint_numeral(cp->tag);
			break;
    case CONSTANT_NameAndType:
      if(!inner) printf("%sName index: %d\n", prefix, cp->info->NameAndType.name_index);
			bprint_info(class, cp->info->NameAndType.name_index - 1, new_prefix, 1);
      if(!inner) printf("%sDescripitor index: %d\n", prefix, cp->info->NameAndType.descriptor_index);
			bprint_info(class, cp->info->NameAndType.descriptor_index - 1, new_prefix, 1);
      break;
    case CONSTANT_Utf8:;
			static char escapes[7][4] = {"\aa", "\bb", "\tt", "\nn", "\vv", "\ff", "\rr"};
      if(!inner) printf("%sLength: %d\n%sBytes: ", prefix, cp->info->Utf8.length, prefix);
			printf("%s\"", inner ? prefix: "");
			u1 *bytes = cp->info->Utf8.bytes;
      for(int i = 0; i < cp->info->Utf8.length; i++){
				wchar_t utf8char;
				if((bytes[i] & 0x80) == 0x00){
					char c[] = {bytes[i], '\0'}, *c1;
					c1 = bsearch(c, escapes, 7, 4, charcmp);
					if(c1){
						printf("\\%c", *++c1);
						utf8char = *++c1;
					}else{
						utf8char = (wchar_t) bytes[i];
					}
				}else if((bytes[i] & 0xE0) == 0xC0)
					utf8char = (wchar_t) (((bytes[i] & 0x1F) << 6) | (bytes[i + 1] & 0x3F)), i++;
				else if((bytes[i] & 0xF0) == 0xE0)
					utf8char = (wchar_t) (((bytes[i] & 0x0F) << 12) | ((bytes[i + 1] & 0x3F) << 6) | (bytes[i + 2] & 0x3F)), i += 2;
				else if((bytes[i] & 0xF8) == 0xF0)
					utf8char = (wchar_t) (((bytes[i] & 0x07) << 18) | ((bytes[i + 1] & 0x3F) << 12) | ((bytes[i + 2] & 0x4F) << 6) | (bytes[i + 3] & 0x3F)), i += 3;
				else
					printf("0x%02x ", bytes[i]);
				printf("%lc", utf8char);
			}
      printf("\"\n");
      break;
  }
	free(new_prefix);
  return index + 1;
}

extern int _jump;
extern struct {
  u4 default_offset;
  u4 npairs;
  u4 **pairs;
} lookup_result;
void bprint_att_info(u1 *u1_stream, int name_index, ClassFile *class, const char prefix[]){
  static char attributes_types[ATT_C][ATT_M_S] = {"Code", "ConstantValue", "Deprecated", "Exceptions", "LineNumberTable", "LocalVariableTable", "SourceFile"}, att_type_value_assign = 1;
  static int lookup = 0;
  if(att_type_value_assign){
    att_type_value_assign = 0;
    // A enum NUMBERS tem que estar de acordo com essa numeração
    for(int i = 0; i < ATT_C; i++)
      attributes_types[i][ATT_M_S - 1] = i;
    if(verbose) printf(BGC(127) FGC(83) "%sSetting attributes array" CLEARN, prefix);
  }
  // Busca nome do atributo com o name_index na constant_pool
  
  char str_name[ATT_M_S] = {[0 ... ATT_M_S - 1] = '\0'};
  memcpy(str_name, class->constant_pool[name_index - 1].info->Utf8.bytes  /*Bytes do nome do atributo*/, class->constant_pool[name_index - 1].info->Utf8.length);
  void *bsearch_result = bsearch(str_name, attributes_types, ATT_C, ATT_M_S, (int (*)(const void *, const void *)) strcmp);
  int number_code = bsearch_result != NULL ? ((char *) bsearch_result)[ATT_M_S - 1] : NUMBER_Invalid;

  printf(BGC(27) FGC(11) "%s%s attribute:" CLEARN, prefix, str_name);

	char *new_prefix = (char *) calloc(strlen(prefix) + 3, sizeof(char));
	strcpy(new_prefix, prefix); strcat(new_prefix, "\t\t");
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
			int ret = 0;
      for(int i = 0; i < att_info.Code.code_length; i++){
        if(ret >= 0 && !_jump) printf("%s\t" "%03d " BGC(80) FGC(96) "0x%02x:" CLEAR " ", prefix, i, att_info.Code.code[i]);
        ret = ((int (*)(u1 *))(opcode_handlers[att_info.Code.code[i]]))(att_info.Code.code + i);
        if(lookup){
          printf("%sNpairs: %d\n", new_prefix, lookup_result.npairs);
          int j; for(j = 0; j < lookup_result.npairs; j++){
            printf(
              "%s%d: %d (%s%d)\n",
              new_prefix, lookup_result.pairs[j][0],
              i + lookup_result.pairs[j][1],
              lookup_result.pairs[j][1] < 0 ? "" : "+",
              lookup_result.pairs[j][1]
            );
            free(lookup_result.pairs[j]);
          }
          free(lookup_result.pairs);
          printf("%sDefault: %d (%s%d)\n", new_prefix, i + lookup_result.default_offset, lookup_result.default_offset < 0 ? "" : "+",lookup_result.default_offset);
          lookup = 0;
        }
				if(_jump){
					printf("%sJump address: %d (Offset: %s%d)\n", new_prefix, i + ret, ret < 0 ? "" : "+", ret);
					i--;
				}else if(ret == -1 && (i + 1) % 4){
					u1 pad = (u1) (4 - ((i + 1 ) % 4));
					att_info.Code.code[i + 1] = pad;
          lookup = 1;
					i--;
				}else if(ret < -1){
					printf("%s", new_prefix);
					bprint_info(class, -++ret - 1, new_prefix, 1);
					i--;
				}else{
					i += ret;
				}
      }
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
      free(att_prefix);
			free(att_info.Code.code);
			free(att_info.Code.exception_table);
			int i; for(i = 0; i < att_info.Code.attributes_count; i++)
				free(att_info.Code.attributes[i].info);
			free(att_info.Code.attributes);
      break;
    case NUMBER_ConstantValue:
      u1_to_ConstantValue(att_info.ConstantValue, u1_stream);
      printf("%s\tConstant value index: %d\n%s", prefix, att_info.ConstantValue.constantvalue_index, new_prefix);
			bprint_info(class, att_info.ConstantValue.constantvalue_index - 1, new_prefix, 1);
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
      for(int i = 0; i < att_info.Exceptions.number_of_exceptions; i++){
        printf(
            "%s\t\tException %d: %d\n%s",
            prefix, i, att_info.Exceptions.exception_index_table[i], new_prefix
        );
				bprint_info(class, att_info.Exceptions.exception_index_table[i] - 1, new_prefix, 1);
			}
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
			free(att_info.LineNumberTable.line_number_table);
      break;
    case NUMBER_LocalVariableTable:
      u1_to_LocalVariableTable(att_info.LocalVariableTable, u1_stream);
      printf(
          "%s\tLocal variable table length: %d\n"
          "%s\tLocal variable table:\n",
          prefix, att_info.LocalVariableTable.local_variable_table_length, prefix
      );
      for(int i = 0; i < att_info.LocalVariableTable.local_variable_table_length; i++){
        printf(
            "%s\t\tLocal variable %d:\n"
            "%s\t\tStart PC: 0x%04x\n"
            "%s\t\tLength: %d\n"
						"%s\t\tName index: %d\n%s",
            prefix, i,
            prefix, att_info.LocalVariableTable.local_variable_table[i].start_pc,
            prefix, att_info.LocalVariableTable.local_variable_table[i].length,
            prefix, att_info.LocalVariableTable.local_variable_table[i].name_index, new_prefix
				);
				bprint_info(class, att_info.LocalVariableTable.local_variable_table[i].name_index - 1, new_prefix, 1);
				printf(
            "%s\t\tDescriptor index: %d\n%s",
            prefix, att_info.LocalVariableTable.local_variable_table[i].descriptor_index, new_prefix
				);
				bprint_info(class, att_info.LocalVariableTable.local_variable_table[i].descriptor_index - 1, new_prefix, 1);
				printf(
            "%s\t\tIndex: %d\n",
            prefix, att_info.LocalVariableTable.local_variable_table[i].index
        );
			}
			free(att_info.LocalVariableTable.local_variable_table);
      break;
    case NUMBER_SourceFile:
      u1_to_SourceFile(att_info.SourceFile, u1_stream);
      printf("%s\tSource file index: %d\n", prefix, att_info.SourceFile.sourcefile_index);
			printf("%s", new_prefix);
			bprint_info(class, att_info.SourceFile.sourcefile_index - 1, new_prefix, 1);
      break;
    default:
      break;
  }
	free(new_prefix);
  return;
}
