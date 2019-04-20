# Bytecode reader and printer
## breader

### Description:
Reads a .class file and prints it's structure as described in Oracle's official Java Virtual Machine Specification (docs.oracle.com)

### Compile: (only tested in Ubuntu 18.04)
	$ cd test/
	$ make

### Run:
	$ ./breader <class file name>

test/class has two simple .class files for testing

## TODO:
* Translate Bytecode to 'Java assembly'
* Print correctly non-ASCII Utf8 characters
* Documentation
