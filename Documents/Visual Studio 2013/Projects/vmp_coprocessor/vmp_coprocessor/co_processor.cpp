
#include "co_processor.h"

/*
COPROCESSOR MODULE
->STACK (disasm) fix
->PEEPHOLE optimization
*/
co_proc::co_proc(std::string _stack_origin)
{
	stack_origin = _stack_origin;
}

void co_proc::process(std::ifstream& file, std::ofstream& processed_file)
{
	std::string line = "";
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			std::size_t found = line.find(stack_origin);
			if (found != std::string::npos)
			{
				line.replace(found, 7, " STACK");
			}
			
			processed_file << line << "\n";
		}
	}

}

void co_proc::peephole(std::ifstream& file, std::ofstream& processed_file)
{
	std::string line = "";
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			std::size_t op_begin = line.find("|") + 1;
			std::size_t op_space = line.find(" ");
			std::string operation = line.substr(op_begin, op_space);
			/*
			  PUSH_32 uint32_t
			  PUSH_32 STACK
			  FETCH32 N1

			  optimizes to:
			  PUSH_32 uint32_t
			  PUSH_32 uint32_t
			*/
			if (operation == "PUSH")
			{
				std::getline(file, line);
				op_begin = line.find("|") + 1;
				op_space = line.find(" ");
				operation = line.substr(op_begin, op_space);
			}
		}
	}
}