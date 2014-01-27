#include "interpreter.h"

bool Interpreter::is_valid_registry(string name) {
	return name == "A" ||
		name == "B" ||
		name == "C" ||
		name == "D";
}

void Interpreter::interpret_code(string blob) {
	/*
	asm:
	op (byte value) - desc
		param desc
	registers:
		A through D are valid register names

	SET (1) - sets the value of [register] to [param]
		example:
			SET:A:7
	ADD (2) - adds [param] to the current value of [register]
	SUB (3) - subtracts [param] from the current value of [register]
	MUL (4) - multiplies current value of [register] by [param]
	DIV (5) - divides current value of [register] by [param]
	JUMP (6) - jumps to [param]th (note: zero-based indexing) command
	JMPZ (7) - jumps to [param]th command if registry 0 is set to 0
	JPNZ (8) - jumps to [param]th command if registry 0 is not set to 0
		for all above:
			if [param] is in ('A', 'B', 'C', 'D'), value is taken from adequate register
			otherwise [param] (fixed size 4) is an int.
		by the way this asm supports forward jumps too, neat.
	IN (9,0) - requests user input, requires int input, which is then stored in [register]
		this gets split into two ops, when the first one (9) is executed,
		message is sent to IN device, requesting for data.
		the second one (0) will execute after data has been received
	OUT (a) - sends [param] to output device
		[param] is a string (char[]) of dynamic length
		if [param] length is 1, [param][0] will be used to access register value
		otherwise first character is ignored (i.e. [param][1:])
		example:
			OUT:A - prints value of register A
			OUT:AHello! - prints "Hello!"
	BYE (b) - tells the program to exit

	each operation should be converted to:
	opcode param_count [param_length param]
	^_char ^_char      ^_char        ^_mixed

	blob example:
	ADD:A:2|JUMP:3|SUB:A:2|OUT:A|BYE

	should be converted into this:
	0        1      2        3   4
	221A400026140018321A40002a11Ab0
	^^^^^^  ^
	||||||__|_param
	|||||_param size
	||||_param
	|||_param size
	||_param count
	|_op number

	and should print 2 to the output
	*/
	vector<unsigned int> line_lengths; // this is needed for forward jumps
	vector<unsigned int> param_lengths; // this is needed for some reason
	vector<string> lines = split(blob, '|');
	op_count = lines.size();
	total_length = lines.size(); // number of op codes
	unsigned int length, line_length;
	// initially we just find the lengths of params
	for(vector<string>::iterator it = lines.begin(); it != lines.end(); ++it) {
		vector<string> parts = split(*it, ':');
		line_length = 2 + parts.size() - 1; // op code, param count, param length in each field
		for (unsigned int i = 1; i < parts.size(); i++) {
			length = 0;
			if (parts[0] == "IN") {
				// this needs to compensate for IN2 opcode (and its param count, param size char, registry field)
				op_count += 1;
				line_length += 4;
				total_length += 4;
				line_lengths.push_back(4);
				param_lengths.push_back(1);
			}
			else if (parts[0] == "OUT") {
				// so basically, if this is OUT (and has params), it can be any length
				length = parts[i].length() + 1;
			}
			else if (parts[0] == "SET" || parts[0] == "ADD" ||
				parts[0] == "SUB" || parts[0] == "MUL" || parts[0] == "DIV") {
				// for these, first argument has to be registry, second can be registry/int
				length = i == 1 || (i == 2 && is_valid_registry(parts[i])) ? 1 : sizeof(unsigned int);
			} else if (parts[0] == "JUMP" || parts[0] == "JMPZ" || parts[0] == "JPNZ") {
				length = i == 1 && is_valid_registry(parts[i]) ? 1 : sizeof(unsigned int);
			} else {
				cout << "To sie nie powinno zdarzyc" << endl;
				// otherwise 4 bytes for int
				//length = sizeof(unsigned int);
			}
			param_lengths.push_back(length);
			line_length += length;
		}
		total_length += line_length;
		line_lengths.push_back(line_length);
	}

	// now that we have that, we can already fill JUMP ops properly
	// but before we do it, we can now create a char[] for our "machine code"

	buffer = new char[total_length];
	unsigned int c = 0, p = 0;
	OpCode opcode;

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
			buffer[c++] = (char)OpCode::IN1;
			buffer[c++] = parts.size() - 1;
			buffer[c++] = param_lengths[p++];
			buffer[c++] = parts[1].c_str()[0];
			opcode = OpCode::IN2;
		} else if (op == "OUT") {
			opcode = OpCode::OUT1;
		} else if (op == "BYE") {
			opcode = OpCode::BYE;
		}
		buffer[c++] = (char)opcode;
		buffer[c++] = parts.size() - 1;
		unsigned int j;
		for (unsigned int i = 1; i < parts.size(); i++) {
			buffer[c++] = param_lengths[p++];
			if ((op == "JUMP" || op == "JMPZ" || op == "JPNZ") && param_lengths[p-1] == sizeof(unsigned int)) {
				j = 0;
				int target = atoi(parts[1].c_str());
				for (int k = 0; k < target; k++) {
					j += line_lengths[k];
				}
				memcpy(buffer + c, &j, sizeof(unsigned int));
				c += sizeof(unsigned int);
			} else {
				switch (param_lengths[p-1]) {
				case 1:
					buffer[c++] = parts[i].c_str()[0];
					break;
				case sizeof(unsigned int) :
					j = atoi(parts[i].c_str());
					memcpy(buffer + c, &j, sizeof(unsigned int));
					c += sizeof(unsigned int);
					break;
				default:
					memcpy(buffer + c, parts[i].c_str(), parts[i].length() + 1);
					c += parts[1].length() + 1;
				}
			}
		}
	}
}
