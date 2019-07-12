/**
 * @file info.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the definition of the constant pool structs.
 */
#ifndef info_h
#define info_h

#include "types.h"

/** \enum CONSTANTS
 * Entries of the constant pool.
 */
enum {
  CONSTANT_Class = 7,
  CONSTANT_Fieldref = 9,
  CONSTANT_Methodref = 10,
  CONSTANT_InterfaceMethodref = 11,
  CONSTANT_String = 8,
  CONSTANT_Integer = 3,
  CONSTANT_Float = 4,
  CONSTANT_Long = 5,
  CONSTANT_Double = 6,
  CONSTANT_NameAndType = 12,
  CONSTANT_Utf8 = 1
} CONSTANTS;

/**
 * \struct CONSTANT_Class_info
 * A CONSTANT_Class from the constant pool.
 */
typedef struct {
  u2 name_index;
} CONSTANT_Class_info;

/**
 * \struct CONSTANT_Fieldref_info
 * A CONSTANT_Fieldref from the constant pool.
 */
typedef struct {
  u2 class_index;
  u2 name_and_type_index;
} CONSTANT_Fieldref_info;

/**
 * \struct CONSTANT_Methodref_info
 * A CONSTANT_Methodref from the constant pool.
 */
typedef struct {
  u2 class_index;
  u2 name_and_type_index;
} CONSTANT_Methodref_info;

/**
 * \struct CONSTANT_InterfaceMethodref_info
 * A CONSTANT_InterfaceMethodref from the constant pool.
 */
typedef struct {
  u2 class_index;
  u2 name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

/**
 * \struct CONSTANT_String_info
 * A CONSTANT_String from the constant pool.
 */
typedef struct {
  u2 string_index;
} CONSTANT_String_info;

/**
 * \struct CONSTANT_Integer_info
 * A CONSTANT_Integer from the constant pool.
 */
typedef struct {
  u4 bytes;
} CONSTANT_Integer_info;

/**
 * \struct CONSTANT_Float_info
 * A CONSTANT_Float from the constant pool.
 */
typedef struct {
  u4 bytes;
} CONSTANT_Float_info;

/**
 * \struct CONSTANT_Long_info
 * A CONSTANT_Long from the constant pool.
 */
typedef struct {
  u4 high_bytes;
  u4 low_bytes;
} CONSTANT_Long_info;

/**
 * \struct CONSTANT_Double_info
 * A CONSTANT_Double from the constant pool.
 */
typedef struct {
  u4 high_bytes;
  u4 low_bytes;
} CONSTANT_Double_info;

/**
 * \struct CONSTANT_NameAndType_info
 * A CONSTANT_NameAndType from the constant pool.
 */
typedef struct {
  u2 name_index;
  u2 descriptor_index;
} CONSTANT_NameAndType_info;

/**
 * \struct CONSTANT_Utf8_info
 * A CONSTANT_Utf8 from the constant pool.
 */
typedef struct {
  u2 length;
  u1 *bytes;
} CONSTANT_Utf8_info;

/**
 * \union info_t
 * Union of the entries of the constant pool.
 */
typedef union {
  CONSTANT_Class_info Class;
  CONSTANT_Fieldref_info Fieldref;
  CONSTANT_Methodref_info Methodref;
  CONSTANT_InterfaceMethodref_info InterfaceMethodref;
  CONSTANT_String_info String;
  CONSTANT_Integer_info Integer;
  CONSTANT_Float_info Float;
  CONSTANT_Long_info Long;
  CONSTANT_Double_info Double;
  CONSTANT_NameAndType_info NameAndType;
  CONSTANT_Utf8_info Utf8;
} info_t;

#endif /*info_h */

