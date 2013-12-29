#include "globLev1.h"

Semafor::Semafor(int i){
	wart = i;
}


void Semafor::pWait(Proces* &x){
	if(wart > 0){
		textLev1(true, "Semafor: Operacja P: Zezwalam na u�ycie zasob�w, bo wart = " + wart);
		x->semaforReceiver = 1;
	} else{
		textLev1(true, "Semafor: Operacja P: Dodaj� proces do listy oczekuj�cych, bo wart = " + wart);
		listaCzekaj.push_back(x);
		x->semaforReceiver = -1;
	}
	wart--;
} 

void Semafor::vSignal(Proces* &x){
	wart++;
	textLev1(true, "Semafor: Operacja V: Wysy�am sygna� do czekaj�cych proces�w, wart = " + wart);
	odpalCzekajacy();
}

void Semafor::odpalCzekajacy(){
	if(listaCzekaj.empty() == false){
		Proces* buf = listaCzekaj.front();
		textLev1(true, "Semafor: Odpalam proces oczekuj�cy, id [" + buf->id /*+ "]"*/);	//INT + STRING
		buf->semaforReceiver = 1;
		
		listaCzekaj.pop_front();
	} else {
		textLev1(true, "Semafor: Brak czekaj�cych proces�w pod semaforem, wart = " + wart);
	}
}

bool Semafor::gotowy(Proces* &x){
	if(x->semaforReceiver == 1){
		x->semaforReceiver = 0;
		textLev1(true, "Proces mo�e u�y� zasob�w");
		return true;
	} else if(x->semaforReceiver == 0){

		textLev1(false, "Proces nie jest w kolejce do semafora");
		return false;
	} else {
		textLev1(false, "B��dna warto�� semaforReceiver = " + x->semaforReceiver);
		return false;
	}
}