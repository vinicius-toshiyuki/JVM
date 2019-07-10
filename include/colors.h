#ifndef colors_h
#define colors_h

#include <stdio.h>

#ifdef __linux__nao_definido_
	#define BGC(__code) "\033[48;5;" #__code "m"
	#define FGC(__code) "\033[38;5;" #__code "m"
	#define CLEAR "\033[0m"
	#define CLEARN "\033[0m\n"
#else
	#define BGC(__code) ""
	#define FGC(__code) ""
	#define CLEAR ""
	#define CLEARN "\n"
#endif

#endif

