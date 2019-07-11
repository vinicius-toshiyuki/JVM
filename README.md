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

>$ ./breader.out (class file name)

## TODO

- [x] Print correctly non-ASCII Utf8 characters
- [ ] Documentation
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

## Nota

### Corretude do interpretador **

Resumo: 100

1.() array simples
2.(X) arrays.length
3.() arrays multidimensionais
4.(X) arrays de referencia
5.(X) doubles - dastore, daload
6.(X) floats - fastore, faload
7.(X) longs - lastore, laload
8.(X) inteiros - falta iastore, iaload
9.(X) shorts
10.(X) strings -certo no viewer falta passar pro interpretador
11.(X) desvios com cat 1
12.(X) operacoes logicas com cat 1  
13.() operacoes de deslocamento com cat 1
14.(X) operacoes aritmeticas de cat 2
15.() operacoes de deslocamento de longs
16.(X) system.out.println (int, float, string e booleano)
17.(X) conversao de e para cat 2
18.() iteracao
19.() switches
20.() fields
21.() interfaces
22.() recursao
23.(X) metodos estaticos
24.() metodos nao estaticos
25.(X) objetos
26.() operacoes de retorno
27.() operacoes de manipulacao de pilha
28.(X) consistencia
29.() exceptions
30.(X) invokes - invokestatic e invokevirtual feitos
31.() polimofismo e reescrita

-------------------------

Resumo: 100

-- leitura do formato ponto class:

- Trata versões superiores? Sim
- Despreza silenciosamente atributos não tratados? Sim
- Consistência? Consistente
- Corretude? Correto
- Exibe mnemônicos? Sim
- Apresenta reindireção das entradas no Constant Pool? Apresenta

Bonus: 10% (bonus sobre a corretude do interpretador)

--  opcionais
Todas as demais instruções.

( ) threads
( ) debug
( ) chamadas às bibliotecas do Java
( ) checagem dinâmica de tipos
( ) coletor de lixo.

-------------------------

Atribuição de nota para a JVM
0,1*leitor_exibidor + 0,4*corretude + 0,4*defesa do interpretador + 0,1*site

Site: 100

- Apresenta o DCM e a descrição de cada função?
- Contem a relação das estruturas de dados e os arquivos?
- Está atualizado?
- Corretude?

## Authors

- Vinicius Toshiyuki Menezes Sugimoto - 17/0023664

- Henrique Mendes de Freitas Mariano - 17/0012280
