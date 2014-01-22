class Semafor;
class Rejestr;
class Proces {
public:
	int id; 		//nie wymaga int t_dodania
	string nazwa;
	//Proces* grupaNext;
	//Proces* grupaLast;
	Proces* wszystkieNext;
	Proces* wszystkieLast;
	bool stopped;
	bool blocked;
	bool running;
	int semaforCommon;
	int semaforReceiver;
	int in_smc;
	int stop_waiting;

	unsigned short auto_storage_size;
	unsigned short pierwszy_bajt_pamieci;
	unsigned short mem_pointer;
	list<string> komunikaty;

	//////Obszary ochronne
	string old_psw;
	int old_registers[4];
	string temp[3]; //

	bool przewidziany; 	//wykonane obliczenia?
	int t_przewidywany; 	//ile wyliczono?
	int t_przewidywany_next;	 //ile nastepna faza
	int t_wykonania; 		// ostatni czas wykonania
	int t_obslugi; 	// czas przetworzonych danych

	Proces(int id, string nazwa, int t_przewidywany_next);
	void zapiszStan(Rejestr* mRejestr);
	void wczytajStan(Rejestr* mRejestr);




};
