/*
  u2_read(class->const_pool_count, classfile);
  printf(
    "Magic: 0x%x\n"
    "Minor: 0x%x\n"
    "Major: 0x%x\n"
    "CPC: %d\n",
    class->magic,
    class->minor_version,
    class->major_version,
    class->const_pool_count
  );



  class->constant_pool = (cp_info *) malloc(sizeof(cp_info) * (class->const_pool_count - 1));
  //return 0;
  int i;
  for(i = 0; i < class->const_pool_count - 1; i++){
    cp_info *cp = &(class->constant_pool[i]);
    u1_read(cp->tag, classfile);
    printf("\e[48;5;221mTag %d: %d\e[0m\n", i + 1, cp->tag);
    switch(cp->tag){
      case CONSTANT_Class:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Class.tag, classfile);
        u2_read(cp->info->Class.name_index, classfile);
        printf(
            "\tName index: %d\n",
            cp->info->Class.name_index
        );
        break;
      case CONSTANT_Fieldref:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Fieldref.tag, classfile);
        u2_read(cp->info->Fieldref.class_index, classfile);
        u2_read(cp->info->Fieldref.name_and_type_index, classfile);
        printf(
            "\tClass index: %d\n"
            "\tName and type index: %d\n",
            cp->info->Fieldref.class_index,
            cp->info->Fieldref.name_and_type_index
        );
        break;
      case CONSTANT_Methodref:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Methodref.tag, classfile);
        u2_read(cp->info->Methodref.class_index, classfile);
        u2_read(cp->info->Methodref.name_and_type_index, classfile);
        printf(
            "\tTag: %d\n"
            "\tClass index: %d\n"
            "\tName and type index: %d\n",
            cp->info->Methodref.tag,
            cp->info->Methodref.class_index,
            cp->info->Methodref.name_and_type_index
        );
        break;
      case CONSTANT_InterfaceMethodref:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->InterfaceMethodref.tag, classfile);
        u2_read(cp->info->InterfaceMethodref.class_index, classfile);
        u2_read(cp->info->InterfaceMethodref.name_and_type_index, classfile);
        printf(
            "\tClass index: %d\n"
            "\tName and type index: %d\n",
            cp->info->InterfaceMethodref.class_index,
            cp->info->InterfaceMethodref.name_and_type_index
        );
        break;
      case CONSTANT_String:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->String.tag, classfile);
        u2_read(cp->info->String.string_index, classfile);
        printf(
            "\tString index: %d\n",
            cp->info->String.string_index
        );
        break;
      case CONSTANT_Integer:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Integer.tag, classfile);
        u4_read(cp->info->Integer.bytes, classfile);
        printf(
            "\tBytes: %d\n",
            cp->info->Integer.bytes
        );
        break;
      case CONSTANT_Float:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Float.tag, classfile);
        u4_read(cp->info->Float.bytes, classfile);
        printf(
            "\tBytes: %f\n",
            (float) cp->info->Float.bytes
        );
        break;
      case CONSTANT_Long:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Long.tag, classfile);
        u4_read(cp->info->Long.high_bytes, classfile);
        u4_read(cp->info->Long.low_bytes, classfile);
        printf(
            "\tHigh bytes: 0x%x\n"
            "\tLow bytes: 0x%x\n",
            cp->info->Long.high_bytes,
            cp->info->Long.low_bytes
        );
        break;
      case CONSTANT_Double:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Double.tag, classfile);
        u4_read(cp->info->Double.high_bytes, classfile);
        u4_read(cp->info->Double.low_bytes, classfile);
        printf(
            "\tHigh bytes: 0x%x\n"
            "\tLow bytes: 0x%x\n",
            cp->info->Double.high_bytes,
            cp->info->Double.low_bytes
        );
        break;
      case CONSTANT_NameAndType:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->NameAndType.tag, classfile);
        u2_read(cp->info->NameAndType.name_index, classfile);
        u2_read(cp->info->NameAndType.descriptor_index, classfile);
        printf(
            "\tName index: %d\n"
            "\tDescriptor index: %d\n",
            cp->info->NameAndType.name_index,
            cp->info->NameAndType.descriptor_index
        );
        break;
      case CONSTANT_Utf8:
        cp->info = (info_t *) malloc(sizeof(info_t));
        //u1_read(cp->info->Utf8.tag, classfile);
        u2_read(cp->info->Utf8.length, classfile);
        printf("\tLength: %d\n\tBytes: \"", cp->info->Utf8.length);
        cp->info->Utf8.bytes = (u1 *) malloc(sizeof(u1) * cp->info->Utf8.length);
        int i;
        for(i = 0; i < cp->info->Utf8.length; i++){
          u1_read(cp->info->Utf8.bytes[i], classfile);
          printf("%c", cp->info->Utf8.bytes[i]);
        }
        //printf("%ls", (wchar_t *) cp->info->Utf8.bytes);
        printf("\"\n");
        break;
      }
  }*/
/*
printf(
      "Access flags: 0x%x\n"
      "This class: %d\n"
      "Super class: %d\n"
      "Interfaces count: %d\n",
      class->access_flags,
      class->this_class,
      class->super_class,
      class->interfaces_count
  );*/
/*
  for(i = 0; i < class->interfaces_count; i++){
    u2_read(class->interfaces[i], classfile);
    printf(
        "\e[48;5;189mInterface %d:\n"
        "\tClass index: %d\n",
        i, class->interfaces[i]
    );
  }*/
