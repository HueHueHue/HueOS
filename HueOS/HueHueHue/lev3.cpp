#include "../global.h"
#include"../Hue/globLev1.h"

#include "../HueHue/pamiec.h"
#include "lev3.h"

Lev3::Lev3(Proces* procesList, Rejestr* mRejestr, pamiec* mPamiec){
	this->procesList = procesList;
	this->mRejestr = mRejestr;
	this->mPamiec = mPamiec;
	IDCounter = 0;
	HANDLE hOut;
	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hOut, 0x0B);
	cout << "Hue3: Lev3 utworzony. Modul wyzszy wita" << endl;
	SetConsoleTextAttribute( hOut, 0x07);
}

void Lev3::dodajProces(string Nazwa, int t_przewidywany_next, unsigned short rozmiar){
	IDCounter ++;
	HANDLE hOut;
	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hOut, 0x0B);
	cout << "Hue3: Dodaje nowy proces " << Nazwa << endl;
	SetConsoleTextAttribute( hOut, 0x07);
	Proces* bufor = procesList;
	bool nazwauzyta = false;
	if(bufor->wszystkieNext != 0){
		do {
			if(bufor->nazwa == Nazwa){
				nazwauzyta = true;
				break;
			}
			bufor = bufor->wszystkieNext;
		} while(bufor->wszystkieNext != procesList);
	} else {
		nazwauzyta = false;
	}
	if(nazwauzyta == true){
		HANDLE hOut;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hOut, 0x0B);
		cout << "Hue3: Nazwa procesu jest uzyta!" << endl;
		SetConsoleTextAttribute( hOut, 0x07);
	} else {
		HANDLE hOut;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hOut, 0x0B);
		cout << "Hue3: Nazwa procesu jest wolna!" << endl;
		SetConsoleTextAttribute( hOut, 0x07);
		Proces* nowyProces = new Proces(IDCounter, Nazwa, t_przewidywany_next);

		//ODPALENIE PROGRAMU PRZYDZIELAJACEGO PAMIEC
		unsigned short pierwszy_bajt = mPamiec->zajmij_pamiec(rozmiar);
		if(pierwszy_bajt == 0xFFFF){
			hOut = GetStdHandle( STD_OUTPUT_HANDLE );
			SetConsoleTextAttribute( hOut, 0x0B);
			cout << "Hue3: Blad - pamiec nie przydzielona, anuluje!" << endl;
			SetConsoleTextAttribute( hOut, 0x07);
			wyslijKomunikat("*IBSUP", "BRAKPAMIECI " + Nazwa);
			delete nowyProces;
		} else {
			HANDLE hOut;
			hOut = GetStdHandle( STD_OUTPUT_HANDLE );
			SetConsoleTextAttribute( hOut, 0x0B);
			cout << "Hue3: Przydzielanie pamieci zakonczone sukcesem, dodaje blok PCB" << endl;
			SetConsoleTextAttribute( hOut, 0x07);
			nowyProces->auto_storage_size = rozmiar;
			nowyProces->pierwszy_bajt_pamieci = pierwszy_bajt;
			dodajPCB(nowyProces,0);
		}
	}


}

void Lev3::usunProces(string nazwa){
	
	Proces* doKasacji = znajdzProces(nazwa);

	if(doKasacji == 0){
		HANDLE hOut;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hOut, 0x0B);
		cout << "Hue3: Brak procesu o takiej nazwie" << endl;
		SetConsoleTextAttribute( hOut, 0x07);
	} else {
		//PROGRAM XZ - zatrzymanie procesu
		HANDLE hOut;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hOut, 0x0B);
		cout << "Hue3: Kasuje proces" << endl;
		SetConsoleTextAttribute( hOut, 0x07);
		zatrzymajProces(nazwa);
		usunPCB(doKasacji);
		mPamiec->zwolnij_pamiec(doKasacji->pierwszy_bajt_pamieci);

		//Kasowanie komunikatow

		delete doKasacji;
	}
}
void Lev3::stop(string nazwa){
	Proces* x = znajdzProces(nazwa);
	if(x != 0){
		while(!x->komunikaty.empty()){
			x->komunikaty.pop_front();
		}
	}
		HANDLE hOut;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hOut, 0x0B);
		cout << "Hue3: Zakonczono wykonywanie procesu" << endl;
		SetConsoleTextAttribute( hOut, 0x07);
	wyslijKomunikat("*IBSUP", "KONIEC " + nazwa);

}
void Lev3::dodajPCB(Proces* nowy, bool zewnetrzny){

	if(procesList->wszystkieLast == 0 && procesList->wszystkieNext == 0){
		//Pierwszy proces
		procesList->wszystkieLast = nowy;
		procesList->wszystkieNext = nowy;
		nowy->wszystkieLast = procesList;
		nowy->wszystkieNext = procesList;
	} else{
		nowy->wszystkieNext = procesList;
		nowy->wszystkieLast = procesList->wszystkieLast;
		procesList->wszystkieLast->wszystkieNext = nowy;
		procesList->wszystkieLast = nowy;
	}
		HANDLE hOut;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hOut, 0x0B);
		if (zewnetrzny) {
			IDCounter++;
			cout << "Hue3: PCB systemowy dodany" << endl;
		} else {
			cout << "Hue3: PCB dodany" << endl;
		}
		SetConsoleTextAttribute( hOut, 0x07);
}
/*
void Lev3::dodajPCB(Proces* nowy, bool zewnetrzny){
	if (zewnetrzny) {
		IDCounter++;
	}
		HANDLE hOut;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hOut, 0x0B);
		cout << "Hue3: PCB systemowy dodany" << endl;
		SetConsoleTextAttribute( hOut, 0x07);
}
*/
void Lev3::usunPCB(Proces* doKasacji){
	if(procesList->wszystkieLast == doKasacji && procesList->wszystkieNext == doKasacji){
		//Pierwszy proces
		procesList->wszystkieLast = 0;
		procesList->wszystkieNext = 0;

	} else{
		doKasacji->wszystkieNext->wszystkieLast = doKasacji->wszystkieLast;
		doKasacji->wszystkieLast->wszystkieNext = doKasacji->wszystkieNext;

		doKasacji->wszystkieNext = 0;
		doKasacji->wszystkieLast = 0;

	}
		HANDLE hOut;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hOut, 0x0B);
		cout << "Hue3: PCB usuniety" << endl;
		SetConsoleTextAttribute( hOut, 0x07);
}

Proces* Lev3::znajdzProces(string nazwa){
	Proces* bufor = procesList;
	bool znalazlem = false;
	if(bufor->wszystkieNext !=0){
		do {
			if(bufor->nazwa == nazwa){
				znalazlem = true;
				break;
			}
			bufor = bufor->wszystkieNext;
		} while(bufor != procesList);
	} else {
		znalazlem = false;
	}
	if(znalazlem){
		return bufor;
	} else {
		return 0;
	}

}
string Lev3::czytajKomunikat(string nazwa){
	Proces* x = znajdzProces(nazwa);
	string komunikat = "";
	if(x != 0){
		if(!x->komunikaty.empty()){
		komunikat = x->komunikaty.front();

		x->komunikaty.pop_front();
		HANDLE hOut;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hOut, 0x0B);
		cout << "Hue3: Komunikat pobrany i zwrocony" << endl;
		SetConsoleTextAttribute( hOut, 0x07);
		} else {
			HANDLE hOut;
			hOut = GetStdHandle( STD_OUTPUT_HANDLE );
			SetConsoleTextAttribute( hOut, 0x0B);
			cout << "Hue3: Brak komunikatow" << endl;
			SetConsoleTextAttribute( hOut, 0x07);
		}
	}
		
	return komunikat;
}
void Lev3::wyslijKomunikat(string nazwa, string text){
	Proces* x = znajdzProces(nazwa);
	if(x != 0){
		x->komunikaty.push_back(text);
		HANDLE hOut;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hOut, 0x0B);
		cout << "Hue3: Komunikat wyslany" << endl;
		SetConsoleTextAttribute( hOut, 0x07);
	}
}
void Lev3::uruchomProces(string nazwa){
	Proces* proc = znajdzProces(nazwa);
	if(proc !=0){
		proc->wczytajStan(mRejestr);
		proc->stopped = 0;
	} else {
		HANDLE hOut;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hOut, 0x0B);
		cout << "Hue3: Nie znaleziono procesu: " << nazwa << endl;
		SetConsoleTextAttribute( hOut, 0x07);
	}
}
void Lev3::zatrzymajProces(string nazwa){
	Proces* proc = znajdzProces(nazwa);
	if(proc !=0){
		if(proc->in_smc == 0){
			proc->zapiszStan(mRejestr);
			proc->stopped = 1;
		} else {
			proc->stop_waiting = 1;
		}
	} else {
		HANDLE hOut;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hOut, 0x0B);
		cout << "Hue3: Nie znaleziono procesu: " << nazwa << endl;
		SetConsoleTextAttribute( hOut, 0x07);
	}
}
