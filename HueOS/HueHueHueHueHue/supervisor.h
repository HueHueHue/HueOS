


class Supervisor {
public:
	CPRINT drukarka1;
	CREAD_File czytnik1;
	Planista* mPlanista;
	Lev3* mPoz3;
	string names[] = { "*IBSUP", "*IN", "*OUT" };

	Supervisor(Planista* mPlanista, Lev3* mPoz3);
	void init();
	void checkMessages();
};
