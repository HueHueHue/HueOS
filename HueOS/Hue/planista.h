
class Proces;
class Planista{
private:
	
	Proces* najlepszyCzasProces;
	int najlepszyCzas;
public:
	Proces* startWszystkie;

	Planista();
	void startCykl();
	void koniecProcesu();
	void nowyProces(Proces* nowyProces);
};