#ifndef l3_h
#define l3_h
class Proces;
class Rejestr;
class pamiec;

class Lev3{
public:
	Proces* procesList;
	Rejestr* mRejestr;
	pamiec* mPamiec;
	int IDCounter; //do nadawania unikalnych numerow

	Lev3(Proces* procesList, Rejestr* mRejestr, pamiec* mPamiec);

	void dodajProces(string nazwa, int t_przewidywany_next, unsigned short rozmiar);	//XC
	void usunProces(string nazwa);	//XD
	void stop(string nazwa);//XH
	void dodajPCB(Proces* nowy, bool zewnetrzny);//XI
	void usunPCB(Proces* doKasacji);	//XJ
	Proces* znajdzProces(string nazwa);	//XN
	string czytajKomunikat(string nazwa);	//XR
	void wyslijKomunikat(string nazwa, string text);// XS
	void uruchomProces(string nazwa);	// XY
	void zatrzymajProces(string nazwa);	// XZ
	//XQUE - bez



};
#endif