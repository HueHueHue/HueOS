class Semafor{
private:
	int wart;
	list<Proces*> listaCzekaj;
	void odpalCzekajacy();

public:
	Semafor(int i);
	void pWait(Proces x);
	void vSignal(Proces x);
	

};