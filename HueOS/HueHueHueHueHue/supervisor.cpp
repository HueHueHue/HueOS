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

const char* const Supervisor::names[] = { "*IBSUP", "*IN", "*OUT" };

Supervisor::Supervisor(Planista* mPlanista, Lev3* mPoz3, pamiec* mPamiec, Rejestr* mRejestr) /*: mPlanista(mPlanista), mPoz3(mPoz3)*/ {
	this->mPoz3 = mPoz3;
	this->mPlanista = mPlanista;
	this->mPamiec = mPamiec;
	this->mRejestr = mRejestr;
	job = new JOB();
	drukarka1 = new CPRINT();
	czytnik1 = new CREAD_File();
}

void Supervisor::init() {
	// uruchom procesy systemowe
	for (int i = 0; i < 3; i++) {
		mPoz3->dodajPCB(new SysProces(i + 1, Supervisor::names[i]), true);
	}
}

bool Supervisor::loadJob(string job_name) {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 0x0D);
	cout << "Hue5: Czytanie $JOB " << job_name << endl;
	SetConsoleTextAttribute(hOut, 0x07);

	if (!job->JOB_nazwapliku(job_name)) {
		SetConsoleTextAttribute(hOut, 0x0D);
		cout << "Hue5: Proces " << job_name << " nie zostal utworzony (brak karty job)" << endl;
		SetConsoleTextAttribute(hOut, 0x07);
		return false;
	}
	Interpreter interpreter;
	interpreter.interpret_code(job->getData());
	if (!mPoz3->dodajProces(job_name, interpreter.op_count, interpreter.total_length)) {
		SetConsoleTextAttribute(hOut, 0x0D);
		cout << "Hue5: Proces " << job_name << " nie zostal utworzony (proces juz istnieje/brak pamieci)" << endl;
		SetConsoleTextAttribute(hOut, 0x07);
		return false;
	}
	Proces* userprog = mPoz3->znajdzProces(job_name);
	if (!userprog) {
		SetConsoleTextAttribute(hOut, 0x0D);
		cout << "Hue5: Proces " << job_name << " nie zostal utworzony" << endl;
		SetConsoleTextAttribute(hOut, 0x07);
		return false;
	}

	for (unsigned int j = 0; j < interpreter.total_length; j++) {
		if (!mPamiec->ustaw_bajt(userprog->pierwszy_bajt_pamieci, j, interpreter.buffer[j])) {
			SetConsoleTextAttribute(hOut, 0x0D);
			cout << "Hue5: Pisanie do bajtu " << j << " nie powiodlo sie" << endl;
			SetConsoleTextAttribute(hOut, 0x07);
			return false;
		}
		else {
			//cout << "Pisanie do bajtu " << j << " powiodlo sie" << endl;
		}
	}
	SetConsoleTextAttribute(hOut, 0x0D);
	cout << "Hue5: Uruchomienie procesu " << job_name << endl;
	SetConsoleTextAttribute(hOut, 0x07);
	mPoz3->uruchomProces(job_name);
	mPlanista->nowyProces(userprog);
	return true;
}

void Supervisor::execute(Proces* proces) {
	if (!proces) {
		return; // brak procesu do wykonania
	}
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 0x0D);
	cout << "Hue5: Wykonuje rozkaz procesu " << proces->nazwa << endl;
	SetConsoleTextAttribute(hOut, 0x07);

	Interpreter::OpCode op = (Interpreter::OpCode)mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
	unsigned short param_count = (unsigned short)mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
	if (param_count == 0xFFFF) {
		cout << "Hue5: Blad odczytu. Przerywam wykonanie." << endl;
		//zatrzymajproces
		return;
	}
	//unsigned short param_length = (unsigned short)mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
	char* raw_param = NULL;
	unsigned int int_param;
	SetConsoleTextAttribute(hOut, 0x0D);
	cout << "Hue5: Proces " << proces->nazwa << " wykonuje rozkaz : ID = " << (char)op;
	/*if (param_length != 0) {
	raw_param = new char[param_length]();
	for (int i = 0; i < param_length; i++) {
	raw_param[i] = mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
	}
	cout << " PARAMS=" << raw_param;
	}*/
	cout << endl;
	SetConsoleTextAttribute(hOut, 0x07);

	// parameter preprocessing
	int reg1, len;
	string in_buffer;
	char out_buffer[10];

	switch (op) {
	case Interpreter::OpCode::SET:
	case Interpreter::OpCode::ADD:
	case Interpreter::OpCode::SUB:
	case Interpreter::OpCode::MUL:
	case Interpreter::OpCode::DIV:
		mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
		reg1 = mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++) - 64;
		switch (mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++)) {
		case sizeof(char) :
			int_param = mRejestr->getRejestr(mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++) - 64);
		case sizeof(unsigned int) :
			raw_param = new char[sizeof(unsigned int)]();
			for (int i = 0; i < sizeof(unsigned int); i++) {
				raw_param[i] = mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
			}
			memcpy(&int_param, raw_param, sizeof(unsigned int));
		}
		break;
	case Interpreter::OpCode::JUMP:
	case Interpreter::OpCode::JMPZ:
	case Interpreter::OpCode::JPNZ:
		len = mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
		raw_param = new char[len]();
		for (int i = 0; i < len; i++) {
			raw_param[i] = mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
		}
		memcpy(&int_param, raw_param, sizeof(unsigned int));
		break;
	case Interpreter::OpCode::IN1:
	case Interpreter::OpCode::IN2:
		mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
		reg1 = mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++) - 64;
		break;
	case Interpreter::OpCode::OUT1:
		len = mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
		raw_param = new char[len + 1]();
		for (int i = 0; i < len; i++) {
			raw_param[i] = mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
		}
		break;
	}

	switch (op) {
	case Interpreter::OpCode::SET:
		mRejestr->setRejestr(reg1, int_param);
		break;
	case Interpreter::OpCode::ADD:
		mRejestr->setRejestr(reg1, mRejestr->getRejestr(reg1) + int_param);
		break;
	case Interpreter::OpCode::SUB:
		mRejestr->setRejestr(reg1, mRejestr->getRejestr(reg1) - int_param);
		break;
	case Interpreter::OpCode::MUL:
		mRejestr->setRejestr(reg1, mRejestr->getRejestr(reg1) * int_param);
		break;
	case Interpreter::OpCode::DIV:
		mRejestr->setRejestr(reg1, mRejestr->getRejestr(reg1) / int_param);
		break;
	case Interpreter::OpCode::JUMP:
		SetConsoleTextAttribute(hOut, 0x0D);
		cout << "Hue5: JUMP " << int_param << endl;
		SetConsoleTextAttribute(hOut, 0x07);
		proces->mem_pointer = int_param;
		mPlanista->koniecProcesu(mRejestr);
		break;
	case Interpreter::OpCode::JMPZ:
		if (mRejestr->getRejestr(1) == 0) {
			SetConsoleTextAttribute(hOut, 0x0D);
			cout << "Hue5: JMPZ " << int_param << endl;
			SetConsoleTextAttribute(hOut, 0x07);
			proces->mem_pointer = int_param;
			mPlanista->koniecProcesu(mRejestr);
		} else {
			SetConsoleTextAttribute(hOut, 0x0D);
			cout << "Hue5: JMPZ " << int_param << " (ignoring)" << endl;
			SetConsoleTextAttribute(hOut, 0x07);
		}
		break;
	case Interpreter::OpCode::JPNZ:
		if (mRejestr->getRejestr(1) != 0) {
			SetConsoleTextAttribute(hOut, 0x0D);
			cout << "Hue5: JPNZ " << int_param << endl;
			SetConsoleTextAttribute(hOut, 0x07);
			proces->mem_pointer = int_param;
			mPlanista->koniecProcesu(mRejestr);
		}
		else {
			SetConsoleTextAttribute(hOut, 0x0D);
			cout << "Hue5: JPNZ " << int_param << " (ignoring)" << endl;
			SetConsoleTextAttribute(hOut, 0x07);
		}
		break;
	case Interpreter::OpCode::IN1:
		mPoz3->wyslijKomunikat("*IN", proces->nazwa);
		SetConsoleTextAttribute(hOut, 0x0D);
		cout << "Hue5: IN1" << endl;
		SetConsoleTextAttribute(hOut, 0x07);
		break;
	case Interpreter::OpCode::IN2:
		in_buffer = mPoz3->czytajKomunikat(proces->nazwa);
		int_param = atoi(in_buffer.c_str());
		mRejestr->setRejestr(reg1, int_param);
		SetConsoleTextAttribute(hOut, 0x0D);
		cout << "Hue5: IN2 " << int_param << " do R" << reg1 << endl;
		SetConsoleTextAttribute(hOut, 0x07);
		break;
	case Interpreter::OpCode::OUT1:
		if (len == 1) {
			sprintf(out_buffer, "%d", mRejestr->getRejestr(reg1));
			//drukarka1->PRINT(out_buffer);
			mPoz3->wyslijKomunikat("*OUT", string(out_buffer));
			//print from register
		}
		else {
			//drukarka1->PRINT(raw_param + 1); // omits first character
			mPoz3->wyslijKomunikat("*OUT", string(raw_param + 1));
		}
		SetConsoleTextAttribute(hOut, 0x0D);
		cout << "Hue5: OUT: " << raw_param << endl;
		SetConsoleTextAttribute(hOut, 0x07);
		break;
	case Interpreter::OpCode::BYE:
		SetConsoleTextAttribute(hOut, 0x0D);
		cout << "Hue5: BYE" << endl;
		SetConsoleTextAttribute(hOut, 0x07);
		mPoz3->zatrzymajProces(proces->nazwa);
		mPlanista->koniecProcesu(mRejestr);
		mPoz3->usunProces(proces->nazwa);
		break;
	default:
		SetConsoleTextAttribute(hOut, 0x0D);
		cout << "Hue5: Nieprawidlowy rozkaz. Proces zostanie usuniety" << endl;
		SetConsoleTextAttribute(hOut, 0x07);
		mPoz3->zatrzymajProces(proces->nazwa);
		mPlanista->koniecProcesu(mRejestr);
		mPoz3->usunProces(proces->nazwa);
	}

	if (raw_param) {
		delete[] raw_param;
	}
	if (proces) {
		proces->t_obslugi++;
	}
}

void Supervisor::checkMessages() {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	string komunikat;
	vector<string> x;
	for (int i = 0; i < 3; i++) {
		komunikat = mPoz3->czytajKomunikat(Supervisor::names[i]);
		if (!komunikat.empty()) {
			SetConsoleTextAttribute(hOut, 0x0D);
			cout << "Hue5: " << Supervisor::names[i] << " otrzymal komunikat: " << komunikat << endl;
			SetConsoleTextAttribute(hOut, 0x07);
			switch (i) {
			case 0: // ibsup
				x = split(komunikat, ' ');
				SetConsoleTextAttribute(hOut, 0x0D);
				cout << "Hue5: Zakonczono proces uzytkownika: " << x[1] << endl;
				SetConsoleTextAttribute(hOut, 0x07);
				break;
			case 1: // in
				mPoz3->wyslijKomunikat(komunikat, czytnik1->READ_String_File("wejscie.txt"));
				SetConsoleTextAttribute(hOut, 0x0D);
				cout << "Hue5: Wczytano wejscie dla procesu " << komunikat << endl;
				SetConsoleTextAttribute(hOut, 0x07);
				break;
			case 2:
				drukarka1->PRINT((char *)komunikat.c_str());
				SetConsoleTextAttribute(hOut, 0x0D);
				cout << "Hue5: Przekazano komunikat do druku: " << komunikat << endl;
				SetConsoleTextAttribute(hOut, 0x07);
				break;
			}
		}
	}
}

void Supervisor::wyswietlDrukarka1(){
	drukarka1->wyswietl();
}

void Supervisor::wyczyscDrukarka1()
{
	drukarka1->wyczyscDrukarka();
}