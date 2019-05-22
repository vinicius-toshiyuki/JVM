SRC= ../src

CFILES= $(SRC)/bread_constant_pool.c $(SRC)/bread_magic.c $(SRC)/bread_versions.c $(SRC)/bread_interfaces.c $(SRC)/main.c $(SRC)/bread_fields.c $(SRC)/bread_attributes.c $(SRC)/bread_methods.c $(SRC)/bread_classfile.c $(SRC)/bprint_classfile.c $(SRC)/bfree_classfile.c $(SRC)/mnemonic.c $(SRC)/stack.c

OFILES= ./main.o ./bread_constant_pool.o ./bread_magic.o ./bread_versions.o ./bread_interfaces.o ./bread_fields.o ./bread_attributes.o ./bread_methods.o ./bread_classfile.o ./bprint_classfile.o ./bfree_classfile.o ./mnemonic.o ./stack.o

FLAGS= -g -std=c99

NAME= breader

all: objects main clean

objects: $(CFILES)
	gcc -c $(CFILES) $(FLAGS)

main: $(OFILES)
	gcc -o ./$(NAME) $(OFILES) $(FLAGS)

clean:
ifeq ($(OS), Windows_NT)
	del *.o
else
	rm $(OFILES)
	rm *.o
endif
