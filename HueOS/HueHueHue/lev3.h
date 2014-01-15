class Proces;

class Lev3{
private:
	Proces* procesList;
	int IDCounter; //do nadawania unikalnych numerow
public:
	Lev3(Proces* procesList);

	void dodajProces(string nazwa, int t_przewidywany_next);	//XC
	void usunProces(string nazwa);	//XD
	//XH?
	void dodajPCB(Proces* &nowy);	//XI
	void usunPCB(Proces* &doKasacji);	//XJ
	Proces* znajdzProces(string nazwa);	//XN
	//XR
	// XS
	// XY
	// XZ
	//XQUE - bez



};