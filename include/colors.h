#ifndef colors_h
#define colors_h

#include <stdio.h>

#define BGC(__code) "\e[48;5;" #__code "m"
#define FGC(__code) "\e[38;5;" #__code "m"
#define CLEAR "\e[0m"
#define CLEARN "\e[0m\n"

#endif

