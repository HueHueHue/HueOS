
class Proces;
class Rejestr;
class Planista{
private:
	
	Proces* najlepszyCzasProces;
	Rejestr* mRejestr;
	int najlepszyCzas;

	void stopowanie();
public:
	Proces* procesList;

	Planista(Proces* procesList, Rejestr* mRejestr);
	void startCykl();
	void koniecProcesu(Rejestr* mRejestr);
	void nowyProces(Proces* nowyProces);

	void xexc(Proces* proc);
	void xcom(Proces* proc);

	Proces* Running;
};