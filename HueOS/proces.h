
class Proces {
public:
	int id; 		//nie wymaga int t_dodania
	string nazwa;
	Proces* grupaNext;
	Proces* grupaLast;
	Proces* wszystkieNext;
	Proces* wszystkieLast;
	bool stopped;
	bool blocked;
	int semaforCommon;
	int semaforReceiver;

	bool przewidziany; 	//wykonane obliczenia?
	int t_przewidywany; 	//ile wyliczono?
	int t_przewidywany_next;	 //ile nastêpna faza
	int t_wykonania; 		// ostatni czas wykonania
	int t_obs³ugi; 	// czas przetworzonych danych

	Proces(int id, string nazwa, Proces* grupaNext, Proces* grupaLast, Proces* wszystkieNext, Proces* wszystkieLast, int t_przewidywany_next);
};
