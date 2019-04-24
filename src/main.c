#include <stdio.h>
#include <stdlib.h>

#include "../include/breads.h"
#include "../include/bprint_classfile.h"
#include "../include/bfree_classfile.h"
#include "../include/stack.h"

int verbose = 1;

int main(int argc, char **argv){
  if(argc < 2){
    fprintf(stderr, "Usage:\n\t%s <.class file name>\n", argv[0]);
    exit(ERR_NOFILE);
  }

  char *filename = argv[1];
  FILE *classfile = fopen(filename, "rb");

  if(classfile == NULL){
    fprintf(stderr, "Failed to open specified file\n");
    exit(ERR_CANTOPENFILE);
  }

  if(verbose) printf("File opened\n");
  
  ClassFile *class = bread_classfile(classfile);

  if(verbose) printf("File read\n");

  bprint_classfile(class);

  bfree_classfile(class);

  fclose(classfile);

  return 0;
}











