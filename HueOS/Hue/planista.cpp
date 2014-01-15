#include "globLev1.h"

Planista::Planista(Proces* procesList){
	this-> procesList = procesList;
	najlepszyCzas = 0;
	najlepszyCzasProces = NULL;
}

void Planista::startCykl(){
	Proces* bufor = procesList;
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
		} while(bufor->wszystkieNext != procesList);
		textLev1(true, "Zakonczono obliczanie czasu przewidywanego dla wszystkich procesow aktywnych");
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
		} while(bufor->wszystkieNext != procesList);

		if(najlepszyCzasProces != NULL){
			string text = "Wybrano proces o najkrotszym czasie wykonywania [";
			
			char str[10];
			itoa(najlepszyCzasProces->id,str,10);
			text += str;
			text += "]";
			textLev1(true, text);
			najlepszyCzasProces->running = 1;
			//WYKONAJ najlepszyCzasProces
		} else {
			textLev1(true, "Brak procesow gotowych do wykonania");
		}

	} else {
		if(bufor == NULL)
			textLev1(true, "Brak procesow na liscie");
		if(najlepszyCzasProces != NULL)
			textLev1(true, "Proces wybrany, w trakcie wykonywania");
	}
}


void Planista::koniecProcesu(){
	if(najlepszyCzasProces != NULL){
		textLev1(true, "Proces zakonczyl dzialanie");
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
	textLev1(true, "Pojawil sie nowy aktywny proces! Testuje jego przewidywany czas wykonywania...");
	if(nowyProces->stopped == 0 && nowyProces->blocked == 0){
		if(nowyProces->przewidziany == false){
			nowyProces->t_przewidywany_next = 0.5 * nowyProces->t_przewidywany + 0.5 * nowyProces-> t_wykonania;
			nowyProces->przewidziany = 1;
		}
		if(nowyProces->t_przewidywany_next < najlepszyCzasProces->t_przewidywany_next - najlepszyCzasProces->t_obslugi){
			textLev1(true, "Nowy proces ma mniejszy przewidywany czas. Wywlaszczam stary i uruchamian nowy");
			//ZATRZYMAJ najlepszyCzasProces
			najlepszyCzasProces->running = 0;
			//ZAPISZ STAN najlepszyCzasProces

			najlepszyCzasProces = nowyProces;
			//WYKONAJ najlepszyCzasProces
			najlepszyCzasProces->running = 1;
		} else {
			textLev1(true, "Nowy proces ma wiekszy przewydywany czas. Kontynuuje wykonywanie starego");
		}
	}
}

void Planista::test(){
	//Proces(int id, string nazwa, Proces* grupaNext, Proces* grupaLast, Proces* wszystkieNext, Proces* wszystkieLast, int t_przewidywany_next);
	Proces* proces1 = new Proces(1, "Test1", 0, 0, 0, 0, 15);
	procesList = proces1;
	Proces* proces2 = new Proces(2, "Test1", 0, proces1, 0, proces1, 15);
	Proces* proces3 = new Proces(3, "Test1", 0, proces2, 0, proces2, 15);
	proces1->grupaLast = proces3;
	proces1->grupaNext = proces2;
	proces1->wszystkieLast = proces3;
	proces1->wszystkieNext = proces2;
	proces2->grupaNext = proces3;
	proces2->wszystkieNext = proces3;
	proces3->grupaNext = proces1;
	proces3->wszystkieNext = proces1;
}