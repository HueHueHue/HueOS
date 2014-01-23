#include "global.h"
#include "Hue/globLev1.h"
#include "HueHueHue/lev3.h"
#include "HueHue/pamiec.h"
#include "HueHueHueHueHue/supervisor.h"
void tRzeczywisty(float t, DWORD tStart);
void decyzja(Planista* mPlanista, pamiec* opamiec);


int main() {
	cout << "Hue0:				Start systemu" << endl;
	system("pause");
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
		for(int i = 0; i<80; i++){
			cout << "-";
		}
		cout << endl;
	while(1){
		tStart = GetTickCount(); //czas na rozpoczeciu petli
		mPlanista->startCykl(); //Hue1

		supervisor->execute(mPlanista->Running);

		supervisor->checkMessages();

		//Koniec operacji w tym cyklu
		//tRzeczywisty(5, tStart); //Czekanie na koniec minimalnego czasu cyklu, tryb AUTO

		decyzja(mPlanista, opamiec); //Tryb manualny
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

	for(int i = 0; i<80; i++){
		cout << "-";
	}
	cout << endl;
}
//
////////////

void wyswietlKomendy();
void decyzja(Planista* mPlanista, pamiec* opamiec){
	cout << "Hue0: Koniec jednostki czasu" << endl;
	string x;
	bool end = false;
	for(int i = 0; i<80; i++){
		cout << "-";
	}
	do{
		cout << endl;
		cout << "> Wprowadz komende (<enter> - nastepna jednostka, help - komendy)" << endl << ">   ";
		
		getline(cin, x);
		cout << endl;
		if(x == "help"){
			
			wyswietlKomendy();
		} else if(x == "start"){
			//dodaj nowy proces z p³ytki job
		} else if(x == "pamiec"){
			opamiec->wyswietl_tablice_pamieci_dziesietnie();
		} else if(x == "pamiec16"){
			opamiec->wyswietl_tablice_pamieci_szesnastkowo();
		} else if(x == "pcb"){
			mPlanista->wyswietl();
		}
		else if (x == "drukarka"){

		}
		else if (x == ""){
			end = true;
		} else {
			cout << "Zla komenda" << endl;
			end = false;
		}



		for(int i = 0; i<80; i++){
			cout << "-";
		}
	} while(end == false);
}

void wyswietlKomendy(){
	cout << "> Dostepne komendy:" << endl;
	cout << "> <ENTER>	- zaczyna kolejna jendnostke czasu systemu" << endl;
	cout << "> pcb		- wyswietla procesy na liscie glownej" << endl;
	cout << "> pamiec		- wyswietla zawartosc pamieci" << endl;
	cout << "> pamiec16		- wyswietla zawartosc pamieci w postaci szesnastkowej" << endl;
	cout << "> start		- zacznij wczytywac nowy proces" << endl;

}