#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/errcodes.h"
#include "../include/utils.h"

/*Verifica os argumentos passado na execução do programa*/
void verify_arguments(int argc, char **argv);

#endif