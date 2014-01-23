class CPRINT;
class CREAD_File;
//class pamiec;

class Supervisor {
public:
	CPRINT* drukarka1;
	CREAD_File* czytnik1;
	Planista* mPlanista;
	pamiec* mPamiec;
	Lev3* mPoz3;
	Rejestr* mRejestr;
	static const char * const names[3];

	Supervisor(Planista* mPlanista, Lev3* mPoz3, pamiec* mPamiec, Rejestr* mRejestr);
	void init();
	void execute(Proces* proces);
	void checkMessages();

	void wyswietlDrukarka1();
};
