#include "../global.h"
#include "lev3.h"
#include"../Hue/globLev1.h"
#include "../HueHue/pamiec.h"
Lev3::Lev3(Proces* procesList, Rejestr* mRejestr, pamiec* mPamiec){
	this->procesList = procesList;
	this->mRejestr = mRejestr;
	this->mPamiec = mPamiec;
	IDCounter = 0;
}

void Lev3::dodajProces(string Nazwa, int t_przewidywany_next, unsigned short rozmiar){
	IDCounter ++;

	Proces* bufor = procesList;
	bool nazwauzyta = false;
	do {
		if(bufor->nazwa == Nazwa){
			nazwauzyta = true;
			break;
		}
		bufor = bufor->wszystkieNext;
	} while(bufor->wszystkieNext != procesList);

	if(nazwauzyta == true){
		cout << "Nazwa procesu jest uzyta!" << endl;
	} else {
		cout << "Nazwa procesu jest wolna!" << endl;
		Proces* nowyProces = new Proces(IDCounter, Nazwa, t_przewidywany_next);

		//ODPALENIE PROGRAMU PRZYDZIELAJACEGO PAMIEC
		if(mPamiec->zajmij_pamiec(rozmiar) == 0xFFFF){
			cout << "Blad - pamiec nie przydzielona, anuluje!" << endl;
			delete nowyProces;
		} else {

		dodajPCB(nowyProces);
		}
	}


}

void Lev3::usunProces(string nazwa){
	
	Proces* doKasacji = znajdzProces(nazwa);

	if(doKasacji == 0){
		cout << "Brak procesu o takiej nazwie" << endl;
	} else {
		//PROGRAM XZ - zatrzymanie procesu
		
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

	wyslijKomunikat("*IBSUP", "KONIEC " + nazwa);

}
void Lev3::dodajPCB(Proces* nowy){
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

}
void Lev3::dodajPCB(Proces* nowy, bool zewnetrzny){
	if (zewnetrzny) {
		IDCounter++;
	}
}

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

}

Proces* Lev3::znajdzProces(string nazwa){
	Proces* bufor = procesList;
	bool znalazlem = false;
	do {
		if(bufor->nazwa == nazwa){
			znalazlem = true;
			break;
		}
		bufor = bufor->wszystkieNext;
	} while(bufor->wszystkieNext != procesList);

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
		} else {
			cout << "Blad - brak komunikatow" << endl;
		}
	}
	return komunikat;
}
void Lev3::wyslijKomunikat(string nazwa, string text){
	Proces* x = znajdzProces(nazwa);
	if(x != 0){
		x->komunikaty.push_back(text);
	}
}
void Lev3::uruchomProces(string nazwa){
	Proces* proc = znajdzProces(nazwa);
	if(proc !=0){
		proc->wczytajStan(mRejestr);
		proc->stopped = 0;
	} else {
		cout << "Nie znaleziono procesu o nazwie" << nazwa;
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
		cout << "Nie znaleziono procesu o nazwie" << nazwa;
	}
}
