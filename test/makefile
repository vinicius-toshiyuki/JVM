SRC= ../src

CFILES= $(SRC)/bread_constant_pool.c $(SRC)/bread_magic.c $(SRC)/bread_versions.c $(SRC)/bread_interfaces.c $(SRC)/main.c $(SRC)/bread_fields.c $(SRC)/bread_attributes.c $(SRC)/bread_methods.c $(SRC)/bread_classfile.c $(SRC)/bprint_classfile.c $(SRC)/bfree_classfile.c $(SRC)/mnemonic.c

OFILES= $(SRC)/main.o $(SRC)/bread_constant_pool.o $(SRC)/bread_magic.o $(SRC)/bread_versions.o $(SRC)/bread_interfaces.o $(SRC)/bread_fields.o $(SRC)/bread_attributes.o $(SRC)/bread_methods.o $(SRC)/bread_classfile.o $(SRC)/bprint_classfile.o $(SRC)/bfree_classfile.o $(SRC)/mnemonic.o

FLAGS= -g -std=c99

NAME= breader

all: objects main clean

objects: $(CFILES)
	gcc -c $(CFILES) $(FLAGS)

main: $(OFILES)
	gcc -o ./$(NAME) $(OFILES) $(FLAGS)

clean:
	rm $(OFILES)
	rm *.o
