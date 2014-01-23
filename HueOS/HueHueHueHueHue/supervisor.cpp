#include "../global.h"
#include "../Hue/globLev1.h"
#include "../HueHue/pamiec.h"
#include "../HueHueHue/lev3.h"
#include "../HueHueHueHue/CPRINT.h"
#include "../HueHueHueHue/CREAD_File.h"
#include "../HueHueHueHue/JOB.h"
#include "sysproces.h"
#include <vector>
#include "interpreter.h"
#include "split.h"

#include "supervisor.h"

const char* const Supervisor::names[] = {"*IBSUP", "*IN", "*OUT"};

Supervisor::Supervisor(Planista* mPlanista, Lev3* mPoz3, pamiec* mPamiec) /*: mPlanista(mPlanista), mPoz3(mPoz3)*/ {
	this->mPoz3 = mPoz3;
	this->mPlanista = mPlanista;
	this->mPamiec = mPamiec;
	drukarka1 = new CPRINT();
	czytnik1 = new CREAD_File();
}

void Supervisor::init() {
	string job_cards[] = {"1.job", "2.job"};

	// uruchom procesy systemowe
	for (int i = 0; i < 3; i++) {
		mPoz3->dodajPCB(new SysProces(i + 1, Supervisor::names[i]), true);
	}

	JOB job; // hey, let's ignore job.job :v

	// parsuj $JOB
	for (int i = 0; i < 2; i++) {
		cout << "Czytanie $JOB " << job_cards[i] << endl;
		job.JOB_nazwapliku(job_cards[i]);
		Interpreter interpreter;
		interpreter.interpret_code(job.getData());
		mPoz3->dodajProces(job_cards[i], interpreter.op_count, interpreter.total_length);
		Proces* userprog = mPoz3->znajdzProces(job_cards[i]);
		if (!userprog) {
			cout << "Proces " << job_cards[i] << " nie zostal utworzony";
		}
		
		for (unsigned int j = 0; j < interpreter.total_length; j++) {
			if (!mPamiec->ustaw_bajt(userprog->pierwszy_bajt_pamieci, j, interpreter.buffer[j])) {
				cout << "Pisanie do bajtu " << j << " nie powiodlo sie" << endl;
			}
			else {
				cout << "Pisanie do bajtu " << j << " powiodlo sie" << endl;
			}
		}

		cout << "Uruchomienie procesu " << job_cards[i];
		mPoz3->uruchomProces(job_cards[i]);

	}

}

void Supervisor::execute(Proces* proces) {
	if (!proces) {
		return; // brak procesu do wykonania
	}
	cout << "Wykonuje rozkaz procesu " << proces->nazwa << endl;
	
	// fixme dodaj obsluge bledow pobierz_bajt
	Interpreter::OpCode op = (Interpreter::OpCode)mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
	unsigned short param_length = (unsigned short)mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
	char* raw_param;
	unsigned int int_param;
	if (param_length != 0) {
		raw_param = new char[param_length];
		for (int i = 0; i < param_length; i++) {
			raw_param[i] = mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
		}
	}

	cout << "OP" << (char)op << " len: " << param_length << " " << raw_param << endl;

	// parameter preprocessing
	switch (op) {
	case Interpreter::OpCode::SET:
	case Interpreter::OpCode::ADD:
	case Interpreter::OpCode::SUB:
	case Interpreter::OpCode::MUL:
	case Interpreter::OpCode::DIV:
	case Interpreter::OpCode::JUMP:
	case Interpreter::OpCode::JMPZ:
	case Interpreter::OpCode::JPNZ:
		memcpy(&int_param, raw_param, sizeof(unsigned int));
		cout << int_param << endl;
	}

	switch (op) {
	case Interpreter::OpCode::SET:
	case Interpreter::OpCode::ADD:
	case Interpreter::OpCode::SUB:
	case Interpreter::OpCode::MUL:
	case Interpreter::OpCode::DIV:
	case Interpreter::OpCode::JUMP:
	case Interpreter::OpCode::JMPZ:
	case Interpreter::OpCode::JPNZ:
	case Interpreter::OpCode::IN1:
	case Interpreter::OpCode::IN2:
	case Interpreter::OpCode::OUT1:
	case Interpreter::OpCode::BYE:
		cout << "Cos uzytecznego! Olewam!";
		break;
	default:
		cout << "Nieprawidlowy rozkaz. Proces zostanie usuniety";
		// fixme usun proces
	}

	if (param_length != 0) {
		delete[] raw_param;
	}
	proces->t_obslugi++;
}

void Supervisor::checkMessages() {
	string komunikat;
	vector<string> x;
	for (int i = 0; i < 3; i++) {
		komunikat = mPoz3->czytajKomunikat(Supervisor::names[i]);
		if (!komunikat.empty()) {
			cout << Supervisor::names[i] << " otrzymal komunikat: " << komunikat << endl;
			switch (i) {
			case 0: // ibsup
				x = split(komunikat, ' ');
				cout << "Zakonczono proces uzytkownika: " << x[1] << endl;
				break;
			case 1: // in
				// pobrac tekst (z pliku podanego w komunikacie?),
				// wyslac komunikat do nadawcy (czyli kogo :v)
				break;
			case 2:
				drukarka1->PRINT((char *)komunikat.c_str());
				cout << "Przekazano komunikat do druku: " << komunikat << endl;
				break;
			}
		}
	}
}