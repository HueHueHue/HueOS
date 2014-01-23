#include "globLev1.h"

Planista::Planista(Proces* procesList, Rejestr* mRejestr){
	this-> procesList = procesList;
	this->mRejestr = mRejestr;
	najlepszyCzas = 0;
	najlepszyCzasProces = NULL;
	Running = NULL;
}
void Planista::stopowanie(){
	Proces* bufor = procesList;
	if(bufor != NULL && bufor->wszystkieNext != 0){
		do {
			if(bufor->stop_waiting == 1){
				if(bufor->in_smc == 0){
					bufor->stopped = 1;
					bufor->stop_waiting = 0;
				}
			}
			bufor = bufor->wszystkieNext;
		} while(bufor != procesList);
	}
}
void Planista::startCykl(){
	stopowanie();


	Proces* bufor = procesList;
	if(Running == 0){
		if(bufor != NULL && bufor->wszystkieNext != 0){
			//wyliczanie czasu
			do {
				if(bufor->blocked == 0 && bufor->stopped == 0){
					if(bufor->przewidziany == 0){
						bufor->t_przewidywany_next = 0.5 * bufor->t_przewidywany + 0.5 * bufor-> t_wykonania;
						bufor->przewidziany = 1;
					}
				}
				bufor = bufor->wszystkieNext;
			} while(bufor != procesList);
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
			} while(bufor != procesList);


			if(najlepszyCzasProces != NULL){
				string text = "Wybrano proces o najkrotszym czasie wykonywania [";
			
				char str[10];
				itoa(najlepszyCzasProces->id,str,10);
				text += str;
				text += "]";
				textLev1(true, text);
				najlepszyCzasProces->running = 1;
				Running = najlepszyCzasProces;
				najlepszyCzasProces = 0;
				//WYKONAJ najlepszyCzasProces
			} else {
				textLev1(true, "Brak procesow gotowych do wykonania");
			}

		} else {
			if(bufor == NULL || bufor->wszystkieNext == 0)
				textLev1(true, "Brak procesow na liscie!!!");
			if(Running != NULL)
				textLev1(true, "Proces wybrany, w trakcie wykonywania");
		}
	} else {
		string text = "Proces jest wykonywany: ID [";
		char str[10];
		itoa(Running->id,str,10);
		text += str;
		text += "], wykonywany od: ";
		itoa(Running->t_obslugi,str,10);
		text += str;
		text += " jednostek czasu";
		textLev1(true, text);
	}
}


void Planista::koniecProcesu(Rejestr* mRejestr){
	if(Running != NULL){
		textLev1(true, "Proces zakonczyl dzialanie");
		Running->przewidziany = false;
		Running->t_przewidywany = Running->t_przewidywany_next;
		Running->t_przewidywany_next = NULL;
		Running->t_wykonania = Running->t_obslugi;
		Running->running = 0;

		Running->zapiszStan(mRejestr);

		Running = NULL;
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
		if(nowyProces->t_przewidywany_next < Running->t_przewidywany_next - Running->t_obslugi){
			textLev1(true, "Nowy proces ma mniejszy przewidywany czas. Wywlaszczam stary i uruchamian nowy");
			//ZATRZYMAJ najlepszyCzasProces
			Running->running = 0;
			koniecProcesu(mRejestr);
			//ZAPISZ STAN najlepszyCzasProces

			Running = nowyProces;
			//WYKONAJ najlepszyCzasProces
			Running->running = 1;
		} else {
			textLev1(true, "Nowy proces ma wiekszy przewydywany czas. Kontynuuje wykonywanie starego");
		}
	}
}


void Planista::xexc(Proces* proc){
	proc->in_smc += 1;
}
void Planista::xcom(Proces* proc){
	proc->in_smc -= 1;
}