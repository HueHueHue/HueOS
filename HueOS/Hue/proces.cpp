#include "globLev1.h"

Proces::Proces(int id, string nazwa, Proces* grupaNext, Proces* grupaLast, Proces* wszystkieNext, Proces* wszystkieLast, int t_przewidywany_next){
	this->id = id;
	this->nazwa = nazwa;
	this->grupaNext = grupaNext;
	this->grupaLast = grupaLast;
	this->wszystkieNext = wszystkieNext;
	this->wszystkieLast = wszystkieLast;
	this->t_przewidywany_next = t_przewidywany_next;


	stopped = 0;
	blocked = 0;
	running = 0;
	semaforCommon = 0;
	semaforReceiver = 0;

	przewidziany = false; 
	t_przewidywany = 1; 

	t_wykonania = 0; 	
	t_obslugi = 0; 
}