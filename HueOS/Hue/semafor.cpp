#include "../global.h"
#include "proces.h"
#include "semafor.h"


Semafor::Semafor(int i){
	wart = i;
}


void Semafor::pWait(Proces x){
	if(wart > 0){
		x.semaforReceiver = 1;
	} else{
		listaCzekaj.push_back(&x);
		x.semaforReceiver = -1;
	}
	wart--;
} 

void Semafor::vSignal(Proces x){
	wart++;
	odpalCzekajacy();
}

void Semafor::odpalCzekajacy(){
	if(listaCzekaj.empty() == false){
		Proces buf = listaCzekaj.front;
		buf.semaforReceiver = 1;
		
		listaCzekaj.pop_front();
	}
}

bool Semafor::gotowy(Proces x){
	if(x.semaforReceiver == 1){
		x.semaforReceiver = 0;
		return true;
	} else if(x.semaforReceiver == 0){
		cout << "Blad: proces nie jest w kolejce do semafora" << endl;
		return false;
	} else {
		return false;
	}
}