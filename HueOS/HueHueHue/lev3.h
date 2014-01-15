class Proces;

class Lev3{
private:
	Proces* procesList;
public:
	Lev3(Proces* procesList);

	void dodajProces(string nazwa);
	void usunProces(string Nazwa);
	//XI?
	void dodajPCB(Proces* nowy);
	void usunPCB(Proces* doKasacji);



};