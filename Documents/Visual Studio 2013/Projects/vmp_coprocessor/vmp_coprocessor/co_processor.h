// reading a text file
#include <iostream>
#include <fstream>
#include <string>
//using namespace std;

//co processor module
class co_proc {
private:
	std::string stack_origin;
public:
	co_proc(std::string _stack_origin);
	void process(std::ifstream& file, std::ofstream& processed_file);
	void peephole(std::ifstream& file, std::ofstream& processed_file);
};
