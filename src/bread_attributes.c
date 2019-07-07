#include "../include/bread_attributes.h"
#include "../include/bprint_classfile.h"
#include "../include/attributes.h"

extern int VERBOSE;

void bread_attributes(attribute_info *atts, int atts_count, FILE *classfile){
	for(int i = 0; i < atts_count; i++){
		u2_read(atts[i].attribute_name_index, classfile);
		u4_read(atts[i].attribute_length, classfile);

		atts[i].info = (u1 *) calloc(atts[i].attribute_length, sizeof(u1));
		for(int j = 0; j < atts[i].attribute_length; j++)
			u1_read(atts[i].info[j], classfile);
	}
  return;
}
