#include <iostream>
#include <string>
#include <fstream>
#include <stdint.h>
#include <sstream>
#include <list>

/*
NODE REPRESENTATION for each bytecode
*/

class bytecode
{
public:
	enum operation{
		PUSH,
		POP,
		ADD,
		SUB,
		DIV,
		MOV,
		NOR,
		NAND,
		SHL,
		SHR,
		JMP,
		TIMESTAMP,
		DIVIDE,
		MUL,
		VM_OUT,
		UNKNOWN,
		VM_QUIT,
		FETCH
	};

	enum operand_mode
	{
		m64,
		m32,
		m16,
		m8
	};
	typedef struct
	{
		enum type {
			reg_scratch,
			reg_stack,
			none,
			value
		};
		enum data_reg_name
		{
			r0, r1, r2, r3, r4, r5, r6, r7, r8, r9,
			ra, rb, rc, rd, re, rf, r10, r11, r12,
			r13, r14, STACK, UNKD
		};
		enum stack_reg_name
		{
			n1, n2, n3, n1n2, UNKS
		};
		//The value (if it is a value)
		uint32_t value32;
		//The stack register name
		stack_reg_name rs_name;
		//The data register name
		data_reg_name rd_name;
		//The operand type
		type reg_type;
		//The access type: T-> is derreferencing data, F-> is the actual data
		bool memory_access;
	} operand;

private:
	int n_operands;
	operation b_operation;
	operand_mode b_op1;
	operand_mode b_op2;
	operand op1;
	operand op2;

	//opecode virtual offset
	uint32_t mem_address;

	//valid?
	bool valid;

	operand::data_reg_name doperand_to_type(std::string operand1)
	{
		if (operand1 == "R1")
		{
			return operand::data_reg_name::r1;
		}
		else if (operand1 == "R0")
		{
			return operand::data_reg_name::r0;
		}
		else if (operand1 == "R2")
		{
			return operand::data_reg_name::r2;
		}
		else if (operand1 == "R3")
		{
			return operand::data_reg_name::r3;
		}
		else if (operand1 == "R4")
		{
			return operand::data_reg_name::r4;
		}
		else if (operand1 == "R5")
		{
			return operand::data_reg_name::r5;
		}
		else if (operand1 == "R6")
		{
			return operand::data_reg_name::r6;
		}
		else if (operand1 == "R7")
		{
			return operand::data_reg_name::r7;
		}
		else if (operand1 == "R8")
		{
			return operand::data_reg_name::r8;
		}
		else if (operand1 == "R9")
		{
			return operand::data_reg_name::r9;
		}
		else if (operand1 == "Ra")
		{
			return operand::data_reg_name::ra;
		}
		else if (operand1 == "Rb")
		{
			return operand::data_reg_name::rb;
		}
		else if (operand1 == "Rc")
		{
			return operand::data_reg_name::rc;
		}
		else if (operand1 == "Rd")
		{
			return operand::data_reg_name::rd;
		}
		else if (operand1 == "Re")
		{
			return operand::data_reg_name::re;
		}
		else if (operand1 == "Rf")
		{
			return operand::data_reg_name::rf;
		}
		else if (operand1 == "R10")
		{
			return operand::data_reg_name::r10;
		}
		else if (operand1 == "R11")
		{
			return operand::data_reg_name::r11;
		}
		else if (operand1 == "R12")
		{
			return operand::data_reg_name::r12;
		}
		else if (operand1 == "R13")
		{
			return operand::data_reg_name::r13;
		}
		else if (operand1 == "R14")
		{
			return operand::data_reg_name::r14;
		}
		else if (operand1 == "STACK")
		{
			return operand::data_reg_name::STACK;
		}
		else if (operand1 == "r1")
		{
			return operand::data_reg_name::r1;
		}
		else if (operand1 == "r0")
		{
			return operand::data_reg_name::r0;
		}
		else if (operand1 == "r2")
		{
			return operand::data_reg_name::r2;
		}
		else if (operand1 == "r3")
		{
			return operand::data_reg_name::r3;
		}
		else if (operand1 == "r4")
		{
			return operand::data_reg_name::r4;
		}
		else if (operand1 == "r5")
		{
			return operand::data_reg_name::r5;
		}
		else if (operand1 == "r6")
		{
			return operand::data_reg_name::r6;
		}
		else if (operand1 == "r7")
		{
			return operand::data_reg_name::r7;
		}
		else if (operand1 == "r8")
		{
			return operand::data_reg_name::r8;
		}
		else if (operand1 == "r9")
		{
			return operand::data_reg_name::r9;
		}
		else if (operand1 == "ra")
		{
			return operand::data_reg_name::ra;
		}
		else if (operand1 == "rb")
		{
			return operand::data_reg_name::rb;
		}
		else if (operand1 == "rc")
		{
			return operand::data_reg_name::rc;
		}
		else if (operand1 == "rd")
		{
			return operand::data_reg_name::rd;
		}
		else if (operand1 == "re")
		{
			return operand::data_reg_name::re;
		}
		else if (operand1 == "rf")
		{
			return operand::data_reg_name::rf;
		}
		else if (operand1 == "r10")
		{
			return operand::data_reg_name::r10;
		}
		else if (operand1 == "r11")
		{
			return operand::data_reg_name::r11;
		}
		else if (operand1 == "r12")
		{
			return operand::data_reg_name::r12;
		}
		else if (operand1 == "r13")
		{
			return operand::data_reg_name::r13;
		}
		else if (operand1 == "r14")
		{
			return operand::data_reg_name::r14;
		}
		else if (operand1 == "STACK")
		{
			return operand::data_reg_name::STACK;
		}
		else
		{
			return operand::data_reg_name::UNKD;
		}

	}
	operand::stack_reg_name soperand_to_type(std::string operand1)
	{
		if (operand1 == "N1")
		{
			return operand::stack_reg_name::n1;
		}
		else if (operand1 == "N2")
		{
			return operand::stack_reg_name::n2;
		}
		else if (operand1 == "N3")
		{
			return operand::stack_reg_name::n3;
		}
		else
		{
			return operand::stack_reg_name::UNKS;
		}
	}
	bool IsNumeric(std::string operand1)
	{
		for (unsigned int i = 0; i < operand1.size(); i++)
		{
			//std::cout << operand1[i] << std::endl;
			if ((!((operand1[i] >= '0') && (operand1[i] <= '9'))) && (!((operand1[i] >= 'a') && (operand1[i] <= 'f'))))
			{
				return false;
			}
		}
		return true;
	}
public:
	bytecode();
	bytecode(std::string input);

	bool IsValid() { return valid; }
	void SetValid(bool v_alid) { valid = v_alid; }
	unsigned int NumberOfOperands() { return n_operands; }
	void SetNumberOfOperands(uint32_t n_ops) { n_operands = n_ops; }
	operation Operation() { return b_operation; }
	void SetOperation(bytecode::operation _new_op) { b_operation = _new_op; }
	operand_mode Operand1Mode() { return b_op1; }
	void SetOperand1Mode(operand_mode op_mode){ b_op1 = op_mode; }
	operand_mode Operand2Mode() { return b_op2; }
	void SetOperand2Mode(operand_mode op_mode){ b_op2 = op_mode; }
	uint32_t ByteCodeVA() { return mem_address; }
	void SetByteCodeVA(uint32_t new_va){ mem_address = new_va; }
	operand GetOperand1() { return op1; }
	void SetOperand1(operand _op1){ op1 = _op1; }
	operand GetOperand2() { return op2; }
	void SetOperand2(operand _op2){ op2 = _op2; }
};