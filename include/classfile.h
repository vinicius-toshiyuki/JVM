/**
 * @file classfile.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the definition of a classfile struct.
 */
#ifndef classfile_h
#define classfile_h

#include "types.h"
#include "info.h"

/**
 * \struct cp_info
 * Definition of cp_info.
 * Contains the struct of the constant pool.
 */
typedef struct {
  u1 tag;
  info_t *info;
} cp_info;

/**
 * \struct attribute_info
 * Definition of attribute_info.
 * Contains the struct of the attribute.
 */
typedef struct {
  u2 attribute_name_index;
  u4 attribute_length;
  u1 *info;
} attribute_info;

/**
 * \struct field_info
 * Definition of field_info.
 * Contains the struct of the field.
 */
typedef struct {
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  attribute_info *attributes;
} field_info;

/**
 * \struct method_info
 * Definition of method_info.
 * Contains the struct of the method.
 */
typedef struct {
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  attribute_info *attributes;
} method_info;

/**
 * \struct ClassFile
 * Definition of ClassFile.
 * Contains the struct of a class file format.
 */
typedef struct {
  u4 magic; /**< Identify a .class format. */
  u2 minor_version;
  u2 major_version;
  u2 const_pool_count; /**< Length of the constant pool. */
  cp_info *constant_pool; /**< Constant pool. */
  u2 access_flags; /**< Indicates the access policy of a class or interface. */
  u2 this_class; /**< Points to a CONSTANT_Class_info structure. */
  u2 super_class; /**< Points to a CONSTANT_Class_info if the class has a parent class, if it does not have a zero value. */
  u2 interfaces_count; /**< Number of direct superinterfaces of this class or interface. */
  u2 *interfaces; /**< Interfaces. */
  u2 fields_count; /**< Number of class variables or variants of instances declared in this class or interface. */
  field_info *fields; /**< Includes only the fields declared in the class or interface. */
  u2 methods_count; /**< Number of methods of the class or interface. */
  method_info *methods; /**< Contains only the methods of the class or interface. */
  u2 attributes_count; /**< Number of class attributes. */
  attribute_info *attributes /**< Class attributes. */;
} ClassFile;

#endif /*classfile_h */

