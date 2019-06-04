#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../include/errcodes.h"

enum {
  OPTION_off = 0,                     
  OPTION_on = 1,                      
  OPTION_viewer = 0,                  
  OPTION_interpreter = 1,
  OPTION_default = 2
} OPTION;

enum {
  ARG_VERBOSE,
  ARG_CONSTPOOL,                          
  ARG_MODE,
  ARG_PATH,
  ARG_FILE                            
} ARG;

int VERBOSE = OPTION_off;
int MODE = OPTION_default;
int CONSTPOOL = OPTION_on;       
char *PATH = NULL;                    
char *CLASSFILE = NULL;              

/*
   TODO - ordenar
*/
#define NOPTIONS 5
struct{
  int id;
  char *option1;
  char *option2;
} OPTIONS[] = {                       
  {ARG_VERBOSE   , "v" , "verbose"  },
  {ARG_CONSTPOOL , "c" , "constpool"},
  {ARG_MODE      , "m" , "mode"     },
  {ARG_PATH      , "p" , "path"     },
  {ARG_FILE      , "f" , "file"     } 
};



/*
TODO:
  Refatorar o código, pois está muito espaguete
  Trata os argumentos passados na execução do programa
  (verificar se PATH é um caminho e se FILE é um arquivo)
*/
void initialize(int argc, char **argv){
  if(argc < 4){
    fprintf(stderr, "Mode, path and file missing!\n");
    exit(ERR_INSARG);
  }
  char **opt_str = argv + 1;
  int opt_qtd = argc - 1;

  /* Configura os argumentos com flag */
  int i;
  uint8_t obg = 0x1, obgf = 0x0;
  for(i = 0; i < opt_qtd; i++){
    /* -f */
    if(*opt_str[i] == '-'){
      int j;
      for(j = 0; j < NOPTIONS; j++){
        if(            /* -file --file*/
            !strcmp(opt_str[i]+1, OPTIONS[j].option1) ||
            (
              *(opt_str[i]+1) == '-' &&
              !strcmp(opt_str[i]+2, OPTIONS[j].option2)
            )
          ){
          switch(OPTIONS[j].id){
            case ARG_VERBOSE: VERBOSE = OPTION_on; break;
            case ARG_CONSTPOOL: CONSTPOOL = OPTION_off; break;
            case ARG_MODE:
              if(strcmp("viewer", opt_str[i+1]))
                  MODE = OPTION_interpreter;
              else if(strcmp("interpreter", opt_str[i+1]))
                  MODE = OPTION_viewer;
              else goto invalid_option;
              i++;
              obgf |= 0x1;
              break;
            case ARG_PATH: PATH = opt_str[++i]; obgf |= 0x2; break;
            case ARG_FILE: CLASSFILE = opt_str[++i]; obgf |= 0x4; break;
            invalid_option:
            default:
              fprintf(
                  stderr,
                  "Unknown option \"%s\"\n",
                  opt_str[i]
              );
              setbuf(stderr, NULL);
              exit(ERR_UNKOPT);
              break;
          }
          break;
        }else if(j == NOPTIONS - 1) goto invalid_option;
      }
    }else{
      while(obg & obgf) obg <<= 1;
      switch(obg){
        case 0x1:
          if(strcmp("viewer", opt_str[i+1]))
            MODE = OPTION_interpreter;
          else if(strcmp("interpreter", opt_str[i+1]))
            MODE = OPTION_viewer;
          else goto invalid_option;
          obg <<= 1;
          break;
        case 0x2:
          PATH = opt_str[i];
          obg <<= 1;
          break;
        case 0x4:
          CLASSFILE = opt_str[i];
          obg <<= 1;
          break;
        default:
          break;
      }
    }
  }
  if(MODE == OPTION_default){
    fprintf(stderr, "No mode.\n");
    exit(ERR_ARGMODE);
  }
  if(!PATH){
    fprintf(stderr, "No path.\n");
    exit(ERR_ARGPATH);
  }
  if(!CLASSFILE){
    fprintf(stderr, "No file.\n");
    exit(ERR_ARGFILE);
  }
  return;
}