#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../include/errcodes.h"
#include "../include/initialize.h"

int VERBOSE = OPTION_off;
int MODE = OPTION_default;
int CONSTPOOL = OPTION_on;       
char *PATH = NULL;                    
char *CLASSFILE = NULL;              
int IGNORE = OPTION_off;
int JVM_ARGC = 0;
char **JVM_ARGV = NULL;

#define NOPTIONS 7
struct{
  int id;
  char *option1;
  char *option2;
} ARG_OPTIONS[] = {                       
  {ARG_VERBOSE   , "v" , "verbose"  },
  {ARG_CONSTPOOL , "c" , "constpool"},
  {ARG_MODE      , "m" , "mode"     },
  {ARG_PATH      , "p" , "path"     },
  {ARG_FILE      , "f" , "file"     }, 
	{ARG_IGNORE    , "i" , "ignore"   },
	{ARG_JVM_ARGS  , "a" , "args"     }
};

/*
TODO:
  Refatorar o código, pois está muito espaguete
  Trata os argumentos passados na execução do programa
  (verificar se PATH é um caminho e se FILE é um arquivo)
*/
void __invalid__option(char *option){
	fprintf(
			stderr,
			"Unknown option \"%s\"\n",
			option
			);
	/* setbuf(stderr, NULL); */
	exit(ERR_UNKOPT);
	return;
}

void initialize(int argc, char **argv){
  if(argc < 4){
    fprintf(stderr, "Mode, path and file missing!\n");
    exit(ERR_INSARG);
  }
  char **opt_str = argv + 1;
  int opt_qtd = argc - 1;

  /* Configura os argumentos com flag */
  int i;
  uint8_t obg = 0x01, obgf = 0x00;
  for(i = 0; i < opt_qtd; i++){
    /* -f */
    if(*opt_str[i] == '-'){
      int j;
      for(j = 0; j < NOPTIONS; j++){
        if(            /* -file --file*/
            !strcmp(opt_str[i]+1, ARG_OPTIONS[j].option1) ||
            (
              *(opt_str[i]+1) == '-' &&
              !strcmp(opt_str[i]+2, ARG_OPTIONS[j].option2)
            )
          ){
          switch(ARG_OPTIONS[j].id){
            case ARG_VERBOSE: VERBOSE = OPTION_on; break;
            case ARG_CONSTPOOL: CONSTPOOL = OPTION_off; break;
            case ARG_MODE:
              if(!strcmp("viewer", opt_str[i+1]))
                  MODE = OPTION_viewer;
              else if(!strcmp("interpreter", opt_str[i+1]))
                  MODE = OPTION_interpreter;
							if(MODE == OPTION_default) __invalid__option(opt_str[++i]);
              i++;
              obgf |= 0x1;
              break;
            case ARG_PATH: PATH = opt_str[++i]; obgf |= 0x2; break;
            case ARG_FILE: CLASSFILE = opt_str[++i]; obgf |= 0x4; break;
            case ARG_IGNORE: IGNORE = OPTION_on; break;
						case ARG_JVM_ARGS:
							/* SE TIVER ESSA FLAG VAI CONSIDERAR TODO O RESTO DOS ARGUMENTOS COMO ARGUMENTOS PARA O INTERPRETADOR */
							JVM_ARGC = opt_qtd-i-1 < 0 ? 0 : opt_qtd-i-1;
							JVM_ARGV = &opt_str[i + 1];
							goto endloop;
            default:
							__invalid__option(opt_str[i]);
              break;
          }
          break;
        }else if(j == NOPTIONS - 1) __invalid__option(opt_str[i]);
      }
    }else{
			if(!(obgf & 0x1)) obg = 0x1;
			else if(!(obgf & 0x2)) obg = 0x2;
			else if(!(obgf & 0x4)) obg = 0x4;
      switch(obg){
        case 0x1:
          if(!strcmp("viewer", opt_str[i]))
            MODE = OPTION_viewer;
          else if(!strcmp("interpreter", opt_str[i]))
            MODE = OPTION_interpreter;
          else __invalid__option(opt_str[i]);
          obgf |= 0x1;
          break;
        case 0x2:
          PATH = opt_str[i];
          obgf |= 0x2;
          break;
        case 0x4:
          CLASSFILE = opt_str[i];
          obgf |= 0x4;
          break;
        default:
					__invalid__option(opt_str[i]);
          break;
      }
    }
  }
endloop:
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
