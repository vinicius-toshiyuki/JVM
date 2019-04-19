#ifndef types_h
#define types_h

#include <stdint.h>

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

#define u1_read(buffer, file) { fread(&buffer, sizeof(u1), 1, file); }
/* Por algum motivo não funciona com um for em algum caso: zera o valor de buffer ao final ou até deu segmentation fault */
#define u2_read(buffer, file) \
{ \
  buffer = 0x0000; \
  u1 __byte; \
  u1_read(__byte, file); \
  buffer |= __byte; \
  u1_read(__byte, file); \
  buffer = (buffer << 8) | __byte; \
}
#define u4_read(buffer, file) { int ____i; for(____i = 0; ____i < 4; ____i++){u1 ____byte; u1_read(____byte, file); buffer <<= ____i == 0 ? 0 : 8; buffer |= ____byte;} }

#endif

