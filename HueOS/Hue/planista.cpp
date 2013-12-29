#include "globLev1.h"

Planista::Planista(Proces* startWszystkie){
	this->startWszystkie = startWszystkie;
	najlepszyCzas = 0;
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
						najlepszyCzas = bufor->t_przewidywany_next - bufor->t_obslugi;
						najlepszyCzasProces = bufor;
					} else {
						if(najlepszyCzas < bufor->t_przewidywany_next - bufor->t_obslugi){
							najlepszyCzas = bufor->t_przewidywany_next - bufor->t_obslugi;
							najlepszyCzasProces = bufor;
						}
					}
				}
			}
			bufor = bufor->wszystkieNext;
		} while(bufor->wszystkieNext != startWszystkie);

		najlepszyCzasProces->running = 1;
		//WYKONAJ najlepszyCzasProces

	} else {
		textLev1(51);
	}
}


void Planista::koniecProcesu(){
	najlepszyCzasProces->przewidziany = false;
	najlepszyCzasProces->t_przewidywany = najlepszyCzasProces->t_przewidywany_next;
	najlepszyCzasProces->t_przewidywany_next = NULL;
	najlepszyCzasProces->t_wykonania = najlepszyCzasProces->t_obslugi;
	najlepszyCzasProces->running = 0;

	najlepszyCzas = 0;
}

void Planista::nowyProces(Proces* nowyProces){
	if(nowyProces->stopped == 0 && nowyProces->blocked == 0){
		if(nowyProces->przewidziany == false){
			nowyProces->t_przewidywany_next = 0.5 * nowyProces->t_przewidywany + 0.5 * nowyProces-> t_wykonania;
			nowyProces->przewidziany = 1;
		}
		if(nowyProces->t_przewidywany_next < najlepszyCzasProces->t_przewidywany_next - najlepszyCzasProces->t_obslugi){
			//ZATRZYMAJ najlepszyCzasProces
			najlepszyCzasProces->running = 0;
			//ZAPISZ STAN najlepszyCzasProces

			najlepszyCzasProces = nowyProces;
			//WYKONAJ najlepszyCzasProces
			najlepszyCzasProces->running = 1;
		}
	}
}