#include "globLev1.h"

Planista::Planista(Proces* procesList, Rejestr* mRejestr){
	this-> procesList = procesList;
	this->mRejestr = mRejestr;
	najlepszyCzas = 0;
	najlepszyCzasProces = NULL;
	Running = NULL;
	textLev1(1, "Planista utworzony. Modul nizszy wita");
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

							string text = "Obliczylem wartosc [";
							char str[10];
							itoa(bufor->t_przewidywany_next,str,10);
							text += str;
							text += "] dla procesu: ";
							text += bufor->nazwa;
							textLev1(true, text);
					}
				}
				bufor = bufor->wszystkieNext;
			} while(bufor != procesList);
			textLev1(true, "Zakonczono obliczanie czasu przewidywanego dla procesow aktywnych");

			//wyszukiwanie najszybszego
			do {
				if(bufor->blocked == 0 && bufor->stopped == 0){
					if(bufor->przewidziany == 1){
						if(najlepszyCzas == 0){
							najlepszyCzas = bufor->t_przewidywany_next - bufor->t_obslugi;
							najlepszyCzasProces = bufor;
							string text = "Pierwsza wartosc [";
							char str[10];
							itoa(bufor->t_przewidywany_next,str,10);
							text += str;
							text += "] dla procesu: ";
							text += bufor->nazwa;
							textLev1(true, text);
						} else {
							if(najlepszyCzas > bufor->t_przewidywany_next - bufor->t_obslugi){
								najlepszyCzas = bufor->t_przewidywany_next - bufor->t_obslugi;
								najlepszyCzasProces = bufor;
								string text = "Lepsza wartosc [";
								char str[10];
								itoa(bufor->t_przewidywany_next,str,10);
								text += str;
								text += "] dla procesu: ";
								text += bufor->nazwa;
								textLev1(true, text);
							} else {
								string text = "Gorsza wartosc [";
								char str[10];
								itoa(bufor->t_przewidywany_next,str,10);
								text += str;
								text += "] dla procesu: ";
								text += bufor->nazwa;
								textLev1(true, text);
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
		string text = "Proces zakonczyl dzialanie: ID [";
		char str[10];
		itoa(Running->id,str,10);
		text += str;
		text += "]";
		textLev1(true, text);
		Running->przewidziany = false;
		Running->t_przewidywany = Running->t_przewidywany_next;
		Running->t_przewidywany_next = NULL;
		Running->t_wykonania = Running->t_obslugi;
		Running->t_obslugi = 0;
		Running->running = 0;

		Running->zapiszStan(mRejestr);

		Running = NULL;
		najlepszyCzas = 0;

	} else {
		textLev1(false, "Nie mozna zakonczyc procesu - brak odpalonego procesu");
	}
}

void Planista::nowyProces(Proces* nowyProces){
	if(Running == 0){
		textLev1(true, "Nie wywlaszczam - nie mam czego!");
	} else {
		textLev1(true, "Pojawil sie nowy aktywny proces " + nowyProces->nazwa);
		textLev1(true, "Testuje przewidywany czas wykonywania...");

		if(nowyProces->stopped == 0 && nowyProces->blocked == 0){
			if(nowyProces->przewidziany == false){
				nowyProces->t_przewidywany_next = 0.5 * nowyProces->t_przewidywany + 0.5 * nowyProces-> t_wykonania;
				nowyProces->przewidziany = 1;
			}
			if(nowyProces->t_przewidywany_next < Running->t_przewidywany_next - Running->t_obslugi){
				string text = "Nowy proces ma mniejszy czas [";
				char str[10];
				itoa(nowyProces->t_przewidywany_next,str,10);
				text += str;
				text += "], wywlaszczam stary i uruchamian nowy";
				textLev1(true, text);
				//ZATRZYMAJ najlepszyCzasProces
				Running->running = 0;
				koniecProcesu(mRejestr);
				//ZAPISZ STAN najlepszyCzasProces

				Running = nowyProces;
				//WYKONAJ najlepszyCzasProces
				Running->running = 1;
			} else {
				string text = "Nowy proces ma wiekszy czas [";
				char str[10];
				itoa(nowyProces->t_przewidywany_next,str,10);
				text += str;
				text += "], kontynuuje wykonywanie starego";
				textLev1(true, text);
			}
		}
	}
}


void Planista::xexc(Proces* proc){
	proc->in_smc += 1;
}
void Planista::xcom(Proces* proc){
	proc->in_smc -= 1;
}

void Planista::wyswietl(){
	HANDLE hOut;
	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hOut, 0x0C);
	cout << "Hue1: Wszystkie dostepne procesy" << endl;
	Proces* bufor = procesList;
	cout << " ID	| run	| stop	| block	| t_prz	| Nazwa" << endl;
	
		do {
			cout << " " <<bufor->id << "	| " << bufor->running << "	| " << bufor->stopped << "	| " << bufor->blocked << "	| " << bufor ->t_przewidywany_next << "	| " << bufor ->nazwa << endl;
			
			bufor = bufor->wszystkieNext;
		} while(bufor != procesList);


	SetConsoleTextAttribute( hOut, 0x07);
}