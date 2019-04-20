#include "../include/bread_attributes.h"

void bread_attributes(attribute_info *atts, int atts_count, FILE *classfile){

  for(int i = 0; i < atts_count; i++){
      u2_read(atts[i].attribute_name_index, classfile);
      u4_read(atts[i].attribute_length, classfile);

      atts[i].info = (u1 *) malloc(sizeof(u1) * atts[i].attribute_length);
      for(int j = 0; j < atts[i].attribute_length; j++)
        u1_read(atts[i].info[j], classfile);
  }

  return;
}
