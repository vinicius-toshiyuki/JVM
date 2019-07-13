#include "../include/utils.h"
#include "../include/engine.h"
#include "../include/frame.h"
#include "../include/constant_pool.h"
#include "../include/string.h"

int comp(const void *a, const void *b) {return *((char *) a) - *((char *) b);}

int charcmp(const void *a, const void *b){
	return *((char *) a) - *((char *) b);
}

void print_utf8(info_t *string_utf8){
	u1 *bytes = string_utf8->Utf8.bytes;
	for(int i = 0; i < string_utf8->Utf8.length; i++){
		wchar_t utf8char = 0x00000000;
		if((bytes[i] & 0x80) == 0x00){
			utf8char = (wchar_t) bytes[i];
		}else if((bytes[i] & 0xE0) == 0xC0)
			utf8char = (wchar_t) (((bytes[i] & 0x1F) << 6) | (bytes[i + 1] & 0x3F)), i++;
		else if((bytes[i] & 0xF0) == 0xE0){
			utf8char = (wchar_t) (((bytes[i] & 0x0F) << 12) | ((bytes[i + 1] & 0x3F) << 6) | (bytes[i + 2] & 0x3F)), i += 2;
			if(utf8char >= 0xD800 && utf8char <= 0xDFFF){
				i++;
				wchar_t utf8char2 = (wchar_t) (((bytes[i] & 0x0F) << 12) | ((bytes[i + 1] & 0x3F) << 6) | (bytes[i + 2] & 0x3F)); i += 2;
				utf8char = (utf8char - 0xD800) * 0x0400 + (utf8char2 - 0xDC00) + 0x10000;
			}
		}
		else if((bytes[i] & 0xF8) == 0xF0)
			utf8char = (wchar_t) (((bytes[i] & 0x07) << 18) | ((bytes[i + 1] & 0x3F) << 12) | ((bytes[i + 2] & 0x4F) << 6) | (bytes[i + 3] & 0x3F)), i += 3;
		printf("%lc", utf8char);
	}
}

wchar_t * get_utf8(info_t *string_utf8){
	wchar_t *str = (wchar_t *) calloc(string_utf8->Utf8.length + 1, sizeof(wchar_t));
	u1 *bytes = string_utf8->Utf8.bytes;
	for(int i = 0, j = 0; i < string_utf8->Utf8.length; i++){
		wchar_t utf8char = 0x00000000;
		if((bytes[i] & 0x80) == 0x00){
			utf8char = (wchar_t) bytes[i];
		}else if((bytes[i] & 0xE0) == 0xC0)
			utf8char = (wchar_t) (((bytes[i] & 0x1F) << 6) | (bytes[i + 1] & 0x3F)), i++;
		else if((bytes[i] & 0xF0) == 0xE0){
			utf8char = (wchar_t) (((bytes[i] & 0x0F) << 12) | ((bytes[i + 1] & 0x3F) << 6) | (bytes[i + 2] & 0x3F)), i += 2;
			if(utf8char >= 0xD800 && utf8char <= 0xDFFF){
				i++;
				wchar_t utf8char2 = (wchar_t) (((bytes[i] & 0x0F) << 12) | ((bytes[i + 1] & 0x3F) << 6) | (bytes[i + 2] & 0x3F)); i += 2;
				utf8char = (utf8char - 0xD800) * 0x0400 + (utf8char2 - 0xDC00) + 0x10000;
			}
		}
		else if((bytes[i] & 0xF8) == 0xF0)
			utf8char = (wchar_t) (((bytes[i] & 0x07) << 18) | ((bytes[i + 1] & 0x3F) << 12) | ((bytes[i + 2] & 0x4F) << 6) | (bytes[i + 3] & 0x3F)), i += 3;
		str[j++] = utf8char;
	}
	return str;
}

void invoke_print(frame_t *frame, char *descriptor){
	char method_descriptor = descriptor[1];
	switch(method_descriptor){
		case 'D':;
			u4 *dvalue_low = cpop(frame->operands_stack);
			u4 *dvalue_high = cpop(frame->operands_stack);
			u8 value = ((u8) *dvalue_high) << 32 | *dvalue_low;
			double dvalue;
			memcpy(&dvalue, &value, 8);
			printf("%0.16lf", dvalue);
			break;
		case 'J':;
			u4 *lvalue_low = cpop(frame->operands_stack);
			u4 *lvalue_high = cpop(frame->operands_stack);
			u8 value_l = ((u8) *lvalue_high) << 32 | *lvalue_low;
			long lvalue;
			memcpy(&lvalue, &value_l, 8);
			printf("%ld", lvalue);
			break;
		case 'I':;
			int32_t ivalue;
			memcpy(&ivalue, cpop(frame->operands_stack), 4);
			printf("%d", ivalue);
			break;
		case 'Z':
			printf("%s", *((u4 *) cpop(frame->operands_stack)) ? "true" : "false");
			break;
		case 'B':;
			int8_t bvalue;
			memcpy(&bvalue, cpop(frame->operands_stack), 1);
			printf("%hhx", bvalue);
			break;
		case 'C':;
			int8_t cvalue;
			memcpy(&cvalue, cpop(frame->operands_stack), 1);
			printf("%c", cvalue);
			break;
		case 'F':;
			float fvalue;
			memcpy(&fvalue, cpop(frame->operands_stack), 4);
			printf("%f", fvalue);
			break;
		case 'S':;
			short svalue;
			memcpy(&svalue, cpop(frame->operands_stack), 2);
			printf("%hi", svalue);
			break;
		case ')':
			break;
		default:;
			char *ponto_e_virgula = strtok(descriptor + 1, ";");
			if(ponto_e_virgula){
				ponto_e_virgula[strlen(ponto_e_virgula) + 1] = '\0';
				ponto_e_virgula[strlen(ponto_e_virgula)] = ';';
			}
			if(!strcmp(ponto_e_virgula, "Ljava/lang/String;")){
				objectref_t *string_info = cpop(frame->operands_stack);
				if(string_info->tag != REF_String || ((String *) string_info->object)->tag != STR_Builder){
					info_t *string_utf8 = get_constant_pool_entry(frame, ((info_t *) string_info)->String.string_index);
					print_utf8(string_utf8);
				}else{
					clist_t *str = ((String *) string_info->object)->data;
					celement_t *iter = str->head;
					int i;
					for(i = 0; i < str->size; i++, iter = iter->next){
						String *el = iter->value;
						switch(el->tag){
							case STR_String:
								printf("%ls", (wchar_t *) el->data);
								break;
							case STR_Double:
								printf("%lf", *((double *) el->data));
								break;
							case STR_Float:
								printf("%f", *((float *) el->data));
								break;
							case STR_Char:
								printf("%c", *((char *) el->data));
								break;
							case STR_Integer:
								printf("%d", *((integer *) el->data));
								break;
							case STR_Short:
								printf("%hi", *((short *) el->data));
								break;
							case STR_Byte:
								printf("%hhx", *((byte *) el->data));
								break;
							case STR_Long:
								printf("%ld", *((long *) el->data));
								break;
							case STR_Boolean:
								printf("%s", (char *) el->data);
								break;
							default:
								break;
						}
					}
					cpush(frame->operands_stack, NULL);
				}
			}else{
				printf("%s@%p", ponto_e_virgula, (void *) cpop(frame->operands_stack));
			}
	}
	cpop(frame->operands_stack);
}

void invoke_append(frame_t *frame, char *descriptor){
	char method_descriptor = descriptor[1];
	String *str = new_string();
	switch(method_descriptor){
		case 'D':;
			double *dvalue = (double *) calloc(1, sizeof(double));
			*dvalue = pop_double(frame);
			string_of(str, STR_Double, dvalue); 
			break;
		case 'J':;
			long *lvalue = (long *) calloc(1, sizeof(long));
			*lvalue = pop_long(frame);
			string_of(str, STR_Long, lvalue);
			break;
		case 'I':;
			integer *ivalue = (integer *) calloc(1, sizeof(integer));
			*ivalue = pop_integer(frame);
			string_of(str, STR_Integer, ivalue);
			break;
		case 'Z':;
			byte Bvalue = pop_boolean(frame);
			char *bstr = NULL;
			if(Bvalue){
				bstr = (char *) calloc(5, sizeof(char));
				strcpy(bstr, "true");
			}else{
				bstr = (char *) calloc(6, sizeof(char));
				strcpy(bstr, "false");
			}
			string_of(str, STR_Boolean, bstr);
			break;
		case 'B':;
			byte *bvalue = (byte *) calloc(1, sizeof(byte));
			*bvalue = pop_byte(frame);
			string_of(str, STR_Byte, bvalue);
			break;
		case 'C':;
			character *cvalue = (character *) calloc(1, sizeof(character));
			*cvalue = pop_char(frame);
			string_of(str, STR_Char, cvalue);
			break;
		case 'F':;
			float *fvalue = (float *) calloc(1, sizeof(float));
			*fvalue = pop_float(frame);
			string_of(str, STR_Float, fvalue);
			break;
		case 'S':;
			short *svalue = (short *) calloc(1, sizeof(short));
			*svalue = pop_short(frame);
			string_of(str, STR_Short, svalue);
			break;
		case ')':
			break;
		default:;
			char *ponto_e_virgula = strtok(descriptor + 1, ";");
			if(ponto_e_virgula){
				ponto_e_virgula[strlen(ponto_e_virgula) + 1] = '\0';
				ponto_e_virgula[strlen(ponto_e_virgula)] = ';';
			}
			if(!strcmp(ponto_e_virgula, "Ljava/lang/String;")){
				info_t *string_info = cpop(frame->operands_stack);
				info_t *string_utf8 = get_constant_pool_entry(frame, ((info_t *) string_info)->String.string_index);
				wchar_t *strutf8 = get_utf8(string_utf8);
				string_of(str, STR_String, strutf8);
			}else{
				char *objstr = (char *) calloc(strlen(ponto_e_virgula) + 20, sizeof(char));
				sprintf(objstr, "%s@%p", ponto_e_virgula, (void *) cpop(frame->operands_stack));
				string_of(str, STR_Boolean, objstr);
			}
	}
	objectref_t *stref = (objectref_t *) cpop(frame->operands_stack);
	cappend(((String *) stref->object)->data, str);
	cpush(frame->operands_stack, stref);
}
