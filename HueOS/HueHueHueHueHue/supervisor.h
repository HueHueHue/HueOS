

class Supervisor {
public:
	CPRINT drukarka1;
	CREAD_File czytnik1;
	Planista* mPlanista;
	Lev3* mPoz3;
	static const char * const names[3];

	Supervisor(Planista* mPlanista, Lev3* mPoz3);
	void init();
	void checkMessages();
};
