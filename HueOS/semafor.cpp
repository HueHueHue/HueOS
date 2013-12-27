#include "global.h"
#include "proces.h"
#include "semafor.h"


Semafor::Semafor(int i){
	wart = i;
}


void Semafor::pWait(Proces x){
	if(wart > 0){
		//WYŒLIJ SYGNA£ DO STARTU
	} else{
		listaCzekaj.push_back(&x);
		//WYŒLIJ SYGNA£ CZEKAJ
	}
	wart--;
} 

void Semafor::vSignal(Proces x){
	wart++;
	odpalCzekajacy();
}

void Semafor::odpalCzekajacy(){
	if(listaCzekaj.empty() == false){
		listaCzekaj.front;
		//WYŒLIJ SYGNA£ DO STARTU
		listaCzekaj.pop_front();
	}
}