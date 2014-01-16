#include "globLev1.h"

Proces::Proces(int id, string nazwa, int t_przewidywany_next){
	this->id = id;
	this->nazwa = nazwa;
	//this->grupaNext = grupaNext;
	//this->grupaLast = grupaLast;
	this->wszystkieNext = 0;
	this->wszystkieLast = 0;
	this->t_przewidywany_next = t_przewidywany_next;


	stopped = 1;
	blocked = 0;
	running = 0;
	semaforCommon = 0;
	semaforReceiver = 0;
	stop_waiting = 0;

	przewidziany = true; 
	t_przewidywany = 0; 

	t_wykonania = 0; 	
	t_obslugi = 0; 

	in_smc = 0;
}

void Proces::zapiszStan(Rejestr* &mRejestr){
	for(int i=0;i<4;i++){
		old_registers[i] = mRejestr->getRejestr(i);
	}
}
void Proces::wczytajStan(Rejestr* &mRejestr){
	for(int i=0;i<4;i++){
		 mRejestr->setRejestr(i, old_registers[i]);
	}
}