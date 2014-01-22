#include "../global.h"
#include <cstdlib>
#include <vector>
#include "split.h"

class Interpreter {
public:
	enum class OpCode : char {
		SET = '1',
		ADD = '2',
		SUB = '3',
		MUL = '4',
		DIV = '5',
		JUMP = '6',
		JMPZ = '7',
		JPNZ = '8',
		IN1 = '9',
		IN2 = '0',
		OUT1 = 'a',
		BYE = 'b',
	};
	unsigned int op_count;
	unsigned int total_length;
	char* buffer;
	~Interpreter();
	void interpret_code(string blob);
};