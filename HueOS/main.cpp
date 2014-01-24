#include "global.h"
#include "Hue/globLev1.h"
#include "HueHueHue/lev3.h"
#include "HueHue/pamiec.h"
#include "HueHueHueHueHue/supervisor.h"
#include "HueHueHueHueHue/split.h"
void tRzeczywisty(float t, DWORD tStart);
void decyzja(Planista* mPlanista, Rejestr* mRejestr, pamiec* opamiec, Supervisor* mSupervisor);


int main() {
	cout << "Hue0:				Start systemu" << endl;
	cin.ignore(INT_MAX, '\n');
	cout << "Hue0: Inicjowanie klas.." << endl;
	cout << endl << "Hue0: Lev1" << endl;
	//1
	Proces* procesList = new Proces(0, "Proces bezczynnosciowy", 0); //proces od ktorego zaczynam iterowac po wszystkich.
	procesList->blocked = 1;
	Rejestr* mRejestr = new Rejestr();
	Planista* mPlanista = new Planista(procesList, mRejestr);
	//1
	cout << endl << "Hue0: Lev2" << endl;
	//2
	pamiec *opamiec = new pamiec();
	//2
	cout << endl << "Hue0: Lev3" << endl;
	//3
	Lev3* mPoz3 = new Lev3(procesList,mRejestr,opamiec);
	//3
	cout << endl << "Hue0: Lev5" << endl;
	//5
	Supervisor* supervisor = new Supervisor(mPlanista, mPoz3, opamiec, mRejestr);
	supervisor->init();
	//5

	DWORD tStart; //Petla czasu rzeczywistego

	cout << endl << endl << "Hue0:			<<<<< Start petli >>>>>" << endl << endl;
	cout << string(80, '-') << endl;
	cout << endl;

	while(1){
		tStart = GetTickCount(); //czas na rozpoczeciu petli
		mPlanista->startCykl(); //Hue1

		supervisor->execute(mPlanista->Running);

		supervisor->checkMessages();

		//Koniec operacji w tym cyklu
		//tRzeczywisty(5, tStart); //Czekanie na koniec minimalnego czasu cyklu, tryb AUTO

		decyzja(mPlanista, mRejestr, opamiec, supervisor); //Tryb manualny
	}

	return 0;
}




////////////
// Czekanie na koniec minimalnego czasu cyklu - funkcja
void tRzeczywisty(float t, DWORD tStart){
	DWORD tTeraz;
	do{
			tTeraz = GetTickCount();
		} while(tTeraz - tStart < t*1000);
	cout << "Hue0: Koniec jednostki czasu" << endl;

	cout << string(80, '-') << endl;
	cout << endl;
}
//
////////////

void wyswietlKomendy();
void decyzja(Planista* mPlanista, Rejestr* mRejestr, pamiec* opamiec, Supervisor* mSupervisor){
	cout << "Hue0: Koniec jednostki czasu" << endl;
	string line;
	vector<string> x;
	bool end = false;
	cout << string(80, '-') << endl;
	do {
		cout << endl;
		cout << "> Wprowadz komende (<ENTER> - nastepna jednostka, help - komendy)" << endl << "> ";
		
		getline(cin, line);
		x = split(line, ' ');
		cout << endl;
		if (x.size() == 0) {
			end = true;
		} else if (x[0] == "help") {
			wyswietlKomendy();
		} else if(x[0] == "load") {
			if (x.size() == 2) {
				mSupervisor->loadJob(x[1]);
			} else {
				cout << "Nieprawidlowa liczba argumentow." << endl;
			}
		} else if(x[0] == "pamiec") {
			opamiec->wyswietl_tablice_pamieci_dziesietnie();
		} else if(x[0] == "pamiec16") {
			opamiec->wyswietl_tablice_pamieci_szesnastkowo();
		} else if(x[0] == "pcb") {
			mPlanista->wyswietl();
		} else if (x[0] == "rejestr") {
			mRejestr->wyswietl();
		} else if (x[0] == "drukarka") {
			mSupervisor->wyswietlDrukarka1();
		} else {
			cout << "Zla komenda" << endl;
			end = false;
		}
		cout << string(80, '-') << endl;
	} while(end == false);
}

void wyswietlKomendy(){
	cout << "> Dostepne komendy:" << endl;
	cout << " >  <ENTER>		- zaczyna kolejna jendnostke czasu systemu" << endl;
	cout << "1> pcb			- wyswietla procesy na liscie glownej" << endl;
	cout << "1> rejestr		- wyswietla stan rejestru" << endl;
	cout << "2> pamiec		- wyswietla zawartosc pamieci" << endl;
	cout << "2> pamiec16		- wyswietla zawartosc pamieci w postaci szesnastkowej" << endl;
	cout << "4> drukarka		- wyswietla ostatnie 10 wydrukowanych danych" << endl;
	cout << "5> load			- zacznij wczytywac nowy proces" << endl;

}