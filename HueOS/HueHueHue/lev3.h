class Proces;
class Rejestr;

class Lev3{
private:
	Proces* procesList;
	Rejestr* mRejestr;
	int IDCounter; //do nadawania unikalnych numerow
public:
	Lev3(Proces* procesList, Rejestr* mRejestr);

	void dodajProces(string nazwa, int t_przewidywany_next);	//XC
	void usunProces(string nazwa);	//XD
	void stop(string nazwa);//XH
	void dodajPCB(Proces* nowy);	//XI
	void usunPCB(Proces* doKasacji);	//XJ
	Proces* znajdzProces(string nazwa);	//XN
	string czytajKomunikat(string nazwa);	//XR
	void wyslijKomunikat(string nazwa, string text);// XS
	void uruchomProces(string nazwa);	// XY
	void zatrzymajProces(string nazwa);	// XZ
	//XQUE - bez



};