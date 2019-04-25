#include <bits/stdc++.h>

using namespace std;

//print in hex format
void printhex(int x, ofstream &file)
{
	if(x == 0)
	{
		file << "0x00000000" << " ";
		return;
	}

	file << showbase
		 << internal
		 << setfill('0');

	file << hex << setw(10) << x << " ";
}

// convert decimal to binary
string decToBinary(int n) 
{ 
	string str = "";

    // Size of an integer is assumed to be 32 bits 
    for (int i = 31; i >= 0; i--) 
    { 
        int k = n >> i; 
        if (k & 1) 
            str += "1"; 
        else
            str += "0";
    } 

    int j = 0;
    for(int i = 0; i < str.size(); i++)
    {
    	if(str[i] == '1')
    		break;
    	else j++;
    }

    string result = "";
    for(int i = j; i < str.size(); i++)
    {
    	result += str[i];
    }

    return result;
}

// set of all instructions
set<string> instruction = {
    "lw", "lb", "sw", "sb",  "add", "addu",
    "sub", "subu", "slt", "sltu", "and", "or", "xor", "nor", "sll", "srl",
    "sra", "mult", "multu", "div", "divu", "addi", "addiu", "andi", "ori", "xori",
    "lui", "slti",  "beq", "bne", "blez", "bgtz", "bltz", "bgez", "j",
    "jal", "jalr", "jr", "mfhi", "mflo", 
     "syscall", "la", "move", "li", "nop", "sltiu"
	};

// map of instructions with the type of syntax of operands
map<string, int >  instr_type = {
	pair<string,int>  ("lw",5),
	pair<string,int>  ("lb",5),
	pair<string,int>  ("sw",5),
	pair<string,int>  ("sb",5),
	pair<string,int>  ("add",2),
	pair<string,int>  ("addu",2),
	pair<string,int>  ("sub",2),
	pair<string,int>  ("subu",2),
	pair<string,int>  ("slt",2),
	pair<string,int>  ("sltu",2),
	pair<string,int>  ("and",2),
	pair<string,int>  ("or",2),
	pair<string,int>  ("xor",2),
	pair<string,int>  ("nor",2),
	pair<string,int>  ("sll",3),
	pair<string,int>  ("srl",3),
	pair<string,int>  ("sra",3),
	pair<string,int>  ("mult",4),
	pair<string,int>  ("multu",4),
	pair<string,int>  ("div",4),
	pair<string,int>  ("divu",4),
	pair<string,int>  ("addi",3),
	pair<string,int>  ("addiu",3),
	pair<string,int>  ("andi",3),
	pair<string,int>  ("ori",3),
	pair<string,int>  ("xori",3),
	pair<string,int>  ("lui",6),
	pair<string,int>  ("slti",3),
	pair<string,int>  ("beq",9),
	pair<string,int>  ("bne",9),
	pair<string,int>  ("blez",7),
	pair<string,int>  ("bgtz",7),
	pair<string,int>  ("bltz",7),
	pair<string,int>  ("bgez",7),
	pair<string,int>  ("j",10),
	pair<string,int>  ("jal",10),
	pair<string,int>  ("jalr",8),
	pair<string,int>  ("jr",8),
	pair<string,int>  ("mfhi",8),
	pair<string,int>  ("mflo",8),
	pair<string,int>  ("syscall",1),
	pair<string,int>  ("la",7),
	pair<string,int>  ("move",4),
	pair<string,int>  ("li",6),
	pair<string,int>  ("nop",1),
	pair<string,int>  ("sltiu",3)
};

//map of register and operations with binary code
map<string, string> type2_op = {
	pair<string, string>  ("add","100000"),
	pair<string, string>  ("addu","100001"),
	pair<string, string>  ("sub","100010"),
	pair<string, string>  ("subu","100011"),
	pair<string, string>  ("slt","101010"),
	pair<string, string>  ("sltu","101011"),
	pair<string, string>  ("and","100100"),
	pair<string, string>  ("or","100101"),
	pair<string, string>  ("xor","100110"),
	pair<string, string>  ("nor","100111")
};

map<string, string> type3_op1 = {
	pair<string, string>  ("addi","001000"),
	pair<string, string>  ("addiu","001001"),
	pair<string, string>  ("andi","001100"),
	pair<string, string>  ("ori","001101"),
	pair<string, string>  ("xori","001110"),
	pair<string, string>  ("slti","001010"),
	pair<string, string>  ("sltiu","001011")
	};

map<string, string> type3_op2 = {
	pair<string, string>  ("sll","000000"),
	pair<string, string>  ("srl","000010"),
	pair<string, string>  ("sra","000011")
};

map <string, string > type4_op = {
	pair<string, string>  ("mult","011000"),
	pair<string, string>  ("multu","011001"),
	pair<string, string>  ("div","011010"),
	pair<string, string>  ("divu","011011")
};

map <string, string > type5_op = {
	pair<string, string>  ("lb","100000"),
	pair<string, string>  ("lw","100011"),
	pair<string, string>  ("sw","101011"),
	pair<string, string>  ("sb","101000")
};

map<string, string > type7_op = {
	pair<string, string>  ("blez","000110"),
	pair<string, string>  ("bgtz","000111"),
	pair<string, string>  ("bltz","000001"),
	pair<string, string>  ("bgez","000001")
};

map<string, string> reg_op = {
	 pair<string,string>  ("$s0","10000"),
 	 pair<string,string>  ("$s1","10001"),
	 pair<string,string>  ("$s2","10010"),
	 pair<string,string>  ("$s3","10011"),
	 pair<string,string>  ("$s4","10100"),
	 pair<string,string>  ("$s5","10101"),
	 pair<string,string>  ("$s6","10110"),
	 pair<string,string>  ("$s7","10111"),
	 pair<string,string>  ("$zero","00000"),
	 pair<string,string>  ("$t0","01000"),
	 pair<string,string>  ("$t1","01001"),
	 pair<string,string>  ("$t2","01010"),
	 pair<string,string>  ("$t3","01011"),
	 pair<string,string>  ("$t4","01100"),
	 pair<string,string>  ("$t5","01101"),
	 pair<string,string>  ("$t6","01110"),
	 pair<string,string>  ("$t7","01111"),
	 pair<string,string>  ("$t8","11000"),
	 pair<string,string>  ("$t9","11001"),
	 pair<string,string>  ("$a0","00100"),
	 pair<string,string>  ("$a1","00101"),
	 pair<string,string>  ("$a2","00110"),
	 pair<string,string>  ("$a3","00111"),
	 pair<string,string>  ("$v0","00010"),
	 pair<string,string>  ("$v1","00011"),
	 pair<string,string>  ("$at","00001"),
	 pair<string,string>  ("$k0","11010"),
	 pair<string,string>  ("$k1","11011"),
	 pair<string,string>  ("$gp","11100"),
	 pair<string,string>  ("$sp","11101"),
	 pair<string,string>  ("$s8","11110"),
	 pair<string,string>  ("$ra","11111"),
	 pair<string,string>  ("$16","10000"),
 	 pair<string,string>  ("$17","10001"),
	 pair<string,string>  ("$18","10010"),
	 pair<string,string>  ("$19","10011"),
	 pair<string,string>  ("$20","10100"),
	 pair<string,string>  ("$21","10101"),
	 pair<string,string>  ("$22","10110"),
	 pair<string,string>  ("$23","10111"),
	 pair<string,string>  ("$0","00000"),
	 pair<string,string>  ("$8","01000"),
	 pair<string,string>  ("$9","01001"),
	 pair<string,string>  ("$10","01010"),
	 pair<string,string>  ("$11","01011"),
	 pair<string,string>  ("$12","01100"),
	 pair<string,string>  ("$13","01101"),
	 pair<string,string>  ("$14","01110"),
	 pair<string,string>  ("$15","01111"),
	 pair<string,string>  ("$24","11000"),
	 pair<string,string>  ("$25","11001"),
	 pair<string,string>  ("$4","00100"),
	 pair<string,string>  ("$5","00101"),
	 pair<string,string>  ("$6","00110"),
	 pair<string,string>  ("$7","00111"),
	 pair<string,string>  ("$2","00010"),
	 pair<string,string>  ("$3","00011"),
	 pair<string,string>  ("$1","00001"),
	 pair<string,string>  ("$26","11010"),
	 pair<string,string>  ("$27","11011"),
	 pair<string,string>  ("$28","11100"),
	 pair<string,string>  ("$29","11101"),
	 pair<string,string>  ("$30","11110"),
	 pair<string,string>  ("$31","11111"),

};

// set of registers
set<string> registers = {
	"$zero",
	"$at",
	"$v0",
	"$v1",
	"$a0",
	"$a1",
	"$a2",
	"$a3",
	"$t0",
	"$t1",
	"$t2",
	"$t3",
	"$t4",
	"$t5",
	"$t6",
	"$t7",
	"$s0",
	"$s1",
	"$s2",
	"$s3",
	"$s4",
	"$s5",
	"$s6",
	"$s7",
	"$t8",
	"$t9",
	"$k0",
	"$k1",
	"$gp",
	"$sp",
	"$s8",
	"$ra",
	"$0",
	"$1",
	"$2",
	"$3",
	"$4",
	"$5",
	"$6",
	"$7",
	"$8",
	"$9",
	"$10",
	"$11",
	"$12",
	"$13",
	"$14",
	"$15",
	"$16",
	"$17",
	"$18",
	"$19",
	"$20",
	"$21",
	"$22",
	"$23",
	"$24",
	"$25",
	"$26",
	"$27",
	"$28",
	"$29",
	"$30",
	"$31"
};