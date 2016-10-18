// vmp_coprocessor.cpp : Defines the entry point for the console application.
//
/*
THAT_FUCKING_COMPILER (VMP)
*/

#include "stdafx.h"
#include "peephole_functions.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdint.h>
#include <sstream>
#include <exception>
#include <list>

//our exceptions
class vmregpush8 : public std::exception
{
	virtual const char* what() const throw()
	{
		return "A Register Push8 Happened!";
	}
} vm_regpush8;

class vmstackprint : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Messed up value to be printed from the stack!";
	}
} vm_stackprint;

//specifies the type of our stack
enum stack_type {
	arg,
	value,
	stack_pointer,
	unknown,
	expression
};

//this will be a 8-bit stack representative
class stack_node{
private:
	std::string Expression;
	stack_type tipo;
	uint8_t bitness;
	uint8_t content;
public:
	stack_node();
	void setType(stack_type type)
	{
		tipo = type;
	}
	stack_type getType() { return tipo; }
	void setExpression(std::string _Expression)
	{
		Expression = _Expression;
	}
	std::string getExpression() { return Expression; }
	void setBitness(uint8_t _bitness) { bitness = _bitness; }
	uint8_t getBitness() { return bitness; }
	void setContent(uint8_t _content ) { content = _content; }
	uint8_t getContent() {
		return content;
	}
	bool operator ==(stack_node& d)
	{
		if ((tipo == unknown) || (d.getType() == unknown))
		{
			return false;
		}
		return ((Expression == d.getExpression()) && (tipo == expression) && (d.getType() == expression)) ||
			((tipo == d.getType()) && (content == d.getContent()));

	}
};

stack_node::stack_node()
{
	Expression = "";
	tipo = arg;
	bitness = 0;
	content = 0;
}

//This class will represent the virtualMachine
// a vm must have a program
// -> must have a set of registers
// -> must be able to execute instructions
class VirtualMachine{
private:
	//registers
	stack_node r0[4];
	stack_node r1[4];
	stack_node r2[4];
	stack_node r3[4];
	stack_node r4[4];
	stack_node r5[4];
	stack_node r6[4];
	stack_node r7[4];
	stack_node r8[4];
	stack_node r9[4];
	stack_node ra[4];
	stack_node rb[4];
	stack_node rc[4];
	stack_node rd[4];
	stack_node re[4];
	stack_node rf[4];
	stack_node r10[4];
	stack_node r11[4];
	stack_node r12[4];
	stack_node r13[4];
	stack_node r14[4];
	//our stack
	std::vector<stack_node> stack;
	//our program
	std::list<bytecode> program;
	//stack functions
	void pushStack4Values(stack_node n1, stack_node n2, stack_node n3, stack_node n4)
	{
		stack.push_back(n1);
		stack.push_back(n2);
		stack.push_back(n3);
		stack.push_back(n4);
	}
	void setRegister4Values(stack_node reg[4], stack_node n1, stack_node n2, stack_node n3, stack_node n4)
	{
		reg[3] = n1;
		reg[2] = n2;
		reg[1] = n3;
		reg[0] = n4;
	}

	//Auxiliary Functions
	//Attempts to get a type
	//unk if type differ
	stack_type getType32(stack_node reg[4])
	{

	}

	//this should be able to print a register value
	std::string PrintStack32(stack_node reg[4])
	{
		if ((reg[0].getType() == unknown) || (reg[1].getType() == unknown) || ( reg[2].getType() == unknown) || (reg[3].getType() == unknown))
		{
			throw vm_stackprint;
		}
		if (~((reg[0].getType() == reg[1].getType()) && (reg[1].getType() == reg[2].getType()) && (reg[3].getType() == reg[4].getType())) == true)
		{
			throw vm_stackprint;
		}
		stack_type ntype = reg[0].getType();
		if (ntype == arg)
		{
			char number[50];
			memset(number, 0, 50);
			itoa(reg[0].getContent(), number, 10);
			return "arg_32(" + std::string(number) + ")";
		}
		if (ntype == value)
		{
			uint32_t value = (reg[0].getContent() << 24) | (reg[1].getContent() << 16) | (reg[2].getContent() << 8) | (reg[3].getContent() << 0);
			char number[50];
			memset(number, 0, 50);
			itoa(value, number, 16);
			return "0x" + std::string(number);
		}

		if (ntype == stack_pointer)
		{
			char number[50];
			memset(number, 0, 50);
			itoa(reg[0].getContent(), number, 10);
			return "STACK@" + std::string(number);
		}

		if (ntype == expression)
		{
			return "expr_" + reg[0].getExpression();
		}

		return "FUCK_";
	}



	//Now we must implement the full instruction set.
	//we start with the PUSHes of integers
	void Push32(uint32_t _value)
	{
		stack_node v1;
		stack_node v2;
		stack_node v3;
		stack_node v4;
		v4.setBitness(32);
		v4.setContent(_value & 0xFF);
		v4.setType(value);

		v3.setBitness(32);
		v3.setContent((_value & 0xFF00)>>8);
		v3.setType(value);

		v2.setBitness(32);
		v2.setContent((_value & 0xFF0000) >> 16);
		v2.setType(value);

		v1.setBitness(32);
		v1.setContent((_value & 0xFF000000) >> 24);
		v1.setType(value);

		stack.push_back(v1);
		stack.push_back(v2);
		stack.push_back(v3);
		stack.push_back(v4);

	}

	void Push16(uint16_t _value)
	{
		stack_node v1;
		stack_node v2;
		v2.setBitness(32);
		v2.setContent(_value & 0xFF);
		v2.setType(value);

		v1.setBitness(32);
		v1.setContent((_value & 0xFF00) >> 8);
		v1.setType(value);

		stack.push_back(v1);
		stack.push_back(v2);
	}

	void Push8(uint8_t _value)
	{
		stack_node v1;
		v1.setBitness(32);
		v1.setContent(_value & 0xFF);
		v1.setType(value);
		stack.push_back(v1);
	}

	//implementation of PUSHes of registers

	void Push32(stack_node reg[4])
	{
		stack_node v1 = reg[0];
		stack_node v2 = reg[1];
		stack_node v3 = reg[2];
		stack_node v4 = reg[3];
		stack.push_back(v1);
		stack.push_back(v2);
		stack.push_back(v3);
		stack.push_back(v4);
	}
	void Push16(stack_node reg[4])
	{
		stack_node v1 = reg[2];
		stack_node v2 = reg[3];
		stack.push_back(v1);
		stack.push_back(v2);
	}
	
	//this one is tricky
	void Push8(stack_node reg[4])
	{
		stack_node v1 = reg[3];
		stack.push_back(v1);
		v1.setBitness(8);
		v1.setContent(0);
		v1.setType(value);
		stack.push_back(v1);

		throw vm_regpush8;
	}


	//Now we are addressing POP of registers
	void Pop32(stack_node reg[4])
	{
		reg[3] = stack.back();
		stack.pop_back();
		reg[2] = stack.back();
		stack.pop_back();
		reg[1] = stack.back();
		stack.pop_back();
		reg[0] = stack.back();
		stack.pop_back();
	}

	void Pop16(stack_node reg[4])
	{
		reg[3] = stack.back();
		stack.pop_back();
		reg[2] = stack.back();
		stack.pop_back();
	}

	void Pop8(stack_node reg[4])
	{
		reg[3] = stack.back();
		stack.pop_back();
	}

	//Arithmetic Operations
	//"ADD N2, N1", "", "MOV EAX, [EBP+0x0]", "ADD [EBP+0x4], EAX" 
	void ADD32()
	{

	}
public:
	VirtualMachine(std::list<bytecode> _program);
};

VirtualMachine::VirtualMachine(std::list<bytecode> _program)
{
	//internal copy of the program
	program = _program;
	//initialize the state of the stack with some values (function arguments):
	for (int i = 12; i >= 0; i--)
	{
		stack_node argument;
		argument.setType(arg);
		argument.setContent(i);
		argument.setBitness(32);
		pushStack4Values(argument, argument, argument, argument);
	}

	stack_node empty;
	empty.setBitness(0);
	empty.setContent(0);
	empty.setType(unknown);

	//Resets the state of all registers:
	setRegister4Values(r1, empty, empty, empty, empty);
	setRegister4Values(r2, empty, empty, empty, empty);
	setRegister4Values(r3, empty, empty, empty, empty);
	setRegister4Values(r4, empty, empty, empty, empty);
	setRegister4Values(r5, empty, empty, empty, empty);
	setRegister4Values(r6, empty, empty, empty, empty);
	setRegister4Values(r7, empty, empty, empty, empty);
	setRegister4Values(r8, empty, empty, empty, empty);
	setRegister4Values(r9, empty, empty, empty, empty);
	setRegister4Values(ra, empty, empty, empty, empty);
	setRegister4Values(rb, empty, empty, empty, empty);
	setRegister4Values(rc, empty, empty, empty, empty);
	setRegister4Values(rd, empty, empty, empty, empty);
	setRegister4Values(re, empty, empty, empty, empty);
	setRegister4Values(rf, empty, empty, empty, empty);
	setRegister4Values(r10, empty, empty, empty, empty);
	setRegister4Values(r11, empty, empty, empty, empty);
	setRegister4Values(r12, empty, empty, empty, empty);
	setRegister4Values(r13, empty, empty, empty, empty);
	setRegister4Values(r14, empty, empty, empty, empty);
}

int _tmain(int argc, _TCHAR* argv[])
{
//	std::ifstream dump_file ("C:/vmp_pwnkit/vmp_pwn_tools/devirtualization/VMPDBG_PROJ/VMPDBG_0_1_0_SRC/dump.txt");
	if (argc < 3)
	{
		std::cout << "vmp_coprocessor_module: invalid number of arguments" << std::endl;
		return 0;
	}

	std::cout << "\n[vmp coprocessor module]: input file (VMP bytecode)" << argv[1];
	std::cout << "\n[vmp coprocessor module]: output file (VMP bytcode)" << argv[2];
	std::ifstream file(argv[1]);
	std::ofstream dump_file(argv[2]);

	std::list<bytecode> program;
	std::string line = "";
	uint32_t original_size, new_size;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			bytecode new_bc(line);
			if (!new_bc.IsValid())
			{
				std::cout << "\n dude you totally have fucked up at " << line << std::endl;
				return 0;
			}
			program.push_back(new_bc);
		}
	}

	original_size = program.size();

	for (int swipes = 0; swipes < 10; swipes++)
	{

		for (std::list<bytecode>::iterator b_it = program.begin(); b_it != program.end();)
		{
			if (p33p_1(program, b_it))
			{
				continue;
			}
			else if (p33p_2(program, b_it))
			{
				continue;
			}
			else
			{
				++b_it;
			}
		}

		new_size = program.size();
		//print statisticsx:
		std::cout << "\n========================";
		std::cout << "\n swipe #" << swipes;
		std::cout << "\n your fancy optimization techniques have awarded you : \n";
		std::cout << "old size: " << std::dec << original_size << "\n";
		std::cout << "new size: " << std::dec << new_size << "\n";
		std::cout << "ratio (from the original code): " << ((float)new_size / (float)original_size) * 100 << "%";
	}
	print_code(program, dump_file);
	dump_file.close();
	printf("Press Any Key to Continue\n");
	getchar();
	return 0;
}

