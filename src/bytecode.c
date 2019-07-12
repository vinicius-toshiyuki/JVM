#include <stdio.h>
#include "../include/mnemonic.h"
#include "../include/bytecode.h"
#include "../include/constant_pool.h"
#include "../include/method_area.h"
#include "../include/jvm.h"
#include "../include/info.h"
#include "../include/engine.h"
#include "../include/array.h"
#include "../include/field_object.h"
#include <math.h>

/**< Map of bytecode-handler */
handler bytecode_handlers[] = {
  [0x32] = AALOAD_handler,
  [0x53] = AASTORE_handler,
  [0x01] = ACONST_NULL_handler,
  [0x19] = ALOAD_handler,
  [0x2a] = ALOAD_0_handler,
  [0x2b] = ALOAD_1_handler,
  [0x2c] = ALOAD_2_handler,
  [0x2d] = ALOAD_3_handler,
  [0xbd] = ANEWARRAY_handler,
  [0xb0] = ARETURN_handler,
  [0xbe] = ARRAYLENGTH_handler,
  [0x3a] = ASTORE_handler,
  [0x4b] = ASTORE_0_handler,
  [0x4c] = ASTORE_1_handler,
  [0x4d] = ASTORE_2_handler,
  [0x4e] = ASTORE_3_handler,
  [0xbf] = ATHROW_handler,
  [0x33] = BALOAD_handler,
  [0x54] = BASTORE_handler,
  [0x10] = BIPUSH_handler,
  [0x34] = CALOAD_handler,
  [0x55] = CASTORE_handler,
  [0xc0] = CHECKCAST_handler,
  [0x90] = D2F_handler,
  [0x8e] = D2I_handler,
  [0x8f] = D2L_handler,
  [0x63] = DADD_handler,
  [0x31] = DALOAD_handler,
  [0x52] = DASTORE_handler,
  [0x98] = DCMPG_handler,
  [0x97] = DCMPL_handler,
  [0x0e] = DCONST_0_handler,
  [0x0f] = DCONST_1_handler,
  [0x6f] = DDIV_handler,
  [0x18] = DLOAD_handler,
  [0x26] = DLOAD_0_handler,
  [0x27] = DLOAD_1_handler,
  [0x28] = DLOAD_2_handler,
  [0x29] = DLOAD_3_handler,
  [0x6b] = DMUL_handler,
  [0x77] = DNEG_handler,
  [0x73] = DREM_handler,
  [0xaf] = DRETURN_handler,
  [0x39] = DSTORE_handler,
  [0x47] = DSTORE_0_handler,
  [0x48] = DSTORE_1_handler,
  [0x49] = DSTORE_2_handler,
  [0x4a] = DSTORE_3_handler,
  [0x67] = DSUB_handler,
  [0x59] = DUP_handler,
  [0x5a] = DUP_X1_handler,
  [0x5b] = DUP_X2_handler,
  [0x5c] = DUP2_handler,
  [0x5d] = DUP2_X1_handler,
  [0x5e] = DUP2_X2_handler,
  [0x8d] = F2D_handler,
  [0x8b] = F2I_handler,
  [0x8c] = F2L_handler,
  [0x62] = FADD_handler,
  [0x30] = FALOAD_handler,
  [0x51] = FASTORE_handler,
  [0x96] = FCMPG_handler,
  [0x95] = FCMPL_handler,
  [0x0b] = FCONST_0_handler,
  [0x0c] = FCONST_1_handler,
  [0x0d] = FCONST_2_handler,
  [0x6e] = FDIV_handler,
  [0x17] = FLOAD_handler,
  [0x22] = FLOAD_0_handler,
  [0x23] = FLOAD_1_handler,
  [0x24] = FLOAD_2_handler,
  [0x25] = FLOAD_3_handler,
  [0x6a] = FMUL_handler,
  [0x76] = FNEG_handler,
  [0x72] = FREM_handler,
  [0xae] = FRETURN_handler,
  [0x38] = FSTORE_handler,
  [0x43] = FSTORE_0_handler,
  [0x44] = FSTORE_1_handler,
  [0x45] = FSTORE_2_handler,
  [0x46] = FSTORE_3_handler,
  [0x66] = FSUB_handler,
  [0xb4] = GETFIELD_handler,
  [0xb2] = GETSTATIC_handler,
  [0xa7] = GOTO_handler,
  [0xc8] = GOTO_W_handler,
  [0x91] = I2B_handler,
  [0x92] = I2C_handler,
  [0x87] = I2D_handler,
  [0x86] = I2F_handler,
  [0x85] = I2L_handler,
  [0x93] = I2S_handler,
  [0x60] = IADD_handler,
  [0x2e] = IALOAD_handler,
  [0x7e] = IAND_handler,
  [0x4f] = IASTORE_handler,
  [0x02] = ICONST_M1_handler,
  [0x03] = ICONST_0_handler,
  [0x04] = ICONST_1_handler,
  [0x05] = ICONST_2_handler,
  [0x06] = ICONST_3_handler,
  [0x07] = ICONST_4_handler,
  [0x08] = ICONST_5_handler,
  [0x6c] = IDIV_handler,
  [0xa5] = IF_ACMPEQ_handler,
  [0xa6] = IF_ACMPNE_handler,
  [0x9f] = IF_ICMPEQ_handler,
  [0xa2] = IF_ICMPGE_handler,
  [0xa3] = IF_ICMPGT_handler,
  [0xa4] = IF_ICMPLE_handler,
  [0xa1] = IF_ICMPLT_handler,
  [0xa0] = IF_ICMPNE_handler,
  [0x99] = IFEQ_handler,
  [0x9c] = IFGE_handler,
  [0x9d] = IFGT_handler,
  [0x9e] = IFLE_handler,
  [0x9b] = IFLT_handler,
  [0x9a] = IFNE_handler,
  [0xc7] = IFNONNULL_handler,
  [0xc6] = IFNULL_handler,
  [0x84] = IINC_handler,
  [0x15] = ILOAD_handler,
  [0x1a] = ILOAD_0_handler,
  [0x1b] = ILOAD_1_handler,
  [0x1c] = ILOAD_2_handler,
  [0x1d] = ILOAD_3_handler,
  [0x68] = IMUL_handler,
  [0x74] = INEG_handler,
  [0xc1] = INSTANCEOF_handler,
  [0xba] = INVOKEDYNAMIC_handler,
  [0xb9] = INVOKEINTERFACE_handler,
  [0xb7] = INVOKESPECIAL_handler,
  [0xb8] = INVOKESTATIC_handler,
  [0xb6] = INVOKEVIRTUAL_handler,
  [0x80] = IOR_handler,
  [0x70] = IREM_handler,
  [0xac] = IRETURN_handler,
  [0x78] = ISHL_handler,
  [0x7a] = ISHR_handler,
  [0x36] = ISTORE_handler,
  [0x3b] = ISTORE_0_handler,
  [0x3c] = ISTORE_1_handler,
  [0x3d] = ISTORE_2_handler,
  [0x3e] = ISTORE_3_handler,
  [0x64] = ISUB_handler,
  [0x7c] = IUSHR_handler,
  [0x82] = IXOR_handler,
  [0xa8] = JSR_handler,
  [0xc9] = JSR_W_handler,
  [0x8a] = L2D_handler,
  [0x89] = L2F_handler,
  [0x88] = L2I_handler,
  [0x61] = LADD_handler,
  [0x2f] = LALOAD_handler,
  [0x7f] = LAND_handler,
  [0x50] = LASTORE_handler,
  [0x94] = LCMP_handler,
  [0x09] = LCONST_0_handler,
  [0x0a] = LCONST_1_handler,
  [0x12] = LDC_handler,
  [0x13] = LDC_W_handler,
  [0x14] = LDC2_W_handler,
  [0x6d] = LDIV_handler,
  [0x16] = LLOAD_handler,
  [0x1e] = LLOAD_0_handler,
  [0x1f] = LLOAD_1_handler,
  [0x20] = LLOAD_2_handler,
  [0x21] = LLOAD_3_handler,
  [0x69] = LMUL_handler,
  [0x75] = LNEG_handler,
  [0xab] = LOOKUPSWITCH_handler,
  [0x81] = LOR_handler,
  [0x71] = LREM_handler,
  [0xad] = LRETURN_handler,
  [0x79] = LSHL_handler,
  [0x7b] = LSHR_handler,
  [0x37] = LSTORE_handler,
  [0x3f] = LSTORE_0_handler,
  [0x40] = LSTORE_1_handler,
  [0x41] = LSTORE_2_handler,
  [0x42] = LSTORE_3_handler,
  [0x65] = LSUB_handler,
  [0x7d] = LUSHR_handler,
  [0x83] = LXOR_handler,
  [0xc2] = MONITORENTER_handler,
  [0xc3] = MONITOREXIT_handler,
  [0xc5] = MULTIANEWARRAY_handler,
  [0xbb] = NEW_handler,
  [0xbc] = NEWARRAY_handler,
  [0x00] = NOP_handler,
  [0x57] = POP_handler,
  [0x58] = POP2_handler,
  [0xb5] = PUTFIELD_handler,
  [0xb3] = PUTSTATIC_handler,
  [0xa9] = RET_handler,
  [0xb1] = RETURN_handler,
  [0x35] = SALOAD_handler,
  [0x56] = SASTORE_handler,
  [0x11] = SIPUSH_handler,
  [0x5f] = SWAP_handler,
  [0xaa] = TABLESWITCH_handler,
  [0xc4] = WIDE_handler
};

extern int VERBOSE;

void AALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer index = pop_integer(frame);
	array_t *array = pop_array(frame);
	cpush(frame->operands_stack, at(array, index));
}
void AASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	objectref_t *ref = (objectref_t *) cpop(frame->operands_stack);
	integer index = pop_integer(frame);
	array_t *array = pop_array(frame);
	put(array, index, ref);
}
void ACONST_NULL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	objectref_t *ref = new_objectref();
	reference_of(ref, REF_Null, NULL);
	cpush(frame->operands_stack, ref);
}
void ALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0]; ++*pc;
	cpush(frame->operands_stack, cat(frame->local_variables, lv_index));
}
void ALOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	cpush(frame->operands_stack, cat(frame->local_variables, 0));
}
void ALOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	cpush(frame->operands_stack, cat(frame->local_variables, 1));
}
void ALOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	cpush(frame->operands_stack, cat(frame->local_variables, 2));
}
void ALOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	cpush(frame->operands_stack, cat(frame->local_variables, 3));
}
void ANEWARRAY_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;
	u1 ref_tag = get_constant_pool_tag(frame, cp_index);

	if(ref_tag != CONSTANT_Class){
		fprintf(stderr, "Invalid class reference in anewarray\n");
		exit(ERR_INVREF);
	}
	info_t *class_info = get_constant_pool_entry(frame, cp_index);
	info_t *class_info_utf8 = get_constant_pool_entry(frame, class_info->Class.name_index);
	char *class_name = (char *) calloc(class_info_utf8->Utf8.length + 1, sizeof(char));
	memcpy(class_name, class_info_utf8->Utf8.bytes, class_info_utf8->Utf8.length);
	int32_t *count = (int32_t *) cpop(frame->operands_stack);

	array_t *array = new_array();
	/* Tem que definir o tipo certinho */
	array_of(array, ARR_RefClass, *count);
	array_of_class(array, class_name);
	free(class_name);
	
	objectref_t *ref = new_objectref();
	reference_of(ref, REF_Array, array);
	cpush(frame->operands_stack, ref);
}
void ARETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	cpush(((frame_t *) jvm->frame_stack->top->next->value)->operands_stack, cpop(frame->operands_stack));
	*pc = NULL;
}
void ARRAYLENGTH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	array_t *array = pop_array(frame);
	int32_t *length = (int32_t *) calloc(1, sizeof(int32_t));
	memcpy(length, &array->length, 4);
	cpush(frame->operands_stack, length);
}
void ASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0]; ++*pc;
	cinsert(frame->local_variables, lv_index, cpop(frame->operands_stack));
}
void ASTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	cinsert(frame->local_variables, 0, cpop(frame->operands_stack));
}
void ASTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	cinsert(frame->local_variables, 1, cpop(frame->operands_stack));
}
void ASTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	cinsert(frame->local_variables, 2, cpop(frame->operands_stack));
}
void ASTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	cinsert(frame->local_variables, 3, cpop(frame->operands_stack));
}
void ATHROW_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void BALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer index = pop_integer(frame);
	array_t *array = pop_array(frame);
	byte *bvalue = (byte *) calloc(1, sizeof(byte));
	*bvalue = *((byte *) at(array, index));
	cpush(frame->operands_stack, bvalue);
}
void BASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	byte bvalue = pop_byte(frame);
	byte *value = (byte *) calloc(1, sizeof(byte));
	*value = bvalue;
	integer index = pop_integer(frame);
	array_t *array = pop_array(frame);
	put(array, index, value);
}
void BIPUSH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
	if((*pc + 1)[0] >> 7 & 0x01){
		*ivalue |= 0xFFFFFFFF;
	}
	memcpy(ivalue, (*pc)++ + 1, 1);
	cpush(frame->operands_stack, ivalue);
}
void CALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer index = pop_integer(frame);
	array_t *array = pop_array(frame);
	character *cvalue = (character *) calloc(1, sizeof(character));
	memcpy(cvalue, at(array, index), 1);
	cpush(frame->operands_stack, cvalue);
}
void CASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	character cvalue = pop_char(frame);
	integer index = pop_integer(frame);
	array_t *array = pop_array(frame);
	character *value = (character *) calloc(1, sizeof(character));
	*value = cvalue;
	put(array, index, value);
}
void CHECKCAST_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void D2F_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	double dvalue = pop_double(frame);
	float fvalue = (float) dvalue;
	push_float(frame, fvalue);
}
void D2I_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	double dvalue = pop_double(frame);
	integer ivalue = (integer) dvalue;
	push_integer(frame, ivalue);
}
void D2L_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	double dvalue = pop_double(frame);
	long lvalue = (long) dvalue;
	push_long(frame, lvalue);
}
void DADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	double dvalue1, dvalue2, dresult;
	dvalue1 = pop_double(frame);
	dvalue2 = pop_double(frame);

	dresult = dvalue2 + dvalue1;
	push_double(frame, dresult);
}
void DALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer index = pop_integer(frame);
	array_t *array = pop_array(frame);

	push_double(frame, *((double *) at(array, index)));
}
void DASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	double dvalue = pop_double(frame);
	integer index = pop_integer(frame);
	array_t *array = pop_array(frame);
	double *value = (double *) calloc(1, sizeof(double));
	*value = dvalue;
	put(array, index, value);
}
void DCMPG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	double dvalue2 = pop_double(frame);
	double dvalue1 = pop_double(frame);
	integer *result = (integer *) calloc(1, sizeof(integer));
	if(dvalue1 > dvalue2)
		*result = 1;
	else if(dvalue1 == dvalue2)
		*result = 0;
	else
		*result = -1;
	cpush(frame->operands_stack, result);
}
void DCMPL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	double dvalue2 = pop_double(frame);
	double dvalue1 = pop_double(frame);
	integer *result = (integer *) calloc(1, sizeof(integer));
	if(dvalue1 < dvalue2)
		*result = 1;
	else if(dvalue1 == dvalue2)
		*result = 0;
	else
		*result = -1;
	cpush(frame->operands_stack, result);
}
void DCONST_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_high = (u4 *) calloc(1, sizeof(u4));
	u4 *dvalue_low = (u4 *) calloc(1, sizeof(u4));
	*dvalue_high = 0x00000000; /* 0.0 IEEE-754 Double */
	*dvalue_low = 0x00000000;
	cpush(frame->operands_stack, dvalue_high);
	cpush(frame->operands_stack, dvalue_low);
}
void DCONST_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_high = (u4 *) calloc(1, sizeof(u4));
	u4 *dvalue_low = (u4 *) calloc(1, sizeof(u4));
	*dvalue_high = 0x3FF00000;
	*dvalue_low = 0x00000000; /* 1.0 IEEE-754 Double */
	cpush(frame->operands_stack, dvalue_high);
	cpush(frame->operands_stack, dvalue_low);
}
void DDIV_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	double dvalue1, dvalue2, dresult;
	dvalue1 = pop_double(frame);
	dvalue2 = pop_double(frame);

	dresult = dvalue2 / dvalue1;
	push_double(frame, dresult);
}
void DLOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0]; ++*pc;
	u4 *dvalue_high = (u4 *) cat(frame->local_variables, lv_index++);
	u4 *dvalue_low = (u4 *) cat(frame->local_variables, lv_index);
	double d = high_low_to_double(dvalue_low, dvalue_high);
	push_double(frame, d);
}
void DLOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_high = (u4 *) cat(frame->local_variables, 0);
	u4 *dvalue_low = (u4 *) cat(frame->local_variables, 1);
	double d = high_low_to_double(dvalue_low, dvalue_high);
	push_double(frame, d);
}
void DLOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_high = (u4 *) cat(frame->local_variables, 1);
	u4 *dvalue_low = (u4 *) cat(frame->local_variables, 2);
	double d = high_low_to_double(dvalue_low, dvalue_high);
	push_double(frame, d);
}
void DLOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_high = (u4 *) cat(frame->local_variables, 2);
	u4 *dvalue_low = (u4 *) cat(frame->local_variables, 3);
	double d = high_low_to_double(dvalue_low, dvalue_high);
	push_double(frame, d);
}
void DLOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_high = (u4 *) cat(frame->local_variables, 3);
	u4 *dvalue_low = (u4 *) cat(frame->local_variables, 4);
	double d = high_low_to_double(dvalue_low, dvalue_high);
	push_double(frame, d);
}
void DMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	double dvalue1, dvalue2, dresult;
	dvalue1 = pop_double(frame);
	dvalue2 = pop_double(frame);

	dresult = dvalue2 * dvalue1;
	push_double(frame, dresult);
}
void DNEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	double dvalue1, dresult;
	dvalue1 = pop_double(frame);

	dresult = -dvalue1;
	push_double(frame, dresult);
}
void DREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	double dvalue1, dvalue2, dresult;
	dvalue1 = pop_double(frame);
	dvalue2 = pop_double(frame);

	dresult = fmod(dvalue2, dvalue1);
	push_double(frame, dresult);
}
void DRETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	void *low = cpop(frame->operands_stack);
	cpush(((frame_t *) jvm->frame_stack->top->next->value)->operands_stack, cpop(frame->operands_stack));
	cpush(((frame_t *) jvm->frame_stack->top->next->value)->operands_stack, low);
	*pc = NULL;
}
void DSTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0]; ++*pc;
	u4 *dvalue_low = (u4 *) cpop(frame->operands_stack);
	u4 *dvalue_high = (u4 *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, lv_index++, dvalue_high);
	cinsert(frame->local_variables, lv_index, dvalue_low);
}
void DSTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_low = (u4 *) cpop(frame->operands_stack);
	u4 *dvalue_high = (u4 *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 0, dvalue_high);
	cinsert(frame->local_variables, 1, dvalue_low);
}
void DSTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_low = (u4 *) cpop(frame->operands_stack);
	u4 *dvalue_high = (u4 *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 1, dvalue_high);
	cinsert(frame->local_variables, 2, dvalue_low);
}
void DSTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_low = (u4 *) cpop(frame->operands_stack);
	u4 *dvalue_high = (u4 *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 2, dvalue_high);
	cinsert(frame->local_variables, 3, dvalue_low);
}
void DSTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_low = (u4 *) cpop(frame->operands_stack);
	u4 *dvalue_high = (u4 *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 3, dvalue_high);
	cinsert(frame->local_variables, 4, dvalue_low);
}
void DSUB_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	double dvalue1, dvalue2, dresult;
	dvalue1 = pop_double(frame);
	dvalue2 = pop_double(frame);

	dresult = dvalue2 - dvalue1;
	push_double(frame, dresult);
}
void DUP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	void *top = (void *) cpop(frame->operands_stack);
	cpush(frame->operands_stack, top);
	cpush(frame->operands_stack, top);
}
void DUP_X1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	void *top = (void *) cpop(frame->operands_stack);
	void *sec = (void *) cpop(frame->operands_stack);

	cpush(frame->operands_stack, top);
	cpush(frame->operands_stack, sec);
	cpush(frame->operands_stack, top);
}
void DUP_X2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	void *top = (void *) cpop(frame->operands_stack);
	void *sec = (void *) cpop(frame->operands_stack);
	void *ter = (void *) cpop(frame->operands_stack);

	cpush(frame->operands_stack, top);
	cpush(frame->operands_stack, ter);
	cpush(frame->operands_stack, sec);
	cpush(frame->operands_stack, top);
}
void DUP2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void DUP2_X1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void DUP2_X2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void F2D_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float value = pop_float(frame);
	double rvalue = (double) value;
	push_double(frame, rvalue);
}
void F2I_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float value = pop_float(frame);
	integer rvalue = (integer) value;
	push_integer(frame, rvalue);
}
void F2L_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float value = pop_float(frame);
	long rvalue = (long) value;
	push_long(frame, rvalue);
}
void FADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float fvalue1 = 0, fvalue2 = 0;
	float fresult;
	fvalue1 = pop_float(frame);
	fvalue2 = pop_float(frame);

	fresult = fvalue2 + fvalue1;
	push_float(frame, fresult);
}
void FALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void FASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void FCMPG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float value1 = pop_float(frame);
	float value2 = pop_float(frame);
	if(value2 > value1){
		push_integer(frame, -1);
	}else if(value2 < value1){
		push_integer(frame, 1);
	}else if(value2 == value1){
		push_integer(frame, 0);
	}
}
void FCMPL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float value1 = pop_float(frame);
	float value2 = pop_float(frame);
	if(value2 > value1){
		push_integer(frame, -1);
	}else if(value2 < value1){
		push_integer(frame, 1);
	}else if(value2 == value1){
		push_integer(frame, 0);
	}
}
void FCONST_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
	*ivalue = 0x00000000; /* 0.0 IEEE-754 Float */
	cpush(frame->operands_stack, ivalue);
}
void FCONST_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
	*ivalue = 0x3F800000; /* 1.0 IEEE-754 Float */
	cpush(frame->operands_stack, ivalue);
}
void FCONST_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
	*ivalue = 0x40000000; /* 2.0 IEEE-754 Float */
	cpush(frame->operands_stack, ivalue);
}
void FDIV_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float fvalue1 = 0, fvalue2 = 0;
	float fresult;
	fvalue1 = pop_float(frame);
	fvalue2 = pop_float(frame);

	fresult = fvalue2 / fvalue1;
	push_float(frame, fresult);
}
void FLOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0]; ++*pc;
	u4 *fvalue = (u4 *) cat(frame->local_variables, lv_index);
	float f;
	memcpy(&f, fvalue, 4);
	push_float(frame, f);
}
void FLOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *fvalue = (u4 *) cat(frame->local_variables, 0);
	float f;
	memcpy(&f, fvalue, 4);
	push_float(frame, f);
}
void FLOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *fvalue = (u4 *) cat(frame->local_variables, 1);
	float f;
	memcpy(&f, fvalue, 4);
	push_float(frame, f);
}
void FLOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *fvalue = (u4 *) cat(frame->local_variables, 2);
	float f;
	memcpy(&f, fvalue, 4);
	push_float(frame, f);
}
void FLOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *fvalue = (u4 *) cat(frame->local_variables, 3);
	float f;
	memcpy(&f, fvalue, 4);
	push_float(frame, f);
}
void FMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float fvalue1 = 0, fvalue2 = 0;
	float fresult;
	fvalue1 = pop_float(frame);
	fvalue2 = pop_float(frame);

	fresult = fvalue2 * fvalue1;
	push_float(frame, fresult);
}
void FNEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float fvalue1 = 0;
	float fresult;
	fvalue1 = pop_float(frame);

	fresult = -fvalue1;
	push_float(frame, fresult);
}
void FREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float fvalue1 = 0, fvalue2 = 0;
	float fresult;
	fvalue1 = pop_float(frame);
	fvalue2 = pop_float(frame);

	fresult = (float) fmod(fvalue2, fvalue1);
	push_float(frame, fresult);
}
void FRETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	cpush(((frame_t *) jvm->frame_stack->top->next->value)->operands_stack, cpop(frame->operands_stack));
	*pc = NULL;
}
void FSTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0]; ++*pc;
	float *fvalue = (float *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, lv_index, fvalue);
}
void FSTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float *fvalue = (float *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 0, fvalue);
}
void FSTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float *fvalue = (float *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 1, fvalue);
}
void FSTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float *fvalue = (float *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 2, fvalue);
}
void FSTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float *fvalue = (float *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 3, fvalue);
}
void FSUB_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	float fvalue1 = 0, fvalue2 = 0;
	float fresult;
	fvalue1 = pop_float(frame);
	fvalue2 = pop_float(frame);

	fresult = fvalue2 - fvalue1;
	push_float(frame, fresult);
}
void GETFIELD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;
	info_t *fieldref = get_constant_pool_entry(frame, cp_index);

	info_t *fieldref_nameandtype = get_constant_pool_entry(frame, fieldref->Fieldref.name_and_type_index);
	info_t *fieldref_name_utf8 = get_constant_pool_entry(frame, fieldref_nameandtype->NameAndType.name_index);
	info_t *fieldref_descriptor_utf8 = get_constant_pool_entry(frame, fieldref_nameandtype->NameAndType.descriptor_index);

	char *fieldref_name = (char *) calloc(fieldref_name_utf8->Utf8.length + 1, sizeof(char));
	memcpy(fieldref_name, fieldref_name_utf8->Utf8.bytes, fieldref_name_utf8->Utf8.length);
/*	printf("%s\n", fieldref_name); */

	char *fieldref_descriptor = (char *) calloc(fieldref_descriptor_utf8->Utf8.length + 1, sizeof(char));
	memcpy(fieldref_descriptor, fieldref_descriptor_utf8->Utf8.bytes, fieldref_descriptor_utf8->Utf8.length);
/*	printf("%s\n", fieldref_descriptor); */

	objectref_t *ref = (objectref_t *) cpop(frame->operands_stack);
	field_object_t *field = ref->object;
/*	printf("%d\n", field->tag); */

	if(field->tag == FIELD_Null){
		fprintf(stderr, "Value not assigned to field %s\n", fieldref_name);
		exit(ERR_UNASSG);
	}

	if(!strcmp(fieldref_descriptor, "B") && field->tag == FIELD_Byte){
		push_byte(frame, field->value.Byte);
	}else if(!strcmp(fieldref_descriptor, "C") && field->tag == FIELD_Char){
		push_char(frame, field->value.Char);
	}else if(!strcmp(fieldref_descriptor, "D") && field->tag == FIELD_Double){
		push_double(frame, field->value.Double);
	}else if(!strcmp(fieldref_descriptor, "F") && field->tag == FIELD_Float){
		push_float(frame, field->value.Float);
	}else if(!strcmp(fieldref_descriptor, "I") && field->tag == FIELD_Integer){
		push_integer(frame, field->value.Integer);
	}else if(!strcmp(fieldref_descriptor, "J") && field->tag == FIELD_Long){
		push_long(frame, field->value.Long);
	}else if(!strcmp(fieldref_descriptor, "S") && field->tag == FIELD_Short){
		push_short(frame, field->value.Short);
	}else if(!strcmp(fieldref_descriptor, "Z") && field->tag == FIELD_Boolean){
		push_boolean(frame, field->value.Boolean);
	}else{
		if(*fieldref_descriptor == 'L' && field->tag == FIELD_ObjectRef){
			cpush(frame->operands_stack, field->value.ObjectRef);
		}else if(*fieldref_descriptor == '[' && field->tag == FIELD_ArrayRef){
			cpush(frame->operands_stack, field->value.ArrayRef);
		}else{
			fprintf(stderr, "Invalid field descriptor %s\n", fieldref_descriptor);
			exit(ERR_INVDESC);
		}
	}

	free(fieldref_name);
	free(fieldref_descriptor);
}
void GETSTATIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;
	info_t *value = get_constant_pool_entry(frame, cp_index);
	info_t *class_info = get_constant_pool_entry(frame, get_constant_pool_entry(frame, value->Fieldref.class_index)->Class.name_index);
	char *classname = (char *) calloc(class_info->Utf8.length + 1, sizeof(char));
	memcpy(classname, class_info->Utf8.bytes, class_info->Utf8.length);
	if(!is_loaded(jvm->marea, classname)){
		char *classfilename = (char *) calloc(strlen(classname) + 7 /* '.class\0' */, sizeof(char));
		strcat(classfilename, classname);
		load_class(jvm->marea, classfilename);
	}
	free(classname);
	objectref_t *ref = new_objectref();
	reference_of(ref, REF_Fieldref, value);
	cpush(frame->operands_stack, ref);
}
void GOTO_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	int16_t offset;
	memcpy(&offset, &offset_bytes, 2);
	*pc += offset - 1;
}
void GOTO_W_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 offset_bytes = (*pc + 1)[0] << 24 | (*pc + 1)[1] << 16 | (*pc + 1)[2] << 8 | (*pc + 1)[3];
	int32_t offset;
	memcpy(&offset, &offset_bytes, 4);
	*pc += offset - 1;
}
void I2B_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer value = pop_integer(frame);
	byte rvalue = (byte) value;
	push_byte(frame, rvalue);
}
void I2C_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer value = pop_integer(frame);
	byte rvalue = (byte) value;
	push_char(frame, rvalue);
}
void I2D_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer value = pop_integer(frame);
	double rvalue = (double) value;
	push_double(frame, rvalue);
}
void I2F_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer value = pop_integer(frame);
	float rvalue = (float) value;
	push_float(frame, rvalue);
}
void I2L_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer value = pop_integer(frame);
	long rvalue = (long) value;
	push_long(frame, rvalue);
}
void I2S_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer value = pop_integer(frame);
	short rvalue = (short) value;
	push_short(frame, rvalue);
}
void IADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer ivalue1 = 0, ivalue2 = 0;
	integer iresult;

	ivalue1 = pop_integer(frame);

	ivalue2 = pop_integer(frame);

	iresult = ivalue2 + ivalue1;

	push_integer(frame, iresult);
}
void IALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer index = pop_integer(frame);
	array_t *array = pop_array(frame);
	push_integer(frame, *((integer *) at(array, index)));
}
void IAND_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer value1 = pop_integer(frame);
	integer value2 = pop_integer(frame);

	integer result = value2 & value1;
	push_integer(frame, result);
}
void IASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer ivalue = pop_integer(frame);
	integer index = pop_integer(frame);
	array_t *array = pop_array(frame);
	integer *value = (integer *) calloc(1, sizeof(integer));
	*value = ivalue;
	put(array, index, value);
}
void ICONST_M1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
	*ivalue = 0xFFFFFFFF;
	cpush(frame->operands_stack, ivalue);	
}	
void ICONST_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	push_integer(frame, 0);
}
void ICONST_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	push_integer(frame, 1);
}
void ICONST_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	push_integer(frame, 2);
}
void ICONST_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	push_integer(frame, 3);
}
void ICONST_4_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	push_integer(frame, 4);
}
void ICONST_5_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	push_integer(frame, 5);
}
void IDIV_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer ivalue1 = 0, ivalue2 = 0;
	integer iresult;

	ivalue1 = pop_integer(frame);

	ivalue2 = pop_integer(frame);

	iresult = ivalue2 / ivalue1;

	push_integer(frame, iresult);
}
void IF_ACMPEQ_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	if(cpop(frame->operands_stack) == cpop(frame->operands_stack)){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	}else{
		*pc += 2;
	}
}
void IF_ACMPNE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	if(cpop(frame->operands_stack) != cpop(frame->operands_stack)){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	}else{
		*pc += 2;
	}
}
void IF_ICMPEQ_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	int32_t *ivalue1 = (int32_t *) cpop(frame->operands_stack);
	int32_t *ivalue2 = (int32_t *) cpop(frame->operands_stack);
	if(*ivalue2 == *ivalue1){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	} else {
		*pc += 2;
	}
}
void IF_ICMPGE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	int32_t *ivalue1 = (int32_t *) cpop(frame->operands_stack);
	int32_t *ivalue2 = (int32_t *) cpop(frame->operands_stack);
	if(*ivalue2 >= *ivalue1){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	} else {
		*pc += 2;
	}
}
void IF_ICMPGT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	int32_t *ivalue1 = (int32_t *) cpop(frame->operands_stack);
	int32_t *ivalue2 = (int32_t *) cpop(frame->operands_stack);
	if(*ivalue2 > *ivalue1){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	}else{
		*pc += 2;
	}
}
void IF_ICMPLE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	int32_t *ivalue1 = (int32_t *) cpop(frame->operands_stack);
	int32_t *ivalue2 = (int32_t *) cpop(frame->operands_stack);
	if(*ivalue2 <= *ivalue1){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	} else {
		*pc += 2;
	}
}
void IF_ICMPLT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	int32_t *ivalue1 = (int32_t *) cpop(frame->operands_stack);
	int32_t *ivalue2 = (int32_t *) cpop(frame->operands_stack);
	if(*ivalue2 < *ivalue1){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	} else {
		*pc += 2;
	}
}
void IF_ICMPNE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	int32_t *ivalue1 = (int32_t *) cpop(frame->operands_stack);
	int32_t *ivalue2 = (int32_t *) cpop(frame->operands_stack);
	if(*ivalue2 != *ivalue1){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	} else {
		*pc += 2;
	}
}
void IFEQ_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	int32_t *ivalue = (int32_t *) cpop(frame->operands_stack);
	if(0 == *ivalue){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	} else {
		*pc += 2;
	}
}
void IFGE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	int32_t *ivalue = (int32_t *) cpop(frame->operands_stack);
	if(0 >= *ivalue){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	} else {
		*pc += 2;
	}
}
void IFGT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	int32_t *ivalue = (int32_t *) cpop(frame->operands_stack);
	if(0 > *ivalue){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	} else {
		*pc += 2;
	}
}
void IFLE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	int32_t *ivalue = (int32_t *) cpop(frame->operands_stack);

	if(0 <= *ivalue){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	} else {
		*pc += 2;
	}
}
void IFLT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	int32_t *ivalue = (int32_t *) cpop(frame->operands_stack);
	if(0 < *ivalue){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	} else {
		*pc += 2;
	}
}
void IFNE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	int32_t *ivalue = (int32_t *) cpop(frame->operands_stack);
	if(0 != *ivalue){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	} else {
		*pc += 2;
	}
}
void IFNONNULL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	if(NIL != cpop(frame->operands_stack)){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	}else{
		*pc += 2;
	}
}
void IFNULL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 offset_bytes = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	if(NIL == cpop(frame->operands_stack)){
		int16_t offset;
		memcpy(&offset, &offset_bytes, 2);
		*pc += offset - 1;
	}else{
		*pc += 2;
	}
}
void IINC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0];
	u1 cvalue_byte = (*pc + 1)[1]; *pc += 2;
	int8_t cvalue;
	memcpy(&cvalue, &cvalue_byte, 1);
	*((int32_t *) cat(frame->local_variables, lv_index)) += cvalue;
}
void ILOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0]; ++*pc;
	u4 *ivalue = (u4 *) cat(frame->local_variables, lv_index);
	integer i;
	memcpy(&i, ivalue, 4);
	push_integer(frame, i);
}
void ILOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *ivalue = (u4 *) cat(frame->local_variables, 0);
	integer i;
	memcpy(&i, ivalue, 4);
	push_integer(frame, i);
}
void ILOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *ivalue = (u4 *) cat(frame->local_variables, 1);
	integer i;
	memcpy(&i, ivalue, 4);
	push_integer(frame, i);
}
void ILOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *ivalue = (u4 *) cat(frame->local_variables, 2);
	integer i;
	memcpy(&i, ivalue, 4);
	push_integer(frame, i);
}
void ILOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *ivalue = (u4 *) cat(frame->local_variables, 3);
	integer i;
	memcpy(&i, ivalue, 4);
	push_integer(frame, i);
}
void IMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer ivalue1 = 0, ivalue2 = 0;
	integer iresult;

	ivalue1 = pop_integer(frame);

	ivalue2 = pop_integer(frame);

	iresult = ivalue2 * ivalue1;

	push_integer(frame, iresult);
}
void INEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer ivalue1 = 0;
	integer iresult;

	ivalue1 = pop_integer(frame);

	iresult = -ivalue1;

	push_integer(frame, iresult);
}
void INSTANCEOF_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;
	if(get_constant_pool_tag(frame, cp_index) != CONSTANT_Class){
		fprintf(stderr, "Invalid reference in instanceof\n");
		exit(ERR_INVREF);
	}

	objectref_t *ref = (objectref_t *) cpop(frame->operands_stack);
	if(ref->tag == REF_Null){
		push_integer(frame, 0);
	}else{
		ClassFile *refclass = ((instance_t *) ref->object)->class;
		info_t *refnameutf8 = refclass->constant_pool[refclass->constant_pool[refclass->this_class - 1].info->Class.name_index].info;
		char *refclassname = (char *) calloc(refnameutf8->Utf8.length + 1, sizeof(char));
		memcpy(refclassname, refnameutf8->Utf8.bytes, refnameutf8->Utf8.length);

		info_t *entry = get_constant_pool_entry(frame, cp_index);
		info_t *entryutf8 = get_constant_pool_entry(frame, entry->Class.name_index);
		char *entryname = (char *) calloc(entryutf8->Utf8.length + 1, sizeof(char));
		memcpy(entryname, entryutf8->Utf8.bytes, entryutf8->Utf8.length);

		if(!is_loaded(jvm->marea, entryname))
			load_class(jvm->marea, entryname);

		if(!strcmp(refclassname, entryname)){
			push_integer(frame, 1);
		}else{
			u2 i;
			for(i = 0; i < refclass->interfaces_count; i++){
				u1 *bytes = refclass->constant_pool[refclass->constant_pool[refclass->interfaces[i] - 1].info->Class.name_index - 1].info->Utf8.bytes;
				u2 length = refclass->constant_pool[refclass->constant_pool[refclass->interfaces[i] - 1].info->Class.name_index - 1].info->Utf8.length;
				char *interfacename = (char *) calloc(length + 1, sizeof(char));
				memcpy(interfacename, bytes, length);
				if(!strcmp(refclassname, interfacename)){
					push_integer(frame, 1);
					return;
				}
			}
		}
		push_integer(frame, 0);
	}
}
void INVOKEDYNAMIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void INVOKEINTERFACE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void INVOKESPECIAL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;

	info_t *methodref = get_constant_pool_entry(frame, cp_index);
	info_t *methodref_class = get_constant_pool_entry(frame, methodref->Methodref.class_index);

	info_t *methodref_classname_utf8 = get_constant_pool_entry(frame, methodref_class->Class.name_index);
	char *methodref_classname = (char *) calloc(methodref_classname_utf8->Utf8.length + 1, sizeof(char));
	memcpy(methodref_classname, methodref_classname_utf8->Utf8.bytes, methodref_classname_utf8->Utf8.length);

	info_t *methodref_nameandtype_info = get_constant_pool_entry(frame, methodref->Methodref.name_and_type_index);

	info_t *methodref_nameandtype_name_utf8 = get_constant_pool_entry(frame, methodref_nameandtype_info->NameAndType.name_index);
	char *methodref_nameandtype = (char *) calloc(methodref_nameandtype_name_utf8->Utf8.length + 1, sizeof(char));
	memcpy(methodref_nameandtype, methodref_nameandtype_name_utf8->Utf8.bytes, methodref_nameandtype_name_utf8->Utf8.length);

	info_t *methodref_nameandtype_descriptor_utf8 = get_constant_pool_entry(frame, methodref_nameandtype_info->NameAndType.descriptor_index);
	char *methodref_descriptor = (char *) calloc(methodref_nameandtype_descriptor_utf8->Utf8.length + 1, sizeof(char));
	memcpy(methodref_descriptor, methodref_nameandtype_descriptor_utf8->Utf8.bytes, methodref_nameandtype_descriptor_utf8->Utf8.length);

	if(VERBOSE){
		printf("Invoke Special\n");
		printf("MethodRef classname %s\n", methodref_classname);
		printf("MethodRef name %s\n", methodref_nameandtype);
		printf("MethodRef type %s\n", methodref_descriptor);
	}

	if(!is_loaded(jvm->marea, methodref_classname))
		load_class(jvm->marea, methodref_classname);

	frame_t *nf = new_frame();
	cpush(jvm->frame_stack, nf);
	cstack_t *args = new_cstack();
	store_arguments(args, frame, methodref_descriptor);

	objectref_t *ref = (objectref_t *) cpop(frame->operands_stack);
	if(ref->tag != REF_Instance){
		fprintf(stderr, "Invalid object reference to invoke special\n");
		exit(ERR_INVREF);
	}

	char *objectref_classname = get_class_name(ref->object);
	method_info *objectref_method = get_method_info_by_name(ref->object, methodref_nameandtype);
	ClassFile *objectref_class = ((instance_t *) ref->object)->class;

	info_t *objectref_method_descriptorutf8 = objectref_class->constant_pool[objectref_method->descriptor_index - 1].info;
	char *objectref_method_descriptor = (char *) calloc(objectref_method_descriptorutf8->Utf8.length + 1, sizeof(char));
	memcpy(objectref_method_descriptor, objectref_method_descriptorutf8->Utf8.bytes, objectref_method_descriptorutf8->Utf8.length);
	
	if(VERBOSE){
		printf("ObjectRef classname %s\n", objectref_classname);
		printf("ObjectRef type %s\n", objectref_method_descriptor);
	}

	nf->constant_pool = ((instance_t *) ref->object)->class->constant_pool;
	Method specialmethod = get_method_by_name(((instance_t *) ref->object)->class, methodref_nameandtype);
	nf->pc = specialmethod.code;

	ClassFile *invokingclass = ((instance_t *) ref->object)->class;

	if(invokingclass->super_class){
		objectref_t *mref = new_objectref();
		instance_t *inst = new_instance();

		info_t *super = invokingclass->constant_pool[invokingclass->super_class - 1].info;
		info_t *super_utf8 = invokingclass->constant_pool[super->Class.name_index - 1].info;
		char *super_name = (char *) calloc(super_utf8->Utf8.length + 1, sizeof(char));
		memcpy(super_name, super_utf8->Utf8.bytes, super_utf8->Utf8.length);

		instantiate_by_name(inst, jvm->marea, super_name, new_clist());
		reference_of(mref, REF_Instance, inst);
		free(super_name);
		cappend(nf->local_variables, mref);
	}
	load_arguments(args, nf);
	destroy_cstack(args);

	run_method(nf, &specialmethod, jvm);

	destroy_frame(nf);
	cpop(jvm->frame_stack);

	free(objectref_classname);
	free(objectref_method_descriptor);
	free(methodref_classname);
	free(methodref_nameandtype);
	free(methodref_descriptor);

	/* cpop(frame->operands_stack); */
}
void INVOKESTATIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;
	info_t *method_ref = get_constant_pool_entry(frame, cp_index);
	info_t *method_class_ref = get_constant_pool_entry(frame, method_ref->Methodref.class_index);
	info_t *method_class_name_utf8 = get_constant_pool_entry(frame, method_class_ref->Class.name_index);
	char *method_class_name = (char *) calloc(method_class_name_utf8->Utf8.length + 1, sizeof(char));
	memcpy(method_class_name, method_class_name_utf8->Utf8.bytes, method_class_name_utf8->Utf8.length);
	if(!is_loaded(jvm->marea, method_class_name)){
		char *method_class_name_classfile = (char *) calloc(strlen(method_class_name) + 7, sizeof(char));
		strcpy(method_class_name_classfile, method_class_name);
		load_class(jvm->marea, method_class_name_classfile);
		free(method_class_name_classfile);
	}

	/* cria nova frame e se tiver argumentos coloca no vetor de variáveis locais */
	frame_t *method_frame = new_frame();
	ClassFile *method_class = get_class_by_name(jvm->marea, method_class_name);
	if(!method_class)
		exit(ERR_UNKTYPE);
	method_frame->constant_pool = method_class->constant_pool;
	cpush(jvm->frame_stack, method_frame);

	info_t *method_name_and_type = get_constant_pool_entry(frame, method_ref->Methodref.name_and_type_index);
	info_t *method_name_utf8 = get_constant_pool_entry(frame, method_name_and_type->NameAndType.name_index);
	char *method_name = (char *) calloc(method_name_utf8->Utf8.length + 1, sizeof(char));
	memcpy(method_name, method_name_utf8->Utf8.bytes, method_name_utf8->Utf8.length);
	Method method = get_method_by_name(method_class, method_name); 
	free(method_name);
	method_frame->pc = method.code;

	info_t *method_type_utf8 = get_constant_pool_entry(frame, method_name_and_type->NameAndType.descriptor_index);
	char *method_descriptor = (char *) calloc(method_type_utf8->Utf8.length + 1, sizeof(char));
	memcpy(method_descriptor, method_type_utf8->Utf8.bytes, method_type_utf8->Utf8.length);
	if(strlen(method_descriptor)){
		cstack_t *args = new_cstack();
		store_arguments(args, frame, method_descriptor);
		load_arguments(args, method_frame);
		destroy_cstack(args);
	}
	free(method_class_name);
	free(method_descriptor);

	run_method(method_frame, &method, jvm);
	destroy_frame(method_frame);
	cpop(jvm->frame_stack);
}

void INVOKEVIRTUAL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;
	info_t *methodref = get_constant_pool_entry(frame, cp_index);
	
	info_t *method_name_utf8 = get_constant_pool_entry(frame, get_constant_pool_entry(frame, methodref->Methodref.name_and_type_index)->NameAndType.name_index);
	char *method_name = (char *) calloc(method_name_utf8->Utf8.length + 1, sizeof(char));
	memcpy(method_name, method_name_utf8->Utf8.bytes, method_name_utf8->Utf8.length);

	if(!strcmp(method_name, "println")){
		/* Descobre o que é que é pra imprimir (int, float, bool etc.) */
		info_t *method_descriptor_utf8 = get_constant_pool_entry(frame, get_constant_pool_entry(frame, methodref->Methodref.name_and_type_index)->NameAndType.descriptor_index);
		char method_descriptor = method_descriptor_utf8->Utf8.bytes[1];
		switch(method_descriptor){
			case 'D':;
				u4 *dvalue_low = cpop(frame->operands_stack);
				u4 *dvalue_high = cpop(frame->operands_stack);
				u8 value = ((u8) *dvalue_high) << 32 | *dvalue_low;
				double dvalue;
				memcpy(&dvalue, &value, 8);
				printf("%0.16lf\n", dvalue);
				break;
			case 'J':;
				u4 *lvalue_low = cpop(frame->operands_stack);
				u4 *lvalue_high = cpop(frame->operands_stack);
				u8 value_l = ((u8) *lvalue_high) << 32 | *lvalue_low;
				long lvalue;
				memcpy(&lvalue, &value_l, 8);
				printf("%ld\n", lvalue);
				break;
			case 'I':;
				int32_t ivalue;
				memcpy(&ivalue, cpop(frame->operands_stack), 4);
				printf("%d\n", ivalue);
				break;
			case 'Z':
				printf("%s\n", *((u4 *) cpop(frame->operands_stack)) ? "True" : "False");
				break;
			case 'B':;
				int8_t bvalue;
				memcpy(&bvalue, cpop(frame->operands_stack), 1);
				printf("%hhx\n", bvalue);
				break;
			case 'C':;
				int8_t cvalue;
				memcpy(&cvalue, cpop(frame->operands_stack), 1);
				printf("%c\n", cvalue);
				break;
			case 'F':;
				float fvalue;
				memcpy(&fvalue, cpop(frame->operands_stack), 4);
				printf("%f\n", fvalue);
				break;
			case 'S':;
				short svalue;
				memcpy(&svalue, cpop(frame->operands_stack), 2);
				printf("%hi\n", svalue);
				break;
			default:;
				/* printf("%s\n", method_descriptor_utf8->Utf8.bytes); */
				char *descriptor_full = (char *) calloc(method_descriptor_utf8->Utf8.length, sizeof(char));
				memcpy(descriptor_full, method_descriptor_utf8->Utf8.bytes + 1, method_descriptor_utf8->Utf8.length);
				char *ponto_e_virgula = strtok(descriptor_full, ";");
				if(ponto_e_virgula){
					ponto_e_virgula[strlen(ponto_e_virgula) + 1] = '\0';
					ponto_e_virgula[strlen(ponto_e_virgula)] = ';';
				}
				if(!strcmp(ponto_e_virgula, "Ljava/lang/String;")){
					info_t *string_info = cpop(frame->operands_stack);
					info_t *string_utf8 = get_constant_pool_entry(frame, string_info->String.string_index);
					char *string_string = (char *) calloc(string_utf8->Utf8.length + 1, sizeof(char));
					memcpy(string_string, string_utf8->Utf8.bytes, string_utf8->Utf8.length);
					printf("%s\n", string_string);
					free(string_string);
					string_string = NULL;
				}else{
					printf("%s@%p\n", ponto_e_virgula, (void *) cpop(frame->operands_stack));
				}
		}
	}else{
		if(!is_loaded(jvm->marea, method_name))
			load_class(jvm->marea, method_name);

		info_t *method_descriptor_utf8 = \
			get_constant_pool_entry(
					frame,
					get_constant_pool_entry(
						frame,
						methodref->Methodref.name_and_type_index
					)->NameAndType.descriptor_index
			);
		char *method_descriptor = (char *) calloc(method_descriptor_utf8->Utf8.length + 1, sizeof(char));
		memcpy(method_descriptor, method_descriptor_utf8->Utf8.bytes, method_descriptor_utf8->Utf8.length);

		cstack_t *args = new_cstack();
		store_arguments(args, frame, method_descriptor);

		objectref_t *ref = (objectref_t *) cpop(frame->operands_stack);
		ClassFile *class = ((instance_t *) ref->object)->class;
		info_t *classname_utf8 = class->constant_pool[class->constant_pool[class->this_class - 1].info->Class.name_index - 1].info;
		char *classname = (char *) calloc(classname_utf8->Utf8.length + 1, sizeof(char));
		memcpy(classname, classname_utf8->Utf8.bytes, classname_utf8->Utf8.length);

		frame_t *nf = new_frame();
		cpush(jvm->frame_stack, nf);
		nf->constant_pool = class->constant_pool;
		Method virtualmethod = get_method_by_name(class, method_name);
		nf->pc = virtualmethod.code;

		instance_t *inst = new_instance();
		instantiate_by_name(inst, jvm->marea, classname, new_clist());
		objectref_t *this = new_objectref();
		reference_of(this, REF_Instance, inst);
		cappend(nf->local_variables, this);

		load_arguments(args, nf);

		run_method(nf, &virtualmethod, jvm);

		free(classname);
		destroy_instance(inst);
		destroy_objectref(this);
		destroy_frame(nf);
		cpop(jvm->frame_stack);

		/*printf("Executar método\n");
		printf("%s\n", method_name);
		exit(-1);*/
	}
	free(method_name);
}

void IOR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer value1 = pop_integer(frame);
	integer value2 = pop_integer(frame);

	integer result = value2 | value1;
	push_integer(frame, result);
}
void IREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer ivalue1 = 0, ivalue2 = 0;
	integer iresult;

	ivalue1 = pop_integer(frame);

	ivalue2 = pop_integer(frame);

	iresult = ivalue2 % ivalue1;

	push_integer(frame, iresult);
}
void IRETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	cpush(((frame_t *) jvm->frame_stack->top->next->value)->operands_stack, cpop(frame->operands_stack));
	*pc = NULL;
}
void ISHL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer value1 = pop_integer(frame);
	integer value2 = pop_integer(frame);

	integer result = value2 << value1;
	push_integer(frame, result);
}
void ISHR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer value1 = pop_integer(frame);
	integer value2 = pop_integer(frame);

	integer result = value2 >> value1;
	push_integer(frame, result);
}
void ISTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0]; ++*pc;
	int *ivalue = (int *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, lv_index, ivalue);
}
void ISTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	int *ivalue = (int *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 0, ivalue);
}
void ISTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	int *ivalue = (int *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 1, ivalue);
}
void ISTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	int *ivalue = (int *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 2, ivalue);
}
void ISTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	int *ivalue = (int *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 3, ivalue);
}
void ISUB_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer ivalue1 = 0, ivalue2 = 0;
	integer iresult;
	ivalue1 = pop_integer(frame);
	ivalue2 = pop_integer(frame);

	iresult = ivalue2 - ivalue1;
	push_integer(frame, iresult);
}
void IUSHR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer ivalue1 = 0, ivalue2 = 0;
	integer iresult;
	ivalue1 = pop_integer(frame);
	ivalue2 = pop_integer(frame);

	iresult = (integer) ((uint32_t) ivalue2 >> ivalue1); /* O shift right lógico só acontece para tipos unsigned em C */
	push_integer(frame, iresult);
}
void IXOR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer value1 = pop_integer(frame);
	integer value2 = pop_integer(frame);

	integer result = value2 ^ value1;
	push_integer(frame, result);
}
void JSR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void JSR_W_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void L2D_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long value = pop_long(frame);
	double rvalue = (double) value;
	push_double(frame, rvalue);
}
void L2F_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long value = pop_long(frame);
	float rvalue = (float) value;
	push_float(frame, rvalue);
}
void L2I_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long value = pop_long(frame);
	integer rvalue = (integer) value;
	push_integer(frame, rvalue);
}
void LADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long lvalue1, lvalue2, lresult;
	lvalue1 = pop_long(frame);
	lvalue2 = pop_long(frame);

	lresult = lvalue2 + lvalue1;
	push_long(frame, lresult);
}
void LALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LAND_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long value1 = pop_long(frame);
	long value2 = pop_long(frame);

	long result = value2 & value1;
	push_long(frame, result);
}
void LASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LCMP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long value1 = pop_long(frame);
	long value2 = pop_long(frame);

	if(value1 == value2){
		push_long(frame, 0);
	}else if(value1 > value2){
		push_long(frame, 1);
	}else{
		push_long(frame, -1);
	}
}
void LCONST_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_high = (u4 *) calloc(1, sizeof(u4));
	u4 *lvalue_low = (u4 *) calloc(1, sizeof(u4));
	*lvalue_high = 0x00000000;
	*lvalue_low = 0x00000000;
	long l = high_low_to_long(lvalue_low, lvalue_high);
	push_long(frame, l);
}
void LCONST_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_high = (u4 *) calloc(1, sizeof(u4));
	u4 *lvalue_low = (u4 *) calloc(1, sizeof(u4));
	*lvalue_high = 0x00000000;
	*lvalue_low = 0x00000001;
	long l = high_low_to_long(lvalue_low, lvalue_high);
	push_long(frame, l);
}
void LDC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 cp_index = (*pc + 1)[0]; ++*pc;

	info_t *cp_entry = get_constant_pool_entry(frame, cp_index);
	u4 *value = (u4 *) calloc(1, sizeof(u4));

	int tag = get_constant_pool_tag(frame, cp_index);
	switch(tag){
		case CONSTANT_Class:
			*value = cp_entry->Class.name_index;
			break;
		case CONSTANT_String:
			*value = cp_entry->String.string_index;
			break;
		case CONSTANT_Integer:
		case CONSTANT_Float:
			*value = cp_entry->Integer.bytes;
			break;
		default:
			/* TODO: será que eu deveria pushar o negócio sem tratar? */
			break;
	}
	cpush(frame->operands_stack, value);
}
void LDC_W_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;

	info_t *cp_entry = get_constant_pool_entry(frame, cp_index);
	u4 *value = (u4 *) calloc(1, sizeof(u4));

	int tag = get_constant_pool_tag(frame, cp_index);
	switch(tag){
		case CONSTANT_Class:
			*value = cp_entry->Class.name_index;
			break;
		case CONSTANT_String:
			*value = cp_entry->String.string_index;
			break;
		case CONSTANT_Integer:
		case CONSTANT_Float:
			*value = cp_entry->Integer.bytes;
			break;
		default:
			/* TODO: será que eu deveria pushar o negócio sem tratar? */
			break;
	}
	cpush(frame->operands_stack, value);
}
void LDC2_W_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc = *pc + 2;
	info_t *cp_entry = get_constant_pool_entry(frame, cp_index);
	cpush(frame->operands_stack, &cp_entry->Double.high_bytes);
	cpush(frame->operands_stack, &cp_entry->Double.low_bytes);
}
void LDIV_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long lvalue1, lvalue2, lresult;
	lvalue1 = pop_long(frame);
	lvalue2 = pop_long(frame);

	lresult = lvalue2 / lvalue1;
	push_long(frame, lresult);
}
void LLOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0]; ++*pc;
	u4 *lvalue_high = (u4 *) cat(frame->local_variables, lv_index++);
	u4 *lvalue_low = (u4 *) cat(frame->local_variables, lv_index);
	long lvalue = high_low_to_long(lvalue_low, lvalue_high);
	push_long(frame, lvalue);
}
void LLOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_high = (u4 *) cat(frame->local_variables, 0);
	u4 *lvalue_low = (u4 *) cat(frame->local_variables, 1);
	long lvalue = high_low_to_long(lvalue_low, lvalue_high);
	push_long(frame, lvalue);
}
void LLOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_high = (u4 *) cat(frame->local_variables, 1);
	u4 *lvalue_low = (u4 *) cat(frame->local_variables, 2);
	long lvalue = high_low_to_long(lvalue_low, lvalue_high);
	push_long(frame, lvalue);
}
void LLOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_high = (u4 *) cat(frame->local_variables, 2);
	u4 *lvalue_low = (u4 *) cat(frame->local_variables, 3);
	long lvalue = high_low_to_long(lvalue_low, lvalue_high);
	push_long(frame, lvalue);
}
void LLOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_high = (u4 *) cat(frame->local_variables, 3);
	u4 *lvalue_low = (u4 *) cat(frame->local_variables, 4);
	long lvalue = high_low_to_long(lvalue_low, lvalue_high);
	push_long(frame, lvalue);
}
void LMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long lvalue1, lvalue2, lresult;
	lvalue1 = pop_long(frame);
	lvalue2 = pop_long(frame);

	lresult = lvalue2 * lvalue1;
	push_long(frame, lresult);
}
void LNEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long lvalue1, lresult;
	lvalue1 = pop_long(frame);

	lresult = -lvalue1;
	push_long(frame, lresult);
}
void LOOKUPSWITCH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer key = pop_integer(frame);

	u4 rem = (*pc + 1 - bp) % 4;
	u1 *fpc = *pc;
	fpc += rem ? 4 - rem : rem;

	integer default_offset = (fpc+1)[0] << 24 | (fpc+1)[1] << 16 | (fpc+1)[2] << 8 | (fpc+1)[3]; fpc += 4;
	integer npairs = (fpc+1)[0] << 24 | (fpc+1)[1] << 16 | (fpc+1)[2] << 8 | (fpc+1)[3]; fpc += 4;

	integer i, option, offset;
	for(i = 0; i < npairs; i++){
		option = \
				(fpc + 1)[0] << 24 | \
				(fpc + 1)[1] << 16 | \
				(fpc + 1)[2] << 8 | \
				(fpc + 1)[3];
		fpc += 4;
		offset = \
				(fpc + 1)[0] << 24 | \
				(fpc + 1)[1] << 16 | \
				(fpc + 1)[2] << 8 | \
				(fpc + 1)[3];
		fpc += 4;
		if(option == key)
			break;
	}
	if(option != key){
		*pc += default_offset - 1;
	}else{
		*pc += offset - 1;
	}
}
void LOR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long value1 = pop_long(frame);
	long value2 = pop_long(frame);

	long result = value2 | value1;
	push_long(frame, result);
}
void LREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long lvalue1, lvalue2, lresult;
	lvalue1 = pop_long(frame);
	lvalue2 = pop_long(frame);

	lresult = lvalue2 % lvalue1;
	push_long(frame, lresult);
}
void LRETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	void *low = cpop(frame->operands_stack);
	cpush(((frame_t *) jvm->frame_stack->top->next->value)->operands_stack, cpop(frame->operands_stack));
	cpush(((frame_t *) jvm->frame_stack->top->next->value)->operands_stack, low);
}
void LSHL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long value1 = pop_long(frame);
	long value2 = pop_long(frame);

	long result = value2 << value1;
	push_long(frame, result);
}
void LSHR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long value1 = pop_long(frame);
	long value2 = pop_long(frame);

	long result = value2 >> value1;
	push_long(frame, result);
}
void LSTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0]; ++*pc;
	u4 *lvalue_low = (u4 *) cpop(frame->operands_stack);
	u4 *lvalue_high = (u4 *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, lv_index++, lvalue_high);
	cinsert(frame->local_variables, lv_index, lvalue_low);
}
void LSTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_low = (u4 *) cpop(frame->operands_stack);
	u4 *lvalue_high = (u4 *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 0, lvalue_high);
	cinsert(frame->local_variables, 1, lvalue_low);
}
void LSTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_low = (u4 *) cpop(frame->operands_stack);
	u4 *lvalue_high = (u4 *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 1, lvalue_high);
	cinsert(frame->local_variables, 2, lvalue_low);
}
void LSTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_low = (u4 *) cpop(frame->operands_stack);
	u4 *lvalue_high = (u4 *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 2, lvalue_high);
	cinsert(frame->local_variables, 3, lvalue_low);
}
void LSTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_low = (u4 *) cpop(frame->operands_stack);
	u4 *lvalue_high = (u4 *) cpop(frame->operands_stack);
	cinsert(frame->local_variables, 3, lvalue_high);
	cinsert(frame->local_variables, 4, lvalue_low);
}
void LSUB_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long lvalue1, lvalue2, lresult;
	lvalue1 = pop_long(frame);
	lvalue2 = pop_long(frame);

	lresult = lvalue2 - lvalue1;
	push_long(frame, lresult);
}
void LUSHR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long value1 = pop_long(frame);
	long value2 = pop_long(frame);

	long result = (long) ((unsigned long) value2 >> value1); /* O shift right lógico só acontece para tipos unsigned em C */;
	push_long(frame, result);
}
void LXOR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	long value1 = pop_long(frame);
	long value2 = pop_long(frame);

	long result = value2 ^ value1;
	push_long(frame, result);
}
void MONITORENTER_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void MONITOREXIT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void MULTIANEWARRAY_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1];
	u1 dimensions = (*pc + 1)[2]; *pc += 3;

	u1 ref_tag = get_constant_pool_tag(frame, cp_index);
	if(ref_tag != CONSTANT_Class){
		fprintf(stderr, "Invalid class reference in multianewarray\n");
		exit(ERR_INVREF);
	}
	info_t *class_info = get_constant_pool_entry(frame, cp_index);
	info_t *class_info_utf8 = get_constant_pool_entry(frame, class_info->Class.name_index);
	char *class_name = (char *) calloc(class_info_utf8->Utf8.length + 1, sizeof(char));
	memcpy(class_name, class_info_utf8->Utf8.bytes, class_info_utf8->Utf8.length);

	frame_t count_frame;
	cstack_t *counts = new_cstack();
	count_frame.operands_stack = counts;

	u1 i;
	for(i = 0; i < dimensions; i++)
		cpush(count_frame.operands_stack, cpop(frame->operands_stack));

	/* COM UM PASSO DE FÉ, DIZEMOS QUE ESTÁ CERTO */
	/* Ao final de tudo ARRAY é pra ter o MULTIARRAY*/
	array_t *array = new_array();
	array_t *arrays = new_array();
	array_of(arrays, ARR_RefArray, 1);
	put(arrays, 0, array);
	for(i = 0; i < dimensions; i++){
		integer k;
		integer count = pop_integer(&count_frame);
		array_t *next_arrays = new_array();
		array_of(next_arrays, ARR_RefArray, count);
		for(k = 0; k < arrays->length; k++){
			/* TODO: devia fazer um iterator */
			array_t *narray = at(arrays, k);
			array_of(narray, ARR_RefArray, count);
			integer j;
			for(j = 0; j < count; j++){
				array_t *nnarray = new_array();
				put(narray, 0, nnarray);
				put(next_arrays, 0, nnarray);
				if(i + 1 == dimensions){
					array_of(nnarray, ARR_RefClass, pop_integer(&count_frame));
					array_of_class(nnarray, class_name);
				}
			}
		}
		destroy_array(arrays);
		arrays = next_arrays;
	}
	destroy_array(arrays);

	free(class_name);

	objectref_t *ref = new_objectref();
	reference_of(ref, REF_Array, array);
	cpush(frame->operands_stack, ref);
}
void NEW_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;

	u1 tag = get_constant_pool_tag(frame, cp_index);
	info_t *template = get_constant_pool_entry(frame, cp_index);
	instance_t *inst = new_instance();
	if(tag == CONSTANT_Class){
		/* Falta inicializar o objeto (<init>) */
		instantiate_by_index(inst, jvm, template->Class.name_index, new_clist());

		/*frame_t *init_frame = new_frame();
		cpush(jvm->frame_stack, init_frame);
		init_frame->constant_pool = inst->class->constant_pool;
		objectref_t *init_this_ref = new_objectref();

		reference_of(init_this_ref, REF_Instance, inst);
		cappend(init_frame->local_variables, init_this_ref);
		Method method_init = get_method_by_name(inst->class, "<init>");
		init_frame->pc = method_init.code;
		run_method(init_frame, &method_init, jvm);
		destroy_frame(init_frame);
		cpop(jvm->frame_stack);*/
	}

	objectref_t *ref = new_objectref();
	reference_of(ref, REF_Instance, inst);
	cpush(jvm->heap, ref);
	cpush(frame->operands_stack, ref);
}
void NEWARRAY_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 tag = (*pc + 1)[0]; ++*pc;
	array_t *array = new_array();
	array_of(array, tag, pop_integer(frame));
	cpush(frame->operands_stack, array);
}
void NOP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	return;
}
void POP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	cpop(frame->operands_stack);
}
void POP2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	cpop(frame->operands_stack);
	cpop(frame->operands_stack);
}
void PUTFIELD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;
	info_t *fieldref = get_constant_pool_entry(frame, cp_index);
	info_t *fieldref_nameandtype = get_constant_pool_entry(frame, fieldref->Fieldref.name_and_type_index);
	info_t *fieldref_descriptor_utf8 = get_constant_pool_entry(frame, fieldref_nameandtype->NameAndType.descriptor_index);
	char *fieldref_descriptor = (char *) calloc(fieldref_descriptor_utf8->Utf8.length + 1, sizeof(char));
	memcpy(fieldref_descriptor, fieldref_descriptor_utf8->Utf8.bytes, fieldref_descriptor_utf8->Utf8.length);

	field_object_t *field = new_field_object();
	field->ref = fieldref;

	if(!strcmp(fieldref_descriptor, "F")){

		field->value.Float = pop_float(frame);
		field->tag = FIELD_Float;
	}else if(!strcmp(fieldref_descriptor, "B")){
		field->value.Byte = pop_byte(frame);
		field->tag = FIELD_Byte;
	}else if(!strcmp(fieldref_descriptor, "C")){
		field->value.Char = pop_char(frame);
		field->tag = FIELD_Char;
	}else if(!strcmp(fieldref_descriptor, "S")){
		field->value.Short = pop_short(frame);
		field->tag = FIELD_Short;
	}else if(!strcmp(fieldref_descriptor, "Z")){
		field->value.Boolean = pop_boolean(frame);
		field->tag = FIELD_Boolean;
	}else if(!strcmp(fieldref_descriptor, "I")){
		field->value.Integer = pop_integer(frame);
		field->tag = FIELD_Integer;
	}else if(!strcmp(fieldref_descriptor, "L")){
		field->value.Long = pop_long(frame);
		field->tag = FIELD_Long;
	}else if(!strcmp(fieldref_descriptor, "D")){
		field->value.Double = pop_double(frame);
		field->tag = FIELD_Double;
	}else{
		if(*fieldref_descriptor == 'L'){
			field->value.ObjectRef = cpop(frame->operands_stack);
			field->tag = FIELD_ObjectRef;
		}else if(*fieldref_descriptor == '['){
			field->value.ArrayRef = cpop(frame->operands_stack);
			field->tag = FIELD_ArrayRef;
		}else{
			fprintf(stderr, "Invalid field descriptor %s\n", fieldref_descriptor);
			exit(ERR_INVDESC);
		}
	}
	objectref_t *ref = cpop(frame->operands_stack);
	if(ref->tag != REF_Instance){
		fprintf(stderr, "Invalid reference in putfield\n");
		exit(ERR_INVREF);
	}
	cappend(((instance_t *) ref->object)->variables, field);
	free(fieldref_descriptor);
}
void PUTSTATIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void RET_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void RETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	*pc = NULL;
}
void SALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer index = pop_integer(frame);
	array_t *array = pop_array(frame);
	short *svalue = (short *) at(array, index);
	push_short(frame, *svalue);
}
void SASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	short *svalue = (short *) calloc(1, sizeof(short));
	*svalue = pop_short(frame);
	integer index = pop_integer(frame);
	array_t *array = pop_array(frame);
	put(array, index, svalue);
}
void SIPUSH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer value = 0x00000000;
	memcpy(&value, *pc + 1, 2);
	*pc += 2;
	push_integer(frame, value);
}
void SWAP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	void *value1 = cpop(frame->operands_stack);
	void *value2 = cpop(frame->operands_stack);
	cpush(frame->operands_stack, value1);
	cpush(frame->operands_stack, value2);
}
void TABLESWITCH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	integer index = pop_integer(frame);
	u4 rem = (*pc + 1 - bp) % 4;
	/* Se rem for diferente de zero, soma 4 - rem, senão zero */
	/* Alinhando o pc */
	u1 *fpc = *pc;
	fpc += rem ? 4 - rem : rem;
	u4 default_offset_bytes = (fpc+1)[0] << 24 | (fpc+1)[1] << 16 | (fpc+1)[2] << 8 | (fpc+1)[3]; fpc += 4;
	u4 low = (fpc+1)[0] << 24 | (fpc+1)[1] << 16 | (fpc+1)[2] << 8 | (fpc+1)[3]; fpc += 4;
	u4 high = (fpc+1)[0] << 24 | (fpc+1)[1] << 16 | (fpc+1)[2] << 8 | (fpc+1)[3]; fpc += 4;
	u4 x = high - low + 1;
	int i, j;
	u4 offset_bytes;
	for(i = 0, j = low; i < x; i++, j++){
		offset_bytes = \
				(fpc + 1)[0] << 24 | \
				(fpc + 1)[1] << 16 | \
				(fpc + 1)[2] << 8 | \
				(fpc + 1)[3];
		fpc += 4;
		if(j == index)
			break;
	}
	if(i == x){
		integer *default_offset = (integer *) &default_offset_bytes;
		*pc += *default_offset - 1;
	}else{
		integer *offset = (integer *) &offset_bytes;
		*pc += *offset - 1;
	}
}
void WIDE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
