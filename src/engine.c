#include "../include/engine.h"
#include "../include/classfile.h"
#include "../include/bread_classfile.h"
#include "../include/attributes.h"
#include "../include/bytecode.h"
#include "../include/errcodes.h"
#include "../include/utils.h"
#include <stdio.h>
#include <string.h>

Method get_method_by_name(ClassFile *class, char *name){
	int mc = class->methods_count, i, j;
	for(i = 0; i < mc; i++)
		if(!strcmp(name, (const char *) class->constant_pool[class->methods[i].name_index - 1].info->Utf8.bytes))
			break;

	int ac = class->methods[i].attributes_count, found = 0;
	for(j = 0; j < ac; j++)
		if(!strcmp("Code", (const char *) class->constant_pool[class->methods[i].attributes[j].attribute_name_index - 1].info->Utf8.bytes)){
			found = 1;
			break;
		}

	if(!found){
		fprintf(stderr, "Can not find method %s\n", name);
		exit(ERR_NOMETH);
	}

	Attributes codeatt;
	get_attribute_from_info(
			class->methods[i].attributes[j].info,
			&codeatt,
			class->methods[i].attributes[j].attribute_name_index,
			class
			);
	return (Method) {
		codeatt.Code.code_length,
			codeatt.Code.code
	};
}

extern handler bytecode_handlers[];
void run_method(frame_t *frame, Method *method, jvm_t *jvm){
	u1 **pc = &frame->pc;
	do bytecode_handlers[(*pc)[0]](pc, method->code, frame, jvm);
	while((*pc)++ != NULL);
}

void store_arguments(cstack_t *args, frame_t *old_frame, char *arguments){
	int i;
	for(i = 0; i < strlen(arguments); i++){
		switch(arguments[i]){
			case '[':
				printv("Passing array ref !\n");
			case 'B':
			case 'C':
			case 'F':
			case 'I':
			case 'S':
			case 'Z':;
							 u4 *value = (u4 *) cpop(old_frame->operands_stack);
							 cpush(args, value);
							 break;
			case 'L':
							 while(arguments[i++] != ';');
							 cpush(args, cpop(old_frame->operands_stack));
							 break;
			case 'J':
			case 'D':;
							 void *low = cpop(old_frame->operands_stack);
							 cpush(args, cpop(old_frame->operands_stack));
							 cpush(args, low);
							 break;
			case '(':
							 break;
			case ')':
							 i = strlen(arguments);
							 break;
			default:
							 fprintf(stderr, "Invalide arg type descriptor (%c)\n", arguments[i]);
							 exit(ERR_UNKTYPE);
		}
	}
}

void load_arguments(cstack_t *args, frame_t *frame){
	while(args->size)
		cappend(frame->local_variables, cpop(args));
}

integer pop_integer(frame_t *frame){
	void *value = cpop(frame->operands_stack);
	integer ivalue;
	memcpy(&ivalue, value, 4);
	free(value);
	return ivalue;
}

void push_integer(frame_t *frame, integer ivalue){
	u4 *value = (u4 *) calloc(1, sizeof(u4));
	u4 i;
	memcpy(&i, &ivalue, 4);
	*value = i;
	cpush(frame->operands_stack, value);
}

byte pop_byte(frame_t *frame){
	void *value = cpop(frame->operands_stack);
	byte bvalue;
	memcpy(&bvalue, value, 1);
	free(value);
	return bvalue;
}

void push_byte(frame_t *frame, byte bvalue){
	u4 *value = (u4 *) calloc(1, sizeof(u4));
	u4 b;
	memcpy(&b, &bvalue, 1);
	*value = b;
	cpush(frame->operands_stack, value);
}

array_t * pop_array(frame_t *frame){
	return (array_t *) ((objectref_t *) cpop(frame->operands_stack))->object;
}

double pop_double(frame_t *frame){
	u4 *low_value = (u4 *) cpop(frame->operands_stack);
	u4 *high_value = (u4 *) cpop(frame->operands_stack);
	u8 value = ((u8) *high_value << 32) | *low_value;
	double dvalue;
	memcpy(&dvalue, &value, 8);
	free(low_value);
	free(high_value);
	return dvalue;
}

void push_double(frame_t *frame, double dvalue){
	u4 *value_low = (u4 *) calloc(1, sizeof(u4));
	u4 *value_high = (u4 *) calloc(1, sizeof(u4));
	u8 *value = (u8 *) &dvalue;

	memcpy(value_low, value, 4);
	*value >>= 32;
	memcpy(value_high, value, 4);
	cpush(frame->operands_stack, value_high);
	cpush(frame->operands_stack, value_low);
}

double high_low_to_double(u4 *value_low, u4* value_high){
	u8 value = ((u8) *value_high << 32) | *value_low;
	double dvalue;
	memcpy(&dvalue, &value, 8);
	return dvalue;
}

long pop_long(frame_t *frame){
	u4 *low_value = (u4 *) cpop(frame->operands_stack);
	u4 *high_value = (u4 *) cpop(frame->operands_stack);
	u8 value = ((u8) *high_value << 32) | *low_value;
	long lvalue;
	memcpy(&lvalue, &value, 8);
	free(low_value);
	free(high_value);
	return lvalue;
}

void push_long(frame_t *frame, long lvalue){
	u4 *value_low = (u4 *) calloc(1, sizeof(u4));
	u4 *value_high = (u4 *) calloc(1, sizeof(u4));
	u8 *value = (u8 *) &lvalue;

	memcpy(value_low, value, 4);
	*value >>= 32;
	memcpy(value_high, value, 4);
	cpush(frame->operands_stack, value_high);
	cpush(frame->operands_stack, value_low);
}

long high_low_to_long(u4 *value_low, u4* value_high){
	u8 value = ((u8) *value_high << 32) | *value_low;
	long lvalue;
	memcpy(&lvalue, &value, 8);
	return lvalue;
}

float pop_float(frame_t *frame){
	void *value = cpop(frame->operands_stack);
	float fvalue;
	memcpy(&fvalue, value, 4);
	free(value);
	return fvalue;
}

void push_float(frame_t *frame, float fvalue){
	u4 *value = (u4 *) calloc(1, sizeof(u4));
	u4 f;
	memcpy(&f, &fvalue, 4);
	*value = f;
	cpush(frame->operands_stack, value);
}

short pop_short(frame_t *frame){
	void *value = cpop(frame->operands_stack);
	short svalue;
	memcpy(&svalue, value, 2);
	free(value);
	return svalue;
}

void push_short(frame_t *frame, short svalue){
	u4 *value = (u4 *) calloc(1, sizeof(u4));
	u2 s;
	memcpy(&s, &svalue, 2);
	*value = s;
	cpush(frame->operands_stack, value);
}

void push_returnAddress(frame_t *frame, u1 *address){
	u4 *value = (u4 *) calloc(1, sizeof(u4));
	memcpy(value, &address, 1);
	cpush(frame->operands_stack, value);
}

u1 * pop_returnAddress(frame_t *frame){
	u4 *value = (u4 *) cpop(frame->operands_stack);
	u1 *rvalue;
	memcpy(&rvalue, value, 1);
	free(value);
	return rvalue;
}
