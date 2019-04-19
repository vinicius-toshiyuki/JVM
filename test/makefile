SRC= ../src
OBJ2= *.o
NAME= breader

all: objects main clean

objects: $(SRC)/bread_constant_pool.c $(SRC)/bread_magic.c $(SRC)/bread_versions.c $(SRC)/main.c
	gcc -c $(SRC)/bread_constant_pool.c $(SRC)/bread_magic.c $(SRC)/bread_versions.c $(SRC)/main.c

main: $(SRC)/bread_constant_pool.o $(SRC)/bread_magic.o $(SRC)/bread_versions.o $(SRC)/main.o
	gcc -o ./$(NAME) $(SRC)/main.o $(SRC)/bread_constant_pool.o $(SRC)/bread_magic.o $(SRC)/bread_versions.o

clean:
	rm $(SRC)/bread_constant_pool.o $(SRC)/bread_magic.o $(SRC)/bread_versions.o $(SRC)/main.o
	rm bread_constant_pool.o bread_magic.o bread_versions.o main.o
