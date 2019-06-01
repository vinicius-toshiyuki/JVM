#ifndef errcodes_h
#define errcodes_h

enum {
  ERR_NOFILE = -1,
  ERR_MAGIC = -2,
  ERR_UNKTAG,
  ERR_CANTOPENFILE,
	ERR_MINOR,
	ERR_MAJOR,
  ERR_SRC
} Errors;

#endif
