#ifndef initialize_haaaa
#define initialize_haaaa

typedef enum {
  OPTION_off = 0,                     
  OPTION_on = 1,                      
  OPTION_viewer = 0,                  
  OPTION_interpreter = 1,
  OPTION_default = 2
} OPTION;

typedef enum {
  ARG_VERBOSE,
  ARG_CONSTPOOL,                          
  ARG_MODE,
  ARG_PATH,
  ARG_FILE,
	ARG_IGNORE,
	ARG_JVM_ARGS
} ARG;

/*
   TODO - ordenar
*/

void initialize(int, char **);
void __invalid__option(char *);

#endif
