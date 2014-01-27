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
	string job_cards[] = {"1.job"};
	// uruchom procesy systemowe
	for (int i = 0; i < 3; i++) {
		mPoz3->dodajPCB(new SysProces(i + 1, Supervisor::names[i]), true);
	}

	JOB job; // hey, let's ignore job.job :v

	// parsuj $JOB
	for (int i = 0; i < 1; i++) {
		loadJob(job_cards[i]);
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
	return true;
}

void Supervisor::execute(Proces* proces) {
	if (!proces) {
		return; // brak procesu do wykonania
	}
	HANDLE hOut;
	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hOut, 0x0D);
	cout << "Hue5: Wykonuje rozkaz procesu " << proces->nazwa << endl;
	SetConsoleTextAttribute( hOut, 0x07);

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
	int reg1, reg2;

	switch (op) {
	case Interpreter::OpCode::SET:
	case Interpreter::OpCode::ADD:
	case Interpreter::OpCode::SUB:
	case Interpreter::OpCode::MUL:
	case Interpreter::OpCode::DIV:
		mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++);
		reg1 = mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++) - 64;
		switch (mPamiec->pobierz_bajt(proces->pierwszy_bajt_pamieci, proces->mem_pointer++)) {
		case sizeof(char):
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
		memcpy(&int_param, raw_param, sizeof(unsigned int));
		cout << int_param << endl;
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
	case Interpreter::OpCode::JMPZ:
	case Interpreter::OpCode::JPNZ:
	case Interpreter::OpCode::IN1:
	case Interpreter::OpCode::IN2:
	case Interpreter::OpCode::OUT1:
	case Interpreter::OpCode::BYE:
		SetConsoleTextAttribute( hOut, 0x0D);
		cout << "Hue5: Cos uzytecznego! Olewam!" << endl;
		SetConsoleTextAttribute( hOut, 0x07);
		break;
	default:
		SetConsoleTextAttribute( hOut, 0x0D);
		cout << "Hue5: Nieprawidlowy rozkaz. Proces zostanie usuniety" << endl;
		SetConsoleTextAttribute( hOut, 0x07);
		// fixme usun proces
	}

	if (raw_param) {
		delete[] raw_param;
	}
	proces->t_obslugi++;
}

void Supervisor::checkMessages() {
	HANDLE hOut;
	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	
	string komunikat;
	vector<string> x;
	for (int i = 0; i < 3; i++) {
		komunikat = mPoz3->czytajKomunikat(Supervisor::names[i]);
		if (!komunikat.empty()) {
			SetConsoleTextAttribute( hOut, 0x0D);
			cout << "Hue5: " << Supervisor::names[i] << " otrzymal komunikat: " << komunikat << endl;
			SetConsoleTextAttribute( hOut, 0x07);
			switch (i) {
			case 0: // ibsup
				x = split(komunikat, ' ');
				SetConsoleTextAttribute( hOut, 0x0D);
				cout << "Hue5: Zakonczono proces uzytkownika: " << x[1] << endl;
				SetConsoleTextAttribute( hOut, 0x07);
				break;
			case 1: // in
				// pobrac tekst (z pliku podanego w komunikacie?),
				// wyslac komunikat do nadawcy (czyli kogo :v)
				break;
			case 2:
				drukarka1->PRINT((char *)komunikat.c_str());
				SetConsoleTextAttribute( hOut, 0x0D);
				cout << "Hue5: Przekazano komunikat do druku: " << komunikat << endl;
				SetConsoleTextAttribute( hOut, 0x07);
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