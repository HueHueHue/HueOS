#include "interpreter.h"

Interpreter::~Interpreter() {
	delete[] buffer;
}

void Interpreter::interpret_code(string blob) {
	/*
	asm:
	op (byte value) - desc
		param desc

	SET (1) - sets the value of registry 0 to [param]
	ADD (2) - adds [param] to the current value of registry 0
	SUB (3) - subtracts [param] from the current value of registry 0
	MUL (4) - multiplies current value of registry 0 by [param]
	DIV (5) - divides current value of registry 0 by [param]
	JUMP (6) - jumps to [param]th (note: zero-based indexing) command
	JMPZ (7) - jumps to [param]th command if registry 0 is set to 0
	JPNZ (8) - jumps to [param]th command if registry 0 is not set to 0
		for all above: [param] (fixed size 4) is an int.

		by the way this asm supports forward jumps too, neat.
	IN (9,0) - requests user input
		this gets split into two ops, when the first one (9) is executed,
		message is sent to IN device, requesting for data.
		the second one (0) will execute after data has been received
	OUT (a) - sends [param] to output device
		[param] is a string (char[]) of dynamic length
		if no [param], sends the value of registry 0
	BYE (b) - tells the program to exit

	blob example:
	ADD:2|JUMP:3|SUB:2|OUT|BYE

	should be converted into this:
	0     1     2     3 4
	240002640018340002a0b0
	^^^  ^
	|||__|_param
	||_param size
	|_op number

	and should print 2 to the output
	*/
	vector<unsigned int> param_lengths; // this is needed for forward jumps
	vector<string> lines = split(blob, '|');
	op_count = lines.size();
	unsigned int total_length = 2 * lines.size();
	unsigned int length;
	// initially we just find the lengths of params
	for(vector<string>::iterator it = lines.begin(); it != lines.end(); ++it) {
		vector<string> parts = split(*it, ':');
		if (parts.size() == 1) {
			length = 0;
			// no param
		} else if (parts[0] == "IN") {
			// this needs to compensate for IN2 opcode (and its param size char)
			op_count += 1;
			total_length += 2;
		} else if (parts[0] == "OUT") {
			// so basically, if this is OUT (and has params), it can be any length
			length = parts[1].length();
		} else {
			// otherwise 4 bytes for int
			length = sizeof(unsigned int);
		}
		total_length += length;
		param_lengths.push_back(length);
	}

	// now that we have that, we can already fill JUMP ops properly
	// but before we do it, we can now create a char[] for our "machine code"

	buffer = new char[total_length];
	unsigned int c = 0;
	enum OpCode opcode;

	for(vector<string>::size_type i = 0; i != lines.size(); i++) {
		vector<string> parts = split(lines[i], ':');
		string op = parts[0];
		if (op == "SET") {
			opcode = OpCode::SET;
		} else if (op == "ADD") {
			opcode = OpCode::ADD;
		} else if (op == "SUB") {
			opcode = OpCode::SUB;
		} else if (op == "MUL") {
			opcode = OpCode::MUL;
		} else if (op == "DIV") {
			opcode = OpCode::DIV;
		} else if (op == "JUMP") {
			opcode = OpCode::JUMP;
		} else if (op == "JMPZ") {
			opcode = OpCode::JMPZ;
		} else if (op == "JPNZ") {
			opcode = OpCode::JPNZ;
		} else if (op == "IN") {
			/*
			this generates two opcodes, explained above
			*/
			opcode = OpCode::IN1;
			buffer[c++] = (char)opcode;
			buffer[c++] = 0; 
			opcode = OpCode::IN2;
		} else if (op == "OUT") {
			opcode = OpCode::OUT1;
		} else if (op == "BYE") {
			opcode = OpCode::BYE;
		}
		buffer[c++] = (char)opcode;
		buffer[c++] = param_lengths[i];
		if (parts.size() == 2) {
			if (op == "OUT") {
				// for(string::size_type i = 0; i < parts[1].size(); ++i) {
				// 	buffer[c++] = parts[1][i];
				// }
				memcpy(buffer + c, parts[1].c_str(), parts[1].length()+1);
			} else {
				unsigned int i = atoi(parts[1].c_str());
				memcpy(buffer + c, &i, sizeof(unsigned int));
				c += sizeof(unsigned int);
			}
		}
	}
}

// do wykonatora (lol)


	// string operation = x[0];
	// string param = x[1];

	// if (operation == "SET") {
	// 	mRejestr[0] = 0 // HUEHUE jak parsowac inty
	// }