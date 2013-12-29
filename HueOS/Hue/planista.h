
class Proces;
class Planista{
private:
	Proces* startWszystkie;
	Proces* najlepszyCzasProces;
	int najlepszyCzas;
public:
	Planista(Proces* startWszystkie);
	void startCykl();
	void koniecProcesu();
	void nowyProces(Proces* nowyProces);
};