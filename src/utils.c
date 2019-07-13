#include "../include/utils.h"

int comp(const void *a, const void *b) {return *((char *) a) - *((char *) b);}

int charcmp(const void *a, const void *b){
	return *((char *) a) - *((char *) b);
}

void print_utf8(info_t *string_utf8){

    setlocale(LC_ALL, "");
	static char escapes[7][4] = {"\aa", "\bb", "\tt", "\nn", "\vv", "\ff", "\rr"};
	u1 *bytes = string_utf8->Utf8.bytes;
	for(int i = 0; i < string_utf8->Utf8.length; i++){
		wchar_t utf8char;
		if((bytes[i] & 0x80) == 0x00){
			char c[] = {bytes[i], '\0'}, *c1;
			c1 = bsearch(c, escapes, 7, 4, charcmp);
			if(c1){
				printf("\\%c", *++c1);
				utf8char = *++c1;
			}else{
				utf8char = (wchar_t) bytes[i];
			}
		}else if((bytes[i] & 0xE0) == 0xC0)
			utf8char = (wchar_t) (((bytes[i] & 0x1F) << 6) | (bytes[i + 1] & 0x3F)), i++;
		else if((bytes[i] & 0xF0) == 0xE0)
			utf8char = (wchar_t) (((bytes[i] & 0x0F) << 12) | ((bytes[i + 1] & 0x3F) << 6) | (bytes[i + 2] & 0x3F)), i += 2;
		else if((bytes[i] & 0xF8) == 0xF0)
			utf8char = (wchar_t) (((bytes[i] & 0x07) << 18) | ((bytes[i + 1] & 0x3F) << 12) | ((bytes[i + 2] & 0x4F) << 6) | (bytes[i + 3] & 0x3F)), i += 3;
		else
			printf("0x%02x ", bytes[i]);
		printf("%lc", utf8char);
	}
}