#ifndef types_h
#define types_h

#include <stdint.h>

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

#define CLEAN 0x0000

/*-------------------------------------------FILE READ------------------------------------------*/

/*Le um byte do class_file e armazena no buffer*/
#define u1_read(__buff__, __class_file__) {\
    fread(&__buff__, sizeof(u1), 1, __class_file__);\
}

/*Le 2 bytes no formato big endian e armazena no buffer*/
#define u2_read(__buff__, __class_file__) { \
    u1 __byte1__ = CLEAN; \
    u1 __byte2__ = CLEAN; \
    fread(&__byte1__, sizeof(u1), 1, __class_file__); \
    fread(&__byte2__, sizeof(u1), 1, __class_file__); \
    __buff__ = ((__byte1__ << 8) | __byte2__); \
}

/*Le 4 bytes no formato big endian e armazena no buffer*/
#define u4_read(__buff__, __class_file__) { \
    u1 __byte1__ = CLEAN; \
    u1 __byte2__ = CLEAN; \
    u1 __byte3__ = CLEAN; \
    u1 __byte4__ = CLEAN; \
    fread(&__byte1__, sizeof(u1), 1, __class_file__); \
    fread(&__byte2__, sizeof(u1), 1, __class_file__); \
    fread(&__byte3__, sizeof(u1), 1, __class_file__); \
    fread(&__byte4__, sizeof(u1), 1, __class_file__); \
    __buff__ = ((__byte1__ << 8) | __byte2__); \
    __buff__ = ((__buff__ << 8) | __byte3__); \
    __buff__ = ((__buff__ << 8) | __byte4__); \
}

#endif

