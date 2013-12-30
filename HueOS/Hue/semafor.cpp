#include "globLev1.h"

Semafor::Semafor(int i){
	wart = i;
}


void Semafor::pWait(Proces* &x){
	//Operacja czekania - pro�ba o dost�p
	if(wart > 0){
		string text = "Semafor: Operacja P: Zezwalam na uzycie zasobow, bo wart = ";
		text += wart;
		textLev1(true, text);
		x->semaforReceiver = 1; //1 = zezwalam
	} else{
		string text = "Semafor: Operacja P: Dodaje proces do listy oczekujacych, bo wart = ";
		text += wart;
		textLev1(true, text);
		listaCzekaj.push_back(x);
		x->semaforReceiver = -1; // -1 = oczekuj� przed semaforem na dane
	}
	wart--;
} 

void Semafor::vSignal(Proces* &x){
	//Operacja sygna�u - po u�yciu zasob�w
	wart++;
	string text = "Semafor: Operacja V: Wysylam sygnal do czekajacych procesow, wart = ";
	text += wart;
	textLev1(true, text);
	odpalCzekajacy();
}

void Semafor::odpalCzekajacy(){
	//Funkcja odpalona po operacji V - najpierw procesy oczekuj�ce dostan� dost�p
	if(listaCzekaj.empty() == false){
		Proces* buf = listaCzekaj.front();
		string text = "Semafor: Odpalam proces oczekujacy, id [";
		text += buf->id;
		text += "]";
		textLev1(true, text);
		buf->semaforReceiver = 1;
		
		listaCzekaj.pop_front();
	} else {
		string text = "Semafor: Brak czekajacych procesow pod semaforem, wart = ";
		text += wart;
		textLev1(true, text);
	}
}

bool Semafor::gotowy(Proces* &x){
	//Funkcja pomocnicza - szybkie sprawdzenie czy proces dosta� zezwolenie od semafora na dost�p do danych

	if(x->semaforReceiver == 1){
		x->semaforReceiver = 0; //nie czekam przed semaforem na dane
		textLev1(true, "Proces moze uzyc zasobow");
		return true;
	} else if(x->semaforReceiver == 0){

		textLev1(false, "Proces nie jest w kolejce do semafora");
		return false;
	} else {
		textLev1(false, "Bledna wartosc semaforReceiver = " + x->semaforReceiver);
		return false;
	}
}