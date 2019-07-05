#include "../include/mnemonic.h"
#include <stdio.h>

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

void AALOAD_handler(jvm_t *jvm, u1 *args){}
void AASTORE_handler(jvm_t *jvm, u1 *args){}
void ACONST_NULL_handler(jvm_t *jvm, u1 *args){}
void ALOAD_handler(jvm_t *jvm, u1 *args){}
void ALOAD_0_handler(jvm_t *jvm, u1 *args){}
void ALOAD_1_handler(jvm_t *jvm, u1 *args){}
void ALOAD_2_handler(jvm_t *jvm, u1 *args){}
void ALOAD_3_handler(jvm_t *jvm, u1 *args){}
void ANEWARRAY_handler(jvm_t *jvm, u1 *args){}
void ARETURN_handler(jvm_t *jvm, u1 *args){}
void ARRAYLENGTH_handler(jvm_t *jvm, u1 *args){}
void ASTORE_handler(jvm_t *jvm, u1 *args){}
void ASTORE_0_handler(jvm_t *jvm, u1 *args){}
void ASTORE_1_handler(jvm_t *jvm, u1 *args){}
void ASTORE_2_handler(jvm_t *jvm, u1 *args){}
void ASTORE_3_handler(jvm_t *jvm, u1 *args){}
void ATHROW_handler(jvm_t *jvm, u1 *args){}
void BALOAD_handler(jvm_t *jvm, u1 *args){}
void BASTORE_handler(jvm_t *jvm, u1 *args){}
void BIPUSH_handler(jvm_t *jvm, u1 *args){}
void BREAKPOINT_handler(jvm_t *jvm, u1 *args){}
void CALOAD_handler(jvm_t *jvm, u1 *args){}
void CASTORE_handler(jvm_t *jvm, u1 *args){}
void CHECKCAST_handler(jvm_t *jvm, u1 *args){}
void D2F_handler(jvm_t *jvm, u1 *args){}
void D2I_handler(jvm_t *jvm, u1 *args){}
void D2L_handler(jvm_t *jvm, u1 *args){}
void DADD_handler(jvm_t *jvm, u1 *args){}
void DALOAD_handler(jvm_t *jvm, u1 *args){}
void DASTORE_handler(jvm_t *jvm, u1 *args){}
void DCMPG_handler(jvm_t *jvm, u1 *args){}
void DCMPL_handler(jvm_t *jvm, u1 *args){}
void DCONST_0_handler(jvm_t *jvm, u1 *args){}
void DCONST_1_handler(jvm_t *jvm, u1 *args){}
void DDIV_handler(jvm_t *jvm, u1 *args){}
void DLOAD_handler(jvm_t *jvm, u1 *args){}
void DLOAD_0_handler(jvm_t *jvm, u1 *args){}
void DLOAD_1_handler(jvm_t *jvm, u1 *args){}
void DLOAD_2_handler(jvm_t *jvm, u1 *args){}
void DLOAD_3_handler(jvm_t *jvm, u1 *args){}
void DMUL_handler(jvm_t *jvm, u1 *args){}
void DNEG_handler(jvm_t *jvm, u1 *args){}
void DREM_handler(jvm_t *jvm, u1 *args){}
void DRETURN_handler(jvm_t *jvm, u1 *args){}
void DSTORE_handler(jvm_t *jvm, u1 *args){}
void DSTORE_0_handler(jvm_t *jvm, u1 *args){}
void DSTORE_1_handler(jvm_t *jvm, u1 *args){}
void DSTORE_2_handler(jvm_t *jvm, u1 *args){}
void DSTORE_3_handler(jvm_t *jvm, u1 *args){}
void DSUB_handler(jvm_t *jvm, u1 *args){}
void DUP_handler(jvm_t *jvm, u1 *args){}
void DUP_X1_handler(jvm_t *jvm, u1 *args){}
void DUP_X2_handler(jvm_t *jvm, u1 *args){}
void DUP2_handler(jvm_t *jvm, u1 *args){}
void DUP2_X1_handler(jvm_t *jvm, u1 *args){}
void DUP2_X2_handler(jvm_t *jvm, u1 *args){}
void F2D_handler(jvm_t *jvm, u1 *args){}
void F2I_handler(jvm_t *jvm, u1 *args){}
void F2L_handler(jvm_t *jvm, u1 *args){}
void FADD_handler(jvm_t *jvm, u1 *args){}
void FALOAD_handler(jvm_t *jvm, u1 *args){}
void FASTORE_handler(jvm_t *jvm, u1 *args){}
void FCMPG_handler(jvm_t *jvm, u1 *args){}
void FCMPL_handler(jvm_t *jvm, u1 *args){}
void FCONST_0_handler(jvm_t *jvm, u1 *args){}
void FCONST_1_handler(jvm_t *jvm, u1 *args){}
void FCONST_2_handler(jvm_t *jvm, u1 *args){}
void FDIV_handler(jvm_t *jvm, u1 *args){}
void FLOAD_handler(jvm_t *jvm, u1 *args){}
void FLOAD_0_handler(jvm_t *jvm, u1 *args){}
void FLOAD_1_handler(jvm_t *jvm, u1 *args){}
void FLOAD_2_handler(jvm_t *jvm, u1 *args){}
void FLOAD_3_handler(jvm_t *jvm, u1 *args){}
void FMUL_handler(jvm_t *jvm, u1 *args){}
void FNEG_handler(jvm_t *jvm, u1 *args){}
void FREM_handler(jvm_t *jvm, u1 *args){}
void FRETURN_handler(jvm_t *jvm, u1 *args){}
void FSTORE_handler(jvm_t *jvm, u1 *args){}
void FSTORE_0_handler(jvm_t *jvm, u1 *args){}
void FSTORE_1_handler(jvm_t *jvm, u1 *args){}
void FSTORE_2_handler(jvm_t *jvm, u1 *args){}
void FSTORE_3_handler(jvm_t *jvm, u1 *args){}
void FSUB_handler(jvm_t *jvm, u1 *args){}
void GETFIELD_handler(jvm_t *jvm, u1 *args){}
void GETSTATIC_handler(jvm_t *jvm, u1 *args){}
void GOTO_handler(jvm_t *jvm, u1 *args){}
void GOTO_W_handler(jvm_t *jvm, u1 *args){}
void I2B_handler(jvm_t *jvm, u1 *args){}
void I2C_handler(jvm_t *jvm, u1 *args){}
void I2D_handler(jvm_t *jvm, u1 *args){}
void I2F_handler(jvm_t *jvm, u1 *args){}
void I2L_handler(jvm_t *jvm, u1 *args){}
void I2S_handler(jvm_t *jvm, u1 *args){}
void IADD_handler(jvm_t *jvm, u1 *args){}
void IALOAD_handler(jvm_t *jvm, u1 *args){}
void IAND_handler(jvm_t *jvm, u1 *args){}
void IASTORE_handler(jvm_t *jvm, u1 *args){}
void ICONST_M1_handler(jvm_t *jvm, u1 *args){}
void ICONST_0_handler(jvm_t *jvm, u1 *args){}
void ICONST_1_handler(jvm_t *jvm, u1 *args){}
void ICONST_2_handler(jvm_t *jvm, u1 *args){}
void ICONST_3_handler(jvm_t *jvm, u1 *args){}
void ICONST_4_handler(jvm_t *jvm, u1 *args){}
void ICONST_5_handler(jvm_t *jvm, u1 *args){}
void IDIV_handler(jvm_t *jvm, u1 *args){}
void IF_ACMPEQ_handler(jvm_t *jvm, u1 *args){}
void IF_ACMPNE_handler(jvm_t *jvm, u1 *args){}
void IF_ICMPEQ_handler(jvm_t *jvm, u1 *args){}
void IF_ICMPGE_handler(jvm_t *jvm, u1 *args){}
void IF_ICMPGT_handler(jvm_t *jvm, u1 *args){}
void IF_ICMPLE_handler(jvm_t *jvm, u1 *args){}
void IF_ICMPLT_handler(jvm_t *jvm, u1 *args){}
void IF_ICMPNE_handler(jvm_t *jvm, u1 *args){}
void IFEQ_handler(jvm_t *jvm, u1 *args){}
void IFGE_handler(jvm_t *jvm, u1 *args){}
void IFGT_handler(jvm_t *jvm, u1 *args){}
void IFLE_handler(jvm_t *jvm, u1 *args){}
void IFLT_handler(jvm_t *jvm, u1 *args){}
void IFNE_handler(jvm_t *jvm, u1 *args){}
void IFNONNULL_handler(jvm_t *jvm, u1 *args){}
void IFNULL_handler(jvm_t *jvm, u1 *args){}
void IINC_handler(jvm_t *jvm, u1 *args){}
void ILOAD_handler(jvm_t *jvm, u1 *args){}
void ILOAD_0_handler(jvm_t *jvm, u1 *args){}
void ILOAD_1_handler(jvm_t *jvm, u1 *args){}
void ILOAD_2_handler(jvm_t *jvm, u1 *args){}
void ILOAD_3_handler(jvm_t *jvm, u1 *args){}
void IMPDEP1_handler(jvm_t *jvm, u1 *args){}
void IMPDEP2_handler(jvm_t *jvm, u1 *args){}
void IMUL_handler(jvm_t *jvm, u1 *args){}
void INEG_handler(jvm_t *jvm, u1 *args){}
void INSTANCEOF_handler(jvm_t *jvm, u1 *args){}
void INVOKEDYNAMIC_handler(jvm_t *jvm, u1 *args){}
void INVOKEINTERFACE_handler(jvm_t *jvm, u1 *args){}
void INVOKESPECIAL_handler(jvm_t *jvm, u1 *args){}
void INVOKESTATIC_handler(jvm_t *jvm, u1 *args){}
void INVOKEVIRTUAL_handler(jvm_t *jvm, u1 *args){}
void IOR_handler(jvm_t *jvm, u1 *args){}
void IREM_handler(jvm_t *jvm, u1 *args){}
void IRETURN_handler(jvm_t *jvm, u1 *args){}
void ISHL_handler(jvm_t *jvm, u1 *args){}
void ISHR_handler(jvm_t *jvm, u1 *args){}
void ISTORE_handler(jvm_t *jvm, u1 *args){}
void ISTORE_0_handler(jvm_t *jvm, u1 *args){}
void ISTORE_1_handler(jvm_t *jvm, u1 *args){}
void ISTORE_2_handler(jvm_t *jvm, u1 *args){}
void ISTORE_3_handler(jvm_t *jvm, u1 *args){}
void ISUB_handler(jvm_t *jvm, u1 *args){}
void IUSHR_handler(jvm_t *jvm, u1 *args){}
void IXOR_handler(jvm_t *jvm, u1 *args){}
void JSR_handler(jvm_t *jvm, u1 *args){}
void JSR_W_handler(jvm_t *jvm, u1 *args){}
void L2D_handler(jvm_t *jvm, u1 *args){}
void L2F_handler(jvm_t *jvm, u1 *args){}
void L2I_handler(jvm_t *jvm, u1 *args){}
void LADD_handler(jvm_t *jvm, u1 *args){}
void LALOAD_handler(jvm_t *jvm, u1 *args){}
void LAND_handler(jvm_t *jvm, u1 *args){}
void LASTORE_handler(jvm_t *jvm, u1 *args){}
void LCMP_handler(jvm_t *jvm, u1 *args){}
void LCONST_0_handler(jvm_t *jvm, u1 *args){}
void LCONST_1_handler(jvm_t *jvm, u1 *args){}
void LDC_handler(jvm_t *jvm, u1 *args){}
void LDC_W_handler(jvm_t *jvm, u1 *args){}
void LDC2_W_handler(jvm_t *jvm, u1 *args){}
void LDIV_handler(jvm_t *jvm, u1 *args){}
void LLOAD_handler(jvm_t *jvm, u1 *args){}
void LLOAD_0_handler(jvm_t *jvm, u1 *args){}
void LLOAD_1_handler(jvm_t *jvm, u1 *args){}
void LLOAD_2_handler(jvm_t *jvm, u1 *args){}
void LLOAD_3_handler(jvm_t *jvm, u1 *args){}
void LMUL_handler(jvm_t *jvm, u1 *args){}
void LNEG_handler(jvm_t *jvm, u1 *args){}
void LOOKUPSWITCH_handler(jvm_t *jvm, u1 *args){}
void LOR_handler(jvm_t *jvm, u1 *args){}
void LREM_handler(jvm_t *jvm, u1 *args){}
void LRETURN_handler(jvm_t *jvm, u1 *args){}
void LSHL_handler(jvm_t *jvm, u1 *args){}
void LSHR_handler(jvm_t *jvm, u1 *args){}
void LSTORE_handler(jvm_t *jvm, u1 *args){}
void LSTORE_0_handler(jvm_t *jvm, u1 *args){}
void LSTORE_1_handler(jvm_t *jvm, u1 *args){}
void LSTORE_2_handler(jvm_t *jvm, u1 *args){}
void LSTORE_3_handler(jvm_t *jvm, u1 *args){}
void LSUB_handler(jvm_t *jvm, u1 *args){}
void LUSHR_handler(jvm_t *jvm, u1 *args){}
void LXOR_handler(jvm_t *jvm, u1 *args){}
void MONITORENTER_handler(jvm_t *jvm, u1 *args){}
void MONITOREXIT_handler(jvm_t *jvm, u1 *args){}
void MULTIANEWARRAY_handler(jvm_t *jvm, u1 *args){}
void NEW_handler(jvm_t *jvm, u1 *args){}
void NEWARRAY_handler(jvm_t *jvm, u1 *args){}
void NOP_handler(jvm_t *jvm, u1 *args){}
void POP_handler(jvm_t *jvm, u1 *args){}
void POP2_handler(jvm_t *jvm, u1 *args){}
void PUTFIELD_handler(jvm_t *jvm, u1 *args){}
void PUTSTATIC_handler(jvm_t *jvm, u1 *args){}
void RET_handler(jvm_t *jvm, u1 *args){}
void RETURN_handler(jvm_t *jvm, u1 *args){}
void SALOAD_handler(jvm_t *jvm, u1 *args){}
void SASTORE_handler(jvm_t *jvm, u1 *args){}
void SIPUSH_handler(jvm_t *jvm, u1 *args){}
void SWAP_handler(jvm_t *jvm, u1 *args){}
void TABLESWITCH_handler(jvm_t *jvm, u1 *args){}
void WIDE_handler(jvm_t *jvm, u1 *args){}
