#include "../include/mnemonic.h"
#include <stdio.h>

char * opcode_to_mnemonic[0x100] = {
  [0x32] = "AALOAD",
  [0x53] = "AASTORE",
  [0x01] = "ACONST_NULL",
  [0x19] = "ALOAD",
  [0x2a] = "ALOAD_0",
  [0x2b] = "ALOAD_1",
  [0x2c] = "ALOAD_2",
  [0x2d] = "ALOAD_3",
  [0xbd] = "ANEWARRAY",
  [0xb0] = "ARETURN",
  [0xbe] = "ARRAYLENGTH",
  [0x3a] = "ASTORE",
  [0x4b] = "ASTORE_0",
  [0x4c] = "ASTORE_1",
  [0x4d] = "ASTORE_2",
  [0x4e] = "ASTORE_3",
  [0xbf] = "ATHROW",
  [0x33] = "BALOAD",
  [0x54] = "BASTORE",
  [0x10] = "BIPUSH",
  [0xca] = "BREAKPOINT",
  [0x34] = "CALOAD",
  [0x55] = "CASTORE",
  [0xc0] = "CHECKCAST",
  [0x90] = "D2F",
  [0x8e] = "D2I",
  [0x8f] = "D2L",
  [0x63] = "DADD",
  [0x31] = "DALOAD",
  [0x52] = "DASTORE",
  [0x98] = "DCMPG",
  [0x97] = "DCMPL",
  [0x0e] = "DCONST_0",
  [0x0f] = "DCONST_1",
  [0x6f] = "DDIV",
  [0x18] = "DLOAD",
  [0x26] = "DLOAD_0",
  [0x27] = "DLOAD_1",
  [0x28] = "DLOAD_2",
  [0x29] = "DLOAD_3",
  [0x6b] = "DMUL",
  [0x77] = "DNEG",
  [0x73] = "DREM",
  [0xaf] = "DRETURN",
  [0x39] = "DSTORE",
  [0x47] = "DSTORE_0",
  [0x48] = "DSTORE_1",
  [0x49] = "DSTORE_2",
  [0x4a] = "DSTORE_3",
  [0x67] = "DSUB",
  [0x59] = "DUP",
  [0x5a] = "DUP_X1",
  [0x5b] = "DUP_X2",
  [0x5c] = "DUP2",
  [0x5d] = "DUP2_X1",
  [0x5e] = "DUP2_X2",
  [0x8d] = "F2D",
  [0x8b] = "F2I",
  [0x8c] = "F2L",
  [0x62] = "FADD",
  [0x30] = "FALOAD",
  [0x51] = "FASTORE",
  [0x96] = "FCMPG",
  [0x95] = "FCMPL",
  [0x0b] = "FCONST_0",
  [0x0c] = "FCONST_1",
  [0x0d] = "FCONST_2",
  [0x6e] = "FDIV",
  [0x17] = "FLOAD",
  [0x22] = "FLOAD_0",
  [0x23] = "FLOAD_1",
  [0x24] = "FLOAD_2",
  [0x25] = "FLOAD_3",
  [0x6a] = "FMUL",
  [0x76] = "FNEG",
  [0x72] = "FREM",
  [0xae] = "FRETURN",
  [0x38] = "FSTORE",
  [0x43] = "FSTORE_0",
  [0x44] = "FSTORE_1",
  [0x45] = "FSTORE_2",
  [0x46] = "FSTORE_3",
  [0x66] = "FSUB",
  [0xb4] = "GETFIELD",
  [0xb2] = "GETSTATIC",
  [0xa7] = "GOTO",
  [0xc8] = "GOTO_W",
  [0x91] = "I2B",
  [0x92] = "I2C",
  [0x87] = "I2D",
  [0x86] = "I2F",
  [0x85] = "I2L",
  [0x93] = "I2S",
  [0x60] = "IADD",
  [0x2e] = "IALOAD",
  [0x7e] = "IAND",
  [0x4f] = "IASTORE",
  [0x02] = "ICONST_M1",
  [0x03] = "ICONST_0",
  [0x04] = "ICONST_1",
  [0x05] = "ICONST_2",
  [0x06] = "ICONST_3",
  [0x07] = "ICONST_4",
  [0x08] = "ICONST_5",
  [0x6c] = "IDIV",
  [0xa5] = "IF_ACMPEQ",
  [0xa6] = "IF_ACMPNE",
  [0x9f] = "IF_ICMPEQ",
  [0xa2] = "IF_ICMPGE",
  [0xa3] = "IF_ICMPGT",
  [0xa4] = "IF_ICMPLE",
  [0xa1] = "IF_ICMPLT",
  [0xa0] = "IF_ICMPNE",
  [0x99] = "IFEQ",
  [0x9c] = "IFGE",
  [0x9d] = "IFGT",
  [0x9e] = "IFLE",
  [0x9b] = "IFLT",
  [0x9a] = "IFNE",
  [0xc7] = "IFNONNULL",
  [0xc6] = "IFNULL",
  [0x84] = "IINC",
  [0x15] = "ILOAD",
  [0x1a] = "ILOAD_0",
  [0x1b] = "ILOAD_1",
  [0x1c] = "ILOAD_2",
  [0x1d] = "ILOAD_3",
  [0xfe] = "IMPDEP1",
  [0xff] = "IMPDEP2",
  [0x68] = "IMUL",
  [0x74] = "INEG",
  [0xc1] = "INSTANCEOF",
  [0xba] = "INVOKEDYNAMIC",
  [0xb9] = "INVOKEINTERFACE",
  [0xb7] = "INVOKESPECIAL",
  [0xb8] = "INVOKESTATIC",
  [0xb6] = "INVOKEVIRTUAL",
  [0x80] = "IOR",
  [0x70] = "IREM",
  [0xac] = "IRETURN",
  [0x78] = "ISHL",
  [0x7a] = "ISHR",
  [0x36] = "ISTORE",
  [0x3b] = "ISTORE_0",
  [0x3c] = "ISTORE_1",
  [0x3d] = "ISTORE_2",
  [0x3e] = "ISTORE_3",
  [0x64] = "ISUB",
  [0x7c] = "IUSHR",
  [0x82] = "IXOR",
  [0xa8] = "JSR",
  [0xc9] = "JSR_W",
  [0x8a] = "L2D",
  [0x89] = "L2F",
  [0x88] = "L2I",
  [0x61] = "LADD",
  [0x2f] = "LALOAD",
  [0x7f] = "LAND",
  [0x50] = "LASTORE",
  [0x94] = "LCMP",
  [0x09] = "LCONST_0",
  [0x0a] = "LCONST_1",
  [0x12] = "LDC",
  [0x13] = "LDC_W",
  [0x14] = "LDC2_W",
  [0x6d] = "LDIV",
  [0x16] = "LLOAD",
  [0x1e] = "LLOAD_0",
  [0x1f] = "LLOAD_1",
  [0x20] = "LLOAD_2",
  [0x21] = "LLOAD_3",
  [0x69] = "LMUL",
  [0x75] = "LNEG",
  [0xab] = "LOOKUPSWITCH",
  [0x81] = "LOR",
  [0x71] = "LREM",
  [0xad] = "LRETURN",
  [0x79] = "LSHL",
  [0x7b] = "LSHR",
  [0x37] = "LSTORE",
  [0x3f] = "LSTORE_0",
  [0x40] = "LSTORE_1",
  [0x41] = "LSTORE_2",
  [0x42] = "LSTORE_3",
  [0x65] = "LSUB",
  [0x7d] = "LUSHR",
  [0x83] = "LXOR",
  [0xc2] = "MONITORENTER",
  [0xc3] = "MONITOREXIT",
  [0xc5] = "MULTIANEWARRAY",
  [0xbb] = "NEW",
  [0xbc] = "NEWARRAY",
  [0x00] = "NOP",
  [0x57] = "POP",
  [0x58] = "POP2",
  [0xb5] = "PUTFIELD",
  [0xb3] = "PUTSTATIC",
  [0xa9] = "RET",
  [0xb1] = "RETURN",
  [0x35] = "SALOAD",
  [0x56] = "SASTORE",
  [0x11] = "SIPUSH",
  [0x5f] = "SWAP",
  [0xaa] = "TABLESWITCH",
  [0xc4] = "WIDE"
};

printer opcode_printers[] = {
  [0x32] = AALOAD_printer,
  [0x53] = AASTORE_printer,
  [0x01] = ACONST_NULL_printer,
  [0x19] = ALOAD_printer,
  [0x2a] = ALOAD_0_printer,
  [0x2b] = ALOAD_1_printer,
  [0x2c] = ALOAD_2_printer,
  [0x2d] = ALOAD_3_printer,
  [0xbd] = ANEWARRAY_printer,
  [0xb0] = ARETURN_printer,
  [0xbe] = ARRAYLENGTH_printer,
  [0x3a] = ASTORE_printer,
  [0x4b] = ASTORE_0_printer,
  [0x4c] = ASTORE_1_printer,
  [0x4d] = ASTORE_2_printer,
  [0x4e] = ASTORE_3_printer,
  [0xbf] = ATHROW_printer,
  [0x33] = BALOAD_printer,
  [0x54] = BASTORE_printer,
  [0x10] = BIPUSH_printer,
  [0xca] = BREAKPOINT_printer,
  [0x34] = CALOAD_printer,
  [0x55] = CASTORE_printer,
  [0xc0] = CHECKCAST_printer,
  [0x90] = D2F_printer,
  [0x8e] = D2I_printer,
  [0x8f] = D2L_printer,
  [0x63] = DADD_printer,
  [0x31] = DALOAD_printer,
  [0x52] = DASTORE_printer,
  [0x98] = DCMPG_printer,
  [0x97] = DCMPL_printer,
  [0x0e] = DCONST_0_printer,
  [0x0f] = DCONST_1_printer,
  [0x6f] = DDIV_printer,
  [0x18] = DLOAD_printer,
  [0x26] = DLOAD_0_printer,
  [0x27] = DLOAD_1_printer,
  [0x28] = DLOAD_2_printer,
  [0x29] = DLOAD_3_printer,
  [0x6b] = DMUL_printer,
  [0x77] = DNEG_printer,
  [0x73] = DREM_printer,
  [0xaf] = DRETURN_printer,
  [0x39] = DSTORE_printer,
  [0x47] = DSTORE_0_printer,
  [0x48] = DSTORE_1_printer,
  [0x49] = DSTORE_2_printer,
  [0x4a] = DSTORE_3_printer,
  [0x67] = DSUB_printer,
  [0x59] = DUP_printer,
  [0x5a] = DUP_X1_printer,
  [0x5b] = DUP_X2_printer,
  [0x5c] = DUP2_printer,
  [0x5d] = DUP2_X1_printer,
  [0x5e] = DUP2_X2_printer,
  [0x8d] = F2D_printer,
  [0x8b] = F2I_printer,
  [0x8c] = F2L_printer,
  [0x62] = FADD_printer,
  [0x30] = FALOAD_printer,
  [0x51] = FASTORE_printer,
  [0x96] = FCMPG_printer,
  [0x95] = FCMPL_printer,
  [0x0b] = FCONST_0_printer,
  [0x0c] = FCONST_1_printer,
  [0x0d] = FCONST_2_printer,
  [0x6e] = FDIV_printer,
  [0x17] = FLOAD_printer,
  [0x22] = FLOAD_0_printer,
  [0x23] = FLOAD_1_printer,
  [0x24] = FLOAD_2_printer,
  [0x25] = FLOAD_3_printer,
  [0x6a] = FMUL_printer,
  [0x76] = FNEG_printer,
  [0x72] = FREM_printer,
  [0xae] = FRETURN_printer,
  [0x38] = FSTORE_printer,
  [0x43] = FSTORE_0_printer,
  [0x44] = FSTORE_1_printer,
  [0x45] = FSTORE_2_printer,
  [0x46] = FSTORE_3_printer,
  [0x66] = FSUB_printer,
  [0xb4] = GETFIELD_printer,
  [0xb2] = GETSTATIC_printer,
  [0xa7] = GOTO_printer,
  [0xc8] = GOTO_W_printer,
  [0x91] = I2B_printer,
  [0x92] = I2C_printer,
  [0x87] = I2D_printer,
  [0x86] = I2F_printer,
  [0x85] = I2L_printer,
  [0x93] = I2S_printer,
  [0x60] = IADD_printer,
  [0x2e] = IALOAD_printer,
  [0x7e] = IAND_printer,
  [0x4f] = IASTORE_printer,
  [0x02] = ICONST_M1_printer,
  [0x03] = ICONST_0_printer,
  [0x04] = ICONST_1_printer,
  [0x05] = ICONST_2_printer,
  [0x06] = ICONST_3_printer,
  [0x07] = ICONST_4_printer,
  [0x08] = ICONST_5_printer,
  [0x6c] = IDIV_printer,
  [0xa5] = IF_ACMPEQ_printer,
  [0xa6] = IF_ACMPNE_printer,
  [0x9f] = IF_ICMPEQ_printer,
  [0xa2] = IF_ICMPGE_printer,
  [0xa3] = IF_ICMPGT_printer,
  [0xa4] = IF_ICMPLE_printer,
  [0xa1] = IF_ICMPLT_printer,
  [0xa0] = IF_ICMPNE_printer,
  [0x99] = IFEQ_printer,
  [0x9c] = IFGE_printer,
  [0x9d] = IFGT_printer,
  [0x9e] = IFLE_printer,
  [0x9b] = IFLT_printer,
  [0x9a] = IFNE_printer,
  [0xc7] = IFNONNULL_printer,
  [0xc6] = IFNULL_printer,
  [0x84] = IINC_printer,
  [0x15] = ILOAD_printer,
  [0x1a] = ILOAD_0_printer,
  [0x1b] = ILOAD_1_printer,
  [0x1c] = ILOAD_2_printer,
  [0x1d] = ILOAD_3_printer,
  [0xfe] = IMPDEP1_printer,
  [0xff] = IMPDEP2_printer,
  [0x68] = IMUL_printer,
  [0x74] = INEG_printer,
  [0xc1] = INSTANCEOF_printer,
  [0xba] = INVOKEDYNAMIC_printer,
  [0xb9] = INVOKEINTERFACE_printer,
  [0xb7] = INVOKESPECIAL_printer,
  [0xb8] = INVOKESTATIC_printer,
  [0xb6] = INVOKEVIRTUAL_printer,
  [0x80] = IOR_printer,
  [0x70] = IREM_printer,
  [0xac] = IRETURN_printer,
  [0x78] = ISHL_printer,
  [0x7a] = ISHR_printer,
  [0x36] = ISTORE_printer,
  [0x3b] = ISTORE_0_printer,
  [0x3c] = ISTORE_1_printer,
  [0x3d] = ISTORE_2_printer,
  [0x3e] = ISTORE_3_printer,
  [0x64] = ISUB_printer,
  [0x7c] = IUSHR_printer,
  [0x82] = IXOR_printer,
  [0xa8] = JSR_printer,
  [0xc9] = JSR_W_printer,
  [0x8a] = L2D_printer,
  [0x89] = L2F_printer,
  [0x88] = L2I_printer,
  [0x61] = LADD_printer,
  [0x2f] = LALOAD_printer,
  [0x7f] = LAND_printer,
  [0x50] = LASTORE_printer,
  [0x94] = LCMP_printer,
  [0x09] = LCONST_0_printer,
  [0x0a] = LCONST_1_printer,
  [0x12] = LDC_printer,
  [0x13] = LDC_W_printer,
  [0x14] = LDC2_W_printer,
  [0x6d] = LDIV_printer,
  [0x16] = LLOAD_printer,
  [0x1e] = LLOAD_0_printer,
  [0x1f] = LLOAD_1_printer,
  [0x20] = LLOAD_2_printer,
  [0x21] = LLOAD_3_printer,
  [0x69] = LMUL_printer,
  [0x75] = LNEG_printer,
  [0xab] = LOOKUPSWITCH_printer,
  [0x81] = LOR_printer,
  [0x71] = LREM_printer,
  [0xad] = LRETURN_printer,
  [0x79] = LSHL_printer,
  [0x7b] = LSHR_printer,
  [0x37] = LSTORE_printer,
  [0x3f] = LSTORE_0_printer,
  [0x40] = LSTORE_1_printer,
  [0x41] = LSTORE_2_printer,
  [0x42] = LSTORE_3_printer,
  [0x65] = LSUB_printer,
  [0x7d] = LUSHR_printer,
  [0x83] = LXOR_printer,
  [0xc2] = MONITORENTER_printer,
  [0xc3] = MONITOREXIT_printer,
  [0xc5] = MULTIANEWARRAY_printer,
  [0xbb] = NEW_printer,
  [0xbc] = NEWARRAY_printer,
  [0x00] = NOP_printer,
  [0x57] = POP_printer,
  [0x58] = POP2_printer,
  [0xb5] = PUTFIELD_printer,
  [0xb3] = PUTSTATIC_printer,
  [0xa9] = RET_printer,
  [0xb1] = RETURN_printer,
  [0x35] = SALOAD_printer,
  [0x56] = SASTORE_printer,
  [0x11] = SIPUSH_printer,
  [0x5f] = SWAP_printer,
  [0xaa] = TABLESWITCH_printer,
  [0xc4] = WIDE_printer
};

int _wide_index = 0;
int _constant_print = 1;
int _jump = 0;

struct {
  u4 default_offset;
  u4 npairs;
  u4 **pairs;
} lookup_result;

int AALOAD_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int AASTORE_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ACONST_NULL_printer(u1 *bytestream){
  /* Push a NULL reference */
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ALOAD_printer(u1 *bytestream){
	if(!_wide_index){
	  printf("%s %d\n", opcode_to_mnemonic[bytestream[0]], bytestream[1]);
 		return 1;
	} else {
		printf("%s %d\n",
				opcode_to_mnemonic[bytestream[0]],
				(bytestream[1] << 8) | bytestream[2]
		);
		return 2;
	}
}
int ALOAD_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ALOAD_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ALOAD_2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ALOAD_3_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ANEWARRAY_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 2;
}
int ARETURN_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ARRAYLENGTH_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ASTORE_printer(u1 *bytestream){
	if(!_wide_index){
	  printf("%s %d\n", opcode_to_mnemonic[bytestream[0]], bytestream[1]);
 		return 1;
	} else {
		printf("%s %d\n",
				opcode_to_mnemonic[bytestream[0]],
				(bytestream[1] << 8) | bytestream[2]
		);
		return 2;
	}
}
int ASTORE_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ASTORE_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ASTORE_2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ASTORE_3_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ATHROW_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int BALOAD_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int BASTORE_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int BIPUSH_printer(u1 *bytestream){
  printf("%s %d\n", opcode_to_mnemonic[bytestream[0]], bytestream[1]);
  return 1;
}
int BREAKPOINT_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int CALOAD_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int CASTORE_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int CHECKCAST_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 2;
}
int D2F_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int D2I_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int D2L_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DADD_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DALOAD_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DASTORE_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DCMPG_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DCMPL_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DCONST_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DCONST_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DDIV_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DLOAD_printer(u1 *bytestream){
	if(!_wide_index){
	  printf("%s %d\n", opcode_to_mnemonic[bytestream[0]], bytestream[1]);
 		return 1;
	} else {
		printf("%s %d\n",
				opcode_to_mnemonic[bytestream[0]],
				(bytestream[1] << 8) | bytestream[2]
		);
		return 2;
	}
}
int DLOAD_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DLOAD_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DLOAD_2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DLOAD_3_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DMUL_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DNEG_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DREM_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DRETURN_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DSTORE_printer(u1 *bytestream){
	if(!_wide_index){
	  printf("%s %d\n", opcode_to_mnemonic[bytestream[0]], bytestream[1]);
 		return 1;
	} else {
		printf("%s %d\n",
				opcode_to_mnemonic[bytestream[0]],
				(bytestream[1] << 8) | bytestream[2]
		);
		return 2;
	}
}
int DSTORE_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DSTORE_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DSTORE_2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DSTORE_3_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DSUB_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DUP_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DUP_X1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DUP_X2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DUP2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DUP2_X1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int DUP2_X2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int F2D_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int F2I_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int F2L_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FADD_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FALOAD_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FASTORE_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FCMPG_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FCMPL_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FCONST_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FCONST_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FCONST_2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FDIV_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FLOAD_printer(u1 *bytestream){
	if(!_wide_index){
	  printf("%s %d\n", opcode_to_mnemonic[bytestream[0]], bytestream[1]);
 		return 1;
	} else {
		printf("%s %d\n",
				opcode_to_mnemonic[bytestream[0]],
				(bytestream[1] << 8) | bytestream[2]
		);
		return 2;
	}
}
int FLOAD_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FLOAD_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FLOAD_2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FLOAD_3_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FMUL_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FNEG_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FREM_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FRETURN_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FSTORE_printer(u1 *bytestream){
	if(!_wide_index){
	  printf("%s %d\n", opcode_to_mnemonic[bytestream[0]], bytestream[1]);
 		return 1;
	} else {
		printf("%s %d\n",
				opcode_to_mnemonic[bytestream[0]],
				(bytestream[1] << 8) | bytestream[2]
		);
		return 2;
	}
}
int FSTORE_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FSTORE_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FSTORE_2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FSTORE_3_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int FSUB_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int GETFIELD_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 2;
}
int GETSTATIC_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 2;
}
int GOTO_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int GOTO_W_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int32_t branchoffset = bytestream[1] << 24 | bytestream[2] << 16 | bytestream[3] << 8 | bytestream[4];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 4;
}
int I2B_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int I2C_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int I2D_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int I2F_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int I2L_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int I2S_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int IADD_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int IALOAD_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int IAND_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int IASTORE_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ICONST_M1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ICONST_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ICONST_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ICONST_2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ICONST_3_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ICONST_4_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ICONST_5_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int IDIV_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int IF_ACMPEQ_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IF_ACMPNE_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IF_ICMPEQ_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IF_ICMPGE_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IF_ICMPGT_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IF_ICMPLE_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IF_ICMPLT_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IF_ICMPNE_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IFEQ_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IFGE_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IFGT_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IFLE_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IFLT_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IFNE_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IFNONNULL_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IFNULL_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int IINC_printer(u1 *bytestream){
	if(!_wide_index){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		for(int i = 0; i < 2; i++)
			printf("%d ", bytestream[i + 1]);
		printf("\b\n");
		return 2;
	} else {
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		for(int i = 0; i < 2; i++)
			printf("%d ", (bytestream[2 * i + 1] << 8) | bytestream[2 * i + 2]);
		printf("\b\n");
		return 4;
	}
}
int ILOAD_printer(u1 *bytestream){
	if(!_wide_index){
	  printf("%s %d\n", opcode_to_mnemonic[bytestream[0]], bytestream[1]);
 		return 1;
	} else {
		printf("%s %d\n",
				opcode_to_mnemonic[bytestream[0]],
				(bytestream[1] << 8) | bytestream[2]
		);
		return 2;
	}
}
int ILOAD_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ILOAD_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ILOAD_2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ILOAD_3_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int IMPDEP1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int IMPDEP2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int IMUL_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int INEG_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int INSTANCEOF_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 2;
}
int INVOKEDYNAMIC_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 4;
}
int INVOKEINTERFACE_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 4;
}
int INVOKESPECIAL_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 2;
}
int INVOKESTATIC_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 2;
}
int INVOKEVIRTUAL_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 2;
}
int IOR_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int IREM_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int IRETURN_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ISHL_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ISHR_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ISTORE_printer(u1 *bytestream){
	if(!_wide_index){
	  printf("%s %d\n", opcode_to_mnemonic[bytestream[0]], bytestream[1]);
 		return 1;
	} else {
		printf("%s %d\n",
				opcode_to_mnemonic[bytestream[0]],
				(bytestream[1] << 8) | bytestream[2]
		);
		return 2;
	}
}
int ISTORE_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ISTORE_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ISTORE_2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ISTORE_3_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int ISUB_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int IUSHR_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int IXOR_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int JSR_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int16_t branchoffset = bytestream[1] << 8 | bytestream[2];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 2;
}
int JSR_W_printer(u1 *bytestream){
	if(!_jump++){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		int32_t branchoffset = bytestream[1] << 24 | bytestream[2] << 16 | bytestream[3] << 8 | bytestream[4];
		printf("%d\n", branchoffset);
		return branchoffset;
	}
	_jump += -2;
  return 4;
}
int L2D_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int L2F_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int L2I_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LADD_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LALOAD_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LAND_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LASTORE_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LCMP_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LCONST_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LCONST_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LDC_printer(u1 *bytestream){
	if(_constant_print--){
	  printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u1 index = bytestream[1];
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 1;
}
int LDC_W_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 2;
}
int LDC2_W_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 2;
}
int LDIV_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LLOAD_printer(u1 *bytestream){
	if(!_wide_index){
	  printf("%s %d\n", opcode_to_mnemonic[bytestream[0]], bytestream[1]);
 		return 1;
	} else {
		printf("%s %d\n",
				opcode_to_mnemonic[bytestream[0]],
				(bytestream[1] << 8) | bytestream[2]
		);
		return 2;
	}
}
int LLOAD_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LLOAD_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LLOAD_2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LLOAD_3_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LMUL_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LNEG_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int LOOKUPSWITCH_printer(u1 *bytestream){
	static int state = 0;
	if(!state){
		state = 1;
		return -1;
	}
	state = 0;
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	u1 pad = bytestream[1];
	u1 *paddedstream = bytestream + pad;
  // Default bytes
	int32_t defaultbytes = \
			(paddedstream[1] << 24) | \
			(paddedstream[2] << 16) | \
			(paddedstream[3] << 8) | \
			paddedstream[4];
  //printf("Default offset: %d ", defaultbytes);
  lookup_result.default_offset = defaultbytes;
  // N pairs
  int32_t npairs = \
			(paddedstream[5] << 24) | \
			(paddedstream[6] << 16) | \
			(paddedstream[7] << 8) | \
			paddedstream[8];
	//printf("Npairs: %d ", npairs);
  lookup_result.npairs = npairs;
  int i;
  lookup_result.pairs = (u4 **) malloc(sizeof(u4 *) * npairs);
  for(i = 0; i < npairs; i++){
    lookup_result.pairs[i] = (u4 *) malloc(sizeof(u4) * 2);
    lookup_result.pairs[i][0] = paddedstream[9 + i * 8] << 24 | paddedstream[10 + i * 8] << 16 | paddedstream[11 + i * 8] << 8 | paddedstream[12 + i * 8];
    lookup_result.pairs[i][1] = paddedstream[13 + i * 8] << 24 | paddedstream[14 + i * 8] << 16 | paddedstream[15 + i * 8] << 8 | paddedstream[16 + i * 8];
    /*printf(
      "(Match: %d Offset: %d) ",
      paddedstream[9 + i * 8] << 24 | paddedstream[10 + i * 8] << 16 | paddedstream[11 + i * 8] << 8 | paddedstream[12 + i * 8],
      paddedstream[13 + i * 8] << 24 | paddedstream[14 + i * 8] << 16 | paddedstream[15 + i * 8] << 8 | paddedstream[16 + i * 8]
    );*/
  }
	return pad + 8 + npairs * 8;
}
int LOR_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int LREM_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int LRETURN_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int LSHL_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int LSHR_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int LSTORE_printer(u1 *bytestream){
	if(!_wide_index){
	  printf("%s %d\n", opcode_to_mnemonic[bytestream[0]], bytestream[1]);
 		return 1;
	} else {
		printf("%s %d\n",
				opcode_to_mnemonic[bytestream[0]],
				(bytestream[1] << 8) | bytestream[2]
		);
		return 2;
	}
}
int LSTORE_0_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int LSTORE_1_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int LSTORE_2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int LSTORE_3_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int LSUB_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int LUSHR_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int LXOR_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int MONITORENTER_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int MONITOREXIT_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int MULTIANEWARRAY_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d %d\n", index, bytestream[3]);
		return -index - 1;
	}
	_constant_print += 2;
	return 3;
}
int NEW_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
	return 2;
}
int NEWARRAY_printer(u1 *bytestream){
  printf("%s %d\n", opcode_to_mnemonic[bytestream[0]], bytestream[1]);
	return 1;
}
int NOP_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int POP_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int POP2_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int PUTFIELD_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 2;
}
int PUTSTATIC_printer(u1 *bytestream){
	if(_constant_print--){
		printf("%s ", opcode_to_mnemonic[bytestream[0]]);
		u2 index = (u2) (bytestream[1] << 8 | bytestream[2]);
		printf("%d\n", index);
		return -index - 1;
	}
	_constant_print += 2;
  return 2;
}
int RET_printer(u1 *bytestream){
	if(!_wide_index){
	  printf("%s %d\n", opcode_to_mnemonic[bytestream[0]], bytestream[1]);
 		return 1;
	} else {
		printf("%s %d\n",
				opcode_to_mnemonic[bytestream[0]],
				(bytestream[1] << 8) | bytestream[2]
		);
		return 2;
	}
}
int RETURN_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
  return 0;
}
int SALOAD_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int SASTORE_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int SIPUSH_printer(u1 *bytestream){
  printf("%s ", opcode_to_mnemonic[bytestream[0]]);
  for(int i = 0; i < 2; i++)
    printf("%d ", bytestream[i + 1]);
  printf("\b\n");
	return 2;
}
int SWAP_printer(u1 *bytestream){
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	return 0;
}
int TABLESWITCH_printer(u1 *bytestream){
	static int state = 0;
	if(state == 0){
		state = 1;
		return -1;
	}
	state = 0;
  printf("%s\n", opcode_to_mnemonic[bytestream[0]]);
	u1 pad = bytestream[1];
	u1 *paddedstream = bytestream + pad;
	// Default bytes (1-4)
	u4 defaultbytes = \
			(paddedstream[1] << 24) | \
			(paddedstream[2] << 16) | \
			(paddedstream[3] << 8) | \
			paddedstream[4];
	lookup_result.default_offset = defaultbytes;
	// Low bytes (1-4)
	u4 low = \
			(paddedstream[5] << 24) | \
			(paddedstream[6] << 16) | \
			(paddedstream[7] << 8) | \
			paddedstream[8];
	// printf("%d ", low);
	// High bytes (1-4)
	u4 high = \
			(paddedstream[9] << 24) | \
			(paddedstream[10] << 16) | \
			(paddedstream[11] << 8) | \
			paddedstream[12];
	// printf("%d ", high);
	// Offsets (x)
	u4 x = high - low + 1;
	lookup_result.npairs = x;
	int i, j;
	lookup_result.pairs = (u4 **) malloc(sizeof(u4 *) * x);
	for(i = 0, j = low; i < x; i++, j++){
    lookup_result.pairs[i] = (u4 *) malloc(sizeof(u4) * 2);
		lookup_result.pairs[i][0] = j;
		lookup_result.pairs[i][1] = \
				paddedstream[13 + i * 4] << 24 | \
				paddedstream[14 + i * 4] << 16 | \
				paddedstream[15 + i * 4] << 8 | \
				paddedstream[16 + i * 4];
	}
	return pad + 12 + x * 4;
}
int WIDE_printer(u1 *bytestream){
  printf("%s ", opcode_to_mnemonic[bytestream[0]]);
	_wide_index = 1;
  int ret = (opcode_printers[bytestream[1]])(bytestream + 1);
	_wide_index = 0;
	return ret + 1; // index bytes + bytestream[1] opcode
}
