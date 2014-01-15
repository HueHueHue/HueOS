
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


	void test();
};