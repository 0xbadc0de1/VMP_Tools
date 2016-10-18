#include "peephole_functions.h"

void format_bytecode(bytecode instruction, std::ofstream& file_buffer)
{
	std::stringstream hex_stream;
	file_buffer << "\n";
	file_buffer << "VA: ";
	hex_stream << std::hex << instruction.ByteCodeVA() << " | ";
	file_buffer << hex_stream.str();
	switch (instruction.Operation())
	{
	case bytecode::ADD:
		file_buffer << "ADD ";
		break;
	case bytecode::PUSH:
		file_buffer << "PUSH ";
		break;
	case bytecode::POP:
		file_buffer << "POP ";
		break;
	case bytecode::SUB:
		file_buffer << "SUB ";
		break;
	case bytecode::MOV:
		file_buffer << "MOV ";
		break;
	case bytecode::NOR:
		file_buffer << "NOR ";
		break;
	case bytecode::NAND:
		file_buffer << "NAND ";
		break;
	case bytecode::SHL:
		file_buffer << "SHL ";
		break;
	case bytecode::SHR:
		file_buffer << "SHR ";
		break;
	case bytecode::JMP:
		file_buffer << "JMP ";
		break;
	case bytecode::TIMESTAMP:
		file_buffer << "TIME_STAMP ";
		break;
	case bytecode::DIVIDE:
		file_buffer << "DIVIDE ";
		break;
	case bytecode::MUL:
		file_buffer << "MUL ";
		break;
	case bytecode::VM_OUT:
		file_buffer << "VM_OUT ";
		break;
	case bytecode::UNKNOWN:
		file_buffer << "UNKNOWN ";
		break;
	case bytecode::VM_QUIT:
		file_buffer << "VM_QUIT ";
		break;
	case bytecode::FETCH:
		file_buffer << "FETCH ";
		break;
	}
	if (instruction.NumberOfOperands() == 0)
	{
		return;
	}
	switch (instruction.Operand1Mode())
	{
	case bytecode::m32:
		file_buffer << "DWORD: ";
		break;
	case bytecode::m64:
		file_buffer << "QWORD: ";
		break;
	case bytecode::m16:
		file_buffer << "WORD: ";
		break;
	case bytecode::m8:
		file_buffer << "BYTE: ";
		break;
	}
	if (instruction.GetOperand1().memory_access == true)
	{
		file_buffer << "[";
	}
	if (instruction.GetOperand1().reg_type == bytecode::operand::reg_scratch)
	{
		switch (instruction.GetOperand1().rd_name)
		{
		case bytecode::operand::r1:
			file_buffer << "r1";
			break;
		case bytecode::operand::r2:
			file_buffer << "r2";
			break;
		case bytecode::operand::r0:
			file_buffer << "r0";
			break;
		case bytecode::operand::r3:
			file_buffer << "r3";
			break;
		case bytecode::operand::r4:
			file_buffer << "r4";
			break;

		case bytecode::operand::r5:
			file_buffer << "r5";
			break;

		case bytecode::operand::r6:
			file_buffer << "r6";
			break;

		case bytecode::operand::r7:
			file_buffer << "r7";
			break;

		case bytecode::operand::r8:
			file_buffer << "r8";
			break;

		case bytecode::operand::r9:
			file_buffer << "r9";
			break;

		case bytecode::operand::ra:
			file_buffer << "ra";
			break;

		case bytecode::operand::rb:
			file_buffer << "rb";
			break;

		case bytecode::operand::rc:
			file_buffer << "rc";
			break;

		case bytecode::operand::rd:
			file_buffer << "rd";
			break;

		case bytecode::operand::re:
			file_buffer << "re";
			break;
		case bytecode::operand::rf:
			file_buffer << "rf";
			break;
		case bytecode::operand::r10:
			file_buffer << "r10";
			break;
		case bytecode::operand::r11:
			file_buffer << "r11";
			break;
		case bytecode::operand::r12:
			file_buffer << "r12";
			break;
		case bytecode::operand::r13:
			file_buffer << "r13";
			break;
		case bytecode::operand::r14:
			file_buffer << "r14";
			break;
		case bytecode::operand::STACK:
			file_buffer << "STACK";
			break;
		default:
			file_buffer << "??";
			break;
		}
	}
	else if (instruction.GetOperand1().reg_type == bytecode::operand::reg_stack)
	{
		switch (instruction.GetOperand1().rs_name)
		{
		case bytecode::operand::n1:
			file_buffer << "n1";
			break;
		case bytecode::operand::n2:
			file_buffer << "n2";
			break;
		case bytecode::operand::n3:
			file_buffer << "n3";
			break;
		case bytecode::operand::n1n2:
			file_buffer << "<n1,n2>";
			break;
		default:
			file_buffer << "wtf?";
			break;
		}
	}
	else if (instruction.GetOperand1().reg_type == bytecode::operand::none)
	{
		file_buffer << "none?!";
	}
	else if (instruction.GetOperand1().reg_type == bytecode::operand::value)
	{
		file_buffer << std::hex << instruction.GetOperand1().value32;
	}
	else
	{
		file_buffer << "wtf??";
	}
	if (instruction.GetOperand1().memory_access == true)
	{
		file_buffer << "]";
	}
	if (instruction.NumberOfOperands() == 1)
	{
		return;
	}
	file_buffer << ", ";

	switch (instruction.Operand2Mode())
	{
	case bytecode::m32:
		file_buffer << "DWORD: ";
		break;
	case bytecode::m64:
		file_buffer << "QWORD: ";
		break;
	case bytecode::m16:
		file_buffer << "WORD: ";
		break;
	case bytecode::m8:
		file_buffer << "BYTE: ";
		break;
	}

	if (instruction.GetOperand2().memory_access == true)
	{
		file_buffer << "[";
	}
	if (instruction.GetOperand2().reg_type == bytecode::operand::reg_scratch)
	{
		switch (instruction.GetOperand2().rd_name)
		{
		case bytecode::operand::r1:
			file_buffer << "r1";
			break;
		case bytecode::operand::r2:
			file_buffer << "r2";
			break;
		case bytecode::operand::r0:
			file_buffer << "r0";
			break;
		case bytecode::operand::r3:
			file_buffer << "r3";
			break;
		case bytecode::operand::r4:
			file_buffer << "r4";
			break;

		case bytecode::operand::r5:
			file_buffer << "r5";
			break;

		case bytecode::operand::r6:
			file_buffer << "r6";
			break;

		case bytecode::operand::r7:
			file_buffer << "r7";
			break;

		case bytecode::operand::r8:
			file_buffer << "r8";
			break;

		case bytecode::operand::r9:
			file_buffer << "r9";
			break;

		case bytecode::operand::ra:
			file_buffer << "ra";
			break;

		case bytecode::operand::rb:
			file_buffer << "rb";
			break;

		case bytecode::operand::rc:
			file_buffer << "rc";
			break;

		case bytecode::operand::rd:
			file_buffer << "rd";
			break;

		case bytecode::operand::re:
			file_buffer << "re";
			break;
		case bytecode::operand::rf:
			file_buffer << "rf";
			break;
		case bytecode::operand::r10:
			file_buffer << "r10";
			break;
		case bytecode::operand::r11:
			file_buffer << "r11";
			break;
		case bytecode::operand::r12:
			file_buffer << "r12";
			break;
		case bytecode::operand::r13:
			file_buffer << "r13";
			break;
		case bytecode::operand::r14:
			file_buffer << "r14";
			break;
		case bytecode::operand::STACK:
			file_buffer << "STACK";
			break;
		default:
			file_buffer << "??";
			break;
		}
	}
	else if (instruction.GetOperand2().reg_type == bytecode::operand::reg_stack)
	{
		switch (instruction.GetOperand2().rs_name)
		{
		case bytecode::operand::n1:
			file_buffer << "n1";
			break;
		case bytecode::operand::n2:
			file_buffer << "n2";
			break;
		case bytecode::operand::n3:
			file_buffer << "n3";
			break;
		case bytecode::operand::n1n2:
			file_buffer << "<n1,n2>";
			break;
		default:
			file_buffer << "wtf?";
			break;
		}
	}
	else if (instruction.GetOperand2().reg_type == bytecode::operand::none)
	{
		file_buffer << "none?!";
	}
	else if (instruction.GetOperand2().reg_type == bytecode::operand::value)
	{
		file_buffer << std::hex << instruction.GetOperand2().value32;
	}
	else
	{
		file_buffer << "wtf??";
	}
	if (instruction.GetOperand2().memory_access == true)
	{
		file_buffer << "]";
	}
	return;
}

void print_code(std::list<bytecode>& bprgm, std::ofstream& file_buffer)
{
	for (std::list<bytecode>::iterator b_it = bprgm.begin(); b_it != bprgm.end(); ++b_it)
	{
		format_bytecode(*b_it, file_buffer);
	}
	return;
}


/*
Peephole functions
*/
/*
Removes all PUSHes
*/
bool p33p_0(std::list<bytecode>& bprgm, std::list<bytecode>::iterator& b_it)
{
	if (b_it->Operation() == bytecode::PUSH)
	{
		b_it = bprgm.erase(b_it);
		return true;
	}
	if (b_it->Operation() == bytecode::POP)
	{
		b_it = bprgm.erase(b_it);
		return true;
	}
	return false;
}
/*
PEEPHOLE #1
40722c|PUSH_32 93fcd063
407227|PUSH_32 STACK
407226|FETCH32 N1
is equivalent to
PUSH_32 93fcd063
PUSH_32 93fcd063
*/
bool p33p_1(std::list<bytecode>& bprgm, std::list<bytecode>::iterator& b_it)
{
	std::list<bytecode>::iterator n_it = b_it;

	std::list<bytecode>::iterator p1;
	std::list<bytecode>::iterator p2;
	std::list<bytecode>::iterator p3;
	std::list<bytecode>::iterator ptr;

	p1 = n_it;
	if (p1 == bprgm.end())
	{
		return false;
	}
	++n_it;
	p2 = n_it;
	if (p2 == bprgm.end())
	{
		return false;
	}
	++n_it;
	p3 = n_it;
	if (p3 == bprgm.end())
	{
		return false;
	}

	if ((p1->Operation() == bytecode::PUSH) && (p1->NumberOfOperands() == 1) && (p1->Operand1Mode() == bytecode::m32) && (p1->GetOperand1().reg_type == bytecode::operand::type::value)
		&& (p2->Operation() == bytecode::PUSH) && (p2->NumberOfOperands() == 1) && (p2->Operand1Mode() == bytecode::m32) && (p2->GetOperand1().reg_type == bytecode::operand::type::reg_scratch) && (p2->GetOperand1().rd_name == bytecode::operand::data_reg_name::STACK)
		&& (p3->Operation() == bytecode::FETCH) && (p3->NumberOfOperands() == 1) && (p3->Operand1Mode() == bytecode::m32) && (p3->GetOperand1().reg_type == bytecode::operand::type::reg_stack) && (p3->GetOperand1().rs_name == bytecode::operand::stack_reg_name::n1))
	{
		if ((p1->GetOperand1().memory_access) || (p1->GetOperand2().memory_access))
		{
			return false;
		}
		bytecode p_optimized;
		bytecode::operand operand_1;
		ptr = p2;
		//Sets the new opcode
		p_optimized.SetByteCodeVA(p2->ByteCodeVA());
		p_optimized.SetNumberOfOperands(1);
		p_optimized.SetOperand1Mode(bytecode::m32);
		p_optimized.SetOperation(bytecode::PUSH);
		p_optimized.SetValid(true);
		//operand
		operand_1.memory_access = false;
		operand_1.reg_type = bytecode::operand::type::value;
		operand_1.value32 = p2->GetOperand1().value32;
		p_optimized.SetOperand1(operand_1);
		ptr = bprgm.insert(p2, p_optimized);
		p2 = bprgm.erase(p2);
		b_it = bprgm.erase(p2);
		return true;
	}

	return false;
}

/*
PEEPHOLE #2
40722c|PUSH_16 y
407227|PUSH_16 x
is equivalent to
PUSH_32 xy
*/
bool p33p_2(std::list<bytecode>& bprgm, std::list<bytecode>::iterator& b_it)
{
	std::list<bytecode>::iterator n_it = b_it;

	std::list<bytecode>::iterator p1;
	std::list<bytecode>::iterator p2;
	std::list<bytecode>::iterator ptr;

	p1 = n_it;
	if (p1 == bprgm.end())
	{
		return false;
	}
	++n_it;
	p2 = n_it;
	if (p2 == bprgm.end())
	{
		return false;
	}


	if ((p1->Operation() == bytecode::PUSH) && (p1->NumberOfOperands() == 1) && (p1->Operand1Mode() == bytecode::m16) && (p1->GetOperand1().reg_type == bytecode::operand::type::value)
		&& (p2->Operation() == bytecode::PUSH) && (p2->NumberOfOperands() == 1) && (p2->Operand1Mode() == bytecode::m16) && (p2->GetOperand1().reg_type == bytecode::operand::type::value))
	{
		if ((p1->GetOperand1().memory_access) || (p1->GetOperand2().memory_access))
		{
			return false;
		}
		bytecode p_optimized;
		bytecode::operand operand_1;
		ptr = p2;
		//Sets the new opcode
		p_optimized.SetByteCodeVA(p1->ByteCodeVA());
		p_optimized.SetNumberOfOperands(1);
		p_optimized.SetOperand1Mode(bytecode::m32);
		p_optimized.SetOperation(bytecode::PUSH);
		p_optimized.SetValid(true);
		//operand
		operand_1.memory_access = false;
		operand_1.reg_type = bytecode::operand::type::value;
		operand_1.value32 = (((p2->GetOperand1().value32) & 0xFFFF)) | (((p1->GetOperand1().value32) & 0xFFFF) << 16);
		p_optimized.SetOperand1(operand_1);
		ptr = bprgm.insert(p1, p_optimized);
		p2 = bprgm.erase(p1);
		b_it = bprgm.erase(p2);
		return true;
	}

	return false;
}