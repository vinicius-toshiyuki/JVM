#ifndef mnemonic_h
#define mnemonic_h

typedef enum {
  AALOAD = 0x32,
  AASTORE = 0x53,
  ACONST_NULL = 0x01,
  ALOAD = 0x19,
  ALOAD_0 = 0x2a,
  ALOAD_1 = 0x2b,
  ALOAD_2 = 0x2c,
  ALOAD_3 = 0x2d,
  ANEWARRAY = 0xbd,
  ARETURN = 0xb0,
  ARRAYLENGTH = 0xbe,
  ASTORE = 0x3a,
  ASTORE_0 = 0x4b,
  ASTORE_1 = 0x4c,
  ASTORE_2 = 0x4d,
  ASTORE_3 = 0x4e,
  ATHROW = 0xbf,
  BALOAD = 0x33,
  BASTORE = 0x54,
  BIPUSH = 0x10,
  BREAKPOINT = 0xca,
  CALOAD = 0x34,
  CASTORE = 0x55,
  CHECKCAST = 0xc0,
  D2F = 0x90,
  D2I = 0x8e,
  D2L = 0x8f,
  DADD = 0x63,
  DALOAD = 0x31,
  DASTORE = 0x52,
  DCMPG = 0x98,
  DCMPL = 0x97,
  DCONST_0 = 0x0e,
  DCONST_1 = 0x0f,
  DDIV = 0x6f,
  DLOAD = 0x18,
  DLOAD_0 = 0x26,
  DLOAD_1 = 0x27,
  DLOAD_2 = 0x28,
  DLOAD_3 = 0x29,
  DMUL = 0x6b,
  DNEG = 0x77,
  DREM = 0x73,
  DRETURN = 0xaf,
  DSTORE = 0x39,
  DSTORE_0 = 0x47,
  DSTORE_1 = 0x48,
  DSTORE_2 = 0x49,
  DSTORE_3 = 0x4a,
  DSUB = 0x67,
  DUP = 0x59,
  DUP_X1 = 0x5a,
  DUP_X2 = 0x5b,
  DUP2 = 0x5c,
  DUP2_X1 = 0x5d,
  DUP2_X2 = 0x5e,
  F2D = 0x8d,
  F2I = 0x8b,
  F2L = 0x8c,
  FADD = 0x62,
  FALOAD = 0x30,
  FASTORE = 0x51,
  FCMPG = 0x96,
  FCMPL = 0x95,
  FCONST_0 = 0x0b,
  FCONST_1 = 0x0c,
  FCONST_2 = 0x0d,
  FDIV = 0x6e,
  FLOAD = 0x17,
  FLOAD_0 = 0x22,
  FLOAD_1 = 0x23,
  FLOAD_2 = 0x24,
  FLOAD_3 = 0x25,
  FMUL = 0x6a,
  FNEG = 0x76,
  FREM = 0x72,
  FRETURN = 0xae,
  FSTORE = 0x38,
  FSTORE_0 = 0x43,
  FSTORE_1 = 0x44,
  FSTORE_2 = 0x45,
  FSTORE_3 = 0x46,
  FSUB = 0x66,
  GETFIELD = 0xb4,
  GETSTATIC = 0xb2,
  GOTO = 0xa7,
  GOTO_W = 0xc8,
  I2B = 0x91,
  I2C = 0x92,
  I2D = 0x87,
  I2F = 0x86,
  I2L = 0x85,
  I2S = 0x93,
  IADD = 0x60,
  IALOAD = 0x2e,
  IAND = 0x7e,
  IASTORE = 0x4f,
  ICONST_M1 = 0x02,
  ICONST_0 = 0x03,
  ICONST_1 = 0x04,
  ICONST_2 = 0x05,
  ICONST_3 = 0x06,
  ICONST_4 = 0x07,
  ICONST_5 = 0x08,
  IDIV = 0x6c,
  IF_ACMPEQ = 0xa5,
  IF_ACMPNE = 0xa6,
  IF_ICMPEQ = 0x9f,
  IF_ICMPGE = 0xa2,
  IF_ICMPGT = 0xa3,
  IF_ICMPLE = 0xa4,
  IF_ICMPLT = 0xa1,
  IF_ICMPNE = 0xa0,
  IFEQ = 0x99,
  IFGE = 0x9c,
  IFGT = 0x9d,
  IFLE = 0x9e,
  IFLT = 0x9b,
  IFNE = 0x9a,
  IFNONNULL = 0xc7,
  IFNULL = 0xc6,
  IINC = 0x84,
  ILOAD = 0x15,
  ILOAD_0 = 0x1a,
  ILOAD_1 = 0x1b,
  ILOAD_2 = 0x1c,
  ILOAD_3 = 0x1d,
  IMPDEP1 = 0xfe,
  IMPDEP2 = 0xff,
  IMUL = 0x68,
  INEG = 0x74,
  INSTANCEOF = 0xc1,
  INVOKEDYNAMIC = 0xba,
  INVOKEINTERFACE = 0xb9,
  INVOKESPECIAL = 0xb7,
  INVOKESTATIC = 0xb8,
  INVOKEVIRTUAL = 0xb6,
  IOR = 0x80,
  IREM = 0x70,
  IRETURN = 0xac,
  ISHL = 0x78,
  ISHR = 0x7a,
  ISTORE = 0x36,
  ISTORE_0 = 0x3b,
  ISTORE_1 = 0x3c,
  ISTORE_2 = 0x3d,
  ISTORE_3 = 0x3e,
  ISUB = 0x64,
  IUSHR = 0x7c,
  IXOR = 0x82,
  JSR = 0xa8,
  JSR_W = 0xc9,
  L2D = 0x8a,
  L2F = 0x89,
  L2I = 0x88,
  LADD = 0x61,
  LALOAD = 0x2f,
  LAND = 0x7f,
  LASTORE = 0x50,
  LCMP = 0x94,
  LCONST_0 = 0x09,
  LCONST_1 = 0x0a,
  LDC = 0x12,
  LDC_W = 0x13,
  LDC2_W = 0x14,
  LDIV = 0x6d,
  LLOAD = 0x16,
  LLOAD_0 = 0x1e,
  LLOAD_1 = 0x1f,
  LLOAD_2 = 0x20,
  LLOAD_3 = 0x21,
  LMUL = 0x69,
  LNEG = 0x75,
  LOOKUPSWITCH = 0xab,
  LOR = 0x81,
  LREM = 0x71,
  LRETURN = 0xad,
  LSHL = 0x79,
  LSHR = 0x7b,
  LSTORE = 0x37,
  LSTORE_0 = 0x3f,
  LSTORE_1 = 0x40,
  LSTORE_2 = 0x41,
  LSTORE_3 = 0x42,
  LSUB = 0x65,
  LUSHR = 0x7d,
  LXOR = 0x83,
  MONITORENTER = 0xc2,
  MONITOREXIT = 0xc3,
  MULTIANEWARRAY = 0xc5,
  NEW = 0xbb,
  NEWARRAY = 0xbc,
  NOP = 0x00,
  POP = 0x57,
  POP2 = 0x58,
  PUTFIELD = 0xb5,
  PUTSTATIC = 0xb3,
  RET = 0xa9,
  RETURN = 0xb1,
  SALOAD = 0x35,
  SASTORE = 0x56,
  SIPUSH = 0x11,
  SWAP = 0x5f,
  TABLESWITCH = 0xaa,
  WIDE = 0xc4
} OPCODES;

void AALOAD_handler(int arg, ...);
void AASTORE_handler(int arg, ...);
void ACONST_NULL_handler(int arg, ...);
void ALOAD_handler(int arg, ...);
void ALOAD_0_handler(int arg, ...);
void ALOAD_1_handler(int arg, ...);
void ALOAD_2_handler(int arg, ...);
void ALOAD_3_handler(int arg, ...);
void ANEWARRAY_handler(int arg, ...);
void ARETURN_handler(int arg, ...);
void ARRAYLENGTH_handler(int arg, ...);
void ASTORE_handler(int arg, ...);
void ASTORE_0_handler(int arg, ...);
void ASTORE_1_handler(int arg, ...);
void ASTORE_2_handler(int arg, ...);
void ASTORE_3_handler(int arg, ...);
void ATHROW_handler(int arg, ...);
void BALOAD_handler(int arg, ...);
void BASTORE_handler(int arg, ...);
void BIPUSH_handler(int arg, ...);
void BREAKPOINT_handler(int arg, ...);
void CALOAD_handler(int arg, ...);
void CASTORE_handler(int arg, ...);
void CHECKCAST_handler(int arg, ...);
void D2F_handler(int arg, ...);
void D2I_handler(int arg, ...);
void D2L_handler(int arg, ...);
void DADD_handler(int arg, ...);
void DALOAD_handler(int arg, ...);
void DASTORE_handler(int arg, ...);
void DCMPG_handler(int arg, ...);
void DCMPL_handler(int arg, ...);
void DCONST_0_handler(int arg, ...);
void DCONST_1_handler(int arg, ...);
void DDIV_handler(int arg, ...);
void DLOAD_handler(int arg, ...);
void DLOAD_0_handler(int arg, ...);
void DLOAD_1_handler(int arg, ...);
void DLOAD_2_handler(int arg, ...);
void DLOAD_3_handler(int arg, ...);
void DMUL_handler(int arg, ...);
void DNEG_handler(int arg, ...);
void DREM_handler(int arg, ...);
void DRETURN_handler(int arg, ...);
void DSTORE_handler(int arg, ...);
void DSTORE_0_handler(int arg, ...);
void DSTORE_1_handler(int arg, ...);
void DSTORE_2_handler(int arg, ...);
void DSTORE_3_handler(int arg, ...);
void DSUB_handler(int arg, ...);
void DUP_handler(int arg, ...);
void DUP_X1_handler(int arg, ...);
void DUP_X2_handler(int arg, ...);
void DUP2_handler(int arg, ...);
void DUP2_X1_handler(int arg, ...);
void DUP2_X2_handler(int arg, ...);
void F2D_handler(int arg, ...);
void F2I_handler(int arg, ...);
void F2L_handler(int arg, ...);
void FADD_handler(int arg, ...);
void FALOAD_handler(int arg, ...);
void FASTORE_handler(int arg, ...);
void FCMPG_handler(int arg, ...);
void FCMPL_handler(int arg, ...);
void FCONST_0_handler(int arg, ...);
void FCONST_1_handler(int arg, ...);
void FCONST_2_handler(int arg, ...);
void FDIV_handler(int arg, ...);
void FLOAD_handler(int arg, ...);
void FLOAD_0_handler(int arg, ...);
void FLOAD_1_handler(int arg, ...);
void FLOAD_2_handler(int arg, ...);
void FLOAD_3_handler(int arg, ...);
void FMUL_handler(int arg, ...);
void FNEG_handler(int arg, ...);
void FREM_handler(int arg, ...);
void FRETURN_handler(int arg, ...);
void FSTORE_handler(int arg, ...);
void FSTORE_0_handler(int arg, ...);
void FSTORE_1_handler(int arg, ...);
void FSTORE_2_handler(int arg, ...);
void FSTORE_3_handler(int arg, ...);
void FSUB_handler(int arg, ...);
void GETFIELD_handler(int arg, ...);
void GETSTATIC_handler(int arg, ...);
void GOTO_handler(int arg, ...);
void GOTO_W_handler(int arg, ...);
void I2B_handler(int arg, ...);
void I2C_handler(int arg, ...);
void I2D_handler(int arg, ...);
void I2F_handler(int arg, ...);
void I2L_handler(int arg, ...);
void I2S_handler(int arg, ...);
void IADD_handler(int arg, ...);
void IALOAD_handler(int arg, ...);
void IAND_handler(int arg, ...);
void IASTORE_handler(int arg, ...);
void ICONST_M1_handler(int arg, ...);
void ICONST_0_handler(int arg, ...);
void ICONST_1_handler(int arg, ...);
void ICONST_2_handler(int arg, ...);
void ICONST_3_handler(int arg, ...);
void ICONST_4_handler(int arg, ...);
void ICONST_5_handler(int arg, ...);
void IDIV_handler(int arg, ...);
void IF_ACMPEQ_handler(int arg, ...);
void IF_ACMPNE_handler(int arg, ...);
void IF_ICMPEQ_handler(int arg, ...);
void IF_ICMPGE_handler(int arg, ...);
void IF_ICMPGT_handler(int arg, ...);
void IF_ICMPLE_handler(int arg, ...);
void IF_ICMPLT_handler(int arg, ...);
void IF_ICMPNE_handler(int arg, ...);
void IFEQ_handler(int arg, ...);
void IFGE_handler(int arg, ...);
void IFGT_handler(int arg, ...);
void IFLE_handler(int arg, ...);
void IFLT_handler(int arg, ...);
void IFNE_handler(int arg, ...);
void IFNONNULL_handler(int arg, ...);
void IFNULL_handler(int arg, ...);
void IINC_handler(int arg, ...);
void ILOAD_handler(int arg, ...);
void ILOAD_0_handler(int arg, ...);
void ILOAD_1_handler(int arg, ...);
void ILOAD_2_handler(int arg, ...);
void ILOAD_3_handler(int arg, ...);
void IMPDEP1_handler(int arg, ...);
void IMPDEP2_handler(int arg, ...);
void IMUL_handler(int arg, ...);
void INEG_handler(int arg, ...);
void INSTANCEOF_handler(int arg, ...);
void INVOKEDYNAMIC_handler(int arg, ...);
void INVOKEINTERFACE_handler(int arg, ...);
void INVOKESPECIAL_handler(int arg, ...);
void INVOKESTATIC_handler(int arg, ...);
void INVOKEVIRTUAL_handler(int arg, ...);
void IOR_handler(int arg, ...);
void IREM_handler(int arg, ...);
void IRETURN_handler(int arg, ...);
void ISHL_handler(int arg, ...);
void ISHR_handler(int arg, ...);
void ISTORE_handler(int arg, ...);
void ISTORE_0_handler(int arg, ...);
void ISTORE_1_handler(int arg, ...);
void ISTORE_2_handler(int arg, ...);
void ISTORE_3_handler(int arg, ...);
void ISUB_handler(int arg, ...);
void IUSHR_handler(int arg, ...);
void IXOR_handler(int arg, ...);
void JSR_handler(int arg, ...);
void JSR_W_handler(int arg, ...);
void L2D_handler(int arg, ...);
void L2F_handler(int arg, ...);
void L2I_handler(int arg, ...);
void LADD_handler(int arg, ...);
void LALOAD_handler(int arg, ...);
void LAND_handler(int arg, ...);
void LASTORE_handler(int arg, ...);
void LCMP_handler(int arg, ...);
void LCONST_0_handler(int arg, ...);
void LCONST_1_handler(int arg, ...);
void LDC_handler(int arg, ...);
void LDC_W_handler(int arg, ...);
void LDC2_W_handler(int arg, ...);
void LDIV_handler(int arg, ...);
void LLOAD_handler(int arg, ...);
void LLOAD_0_handler(int arg, ...);
void LLOAD_1_handler(int arg, ...);
void LLOAD_2_handler(int arg, ...);
void LLOAD_3_handler(int arg, ...);
void LMUL_handler(int arg, ...);
void LNEG_handler(int arg, ...);
void LOOKUPSWITCH_handler(int arg, ...);
void LOR_handler(int arg, ...);
void LREM_handler(int arg, ...);
void LRETURN_handler(int arg, ...);
void LSHL_handler(int arg, ...);
void LSHR_handler(int arg, ...);
void LSTORE_handler(int arg, ...);
void LSTORE_0_handler(int arg, ...);
void LSTORE_1_handler(int arg, ...);
void LSTORE_2_handler(int arg, ...);
void LSTORE_3_handler(int arg, ...);
void LSUB_handler(int arg, ...);
void LUSHR_handler(int arg, ...);
void LXOR_handler(int arg, ...);
void MONITORENTER_handler(int arg, ...);
void MONITOREXIT_handler(int arg, ...);
void MULTIANEWARRAY_handler(int arg, ...);
void NEW_handler(int arg, ...);
void NEWARRAY_handler(int arg, ...);
void NOP_handler(int arg, ...);
void POP_handler(int arg, ...);
void POP2_handler(int arg, ...);
void PUTFIELD_handler(int arg, ...);
void PUTSTATIC_handler(int arg, ...);
void RET_handler(int arg, ...);
void RETURN_handler(int arg, ...);
void SALOAD_handler(int arg, ...);
void SASTORE_handler(int arg, ...);
void SIPUSH_handler(int arg, ...);
void SWAP_handler(int arg, ...);
void TABLESWITCH_handler(int arg, ...);
void WIDE_handler(int arg, ...);

#endif
