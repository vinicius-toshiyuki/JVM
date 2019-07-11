#include <stdio.h>
#include "../include/mnemonic.h"
#include "../include/bytecode.h"
#include "../include/constant_pool.h"
#include "../include/method_area.h"
#include "../include/jvm.h"
#include "../include/info.h"
#include <math.h>

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
  [0xca] = BREAKPOINT_handler,
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

void AALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void AASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void ACONST_NULL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  cpush(frame->operands_stack, NIL);
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
void ANEWARRAY_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void ARETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void ARRAYLENGTH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void BALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void BASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void BIPUSH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
  if((*pc + 1)[0] >> 7 & 0x01){
    *ivalue |= 0xFFFFFFFF;
  }
  memcpy(ivalue, (*pc)++ + 1, 1);
  cpush(frame->operands_stack, ivalue);
}
void BREAKPOINT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void CALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void CASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void CHECKCAST_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void D2F_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void D2I_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void D2L_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void DADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_low1 = NULL, *dvalue_high1 = NULL, *dvalue_low2 = NULL, *dvalue_high2 = NULL;
	double dvalue1, dvalue2, dresult;
	u8 value1 = 0x000000000000000, value2 = 0x000000000000000;

	dvalue_low1 = cpop(frame->operands_stack);
	dvalue_high1 = cpop(frame->operands_stack);
	dvalue_low2 = cpop(frame->operands_stack);
	dvalue_high2 = cpop(frame->operands_stack);

	value1 = ((u8) *dvalue_high1) << 32 | *dvalue_low1;
	memcpy(&dvalue1, &value1, 8);

	value2 = ((u8) *dvalue_high2) << 32 | *dvalue_low2;
	memcpy(&dvalue2, &value2, 8);

	dresult = dvalue1 + dvalue2;
	memcpy(&value1, &dresult, 8);

	u4 *dresult_low = (u4 *) calloc(1, sizeof(u4));
	u4 *dresult_high = (u4 *) calloc(1, sizeof(u4));
	memcpy(dresult_low, &value1, 4);
	value1 >>= 32;
	memcpy(dresult_high, &value1, 4);
	cpush(frame->operands_stack, dresult_high);
	cpush(frame->operands_stack, dresult_low);
}
void DALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void DASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void DCMPG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void DCMPL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
  u4 *dvalue_low1 = NULL, *dvalue_high1 = NULL, *dvalue_low2 = NULL, *dvalue_high2 = NULL;
	double dvalue1, dvalue2, dresult;
	u8 value1 = 0x000000000000000, value2 = 0x000000000000000;

	dvalue_low1 = cpop(frame->operands_stack);
	dvalue_high1 = cpop(frame->operands_stack);
	dvalue_low2 = cpop(frame->operands_stack);
	dvalue_high2 = cpop(frame->operands_stack);

	value1 = ((u8) *dvalue_high1) << 32 | *dvalue_low1;
	memcpy(&dvalue1, &value1, 8);

	value2 = ((u8) *dvalue_high2) << 32 | *dvalue_low2;
	memcpy(&dvalue2, &value2, 8);

	dresult = dvalue2 / dvalue1;
	memcpy(&value1, &dresult, 8);

	u4 *dresult_low = (u4 *) calloc(1, sizeof(u4));
	u4 *dresult_high = (u4 *) calloc(1, sizeof(u4));
	memcpy(dresult_low, &value1, 4);
	value1 >>= 32;
	memcpy(dresult_high, &value1, 4);
	cpush(frame->operands_stack, dresult_high);
	cpush(frame->operands_stack, dresult_low);
}
void DLOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0]; ++*pc;
	u4 *dvalue_high = (u4 *) cat(frame->local_variables, lv_index++);
	u4 *dvalue_low = (u4 *) cat(frame->local_variables, lv_index);
	cpush(frame->operands_stack, dvalue_high);
	cpush(frame->operands_stack, dvalue_low);
}
void DLOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_high = (u4 *) cat(frame->local_variables, 0);
	u4 *dvalue_low = (u4 *) cat(frame->local_variables, 1);
	cpush(frame->operands_stack, dvalue_high);
	cpush(frame->operands_stack, dvalue_low);
}
void DLOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_high = (u4 *) cat(frame->local_variables, 1);
	u4 *dvalue_low = (u4 *) cat(frame->local_variables, 2);
	cpush(frame->operands_stack, dvalue_high);
	cpush(frame->operands_stack, dvalue_low);
}
void DLOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_high = (u4 *) cat(frame->local_variables, 2);
	u4 *dvalue_low = (u4 *) cat(frame->local_variables, 3);
	cpush(frame->operands_stack, dvalue_high);
	cpush(frame->operands_stack, dvalue_low);
}
void DLOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *dvalue_high = (u4 *) cat(frame->local_variables, 3);
	u4 *dvalue_low = (u4 *) cat(frame->local_variables, 4);
	cpush(frame->operands_stack, dvalue_high);
	cpush(frame->operands_stack, dvalue_low);
}
void DMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *dvalue_low1 = NULL, *dvalue_high1 = NULL, *dvalue_low2 = NULL, *dvalue_high2 = NULL;
	double dvalue1, dvalue2, dresult;
	u8 value1 = 0x000000000000000, value2 = 0x000000000000000;

	dvalue_low1 = cpop(frame->operands_stack);
	dvalue_high1 = cpop(frame->operands_stack);
	dvalue_low2 = cpop(frame->operands_stack);
	dvalue_high2 = cpop(frame->operands_stack);

	value1 = ((u8) *dvalue_high1) << 32 | *dvalue_low1;
	memcpy(&dvalue1, &value1, 8);

	value2 = ((u8) *dvalue_high2) << 32 | *dvalue_low2;
	memcpy(&dvalue2, &value2, 8);

	dresult = dvalue1 * dvalue2;
	memcpy(&value1, &dresult, 8);

	u4 *dresult_low = (u4 *) calloc(1, sizeof(u4));
	u4 *dresult_high = (u4 *) calloc(1, sizeof(u4));
	memcpy(dresult_low, &value1, 4);
	value1 >>= 32;
	memcpy(dresult_high, &value1, 4);
	cpush(frame->operands_stack, dresult_high);
	cpush(frame->operands_stack, dresult_low);
}
void DNEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *dvalue_low = NULL, *dvalue_high = NULL;
	double dvalue1, dresult;
	u8 value1 = 0x000000000000000;

	dvalue_low = cpop(frame->operands_stack);
	dvalue_high = cpop(frame->operands_stack);

	value1 = ((u8) *dvalue_high) << 32 | *dvalue_low;
	memcpy(&dvalue1, &value1, 8);

	dresult = -dvalue1;
	memcpy(&value1, &dresult, 8);

	u4 *dresult_low = (u4 *) calloc(1, sizeof(u4));
	u4 *dresult_high = (u4 *) calloc(1, sizeof(u4));
	memcpy(dresult_low, &value1, 4);
	value1 >>= 32;
	memcpy(dresult_high, &value1, 4);
	cpush(frame->operands_stack, dresult_high);
	cpush(frame->operands_stack, dresult_low);
}
void DREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *dvalue_low1 = NULL, *dvalue_high1 = NULL, *dvalue_low2 = NULL, *dvalue_high2 = NULL;
	double dvalue1, dvalue2, dresult;
	u8 value1 = 0x000000000000000, value2 = 0x000000000000000;

	dvalue_low1 = cpop(frame->operands_stack);
	dvalue_high1 = cpop(frame->operands_stack);
	dvalue_low2 = cpop(frame->operands_stack);
	dvalue_high2 = cpop(frame->operands_stack);

	value1 = ((u8) *dvalue_high1) << 32 | *dvalue_low1;
	memcpy(&dvalue1, &value1, 8);

	value2 = ((u8) *dvalue_high2) << 32 | *dvalue_low2;
	memcpy(&dvalue2, &value2, 8);

	dresult = fmod(dvalue2, dvalue1);
	memcpy(&value1, &dresult, 8);

	u4 *dresult_low = (u4 *) calloc(1, sizeof(u4));
	u4 *dresult_high = (u4 *) calloc(1, sizeof(u4));
	memcpy(dresult_low, &value1, 4);
	value1 >>= 32;
	memcpy(dresult_high, &value1, 4);
	cpush(frame->operands_stack, dresult_high);
	cpush(frame->operands_stack, dresult_low);
}
void DRETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
  u4 *dvalue_low1 = NULL, *dvalue_high1 = NULL, *dvalue_low2 = NULL, *dvalue_high2 = NULL;
	double dvalue1, dvalue2, dresult;
	u8 value1 = 0x000000000000000, value2 = 0x000000000000000;

	dvalue_low1 = cpop(frame->operands_stack);
	dvalue_high1 = cpop(frame->operands_stack);
	dvalue_low2 = cpop(frame->operands_stack);
	dvalue_high2 = cpop(frame->operands_stack);

	value1 = ((u8) *dvalue_high1) << 32 | *dvalue_low1;
	memcpy(&dvalue1, &value1, 8);

	value2 = ((u8) *dvalue_high2) << 32 | *dvalue_low2;
	memcpy(&dvalue2, &value2, 8);

	dresult = dvalue2 - dvalue1;
	memcpy(&value1, &dresult, 8);

	u4 *dresult_low = (u4 *) calloc(1, sizeof(u4));
	u4 *dresult_high = (u4 *) calloc(1, sizeof(u4));
	memcpy(dresult_low, &value1, 4);
	value1 >>= 32;
	memcpy(dresult_high, &value1, 4);
	cpush(frame->operands_stack, dresult_high);
	cpush(frame->operands_stack, dresult_low);
}
void DUP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  void *top = frame->operands_stack->top;
  cpush(frame->operands_stack, top);
}
void DUP_X1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void DUP_X2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void DUP2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void DUP2_X1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void DUP2_X2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void F2D_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void F2I_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void F2L_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void FADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  float *ivalue1 = NULL, *ivalue2 = NULL;
	float *iresult;
	u4 *value1 = NULL, *value2 = NULL;

	value1 = (u4 *) cpop(frame->operands_stack);
  ivalue1 = (float *) value1;

	value2 = (u4 *) cpop(frame->operands_stack);
	ivalue2 = (float *) value2;

  iresult = calloc(1, sizeof(float));
	*iresult = *ivalue2 + *ivalue1;

	cpush(frame->operands_stack, iresult);
}
void FALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void FASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void FCMPG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void FCMPL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
  float *ivalue1 = NULL, *ivalue2 = NULL;
	float *iresult;
	u4 *value1 = NULL, *value2 = NULL;

	value1 = (u4 *) cpop(frame->operands_stack);
  ivalue1 = (float *) value1;

	value2 = (u4 *) cpop(frame->operands_stack);
	ivalue2 = (float *) value2;

  iresult = calloc(1, sizeof(float));
  
	*iresult = *ivalue2 / *ivalue1;

	cpush(frame->operands_stack, iresult);
}
void FLOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0]; ++*pc;
	u8 *fvalue = (u8 *) cat(frame->local_variables, lv_index);
	cpush(frame->operands_stack, fvalue);
}
void FLOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u8 *fvalue = (u8 *) cat(frame->local_variables, 0);
	cpush(frame->operands_stack, fvalue);
}
void FLOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u8 *fvalue = (u8 *) cat(frame->local_variables, 1);
	cpush(frame->operands_stack, fvalue);
}
void FLOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u8 *fvalue = (u8 *) cat(frame->local_variables, 2);
	cpush(frame->operands_stack, fvalue);
}
void FLOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u8 *fvalue = (u8 *) cat(frame->local_variables, 3);
	cpush(frame->operands_stack, fvalue);
}
void FMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  float *ivalue1 = NULL, *ivalue2 = NULL;
	float *iresult;
	u4 *value1 = NULL, *value2 = NULL;

	value1 = (u4 *) cpop(frame->operands_stack);
  ivalue1 = (float *) value1;

	value2 = (u4 *) cpop(frame->operands_stack);
	ivalue2 = (float *) value2;

  iresult = calloc(1, sizeof(float));
	*iresult = *ivalue2 * *ivalue1;

	cpush(frame->operands_stack, iresult);
}
void FNEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  float *ivalue1 = NULL;
	float *iresult;
	u4 *value1 = NULL;

	value1 = (u4 *) cpop(frame->operands_stack);
  ivalue1 = (float *) value1;

  iresult = calloc(1, sizeof(float));
	*iresult = -*ivalue1;

	cpush(frame->operands_stack, iresult);
}
void FREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  float *ivalue1 = NULL, *ivalue2 = NULL;
	float *iresult;
	u4 *value1 = NULL, *value2 = NULL;

	value1 = (u4 *) cpop(frame->operands_stack);
  ivalue1 = (float *) value1;

	value2 = (u4 *) cpop(frame->operands_stack);
	ivalue2 = (float *) value2;

  iresult = calloc(1, sizeof(float));
	*iresult = (float) fmod(*ivalue2, *ivalue1);

	cpush(frame->operands_stack, iresult);
}
void FRETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
  float *ivalue1 = NULL, *ivalue2 = NULL;
	float *iresult;
	u4 *value1 = NULL, *value2 = NULL;

	value1 = (u4 *) cpop(frame->operands_stack);
  ivalue1 = (float *) value1;

	value2 = (u4 *) cpop(frame->operands_stack);
	ivalue2 = (float *) value2;

  iresult = calloc(1, sizeof(float));
	*iresult = *ivalue2 - *ivalue1;

	cpush(frame->operands_stack, iresult);
}
void GETFIELD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void GETSTATIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;
	/* objectref aqui é uma referência simbólica para um field, que é um Fieldref */
	CONSTANT_Fieldref_info *value = (CONSTANT_Fieldref_info *) get_constant_pool_entry(frame, cp_index);
	/* tem que resolver a referência */
	info_t *class_info = get_constant_pool_entry(frame, get_constant_pool_entry(frame, value->class_index)->Class.name_index);
	char *classname = (char *) calloc(class_info->Utf8.length + 1, sizeof(char));
	memcpy(classname, class_info->Utf8.bytes, class_info->Utf8.length);
	if(!is_loaded(jvm->marea, classname)){
		char *classfilename = (char *) calloc(strlen(classname) + 9 /* './' e '.class\0' */, sizeof(char));
		strcpy(classfilename, "./");
		strcat(classfilename, classname);
		strcat(classfilename, ".class");
		load_class(jvm->marea, classfilename);
	}
	free(classname);
	/* TODO: falta resolver a referência e entender como fazer o tal do println */
	/*
		É basicamente ver se o campo existe e se a classe atual tem  (vamos assumir que sim ;p)
		VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVpermissão de acessoVV
		When resolving a field reference, field resolution first attempts to look up the referenced field in C and its superclasses:
			If C declares a field with the name and descriptor specified by the field reference, field lookup succeeds. The declared field is the result of the field lookup.
			Otherwise, field lookup is applied recursively to the direct superinterfaces of the specified class or interface C.
			Otherwise, if C has a superclass S, field lookup is applied recursively to S.
			Otherwise, field lookup fails.
		Then:
			If field lookup fails, field resolution throws a NoSuchFieldError.
			Otherwise, if field lookup succeeds but the referenced field is not accessible (§5.4.4) to D, field resolution throws an IllegalAccessError.
			Otherwise, let <E, L1> be the class or interface in which the referenced field is actually declared and let L2 be the defining loader of D.
			Given that the type of the referenced field is Tf, let T be Tf if Tf is not an array type, and let T be the element type (§2.4) of Tf otherwise.
			The Java Virtual Machine must impose the loading constraint that TL1 = TL2 (§5.3.4).
	*/
	cpush(frame->operands_stack, value);
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
  int32_t *ivalue = (int32_t *) cpop(frame->operands_stack);
  int8_t aux = (int8_t) *ivalue;
  u4 *brvalue = (u4 *) calloc(1, sizeof(u4));
  memcpy(brvalue, &aux, 1);

  cpush(frame->operands_stack, brvalue);
}
void I2C_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  int32_t *ivalue = (int32_t *) cpop(frame->operands_stack);
  int8_t aux = (int8_t) *ivalue;
  u4 *crvalue = (u4 *) calloc(1, sizeof(u4));
  memcpy(crvalue, &aux, 1);
  
  cpush(frame->operands_stack, crvalue);
}
void I2D_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  int32_t *ivalue = (int32_t *) cpop(frame->operands_stack);
  double aux = (double) *ivalue;
  u8 *dvalue = (u8 *) &aux;

  u4 *dhigh = (u4 *) calloc(1, sizeof(u4));
  u4 *dlow = (u4 *) calloc(1, sizeof(u4));
  *dhigh = *dvalue >> 32;
  *dlow |= *dvalue;
  
  cpush(frame->operands_stack, dhigh);
  cpush(frame->operands_stack, dlow);
}
void I2F_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  int32_t *ivalue = (int32_t *) cpop(frame->operands_stack);
  float aux = (float) *ivalue;
  u4 *fvalue = (u4 *) &aux;

  u4 *frvalue = (u4 *) calloc(1, sizeof(u4));
  *frvalue = *fvalue;
  cpush(frame->operands_stack, frvalue);
}
void I2L_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  int32_t *ivalue = (int32_t *) cpop(frame->operands_stack);
  int64_t aux = (int64_t) *ivalue;
  u8 *lvalue = (u8 *) &aux;

  u4 *lhigh = (u4 *) calloc(1, sizeof(u4));
  u4 *llow = (u4 *) calloc(1, sizeof(u4));
  *lhigh = *lvalue >> 32;
  *llow |= *lvalue;

  cpush(frame->operands_stack, lhigh);
  cpush(frame->operands_stack, llow);
}
void I2S_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  int32_t *ivalue1 = NULL, *ivalue2 = NULL;
	int32_t *iresult;
	u4 *value1 = NULL, *value2 = NULL;

	value1 = (u4 *) cpop(frame->operands_stack);
  ivalue1 = (int32_t *) value1;

	value2 = (u4 *) cpop(frame->operands_stack);
	ivalue2 = (int32_t *) value2;

  iresult = calloc(1, sizeof(int32_t));
	*iresult = *ivalue2 + *ivalue1;

	cpush(frame->operands_stack, iresult);
}
void IALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IAND_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void ICONST_M1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
  *ivalue = 0xFFFFFFFF;
  cpush(frame->operands_stack, ivalue);  
}  
void ICONST_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
  *ivalue = 0;
  cpush(frame->operands_stack, ivalue);
}
void ICONST_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
  *ivalue = 1;
  cpush(frame->operands_stack, ivalue);
}
void ICONST_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
  *ivalue = 2;
  cpush(frame->operands_stack, ivalue);
}
void ICONST_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
  *ivalue = 3;
  cpush(frame->operands_stack, ivalue);
}
void ICONST_4_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
  *ivalue = 4;
  cpush(frame->operands_stack, ivalue);
}
void ICONST_5_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
  *ivalue = 5;
  cpush(frame->operands_stack, ivalue);
}
void IDIV_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  int32_t *ivalue1 = NULL, *ivalue2 = NULL;
	int32_t *iresult;
	u4 *value1 = NULL, *value2 = NULL;

	value1 = (u4 *) cpop(frame->operands_stack);
  ivalue1 = (int32_t *) value1;

	value2 = (u4 *) cpop(frame->operands_stack);
	ivalue2 = (int32_t *) value2;

  iresult = calloc(1, sizeof(int32_t));
	*iresult = *ivalue2 / *ivalue1;

	cpush(frame->operands_stack, iresult);
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
	cpush(frame->operands_stack, ivalue);
}
void ILOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *ivalue = (u4 *) cat(frame->local_variables, 0);
	cpush(frame->operands_stack, ivalue);
}
void ILOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *ivalue = (u4 *) cat(frame->local_variables, 1);
	cpush(frame->operands_stack, ivalue);
}
void ILOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *ivalue = (u4 *) cat(frame->local_variables, 2);
	cpush(frame->operands_stack, ivalue);
}
void ILOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *ivalue = (u4 *) cat(frame->local_variables, 3);
	cpush(frame->operands_stack, ivalue);
}
void IMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  int32_t *ivalue1 = NULL, *ivalue2 = NULL;
	int32_t *iresult;
	u4 *value1 = NULL, *value2 = NULL;

	value1 = (u4 *) cpop(frame->operands_stack);
  ivalue1 = (int32_t *) value1;

	value2 = (u4 *) cpop(frame->operands_stack);
	ivalue2 = (int32_t *) value2;

  iresult = calloc(1, sizeof(int32_t));
	*iresult = *ivalue2 * *ivalue1;

	cpush(frame->operands_stack, iresult);
}
void INEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  int32_t *ivalue1 = NULL;
	int32_t *iresult;
	u4 *value1 = NULL;

	value1 = (u4 *) cpop(frame->operands_stack);
  ivalue1 = (int32_t *) value1;

  iresult = calloc(1, sizeof(int32_t));
	*iresult = -*ivalue1;

	cpush(frame->operands_stack, iresult);
}
void INSTANCEOF_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  /*u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;
  info_t *objectref = (info_t *) cpop(frame->operands_stack);
  if(objectref != NIL){
    info_t *cp_entry = get_constant_pool_entry(frame, cp_index);
    u1 cp_tag = get_constant_pool_tag(frame, cp_index);
  }*/
}
void INVOKEDYNAMIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void INVOKEINTERFACE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void INVOKESPECIAL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  
}
void INVOKESTATIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  // u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;
  // info_t *method_ref = get_constant_pool_entry(frame, cp_index);
  // info_t *method_class_ref = get_constant_pool_entry(frame, method_ref->Methodref.class_index);
  // info_t *method_class_name_utf8 = get_constant_pool_entry(frame, method_class_ref->Class.name_index);
  // char *method_class_name = (char *) calloc(method_class_name_utf8->Utf8.length + 1, sizeof(char));
  // memcpy(method_class_name, method_class_name_utf8->Utf8.bytes, method_class_name_utf8->Utf8.length);
  // if(!is_loaded(jvm->marea, method_class_name)){
  //   printf("Is not loaded %s\n", method_class_name);
  //   load_class(jvm->marea, method_class_name);
  // }
  // info_t *method_name_and_type = get_constant_pool_entry(frame, method_ref->Methodref.name_and_type_index);
  // info_t *method_type_utf8 = get_constant_pool_entry(frame, method_name_and_type->NameAndType.descriptor_index);
  // char *method_descriptor = (char *) calloc(method_type_utf8->Utf8.length + 1, sizeof(char));
  // memcpy(method_descriptor, method_type_utf8)
  // free(method_class_name);

}
/*
Na programação orientada a objetos uma função virtual ou método virtual é 
uma função ou método cujo comportamento pode ser 
sobrescrito em uma classe herdeira por uma função com a 
mesma assinatura. 
Esse conceito é uma parte 
muito importante do polimorfismo em 
programação orientada a objetos (OOP). */
void INVOKEVIRTUAL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  /* se for print só imprime */
  /* java/lang/System.class tem o field out */
  /* System.out.println() */
  /* out é um campo do tipo PrintStream */
  /* O que está sendo chamado é o método println (D)V do objeto out */
  /* ou faz um if aqui dentro ou faz um método nativo */
  
/*
The unsigned indexbyte1 and indexbyte2 are used to construct an index into the run-time constant pool of the current class (§2.6), where the value of the index is (indexbyte1 << 8) | indexbyte2. The run-time constant pool item at that index must be a symbolic reference to a method (§5.1), which gives the name and descriptor (§4.3.3) of the method as well as a symbolic reference to the class in which the method is to be found. The named method is resolved (§5.4.3.3). The resolved method must not be an instance initialization method (§2.9) or the class or interface initialization method (§2.9). Finally, if the resolved method is protected (§4.6), and it is a member of a superclass of the current class, and the method is not declared in the same run-time package (§5.3) as the current class, then the class of objectref must be either the current class or a subclass of the current class.
If the resolved method is not signature polymorphic (§2.9), then the invokevirtual instruction proceeds as follows.
Let C = System be the class of objectref = out. The actual method = println to be invoked is selected by the following lookup procedure:
    If C contains a declaration for an instance method m that overrides (§5.4.5) the resolved method, then m is the method to be invoked, and the lookup procedure terminates.
    Otherwise, if C has a superclass, this same lookup procedure is performed recursively using the direct superclass of C; the method to be invoked is the result of the recursive invocation of this lookup procedure.
If the method is not native, the nargs argument values and objectref are popped from the operand stack. A new frame is created on the Java Virtual Machine stack for the method being invoked. The objectref and the argument values are consecutively made the values of local variables of the new frame, with objectref in local variable 0, arg1 in local variable 1 (or, if arg1 is of type long or double, in local variables 1 and 2), and so on. Any argument value that is of a floating-point type undergoes value set conversion (§2.8.3) prior to being stored in a local variable. The new frame is then made current, and the Java Virtual Machine pc is set to the opcode of the first instruction of the method to be invoked. Execution continues with the first instruction of the method.
If the method is native and the platform-dependent code that implements it has not yet been bound (§5.6) into the Java Virtual Machine, that is done. The nargs argument values and objectref are popped from the operand stack and are passed as parameters to the code that implements the method. Any argument value that is of a floating-point type undergoes value set conversion (§2.8.3) prior to being passed as a parameter. The parameters are passed and the code is invoked in an implementation-dependent manner. When the platform-dependent code returns, the following take place:
    If the native method is synchronized, the monitor associated with objectref is updated and possibly exited as if by execution of a monitorexit instruction (§monitorexit) in the current thread.
    If the native method returns a value, the return value of the platform-dependent code is converted in an implementation-dependent way to the return type of the native method and pushed onto the operand stack.
If the resolved method is signature polymorphic (§2.9), then the invokevirtual instruction proceeds as follows.
First, a reference to an instance of java.lang.invoke.MethodType is obtained as if by resolution of a symbolic reference to a method type (§5.4.3.5) with the same parameter and return types as the descriptor of the method referenced by the invokevirtual instruction.
    If the named method is invokeExact, the instance of java.lang.invoke.MethodType must be semantically equal to the type descriptor of the receiving method handle objectref. The method handle to be invoked is objectref.
    If the named method is invoke, and the instance of java.lang.invoke.MethodType is semantically equal to the type descriptor of the receiving method handle objectref, then the method handle to be invoked is objectref.
    If the named method is invoke, and the instance of java.lang.invoke.MethodType is not semantically equal to the type descriptor of the receiving method handle objectref, then the Java Virtual Machine attempts to adjust the type descriptor of the receiving method handle, as if by a call to java.lang.invoke.MethodHandle.asType, to obtain an exactly invokable method handle m. The method handle to be invoked is m.
The objectref must be followed on the operand stack by nargs argument values, where the number, type, and order of the values must be consistent with the type descriptor of the method handle to be invoked. (This type descriptor will correspond to the method descriptor appropriate for the kind of the method handle to be invoked, as specified in §5.4.3.5.)
Then, if the method handle to be invoked has bytecode behavior, the Java Virtual Machine invokes the method handle as if by execution of the bytecode behavior associated with the method handle's kind. If the kind is 5 (REF_invokeVirtual), 6 (REF_invokeStatic), 7 (REF_invokeSpecial), 8 (REF_newInvokeSpecial), or 9 (REF_invokeInterface), then a frame will be created and made current in the course of executing the bytecode behavior; when the method invoked by the bytecode behavior completes (normally or abruptly), the frame of its invoker is considered to be the frame for the method containing this invokevirtual instruction.
The frame in which the bytecode behavior itself executes is not visible.
Otherwise, if the method handle to be invoked has no bytecode behavior, the Java Virtual Machine invokes it in an implementation-dependent manner. 
 */
  u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc += 2;
  info_t *methodref = get_constant_pool_entry(frame, cp_index);
  
  info_t *method_name_utf8 = get_constant_pool_entry(frame, get_constant_pool_entry(frame, methodref->Methodref.name_and_type_index)->NameAndType.name_index);
  char *method_name = (char *) calloc(method_name_utf8->Utf8.length + 1, sizeof(char));
  memcpy(method_name, method_name_utf8->Utf8.bytes, method_name_utf8->Utf8.length);
  /* Se o método for println, entra no if */
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
        printf("%lf\n", dvalue);
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
    /*pilha antes = objectref, [arg1, arg2, ...] -> pilha depois = result*/
  }else{
    printf("Executar método\n");
    printf("%s\n", method_name);
    exit(-1);
  }

}

void IOR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  int32_t *ivalue1 = NULL, *ivalue2 = NULL;
	int32_t *iresult;
	u4 *value1 = NULL, *value2 = NULL;

	value1 = (u4 *) cpop(frame->operands_stack);
  ivalue1 = (int32_t *) value1;

	value2 = (u4 *) cpop(frame->operands_stack);
	ivalue2 = (int32_t *) value2;

  iresult = calloc(1, sizeof(int32_t));
	*iresult = *ivalue2 % *ivalue1;

	cpush(frame->operands_stack, iresult);
}
void IRETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void ISHL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void ISHR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
  int32_t *ivalue1 = NULL, *ivalue2 = NULL;
	int32_t *iresult;
	u4 *value1 = NULL, *value2 = NULL;

	value1 = (u4 *) cpop(frame->operands_stack);
  ivalue1 = (int32_t *) value1;

	value2 = (u4 *) cpop(frame->operands_stack);
	ivalue2 = (int32_t *) value2;

  iresult = calloc(1, sizeof(int32_t));
	*iresult = *ivalue2 - *ivalue1;

	cpush(frame->operands_stack, iresult);
}
void IUSHR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IXOR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void JSR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void JSR_W_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void L2D_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void L2F_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void L2I_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LAND_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LCMP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LCONST_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *lvalue_high = (u4 *) calloc(1, sizeof(u4));
  u4 *lvalue_low = (u4 *) calloc(1, sizeof(u4));
	*lvalue_high = 0x00000000;
  *lvalue_low = 0x00000000;
	cpush(frame->operands_stack, lvalue_high);
  cpush(frame->operands_stack, lvalue_low);
}
void LCONST_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *lvalue_high = (u4 *) calloc(1, sizeof(u4));
  u4 *lvalue_low = (u4 *) calloc(1, sizeof(u4));
	*lvalue_high = 0x00000000;
  *lvalue_low = 0x00000001;
	cpush(frame->operands_stack, lvalue_high);
  cpush(frame->operands_stack, lvalue_low);
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
void LDIV_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LLOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u1 lv_index = (*pc + 1)[0]; ++*pc;
	u4 *lvalue_high = (u4 *) cat(frame->local_variables, lv_index++);
	u4 *lvalue_low = (u4 *) cat(frame->local_variables, lv_index);
	cpush(frame->operands_stack, lvalue_high);
	cpush(frame->operands_stack, lvalue_low);
}
void LLOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_high = (u4 *) cat(frame->local_variables, 0);
	u4 *lvalue_low = (u4 *) cat(frame->local_variables, 1);
	cpush(frame->operands_stack, lvalue_high);
	cpush(frame->operands_stack, lvalue_low);
}
void LLOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_high = (u4 *) cat(frame->local_variables, 1);
	u4 *lvalue_low = (u4 *) cat(frame->local_variables, 2);
	cpush(frame->operands_stack, lvalue_high);
	cpush(frame->operands_stack, lvalue_low);
}
void LLOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_high = (u4 *) cat(frame->local_variables, 2);
	u4 *lvalue_low = (u4 *) cat(frame->local_variables, 3);
	cpush(frame->operands_stack, lvalue_high);
	cpush(frame->operands_stack, lvalue_low);
}
void LLOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
	u4 *lvalue_high = (u4 *) cat(frame->local_variables, 3);
	u4 *lvalue_low = (u4 *) cat(frame->local_variables, 4);
	cpush(frame->operands_stack, lvalue_high);
	cpush(frame->operands_stack, lvalue_low);
}
void LMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LNEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LOOKUPSWITCH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LOR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LRETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LSHL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LSHR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void LSUB_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LUSHR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void LXOR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void MONITORENTER_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void MONITOREXIT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void MULTIANEWARRAY_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void NEW_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void NEWARRAY_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void PUTFIELD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void PUTSTATIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void RET_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void RETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  *pc = NULL;
}
void SALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void SASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void SIPUSH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void SWAP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void TABLESWITCH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void WIDE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
