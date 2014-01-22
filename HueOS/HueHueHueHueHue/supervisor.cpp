#include "supervisor.h"


Supervisor::Supervisor(Planista* mPlanista, Lev3* mPoz3) : mPlanista(mPlanista), mPoz3(mPoz3) {}

void Supervisor::init() {
	string job_cards[] = {"1.job", "2.job"};

	// uruchom procesy systemowe
	for (int i = 0; i < 3; i++) {
		mPoz3->dodajPCB(new SysProces(i+1, names[i]), true);
	}

	JOB job; // hey, let's ignore job.job :v

	// parsuj $JOB
	for (int i = 0; i < sizeof(job_cards)/sizeof(job_cards[0]); i++) {
		job.JOB_nazwapliku(job_cards[i]);
		Interpreter interpreter;
		interpreter.interpret_code(job.getData());
		mPoz3->dodajProces(job_cards[i], interpreter.op_count, interpreter.total_length);
		Proces* userprog = mPoz3->znajdzProces(job_cards[i]);
		if (!userprog) {
			cout << "Proces " << job_cards[i] << " nie zostal utworzony";
		}

		for (int i = 0; i < interpreter.total_length; i++) {
			if(!mPoz3->mPamiec->ustaw_bajt(userprog->auto_storage_size, i, interpreter.buffer[i])) {
				cout << "Pisanie do bajtu " << i << " nie powiodlo sie";
			}
		}

		mPoz3->uruchomProces(job_cards[i]);
	}

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
				drukarka1.PRINT((char *)komunikat.c_str());
				cout << "Przekazano komunikat do druku: " << komunikat << endl;
				break;
			}
		}
	}
}
