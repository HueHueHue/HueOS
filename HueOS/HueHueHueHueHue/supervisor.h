class CPRINT;
class CREAD_File;
class pamiec;

class Supervisor {
public:
	CPRINT* drukarka1;
	CREAD_File* czytnik1;
	Planista* mPlanista;
	Lev3* mPoz3;
	pamiec* mPamiec;
	static const char * const names[3];

	Supervisor(Planista* mPlanista, Lev3* mPoz3, pamiec* mPamiec);
	void init();
	void checkMessages();
};
