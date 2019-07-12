/**
 * @file bytecode.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the implementation of the java machine instructions.
 */
#ifndef bytecode_h
#define bytecode_h

#include "types.h"
#include "frame.h"
#include "jvm.h"
#include "constant_pool.h"
#include "objectref.h"
#include "instance.h"

#define NIL (void *) 0x1

typedef void (*handler)(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);

void AALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void AASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ACONST_NULL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ALOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ALOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ALOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ALOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ANEWARRAY_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ARETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ARRAYLENGTH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ASTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ASTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ASTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ASTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ATHROW_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void BALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void BASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void BIPUSH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void CALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void CASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void CHECKCAST_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void D2F_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void D2I_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void D2L_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DCMPG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DCMPL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DCONST_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DCONST_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DDIV_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DLOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DLOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DLOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DLOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DLOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DNEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DRETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DSTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DSTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DSTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DSTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DSTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DSUB_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DUP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DUP_X1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DUP_X2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DUP2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DUP2_X1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void DUP2_X2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void F2D_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void F2I_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void F2L_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FCMPG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FCMPL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FCONST_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FCONST_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FCONST_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FDIV_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FLOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FLOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FLOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FLOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FLOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FNEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FRETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FSTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FSTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FSTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FSTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FSTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void FSUB_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void GETFIELD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void GETSTATIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void GOTO_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void GOTO_W_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void I2B_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void I2C_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void I2D_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void I2F_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void I2L_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void I2S_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IAND_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ICONST_M1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ICONST_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ICONST_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ICONST_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ICONST_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ICONST_4_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ICONST_5_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IDIV_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IF_ACMPEQ_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IF_ACMPNE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IF_ICMPEQ_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IF_ICMPGE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IF_ICMPGT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IF_ICMPLE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IF_ICMPLT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IF_ICMPNE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IFEQ_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IFGE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IFGT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IFLE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IFLT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IFNE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IFNONNULL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IFNULL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IINC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ILOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ILOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ILOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ILOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ILOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void INEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void INSTANCEOF_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void INVOKEDYNAMIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void INVOKEINTERFACE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void INVOKESPECIAL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void INVOKESTATIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void INVOKEVIRTUAL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IOR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IRETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ISHL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ISHR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ISTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ISTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ISTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ISTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ISTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void ISUB_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IUSHR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void IXOR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void JSR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void JSR_W_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void L2D_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void L2F_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void L2I_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LADD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LAND_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LCMP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LCONST_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LCONST_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LDC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LDC_W_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LDC2_W_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LDIV_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LLOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LLOAD_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LLOAD_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LLOAD_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LLOAD_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LMUL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LNEG_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LOOKUPSWITCH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LOR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LREM_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LRETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LSHL_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LSHR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LSTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LSTORE_0_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LSTORE_1_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LSTORE_2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LSTORE_3_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LSUB_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LUSHR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void LXOR_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void MONITORENTER_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void MONITOREXIT_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void MULTIANEWARRAY_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void NEW_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void NEWARRAY_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void NOP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void POP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void POP2_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void PUTFIELD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void PUTSTATIC_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void RET_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void RETURN_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void SALOAD_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void SASTORE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void SIPUSH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void SWAP_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void TABLESWITCH_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);
void WIDE_handler(u1 **pc, u1 *bp, frame_t *frame, jvm_t *jvm);

#endif
