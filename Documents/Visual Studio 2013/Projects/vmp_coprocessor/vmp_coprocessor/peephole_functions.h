#include "stdafx.h"
#include "co_processor.h"
#include "bytecode_ir.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdint.h>
#include <sstream>
#include <list>


void format_bytecode(bytecode instruction, std::ofstream& file_buffer);

void print_code(std::list<bytecode>& bprgm, std::ofstream& file_buffer);


/*
Peephole functions
*/
/*
Removes all PUSHes
*/
bool p33p_0(std::list<bytecode>& bprgm, std::list<bytecode>::iterator& b_it);
/*
PEEPHOLE #1
40722c|PUSH_32 93fcd063
407227|PUSH_32 STACK
407226|FETCH32 N1
is equivalent to
PUSH_32 93fcd063
PUSH_32 93fcd063
*/
bool p33p_1(std::list<bytecode>& bprgm, std::list<bytecode>::iterator& b_it);

/*
PEEPHOLE #2
40722c|PUSH_16 y
407227|PUSH_16 x
is equivalent to
PUSH_32 xy
*/
bool p33p_2(std::list<bytecode>& bprgm, std::list<bytecode>::iterator& b_it);