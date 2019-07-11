#include "../include/engine.h"
#include "../include/classfile.h"
#include "../include/bread_classfile.h"
#include "../include/attributes.h"
#include "../include/bytecode.h"
#include "../include/errcodes.h"
#include "../include/utils.h"
#include <stdio.h>
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
    u1 **pc = &frame->pc;
    do bytecode_handlers[(*pc)[0]](pc, method->code, frame, jvm);
    while((*pc)++ != NULL);
}
void store_arguments(frame_t *frame, frame_t *old_frame, char *arguments){
    int i;
    for(i = 0; i < strlen(arguments); i++){
        switch(arguments[i]){
            case '[':
                printv("Passing array ref !\n");
            case 'B':
            case 'C':
            case 'F':
            case 'I':
            case 'S':
            case 'Z':;
                u4 *value = (u4 *) cpop(old_frame->operands_stack);
                printf("%04x\n", *value);
                cappend(frame->local_variables, value);
                break;
            case 'L':
                while(arguments[i++] != ';');
                cappend(frame->local_variables, cpop(old_frame->operands_stack));
                break;
            case 'J':
            case 'D':;
                void *low = cpop(old_frame->operands_stack);
                cappend(frame->local_variables, cpop(old_frame->operands_stack));
                cappend(frame->local_variables, low);
                break;
            case '(':
                break;
            case ')':
                i = strlen(arguments);
                break;
            default:
                fprintf(stderr, "Invalide arg type descriptor (%c)\n", arguments[i]);
                exit(ERR_UNKTYPE);
        }
    }
}