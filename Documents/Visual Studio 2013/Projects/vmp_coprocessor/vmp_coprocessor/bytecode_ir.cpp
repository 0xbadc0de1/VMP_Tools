#include "bytecode_ir.h"



bytecode::bytecode()
{
	//assumes valid
	valid=true;
}

bytecode::bytecode(std::string input)
{
	valid = true;
	std::stringstream ss;
	std::string operand1 = "";
	std::string operand2 = "";
	std::size_t bgn = input.find("|");
	std::string operation = input.substr(bgn + 1);

	//get memory address
	if (!IsNumeric(input.substr(0, bgn)))
	{
		std::cout << "\n Not valid VA " << input.substr(0, bgn) << std::endl;
		valid = false;
		return;
	}
	ss << std::hex << input.substr(0, bgn);
	ss >> mem_address;


	if (operation.substr(0, 4) == "PUSH")
	{
		n_operands = 1;
		b_operation = PUSH;
		//PuSH operation
		if (operation.substr(0, 7) == "PUSH_32")
		{
			b_op1 = m32;
			operand1 = operation.substr(8);
			if (!IsNumeric(operand1))
			{
				op1.memory_access = false;
				op1.rd_name = doperand_to_type(operand1);
				if (op1.rd_name == operand::data_reg_name::UNKD)
				{
					op1.reg_type = operand::type::reg_stack;
					op1.rs_name = soperand_to_type(operand1);
					return;
				}
				else
				{
					op1.reg_type = operand::type::reg_scratch;
					return;
				}
			}
			else
			{
				op1.memory_access = false;
				op1.reg_type = operand::type::value;
				std::stringstream string_buffer;
				string_buffer << std::hex << operand1;
				string_buffer >> op1.value32;
				return;
			}

		}
		else if (operation.substr(0, 7) == "PUSH_16")
		{
			b_op1 = m16;
			operand1 = operation.substr(8);
			if (!IsNumeric(operand1))
			{
				op1.memory_access = false;
				op1.rd_name = doperand_to_type(operand1);
				if (op1.rd_name == operand::data_reg_name::UNKD)
				{
					op1.reg_type = operand::type::reg_stack;
					op1.rs_name = soperand_to_type(operand1);
					return;
				}
				else
				{
					op1.reg_type = operand::type::reg_scratch;
					return;
				}
			}
			else
			{
				op1.memory_access = false;
				op1.reg_type = operand::type::value;
				std::stringstream string_buffer;
				string_buffer << std::hex << operand1;
				string_buffer >> op1.value32;
				return;
			}
		}
		else if (operation.substr(0, 7) == "PUSH_8")
		{
			std::cout << "\nFUCKED UP: PUSH_8" << std::endl;
			valid = false;
			return;
		}
	}
	else if (operation == "TIME_STAMP")
	{
		n_operands = 0;
		b_operation = TIMESTAMP;
		op1.reg_type = operand::type::none;
		op2.reg_type = operand::type::none;
		return;
	}
	else if (operation.substr(0, 3) == "POP")
	{
		n_operands = 1;
		b_operation = POP;
		//Pop operation
		if (operation.substr(0, 6) == "POP_32")
		{
			b_op1 = m32;
			operand1 = operation.substr(7);
			if (!IsNumeric(operand1))
			{
				op1.memory_access = false;
				op1.rd_name = doperand_to_type(operand1);
				if (op1.rd_name == operand::data_reg_name::UNKD)
				{
					op1.reg_type = operand::type::reg_stack;
					op1.rs_name = soperand_to_type(operand1);
					return;
				}
				else
				{
					op1.reg_type = operand::type::reg_scratch;
					return;
				}
			}
			else
			{
				op1.memory_access = false;
				op1.reg_type = operand::type::value;
				std::stringstream string_buffer;
				string_buffer << std::hex << operand1;
				string_buffer >> op1.value32;
				return;
			}

		}
		else if (operation.substr(0, 6) == "POP_16")
		{
			b_op1 = m16;
			operand1 = operation.substr(7);
			if (!IsNumeric(operand1))
			{
				op1.memory_access = false;
				op1.rd_name = doperand_to_type(operand1);
				if (op1.rd_name == operand::data_reg_name::UNKD)
				{
					op1.reg_type = operand::type::reg_stack;
					op1.rs_name = soperand_to_type(operand1);
					return;
				}
				else
				{
					op1.reg_type = operand::type::reg_scratch;
					return;
				}
			}
			else
			{
				op1.memory_access = false;
				op1.reg_type = operand::type::value;
				std::stringstream string_buffer;
				string_buffer << std::hex << operand1;
				string_buffer >> op1.value32;
				return;
			}
		}
		else if (operation.substr(0, 5) == "POP_8")
		{
			b_op1 = m8;
			operand1 = operation.substr(6);
			if (!IsNumeric(operand1))
			{
				op1.memory_access = false;
				op1.rd_name = doperand_to_type(operand1);
				if (op1.rd_name == operand::data_reg_name::UNKD)
				{
					op1.reg_type = operand::type::reg_stack;
					op1.rs_name = soperand_to_type(operand1);
					return;
				}
				else
				{
					op1.reg_type = operand::type::reg_scratch;
					return;
				}
			}
			else
			{
				op1.memory_access = false;
				op1.reg_type = operand::type::value;
				std::stringstream string_buffer;
				string_buffer << std::hex << operand1;
				string_buffer >> op1.value32;
				return;
			}
		}
		else
		{
			std::cout << "\nwtf with pop?" << std::endl;
			valid = false;
			return;
		}
	}
	else if (operation.substr(0, 3) == "ADD")
	{
		/*
		ADD has 3 modes:
		ADD N2, N1 -> 32 bit mode
		ADD WORD N2, WORD N1 -> 16 bit mode
		ADD BYTE N1, BYTE N2 ;CF -> 8 bit mode
		*/
		n_operands = 2;
		b_operation = ADD;
		if (operation.substr(0, 8) == "ADD WORD")
		{
			std::string operand_1 = operation.substr(9, 2);
			b_op1 = m16;
			//first operand
			if (operand_1[0] == 'N')
			{
				op1.memory_access = false;
				op1.reg_type = operand::type::reg_stack;
				op1.rs_name = soperand_to_type(operand_1);
			}
			else
			{
				//data register
				op1.memory_access = false;
				op1.reg_type = operand::type::reg_scratch;
				op1.rd_name = doperand_to_type(operand_1);
			}
		}
		else if (operation.substr(0, 8) == "ADD BYTE")
		{
			//8 bit addition operand
			std::string operand_1 = operation.substr(9, 2);
			b_op1 = m8;

			if (operand_1[0] == 'N')
			{
				op1.memory_access = false;
				op1.reg_type = operand::type::reg_stack;
				op1.rs_name = soperand_to_type(operand_1);
			}
			else
			{
				//data register
				op1.memory_access = false;
				op1.reg_type = operand::type::reg_scratch;
				op1.rd_name = doperand_to_type(operand_1);
			}
		}
		else if (operation.substr(0, 9) == "ADD STACK")
		{
			//first operand is 32 bit
			b_op1 = m32;
			//first operand
			op1.memory_access = false;
			op1.reg_type = operand::type::reg_scratch;
			op1.rd_name = operand::data_reg_name::STACK;
			return;
		}
		else if (operation.substr(0, 4) == "ADD ")
		{
			//first operand is 32 bit
			std::string operand_1 = operation.substr(4, 2);
			b_op1 = m32;
			//first operand
			if (operand_1[0] == 'N')
			{
				op1.memory_access = false;
				op1.reg_type = operand::type::reg_stack;
				op1.rs_name = soperand_to_type(operand_1);
			}
			else
			{
				//data register
				op1.memory_access = false;
				op1.reg_type = operand::type::reg_scratch;
				op1.rd_name = doperand_to_type(operand_1);
			}
		}
		else
		{
			std::cout << "\ndude, you f*cked up on addition" << std::endl;
			valid = false;
			return;
		}

		//second operand
		//parse second operand
		size_t comma = operation.find(",");
		std::string operation_2 = operation.substr(comma, std::string::npos);
		operation_2 = operation_2.substr(2, std::string::npos);
		if (operation_2[0] == 'N')
		{
			b_op2 = m32;
			op2.memory_access = false;
			op2.reg_type = operand::type::reg_stack;
			op2.rs_name = soperand_to_type(operation_2.substr(0, 2));
		}
		else if (IsNumeric(operation_2))
		{
			b_op2 = m32;
			op2.memory_access = false;
			op2.reg_type = operand::type::value;
			std::stringstream string_buffer;
			string_buffer << std::hex << operation_2;
			string_buffer >> op2.value32;
		}
		else if (operation_2.substr(0, 4) == "WORD")
		{
			b_op2 = m16;
			op2.memory_access = false;

			std::string operand_2 = operation_2.substr(5, 2);
			//first operand
			if (operand_2[0] == 'N')
			{
				op2.memory_access = false;
				op2.reg_type = operand::type::reg_stack;
				op2.rs_name = soperand_to_type(operand_2);
			}
			else if (operand_2[0] == 'r')
			{
				op2.memory_access = false;
				op2.reg_type = operand::type::reg_scratch;
				op2.rd_name = doperand_to_type(operand_2);
			}
			else
			{
				//value
				operand_2 = operation_2.substr(5, std::string::npos);
				size_t value_endpos = operand_2.find(" ");
				operand_2 = operand_2.substr(0, value_endpos);
				op2.memory_access = false;
				op2.reg_type = operand::type::value;
				std::stringstream string_buffer;
				string_buffer << std::hex << operand_2;
				string_buffer >> op2.value32;
			}
		}
		else if (operation_2.substr(0, 4) == "BYTE")
		{
			b_op2 = m8;
			op2.memory_access = false;

			std::string operand_2 = operation_2.substr(5, 2);
			//first operand
			if (operand_2[0] == 'N')
			{
				op2.memory_access = false;
				op2.reg_type = operand::type::reg_stack;
				op2.rs_name = soperand_to_type(operand_2);
			}
			else if (operand_2[0] == 'r')
			{
				op2.memory_access = false;
				op2.reg_type = operand::type::reg_scratch;
				op2.rd_name = doperand_to_type(operand_2);
			}
			else
			{
				//value
				operand_2 = operation_2.substr(5, std::string::npos);
				size_t value_endpos = operand_2.find(" ");
				operand_2 = operand_2.substr(0, value_endpos);
				op2.memory_access = false;
				op2.reg_type = operand::type::value;
				std::stringstream string_buffer;
				string_buffer << std::hex << operand_2;
				string_buffer >> op2.value32;
			}
		}
		else
		{
			std::cout << "\n dude you fucked up on operand two with addition" << std::endl;
			valid = false;
			return;
		}
		return;
	}
	else if (operation.substr(0, 5) == "FETCH")
	{
		//parsing FETCH opcode
		/*
		FETCH_8 N1
		FETCH_16
		FETCH32 N1
		*/
		n_operands = 1;
		b_operation = FETCH;
		if (operation.substr(0, 7) == "FETCH_8")
		{
			b_op1 = m8;
			op1.memory_access = true;
			op1.reg_type = operand::type::reg_stack;
			op1.rs_name = operand::stack_reg_name::n1;
			return;
		}
		else if (operation.substr(0, 8) == "FETCH_16")
		{
			b_op1 = m16;
			op1.memory_access = true;
			op1.reg_type = operand::type::reg_stack;
			op1.rs_name = operand::stack_reg_name::n1;
			return;
		}
		else if (operation.substr(0, 7) == "FETCH32")
		{
			b_op1 = m32;
			op1.memory_access = true;
			op1.reg_type = operand::type::reg_stack;
			op1.rs_name = operand::stack_reg_name::n1;
			return;
		}
		else
		{
			std::cout << "\n dude you fucked up with the fetches" << std::endl;
			valid = false;
			return;
		}
	}
	else if (operation.substr(0, 3) == "MOV")
	{
		//MOV [N1], WORD N2
		//MOV [N1], N2 //destroy both
		//MOV WORD N2, BYTE: [N1] 

		n_operands = 2;
		b_operation = MOV;
		if (operation.substr(0, 8) == "MOV WORD")
		{
			std::string operand_1 = operation.substr(9, 2);
			b_op1 = m16;
			//first operand
			if (operand_1[0] == 'N')
			{
				op1.memory_access = false;
				op1.reg_type = operand::type::reg_stack;
				op1.rs_name = soperand_to_type(operand_1);
			}
			else
			{
				//data register
				op1.memory_access = false;
				op1.reg_type = operand::type::reg_scratch;
				op1.rd_name = doperand_to_type(operand_1);
			}
		}
		else if (operation.substr(0, 5) == "MOV [")
		{
			//first operand is 32 bit
			std::string operand_1 = operation.substr(5, 2);
			b_op1 = m32;
			//first operand
			if (operand_1[0] == 'N')
			{
				op1.memory_access = true;
				op1.reg_type = operand::type::reg_stack;
				op1.rs_name = soperand_to_type(operand_1);
			}
			else
			{
				//data register
				op1.memory_access = true;
				op1.reg_type = operand::type::reg_scratch;
				op1.rd_name = doperand_to_type(operand_1);
			}
		}
		else
		{
			std::cout << "\ndude, you f*cked up on moving" << std::endl;
			valid = false;
			return;
		}

		//second operand
		//parse second operand
		size_t comma = operation.find(",");
		std::string operation_2 = operation.substr(comma, std::string::npos);
		operation_2 = operation_2.substr(2, std::string::npos);
		if (operation_2[0] == 'N')
		{
			b_op2 = m32;
			op2.memory_access = false;
			op2.reg_type = operand::type::reg_stack;
			op2.rs_name = soperand_to_type(operation_2.substr(0, 2));
		}
		else if (operation_2.substr(0, 4) == "WORD")
		{
			b_op2 = m16;
			op2.memory_access = false;

			std::string operand_2 = operation_2.substr(5, 2);
			//first operand
			if (operand_2[0] == 'N')
			{
				op2.memory_access = false;
				op2.reg_type = operand::type::reg_stack;
				op2.rs_name = soperand_to_type(operand_2);
			}
			else if (operand_2[0] == 'r')
			{
				op2.memory_access = false;
				op2.reg_type = operand::type::reg_scratch;
				op2.rd_name = doperand_to_type(operand_2);
			}
			else
			{
				//value
				operand_2 = operation_2.substr(5, std::string::npos);
				size_t value_endpos = operand_2.find(" ");
				operand_2 = operand_2.substr(0, value_endpos);
				op2.memory_access = false;
				op2.reg_type = operand::type::value;
				std::stringstream string_buffer;
				string_buffer << std::hex << operand_2;
				string_buffer >> op2.value32;
			}
		}
		else if (operation_2.substr(0, 7) == "BYTE: [")
		{
			b_op2 = m8;
			op2.memory_access = true;

			std::string operand_2 = operation_2.substr(7, 2);
			//first operand
			if (operand_2[0] == 'N')
			{
				op2.memory_access = true;
				op2.reg_type = operand::type::reg_stack;
				op2.rs_name = soperand_to_type(operand_2);
			}
			else if (operand_2[0] == 'r')
			{
				op2.memory_access = true;
				op2.reg_type = operand::type::reg_scratch;
				op2.rd_name = doperand_to_type(operand_2);
			}
			else
			{
				//value
				operand_2 = operation_2.substr(7, std::string::npos);
				size_t value_endpos = operand_2.find(" ");
				operand_2 = operand_2.substr(0, value_endpos);
				op2.memory_access = true;
				op2.reg_type = operand::type::value;
				std::stringstream string_buffer;
				string_buffer << std::hex << operand_2;
				string_buffer >> op2.value32;
			}
		}
		else
		{
			std::cout << "\n dude you fucked up on operand two with moving" << std::endl;
			valid = false;
			return;
		}
		return;

	}
	else if (operation.substr(0, 3) == "NOR")
	{
		//40720f|NOR_32 N2, N1 ;CF
		/*
		NOR_32 N2, N1 ;CF
		NOR_16 ;CF
		*/
		if (operation == "NOR_32 N2, N1 ;CF")
		{
			n_operands = 2;
			b_operation = NOR;
			b_op1 = m32;
			b_op2 = m32;
			op1.memory_access = false;
			op2.memory_access = false;
			op1.reg_type = operand::type::reg_stack;
			op2.reg_type = operand::type::reg_stack;
			op1.rs_name = operand::stack_reg_name::n2;
			op2.rs_name = operand::stack_reg_name::n1;
			return;
		}
		else if (operation == "NOR_16 ;CF")
		{
			n_operands = 1;
			b_operation = NOR;
			b_op1 = m32;
			op1.memory_access = false;
			op1.reg_type = operand::type::reg_stack;
			op1.rs_name = operand::stack_reg_name::n1;
			return;
		}
		else
		{
			std::cout << "\n your NOR is fucked up " << operation << std::endl;
			valid = false;
			return;
		}
	}
	else if (operation == "NAND WORD N1, WORD N2 ;CF")
	{
		n_operands = 2;
		b_operation = NAND;
		b_op1 = m16;
		b_op2 = m16;
		op1.memory_access = false;
		op2.memory_access = false;
		op1.reg_type = operand::type::reg_stack;
		op2.reg_type = operand::type::reg_stack;
		op1.rs_name = operand::stack_reg_name::n1;
		op2.rs_name = operand::stack_reg_name::n2;
		return;
	}
	else if (operation.substr(0, 3) == "SHL")
	{
		/*
		407133|SHL WORD N1, BYTE N2
		407abd|SHL BYTE N1, BYTE N2 ;CF
		407ab2|SHL N1, BYTE N2
		407840|SHL_64 <N1,N2>, BYTE N3
		*/
		if (operation == "SHL WORD N1, BYTE N2")
		{
			n_operands = 2;
			b_operation = SHL;
			b_op1 = m16;
			b_op2 = m8;
			op1.memory_access = false;
			op2.memory_access = false;
			op1.reg_type = operand::type::reg_stack;
			op2.reg_type = operand::type::reg_stack;
			op1.rs_name = operand::stack_reg_name::n1;
			op2.rs_name = operand::stack_reg_name::n2;
			return;
		}
		else if (operation == "SHL BYTE N1, BYTE N2 ;CF")
		{
			n_operands = 2;
			b_operation = SHL;
			b_op1 = m8;
			b_op2 = m8;
			op1.memory_access = false;
			op2.memory_access = false;
			op1.reg_type = operand::type::reg_stack;
			op2.reg_type = operand::type::reg_stack;
			op1.rs_name = operand::stack_reg_name::n1;
			op2.rs_name = operand::stack_reg_name::n2;
			return;
		}
		else if (operation == "SHL N1, BYTE N2")
		{
			n_operands = 2;
			b_operation = SHL;
			b_op1 = m32;
			b_op2 = m8;
			op1.memory_access = false;
			op2.memory_access = false;
			op1.reg_type = operand::type::reg_stack;
			op2.reg_type = operand::type::reg_stack;
			op1.rs_name = operand::stack_reg_name::n1;
			op2.rs_name = operand::stack_reg_name::n2;
			return;
		}
		else if (operation == "SHL_64 <N1,N2>, BYTE N3")
		{
			n_operands = 2;
			b_operation = SHL;
			b_op1 = m64;
			b_op2 = m8;
			op1.memory_access = false;
			op2.memory_access = false;
			op1.reg_type = operand::type::reg_stack;
			op2.reg_type = operand::type::reg_stack;
			op1.rs_name = operand::stack_reg_name::n1n2;
			op2.rs_name = operand::stack_reg_name::n3;
			return;
		}
		else
		{
			std::cout << "\ndude, you totally fucked up with SHL" << std::endl;
			valid = false;
			return;
		}
	}
	else if (operation.substr(0, 3) == "SHR")
	{
		/*
		407133|SHL WORD N1, BYTE N2
		407abd|SHL BYTE N1, BYTE N2 ;CF
		407ab2|SHL N1, BYTE N2
		407840|SHL_64 <N1,N2>, BYTE N3
		*/
		if (operation == "SHR WORD N1, BYTE N2")
		{
			n_operands = 2;
			b_operation = SHR;
			b_op1 = m16;
			b_op2 = m8;
			op1.memory_access = false;
			op2.memory_access = false;
			op1.reg_type = operand::type::reg_stack;
			op2.reg_type = operand::type::reg_stack;
			op1.rs_name = operand::stack_reg_name::n1;
			op2.rs_name = operand::stack_reg_name::n2;
			return;
		}
		else if (operation == "SHR BYTE N1, BYTE N2 ;CF")
		{
			n_operands = 2;
			b_operation = SHR;
			b_op1 = m8;
			b_op2 = m8;
			op1.memory_access = false;
			op2.memory_access = false;
			op1.reg_type = operand::type::reg_stack;
			op2.reg_type = operand::type::reg_stack;
			op1.rs_name = operand::stack_reg_name::n1;
			op2.rs_name = operand::stack_reg_name::n2;
			return;
		}
		else if (operation == "SHR N1, BYTE N2")
		{
			n_operands = 2;
			b_operation = SHR;
			b_op1 = m32;
			b_op2 = m8;
			op1.memory_access = false;
			op2.memory_access = false;
			op1.reg_type = operand::type::reg_stack;
			op2.reg_type = operand::type::reg_stack;
			op1.rs_name = operand::stack_reg_name::n1;
			op2.rs_name = operand::stack_reg_name::n2;
			return;
		}
		else if (operation == "SHR_64 <N1,N2>, BYTE N3")
		{
			n_operands = 2;
			b_operation = SHR;
			b_op1 = m64;
			b_op2 = m8;
			op1.memory_access = false;
			op2.memory_access = false;
			op1.reg_type = operand::type::reg_stack;
			op2.reg_type = operand::type::reg_stack;
			op1.rs_name = operand::stack_reg_name::n1n2;
			op2.rs_name = operand::stack_reg_name::n3;
			return;
		}
		else
		{
			std::cout << "\ndude, you totally fucked up with SHL" << std::endl;
			valid = false;
			return;
		}
	}
	else if (operation == "JUMP N1+N2 ")
	{
		n_operands = 2;
		b_operation = JMP;
		b_op1 = m32;
		b_op2 = m32;
		op1.memory_access = false;
		op2.memory_access = false;
		op1.reg_type = operand::type::reg_stack;
		op2.reg_type = operand::type::reg_stack;
		op1.rs_name = operand::stack_reg_name::n1;
		op2.rs_name = operand::stack_reg_name::n2;
		return;
	}
	else if (operation == "MUL N1, N2")
	{
		n_operands = 2;
		b_operation = MUL;
		b_op1 = m32;
		b_op2 = m32;
		op1.memory_access = false;
		op2.memory_access = false;
		op1.reg_type = operand::type::reg_stack;
		op2.reg_type = operand::type::reg_stack;
		op1.rs_name = operand::stack_reg_name::n1;
		op2.rs_name = operand::stack_reg_name::n2;
		return;
	}
	else if (operation == "MUL WORD N1, WORD N2 ;CF")
	{
		n_operands = 2;
		b_operation = MUL;
		b_op1 = m16;
		b_op2 = m16;
		op1.memory_access = false;
		op2.memory_access = false;
		op1.reg_type = operand::type::reg_stack;
		op2.reg_type = operand::type::reg_stack;
		op1.rs_name = operand::stack_reg_name::n1;
		op2.rs_name = operand::stack_reg_name::n2;
		return;
	}
	else if (operation == "DIVIDE WORD N3 ;CF")
	{
		n_operands = 3;
		b_operation = DIVIDE;
		b_op1 = m32;
		b_op2 = m16;
		op1.memory_access = false;
		op2.memory_access = false;
		op1.reg_type = operand::type::reg_stack;
		op2.reg_type = operand::type::reg_stack;
		op1.rs_name = operand::stack_reg_name::n1n2;
		op2.rs_name = operand::stack_reg_name::n3;
		return;
	}
	else if (operation == "VM_OUTSIDE")
	{
		n_operands = 0;
		b_operation = VM_OUT;
		return;
	}
	else if (operation.substr(0, 8) == " unknown")
	{
		n_operands = 0;
		b_operation = UNKNOWN;
		std::cout << "\n handler was unknown " << operation << std::endl;
		return;
	}
	else if (operation == "vm_quit")
	{
		n_operands = 0;
		b_operation = VM_QUIT;
		return;
	}
	else
	{
		std::cout << "\n unknown operand " << std::endl;
		std::cout << operation << std::endl;
		valid = false;
		return;
	}
}