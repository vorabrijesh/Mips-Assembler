Mips Assembler
==============

An assembler for a subset of the MIPS instruction set.

# How to use
The assembler will take a file written in assembly language as input on the command line and will produce an output file containing the MIPS machine code. Each line in the input assembly file contains either a mnemonic, a section header (such as .data or .text) or a label (jump or branch target.

The assembler supports the following 46 instruction set:

- "lw"
- "lb"
- "sw"
- "sb" 
- "add"
- "addu"
- "sub"
- "subu"
- "slt"
- "sltu"
- "and"
- "or"
- "xor"
- "nor"
- "sll"
- "srl",
- "sra"
- "mult"
- "multu"
- "div"
- "divu"
- "addi"
- "addiu"
- "andi"
- "ori"
- "xori"
- "lui"
- "slti"
- "beq"
- "bne"
- "blez"
- "bgtz"
- "bltz"
- "bgez"
- "j"
- "jal"
- "jalr"
- "jr"
- "mfhi"
- "mflo" 
- "syscall",
- "la"
- "move"
- "li"
- "nop"
- "sltiu"

# Compile and Run
	Complile :
	$ g++ assembler.cpp -o assembler

    After compiling, run:
    $ ./assembler test.asm test.o log.txt
