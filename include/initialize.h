/**
 * @file initialize.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contains the types of arguments passed by main.
 */
#ifndef initialize_h
#define initialize_h

/**
 * \enum OPTION
 * Types of options used by define the aspect of the program.
 */
typedef enum {
  OPTION_off = 0,                     
  OPTION_on = 1,                      
  OPTION_viewer = 0,                  
  OPTION_interpreter = 1,
  OPTION_default = 2
} OPTION;

/**
 * \enum ARG
 * Types of arguments used by define the aspect of the program.
 */
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

/**
 * Treats arguments passed to main.
 */
void initialize(int, char **);

/**
 * Throws an error if the option is invalid.
 */
void __invalid__option(char *);

#endif /* initialize_h */
