#include <stdio.h>
#include <stdlib.h>

#include "../include/breads.h"
#include "../include/bprint_classfile.h"

int main(int argc, char **argv){
  if(argc < 2){
    fprintf(stderr, "Usage:\n\t%s <.class file name>\n", argv[0]);
    exit(ERR_NOFILE);
  }

  char *filename = argv[1];
  FILE *classfile = fopen(filename, "rb");
  
  ClassFile *class = bread_classfile(classfile);

  bprint_classfile(class);

  return 0;
}











