# Bytecode viewer and interpreter

## breader

![Java 8 Logo](./.javasrc/javalogo.jpg "Java Logo")

### Description

Reads .class files and let you choose to prints it's structure as described in Oracle's official [Java Virtual Machine Specification](https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html "Documentation") or interpret it's instrunctions as JVM 8 does (mais ou menos ne)

### Compile: (tested in Ubuntu 18.04 and Windows 10)

>$ cd test/
>
>$ make

### Run

>$ ./breader.out <\mode> <\path> <\file> [<\options>]*

## TODO

- [x] Print correctly non-ASCII Utf8 characters
- [X] Documentation
- [x] Print constant pool value using opcode argument as index if needed
- [x] Print jump destination on jump opcodes printing
- [x] Fix consistency
- [x] Clean output
- [ ] Refactor code
- [x] Pass command line arguments (path, main and mode at least)
- [ ] Implement java bytecode instructions
- [x] Frame stack
- [x] Method area
- [x] Fix string
- [x] Fix float printing in viewer mode
- [x] Fix iinc printing in viewer mode

## Authors

- Vinicius Toshiyuki Menezes Sugimoto - 17/0023664

- Henrique Mendes de Freitas Mariano - 17/0012280
