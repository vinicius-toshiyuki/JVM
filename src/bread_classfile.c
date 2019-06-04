#include "../include/bread_classfile.h"

#define JAVAVERSION 0x34

extern int VERBOSE;
extern char *CLASSFILE;
extern char *java_version[];

ClassFile * bread_classfile(FILE *classfile){

	ClassFile *class = (ClassFile *) calloc(1, sizeof(ClassFile));
	if(VERBOSE) printf("Alloc'd memory for ClassFile\n");

		/* Magic number */
	if(bread_magic(class, classfile)){
		free(class);
		fclose(classfile);
		fprintf(stderr, "Invalid .class file. Magic number \"0xcafebabe\" does not check.\n");
		exit(ERR_MAGIC);
	}
	if(VERBOSE) printf("Read magic number\n");

		/* Minor and major versions */
	if(bread_minor(class, classfile) > JAVAVERSION){
		fprintf(stderr, "Minor version superior to %s\n", java_version[JAVAVERSION]);
		fprintf(stderr, "\'y\': continue anyways\nany other key: stop\n");
		setbuf(stdin, NULL);
		if(getchar() != 'y'){
			fclose(classfile);
			free(class);
			exit(ERR_MINOR);
		}
	}
	if(VERBOSE) printf("Read minor version\n");
	if(bread_major(class, classfile) < JAVAVERSION){
		fprintf(stderr, "Major version inferior to %s\n", java_version[JAVAVERSION]);
		fprintf(stderr, "\'y\': continue anyways\nany other key: stop\n");
		setbuf(stdin, NULL);
		if(getchar() != 'y'){
			fclose(classfile);
			free(class);
			exit(ERR_MAJOR);
		}
	}
	if(VERBOSE) printf("Read major version\n");
		/* Constant pool count and constant pool */
	bread_constant_pool(class, classfile);
	if(VERBOSE) printf("Read constant pool\n");
		/* Access flags, this class and super class */
	bread_access_flags(class, classfile);
	if(VERBOSE) printf("Read access flags\n");
	bread_this_class(class, classfile);
	if(VERBOSE) printf("Read this class\n");
	bread_super_class(class, classfile);
	if(VERBOSE) printf("Read super class\n");
		/* Interfaces count and interfaces */
	bread_interfaces(class, classfile);
	if(VERBOSE) printf("Read interfaces\n");
		/* Fields count and fields */
	bread_fields(class, classfile);
	if(VERBOSE) printf("Read fields\n");
		/* Methods */
	bread_methods(class, classfile);
	if(VERBOSE) printf("Read methods\n");
		/* Attributes */
	bread_attributes_count(class, classfile);
	if(VERBOSE) printf("Read attributes count\n");
	bread_attributes(class->attributes, class->attributes_count, classfile);
	if(VERBOSE) printf("Read attributes\n");

	int len = strlen(CLASSFILE);
	char *novo;
	/* ./class/novo = {double_aritimetica}\0class */
	for(int i = 0; i < len;  i++){
		if(CLASSFILE[len - i] == '.'){
			CLASSFILE[len - i] = '\0';
		}
		if(CLASSFILE[len - i] == '/' || CLASSFILE[len - i] == '\\'){
			novo = CLASSFILE + len - i + 1;
			break;
		}
	}
	strcat(novo, ".java");
	if(strcmp(novo, (char *) class->constant_pool[class->attributes[0].attribute_name_index].info->Utf8.bytes)){
		fprintf(stderr, "Source file name not equal\n");
		fclose(classfile);
		free(class);
		free(CLASSFILE);
		exit(ERR_SRC);
	}
	free(CLASSFILE);

	if(VERBOSE) printf("Finished reading class\n");
	return class;
}
