#ifndef errcodes_h
#define errcodes_h

enum {
  ERR_NOFILE = -1,
  ERR_MAGIC = -2,
  ERR_UNKTAG,
  ERR_CANTOPENFILE,
	ERR_MINOR,
	ERR_MAJOR,
  ERR_SRC,
  ERR_UNKOPT,
  ERR_INSARG,
  ERR_ARGMODE,
  ERR_ARGPATH,
  ERR_ARGFILE,
	ERR_INDEX,
  ERR_UNKTYPE,
  ERR_EMPTY,
	ERR_INVREF
} Errors;

#endif
