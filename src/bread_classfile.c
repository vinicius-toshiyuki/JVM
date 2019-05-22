#include "../include/bread_classfile.h"

extern int verbose;

ClassFile * bread_classfile(FILE *classfile){

	ClassFile *class = (ClassFile *) calloc(1, sizeof(ClassFile));
	if(verbose) printf("Alloc'd memory for ClassFile\n");

		/* Magic number */
	if(bread_magic(class, classfile)){
		free(class);
		fprintf(stderr, "Invalid .class file. Magic number \"0xcafebabe\" does not check.\n");
		exit(ERR_MAGIC);
	}
	if(verbose) printf("Read magic number\n");

		/* Minor and major versions */
	bread_minor(class, classfile);
	if(verbose) printf("Read minor version\n");
	bread_major(class, classfile);
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

	if(verbose) printf("Finished reading class\n");
	return class;
}
