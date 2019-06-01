#include "../include/bread_classfile.h"

#define JAVAVERSION 0x34

extern int verbose;
extern char *nomearq;

ClassFile * bread_classfile(FILE *classfile){

	ClassFile *class = (ClassFile *) calloc(1, sizeof(ClassFile));
	if(verbose) printf("Alloc'd memory for ClassFile\n");

		/* Magic number */
	if(bread_magic(class, classfile)){
		free(class);
		free(classfile);
		fprintf(stderr, "Invalid .class file. Magic number \"0xcafebabe\" does not check.\n");
		exit(ERR_MAGIC);
	}
	if(verbose) printf("Read magic number\n");

		/* Minor and major versions */
	if(bread_minor(class, classfile) > JAVAVERSION){
		fprintf(stderr, "Minor version superior to Java SE (0x%02x)\n", JAVAVERSION);
		fprintf(stderr, "\'y\': continue anyways\nany other key: stop\n");
		if(getchar() != 'y'){
			free(classfile);
			free(class);
			exit(ERR_MINOR);
		}
	}
	if(verbose) printf("Read minor version\n");
	if(bread_major(class, classfile) < JAVAVERSION){
		fprintf(stderr, "Major version inferior to Java SE (0x%02x)\n", JAVAVERSION);
		fprintf(stderr, "\'y\': continue anyways\nany other key: stop\n");
		if(getchar() != 'y'){
			free(classfile);
			free(class);
			exit(ERR_MAJOR);
		}
	}
	if(verbose) printf("Read major version\n");
		/* Constant pool count and constant pool */
	bread_constant_pool(class, classfile);
	if(verbose) printf("Read constant pool\n");
		/* Access flags, this class and super class */
	bread_access_flags(class, classfile);
	if(verbose) printf("Read access flags\n");
	bread_this_class(class, classfile);
	if(verbose) printf("Read this class\n");
	bread_super_class(class, classfile);
	if(verbose) printf("Read super class\n");
		/* Interfaces count and interfaces */
	bread_interfaces(class, classfile);
	if(verbose) printf("Read interfaces\n");
		/* Fields count and fields */
	bread_fields(class, classfile);
	if(verbose) printf("Read fields\n");
		/* Methods */
	bread_methods(class, classfile);
	if(verbose) printf("Read methods\n");
		/* Attributes */
	bread_attributes_count(class, classfile);
	if(verbose) printf("Read attributes count\n");
	bread_attributes(class->attributes, class->attributes_count, classfile);
	if(verbose) printf("Read attributes\n");

	int len = strlen(nomearq), ponto = 0, barra = 0;
	char *novo;
	for(int i = 0; i < len;  i++){
		if(nomearq[len - i] == '.'){
			ponto = 1;
			nomearq[len - i] = '\0';
		}
		if(!ponto){
			nomearq[len - i] = '\0';
		}
		if(nomearq[len - i] == '/' || nomearq[len - i] == '\\'){
			novo = nomearq + len - i + 1;
			break;
		}
	}
	strcat(novo, ".java");
	if(strcmp(novo, (char *) class->constant_pool[class->attributes[0].attribute_name_index].info->Utf8.bytes)){
		fprintf(stderr, "Source file name not equal\n");
		free(classfile);
		free(class);
		free(nomearq);
		exit(ERR_SRC);
	}
	free(nomearq);

	if(verbose) printf("Finished reading class\n");
	return class;
}
