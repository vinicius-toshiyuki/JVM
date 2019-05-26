# Bytecode reader and printer
## breader

![Java 8 Logo](./.javasrc/javalogo.jpg "Java Logo")

### Description:
Reads a .class file and prints it's structure as described in Oracle's official [Java Virtual Machine Specification](https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html "Documentation")

### Compile: (only tested in Ubuntu 18.04)
	$ cd test/
	$ make

### Run:
	$ ./breader <class file name>

## TODO:
- [x] Print correctly non-ASCII Utf8 characters
- [ ] Documentation
- [x] Print constant pool value using opcode argument as index if needed
- [x] Print jump destination on jump opcodes printing
