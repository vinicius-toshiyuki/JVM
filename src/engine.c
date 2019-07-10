#include "../include/engine.h"
#include "../include/classfile.h"
#include "../include/bread_classfile.h"
#include "../include/attributes.h"
#include "../include/bytecode.h"
#include <string.h>

Method get_method_by_name(ClassFile *class, char *name){
    int mc = class->methods_count, i, j;
    for(i = 0; i < mc; i++)
        if(!strcmp(name, (const char *) class->constant_pool[class->methods[i].name_index - 1].info->Utf8.bytes))
            break;
    
    int ac = class->methods[i].attributes_count;
    for(j = 0; j < ac; j++)
        if(!strcmp("Code", (const char *) class->constant_pool[class->methods[i].attributes[j].attribute_name_index - 1].info->Utf8.bytes))
            break;
    
    Attributes codeatt;
    get_attribute_from_info(
        class->methods[i].attributes[j].info,
        &codeatt,
        class->methods[i].attributes[j].attribute_name_index,
        class
        );
    return (Method) {
        codeatt.Code.code_length,
        codeatt.Code.code
    };
}

extern handler bytecode_handlers[];
void run_method(frame_t *frame, Method *method, jvm_t *jvm){
    u1 **pc = &method->code;
    u2 i;
    for(i = 0; i < method->length; i++, (*pc)++)
        bytecode_handlers[(*pc)[0]](pc, method->code, frame, jvm);
    return;
}
