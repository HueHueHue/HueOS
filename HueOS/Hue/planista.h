
class Proces;
class Planista{
private:
	
	Proces* najlepszyCzasProces;
	int najlepszyCzas;

	void stopowanie();
public:
	Proces* procesList;

	Planista(Proces* procesList);
	void startCykl();
	void koniecProcesu(Rejestr* & mRejestr);
	void nowyProces(Proces* nowyProces);

	void xexc(Proces* proc);
	void xcom(Proces* proc);

	Proces* Running;
};