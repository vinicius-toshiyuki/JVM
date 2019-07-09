#include <stdio.h>
#include "../include/mnemonic.h"
#include "../include/bytecode.h"
#include "../include/constant_pool.h"

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

void AALOAD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void AASTORE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ACONST_NULL_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ALOAD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ALOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ALOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ALOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ALOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ANEWARRAY_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ARETURN_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ARRAYLENGTH_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ASTORE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ASTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ASTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ASTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ASTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ATHROW_handler(u1 **pc, u1 *bp, frame_t *frame){}
void BALOAD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void BASTORE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void BIPUSH_handler(u1 **pc, u1 *bp, frame_t *frame){}
void BREAKPOINT_handler(u1 **pc, u1 *bp, frame_t *frame){}
void CALOAD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void CASTORE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void CHECKCAST_handler(u1 **pc, u1 *bp, frame_t *frame){}
void D2F_handler(u1 **pc, u1 *bp, frame_t *frame){}
void D2I_handler(u1 **pc, u1 *bp, frame_t *frame){}
void D2L_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DADD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DALOAD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DASTORE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DCMPG_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DCMPL_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DCONST_0_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DCONST_1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DDIV_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DLOAD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DLOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DLOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DLOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DLOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DMUL_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DNEG_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DREM_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DRETURN_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DSTORE_handler(u1 **pc, u1 *bp, frame_t *frame){

  return;
}
void DSTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame){}

void DSTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame){
  printf("Passou por aqui\n");
  fpurge(stdout);
  return;
}
void DSTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DSTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DSUB_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DUP_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DUP_X1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DUP_X2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DUP2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DUP2_X1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void DUP2_X2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void F2D_handler(u1 **pc, u1 *bp, frame_t *frame){}
void F2I_handler(u1 **pc, u1 *bp, frame_t *frame){}
void F2L_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FADD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FALOAD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FASTORE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FCMPG_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FCMPL_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FCONST_0_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FCONST_1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FCONST_2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FDIV_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FLOAD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FLOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FLOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FLOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FLOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FMUL_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FNEG_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FREM_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FRETURN_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FSTORE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FSTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FSTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FSTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FSTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame){}
void FSUB_handler(u1 **pc, u1 *bp, frame_t *frame){}
void GETFIELD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void GETSTATIC_handler(u1 **pc, u1 *bp, frame_t *frame){
	// u2 cp_index = args[0] << 8 | args[1];
	// void *value = getConstantPoolEntry(cp_index);
	// return;
}
void GOTO_handler(u1 **pc, u1 *bp, frame_t *frame){}
void GOTO_W_handler(u1 **pc, u1 *bp, frame_t *frame){}
void I2B_handler(u1 **pc, u1 *bp, frame_t *frame){}
void I2C_handler(u1 **pc, u1 *bp, frame_t *frame){}
void I2D_handler(u1 **pc, u1 *bp, frame_t *frame){}
void I2F_handler(u1 **pc, u1 *bp, frame_t *frame){}
void I2L_handler(u1 **pc, u1 *bp, frame_t *frame){}
void I2S_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IADD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IALOAD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IAND_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IASTORE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ICONST_M1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ICONST_0_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ICONST_1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ICONST_2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ICONST_3_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ICONST_4_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ICONST_5_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IDIV_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IF_ACMPEQ_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IF_ACMPNE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IF_ICMPEQ_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IF_ICMPGE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IF_ICMPGT_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IF_ICMPLE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IF_ICMPLT_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IF_ICMPNE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IFEQ_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IFGE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IFGT_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IFLE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IFLT_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IFNE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IFNONNULL_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IFNULL_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IINC_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ILOAD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ILOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ILOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ILOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ILOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IMPDEP1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IMPDEP2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IMUL_handler(u1 **pc, u1 *bp, frame_t *frame){}
void INEG_handler(u1 **pc, u1 *bp, frame_t *frame){}
void INSTANCEOF_handler(u1 **pc, u1 *bp, frame_t *frame){}
void INVOKEDYNAMIC_handler(u1 **pc, u1 *bp, frame_t *frame){}
void INVOKEINTERFACE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void INVOKESPECIAL_handler(u1 **pc, u1 *bp, frame_t *frame){}
void INVOKESTATIC_handler(u1 **pc, u1 *bp, frame_t *frame){}
void INVOKEVIRTUAL_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IOR_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IREM_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IRETURN_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ISHL_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ISHR_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ISTORE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ISTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ISTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ISTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ISTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame){}
void ISUB_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IUSHR_handler(u1 **pc, u1 *bp, frame_t *frame){}
void IXOR_handler(u1 **pc, u1 *bp, frame_t *frame){}
void JSR_handler(u1 **pc, u1 *bp, frame_t *frame){}
void JSR_W_handler(u1 **pc, u1 *bp, frame_t *frame){}
void L2D_handler(u1 **pc, u1 *bp, frame_t *frame){}
void L2F_handler(u1 **pc, u1 *bp, frame_t *frame){}
void L2I_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LADD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LALOAD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LAND_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LASTORE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LCMP_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LCONST_0_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LCONST_1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LDC_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LDC_W_handler(u1 **pc, u1 *bp, frame_t *frame){}

void LDC2_W_handler(u1 **pc, u1 *bp, frame_t *frame){
  /* index na constant pool do valor cat 2 que queremos pôr na pilha */
	u2 cp_index = (*pc + 1)[0] << 8 | (*pc + 1)[1]; *pc = *pc + 2;
  info_t *cp_entry = getConstantPoolEntry(frame, cp_index);
  u8 *value = (u8 *) calloc(1, sizeof(u8));
	*value = ((u8) cp_entry->Double.high_bytes) << 32 | cp_entry->Double.low_bytes;
	cpush(frame->operands_stack, value);
	return;
}

void LDIV_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LLOAD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LLOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LLOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LLOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LLOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LMUL_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LNEG_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LOOKUPSWITCH_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LOR_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LREM_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LRETURN_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LSHL_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LSHR_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LSTORE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LSTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LSTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LSTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LSTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LSUB_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LUSHR_handler(u1 **pc, u1 *bp, frame_t *frame){}
void LXOR_handler(u1 **pc, u1 *bp, frame_t *frame){}
void MONITORENTER_handler(u1 **pc, u1 *bp, frame_t *frame){}
void MONITOREXIT_handler(u1 **pc, u1 *bp, frame_t *frame){}
void MULTIANEWARRAY_handler(u1 **pc, u1 *bp, frame_t *frame){}
void NEW_handler(u1 **pc, u1 *bp, frame_t *frame){}
void NEWARRAY_handler(u1 **pc, u1 *bp, frame_t *frame){}
void NOP_handler(u1 **pc, u1 *bp, frame_t *frame){}
void POP_handler(u1 **pc, u1 *bp, frame_t *frame){}
void POP2_handler(u1 **pc, u1 *bp, frame_t *frame){}
void PUTFIELD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void PUTSTATIC_handler(u1 **pc, u1 *bp, frame_t *frame){}
void RET_handler(u1 **pc, u1 *bp, frame_t *frame){}
void RETURN_handler(u1 **pc, u1 *bp, frame_t *frame){}
void SALOAD_handler(u1 **pc, u1 *bp, frame_t *frame){}
void SASTORE_handler(u1 **pc, u1 *bp, frame_t *frame){}
void SIPUSH_handler(u1 **pc, u1 *bp, frame_t *frame){}
void SWAP_handler(u1 **pc, u1 *bp, frame_t *frame){}
void TABLESWITCH_handler(u1 **pc, u1 *bp, frame_t *frame){}
void WIDE_handler(u1 **pc, u1 *bp, frame_t *frame){}