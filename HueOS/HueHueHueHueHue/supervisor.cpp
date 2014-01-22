#include "supervisor.h"


Supervisor::Supervisor(Planista* mPlanista, Lev3* mPoz3) : mPlanista(mPlanista), mPoz3(mPoz3) {}

void Supervisor::init() {
	// uruchom procesy systemowe
	for (int i = 0; i < 3; i++) {
		mPoz3->dodajPCB(new SysProces(i+1, names[i]), true);
	}

	// parsuj $JOB
	Interpreter interpreter;
	interpreter.interpret_code(karta1.getData());
}

void Supervisor::checkMessages() {
	string komunikat;
	vector<string> x;
	for (int i = 0; i < 3; i++) {
		komunikat = mPoz3->czytajKomunikat(names[i]);
		if (!komunikat.empty()) {
			cout << names[i] << " otrzymal komunikat: " << komunikat << endl;
			switch (i) {
			case 0: // ibsup
				x = split(komunikat, ' ');
				cout << "Zakonczono proces uzytkownika: " << x[1] << endl;
				break;
			case 1: // in
				// pobrac tekst (z pliku podanego w komunikacie?),
				// wyslac komunikat do nadawcy (czyli kogo :v)
				break;
			case 2:
				drukarka1.PRINT(komunikat.c_str());
				cout << "Przekazano komunikat do druku: " << komunikat << endl;
				break;
			}
		}
	}
}
