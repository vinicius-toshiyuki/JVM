#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

#define u1_read(buffer, file) { fread(&buffer, sizeof(u1), 1, file); }
#define u2_read(buffer, file) { int i; for(i = 0; i < 2; i++){u1 byte; u1_read(byte, file); buffer <<= i == 0 ? 0 : 8; buffer |= byte;} }
#define u4_read(buffer, file) { int i; for(i = 0; i < 4; i++){u1 byte; u1_read(byte, file); buffer <<= i == 0 ? 0 : 8; buffer |= byte;} }

int main(int argc, char **argv){
  if(argc < 2){
    fprintf(stderr, "Faltou o arquivo\n");
    exit(-1);
  }
  char *filename = argv[1];
  FILE *class = fopen(filename, "rb");

  u4 cafe;
  u4_read(cafe, class);

  printf("%x\n", cafe);

  u2 m, M;
  u2_read(m, class);
  u2_read(M, class);

  printf("Minor: %x\nMajor: %x\n", m, M);

  u2 const_pool_count;
  u2_read(const_pool_count, class);

  printf("CPC: %x (%hu)\n", const_pool_count, const_pool_count);

  return 0;
}
