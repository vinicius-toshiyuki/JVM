#include "../include/method_area.h"
#include "../include/attributes.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

method_area_t * new_method_area(void){
	method_area_t *new = (method_area_t *) malloc(sizeof(method_area_t));
	new->count = 0;
	new->loaded = new_clist();
	return new;
}

void destroy_method_area(method_area_t *ma){

	return;
}

extern char *PATH;
void load_class(method_area_t *marea, char *pathtoclass){
	/* PATH + pathtoclass */
	char *fullpath = (char *) calloc(strlen(PATH) + strlen(pathtoclass) + 1, sizeof(char));
	strcat(fullpath, PATH);
	strcat(fullpath, pathtoclass);
	FILE *classfile = fopen(fullpath, "rb");
	if(!classfile){
		fprintf(stderr, "Can not open specified file.\n");
		exit(ERR_CANTOPENFILE);
	}
	ClassFile *class = bread_classfile(classfile, fullpath);
	link_class(marea, class);
	free(fullpath);
	return;
}

void link_class(method_area_t *marea, ClassFile *class){
	cappend(marea->loaded, class);
	marea->count = marea->loaded->size;
	/* initialize_class(class); */
	return;
}

int is_loaded(method_area_t *marea, char *classname){
	int i, is = 0;
	celement_t *iter = marea->loaded->head;
	char *javaclassname = (char *) calloc(strlen(classname) + 6 /* .java\0 */, sizeof(char));
	char *jcn = javaclassname;
	strcpy(javaclassname, classname);
	strcat(javaclassname, ".java");
	for(i = 0; i < strlen(javaclassname); i++)
		if(javaclassname[strlen(javaclassname) - i] == '/'){
			jcn = javaclassname + strlen(javaclassname) - i + 1;
			break;
		}
	Attributes att;
	for(i = 0; i < marea->count; i++, iter = iter->next){
		ClassFile *class = (ClassFile *) iter->value;
		attribute_info *att_info = class->attributes;
		get_attribute_from_info(att_info[0].info, &att, att_info[0].attribute_name_index, class);
		char *curr_name = (char *) calloc(class->constant_pool[att.SourceFile.sourcefile_index - 1].info->Utf8.length + 1, sizeof(char));
		memcpy(curr_name, class->constant_pool[att.SourceFile.sourcefile_index - 1].info->Utf8.bytes, class->constant_pool[att.SourceFile.sourcefile_index - 1].info->Utf8.length);
		if(!strcmp(curr_name, jcn)){
			free(curr_name);
			is = 1;
			break;
		}
		free(curr_name);
	}
	free(javaclassname);
	return is;
}

ClassFile * get_class_by_name(method_area_t *marea, char *classname){
	int i;
	ClassFile *ret_class = NULL;
	celement_t *iter = marea->loaded->head;
	char *javaclassname = (char *) calloc(strlen(classname) + 6 /* .java\0 */, sizeof(char));
	char *jcn = javaclassname;
	strcpy(javaclassname, classname);
	strcat(javaclassname, ".java");
	for(i = 0; i < strlen(javaclassname); i++)
		if(javaclassname[strlen(javaclassname) - i] == '/'){
			jcn = javaclassname + strlen(javaclassname) - i + 1;
			break;
		}
	Attributes att;
	for(i = 0; i < marea->count; i++, iter = iter->next){
		ClassFile *class = (ClassFile *) iter->value;
		attribute_info *att_info = class->attributes;
		get_attribute_from_info(att_info[0].info, &att, att_info[0].attribute_name_index, class);
		char *curr_name = (char *) calloc(class->constant_pool[att.SourceFile.sourcefile_index - 1].info->Utf8.length + 1, sizeof(char));
		memcpy(curr_name, class->constant_pool[att.SourceFile.sourcefile_index - 1].info->Utf8.bytes, class->constant_pool[att.SourceFile.sourcefile_index - 1].info->Utf8.length);
		if(!strcmp(curr_name, jcn)){
			free(curr_name);
			ret_class = class;
			break;
		}
		free(curr_name);
	}
	free(javaclassname);
	return ret_class;

}
