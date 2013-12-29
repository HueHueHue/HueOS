#include "globLev1.h"

Planista::Planista(){
	startWszystkie = NULL;
	najlepszyCzas = 0;
	najlepszyCzasProces = NULL;
}

void Planista::startCykl(){
	Proces* bufor = startWszystkie;
	if(bufor != NULL && najlepszyCzasProces == NULL){
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
		textLev1(true, "Zakoñczono obliczanie czasu przewidywanego dla wszystkich procesów aktywnych");
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

		if(najlepszyCzasProces != NULL){
			textLev1(true, "Wybrano proces o najkrótszym czasie wykonywania" /*+ najlepszyCzasProces->id + "]"*/);	//INT + STRING
			najlepszyCzasProces->running = 1;
			//WYKONAJ najlepszyCzasProces
		} else {
			textLev1(true, "Brak procesów gotowych do wykonania");
		}

	} else {
		if(bufor == NULL)
			textLev1(true, "Brak procesów na liœcie");
		if(najlepszyCzasProces != NULL)
			textLev1(true, "Proces wybrany, w trakcie wykonywania");
	}
}


void Planista::koniecProcesu(){
	if(najlepszyCzasProces != NULL){
		textLev1(true, "Proces zakonczy³ dzia³anie");
		najlepszyCzasProces->przewidziany = false;
		najlepszyCzasProces->t_przewidywany = najlepszyCzasProces->t_przewidywany_next;
		najlepszyCzasProces->t_przewidywany_next = NULL;
		najlepszyCzasProces->t_wykonania = najlepszyCzasProces->t_obslugi;
		najlepszyCzasProces->running = 0;

		najlepszyCzasProces = NULL;
		najlepszyCzas = 0;
	} else {
		textLev1(false, "Nie mozna zakonczyc procesu - brak odpalonego procesu");
	}
}

void Planista::nowyProces(Proces* nowyProces){
	textLev1(true, "Pojawi³ siê nowy aktywny proces! Testujê jego przewidywany czas wykonywania...");
	if(nowyProces->stopped == 0 && nowyProces->blocked == 0){
		if(nowyProces->przewidziany == false){
			nowyProces->t_przewidywany_next = 0.5 * nowyProces->t_przewidywany + 0.5 * nowyProces-> t_wykonania;
			nowyProces->przewidziany = 1;
		}
		if(nowyProces->t_przewidywany_next < najlepszyCzasProces->t_przewidywany_next - najlepszyCzasProces->t_obslugi){
			textLev1(true, "Nowy proces ma mniejszy przewidywany czas. Wyw³aszczam stary i uruchamian nowy");
			//ZATRZYMAJ najlepszyCzasProces
			najlepszyCzasProces->running = 0;
			//ZAPISZ STAN najlepszyCzasProces

			najlepszyCzasProces = nowyProces;
			//WYKONAJ najlepszyCzasProces
			najlepszyCzasProces->running = 1;
		} else {
			textLev1(true, "Nowy proces ma wiêkszy przewydywany czas. Kontynuujê wykonywanie starego");
		}
	}
}