/**
 * @file errcodes.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contains the erros types may occur during the execution of the program.
 */
#ifndef errcodes_h
#define errcodes_h

/**
 * \enum Errors
 * Errors Types may occur during the execution of the program.
 */
enum {
  ERR_NOFILE = 1, /**< File not encountered. */
  ERR_MAGIC, /**< Magic Number does not equal to 0xCAFEBABE. */
  ERR_UNKTAG, /**< Unknown entry from constant pool. */
  ERR_CANTOPENFILE, /**< Can't open the file. */
	ERR_MINOR, /**< JVM version is below minor version required. */
	ERR_MAJOR, /**< JVM version is below major version required. */
  ERR_SRC,
  ERR_UNKOPT, /**< Unknown option. */
  ERR_INSARG, /**< Insufficient arguments. */
  ERR_ARGMODE, /**< No Mode argument. */
  ERR_ARGPATH, /**< No Path argument. */
  ERR_ARGFILE, /**< No class file argument. */
	ERR_INDEX,  /**< Invalid index. */
  ERR_UNKTYPE, /**< Unknown type. */
  ERR_EMPTY,  /**< Stack or List Empty. */
	ERR_INVREF, /**< Invalid Reference. */
	ERR_INVARR, /**< Invalid Array. */
	ERR_UNASSG,
	ERR_INVDESC, /**< Invalid Descriptor. */
	ERR_NOMETH /**< No Method. */
} Errors;

#endif /* errcodes_h */
