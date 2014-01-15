
class Proces;
class Planista{
private:
	
	Proces* najlepszyCzasProces;
	int najlepszyCzas;
public:
	Proces* procesList;

	Planista(Proces* procesList);
	void startCykl();
	void koniecProcesu();
	void nowyProces(Proces* nowyProces);

	void xexc(Proces* proc);
	void xcom(Proces* proc);

	Proces* Running;

	void test();
};