#include <stdio.h>
#include "../include/mnemonic.h"
#include "../include/bytecode.h"
#include "../include/constant_pool.h"
#include "../include/method_area.h"
#include "../include/jvm.h"
#include "../include/info.h"

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
  [0xfe] = IMPDEP1_handler,
  [0xff] = IMPDEP2_handler,
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
void ACONST_NULL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void BIPUSH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void DDIV_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void DMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void DNEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void DREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void DSUB_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void FADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void FDIV_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void FMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void FNEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void FREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void FSUB_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
		É basicamente ver se o campo existe e se a classe atual tem permissão de acesso (vamos assumir que sim ;p)
		VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
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
void GOTO_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void GOTO_W_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void I2B_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void I2C_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void I2D_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void I2F_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void I2L_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void I2S_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IAND_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void ICONST_M1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){
  u4 *ivalue = (u4 *) calloc(1, sizeof(u4));
  *ivalue = 0xFFFFFFFF; /* -1 em complemento de dois */
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
void IDIV_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IF_ACMPEQ_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IF_ACMPNE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IF_ICMPEQ_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IF_ICMPGE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IF_ICMPGT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IF_ICMPLE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IF_ICMPLT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IF_ICMPNE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IFEQ_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IFGE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IFGT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IFLE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IFLT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IFNE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IFNONNULL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IFNULL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IINC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void IMPDEP1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IMPDEP2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void INEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void INSTANCEOF_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void INVOKEDYNAMIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void INVOKEINTERFACE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void INVOKESPECIAL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void INVOKESTATIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void INVOKEVIRTUAL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IOR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void IREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void ISUB_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
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
void RETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void SALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void SASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void SIPUSH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void SWAP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void TABLESWITCH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
void WIDE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm){}
