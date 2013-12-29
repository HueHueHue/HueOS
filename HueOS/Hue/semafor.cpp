#include "globLev1.h"

Semafor::Semafor(int i){
	wart = i;
}


void Semafor::pWait(Proces* &x){
	if(wart > 0){
		textLev1(true, "Semafor: Operacja P: Zezwalam na uzycie zasobow, bo wart = " + wart);
		x->semaforReceiver = 1;
	} else{
		textLev1(true, "Semafor: Operacja P: Dodaje proces do listy oczekujacych, bo wart = " + wart);
		listaCzekaj.push_back(x);
		x->semaforReceiver = -1;
	}
	wart--;
} 

void Semafor::vSignal(Proces* &x){
	wart++;
	textLev1(true, "Semafor: Operacja V: Wysylam sygnal do czekajacych procesow, wart = " + wart);
	odpalCzekajacy();
}

void Semafor::odpalCzekajacy(){
	if(listaCzekaj.empty() == false){
		Proces* buf = listaCzekaj.front();
		textLev1(true, "Semafor: Odpalam proces oczekujacy, id [" + buf->id /*+ "]"*/);	//INT + STRING
		buf->semaforReceiver = 1;
		
		listaCzekaj.pop_front();
	} else {
		textLev1(true, "Semafor: Brak czekajacych procesow pod semaforem, wart = " + wart);
	}
}

bool Semafor::gotowy(Proces* &x){
	if(x->semaforReceiver == 1){
		x->semaforReceiver = 0;
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