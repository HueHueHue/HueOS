
class Proces {
	int id; 		//nie wymaga int t_dodania
	string nazwa;
	Proces* grupaNext;
	Proces* grupaLast;
	Proces* wszystkieNext;
	Proces* wszystkieLast
	bool ready;			//do przetwarzania
	bool przewidziany; 	//wykonane obliczenia?
	int t_przewidywany; 	//ile wyliczono?
	int t_przewidywany_next;	 //ile nast�pna faza
	int t_wykonania; 		// ostatni czas wykonania
	int t_obs�ugi; 	// czas przetworzonych danych
};
