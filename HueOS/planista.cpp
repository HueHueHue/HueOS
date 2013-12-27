#include "global.h"
#include "proces.h"
#include "planista.h"

Planista::Planista(Proces* startWszystkie){
	this->startWszystkie = startWszystkie;
}

void Planista::startCykl(){
	Proces* bufor = startWszystkie;
	if(bufor != NULL){
		//wyliczanie czasu
		do {
			if(bufor->blocked == 0 && bufor->stopped == 0){
				if(bufor->przewidziany == 0){
					bufor->t_przewidywany_next = 0.5 * bufor->t_przewidywany + 0.5 * bufor-> t_wykonania;
					bufor->przewidziany = 1;
				}
			}
			bufor = bufor->wszystkieNext;
		} while(bufor->wszystkieNext != startWszystkie);
		//wyszukiwanie najszybszego
		

		do {
			if(bufor->blocked == 0 && bufor->stopped == 0){
				if(bufor->przewidziany == 1){
					if(najlepszyCzas == 0){
						najlepszyCzas = bufor->t_przewidywany_next - bufor->t_obs³ugi;
						najlepszyCzasProces = bufor;
					} else {
						if(najlepszyCzas < bufor->t_przewidywany_next - bufor->t_obs³ugi){
							najlepszyCzas = bufor->t_przewidywany_next - bufor->t_obs³ugi;
							najlepszyCzasProces = bufor;
						}
					}
				}
			}
			bufor = bufor->wszystkieNext;
		} while(bufor->wszystkieNext != startWszystkie);

		//WYKONAJ najlepszyCzasProces

	}
}


void Planista::koniecProcesu(){
	najlepszyCzasProces->przewidziany = false;
	najlepszyCzasProces->t_przewidywany = najlepszyCzasProces->t_przewidywany_next;
	najlepszyCzasProces->t_przewidywany_next = NULL;
	najlepszyCzasProces->t_wykonania = najlepszyCzasProces->t_obs³ugi;
}

void Planista::nowyProces(Proces* nowyProces){
	if(nowyProces->stopped == 0 && nowyProces->blocked == 0;){
		if(nowyProces->przewidziany == false){
			nowyProces->t_przewidywany_next = 0.5 * nowyProces->t_przewidywany + 0.5 * nowyProces-> t_wykonania;
			nowyProces->przewidziany = 1;
		}
		if(nowyProces->t_przewidywany_next < najlepszyCzasProces->t_przewidywany_next - najlepszyCzasProces->t_obs³ugi){
			//ZATRZYMAJ najlepszyCzasProces
			//ZAPISZ STAN najlepszyCzasProces

			najlepszyCzasProces = nowyProces;
			//WYKONAJ najlepszyCzasProces
		}
	}
}