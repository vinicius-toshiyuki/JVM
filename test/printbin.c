#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
	FILE *f = fopen(argv[1], "rb");
	while(!feof(f) || (printf("\b\n") && 0))
		printf("0x%02x ", fgetc(f));
	return 0;
}
