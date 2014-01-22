#include "global.h"
#include "Hue/globLev1.h"
#include "HueHueHue/lev3.h"
#include "HueHue/pamiec.h"
#include "HueHueHueHueHue/supervisor.h"
void tRzeczywisty(float t, DWORD tStart);

int main() {
	//1
	Proces* procesList = new Proces(0, "Proces bezczynnosciowy", 0); //proces od ktorego zaczynam iterowac po wszystkich.
	Rejestr* mRejestr = new Rejestr();
	
	Planista* mPlanista = new Planista(procesList, mRejestr);
	//1
	//2
	pamiec *opamiec = new pamiec();
	//2
	//3
	Lev3* mPoz3 = new Lev3(procesList,mRejestr,opamiec);
	//3

	Supervisor* supervisor = new Supervisor(mPlanista, mPoz3, opamiec);
	supervisor->init();

	DWORD tStart; //Petla czasu rzeczywistego

	cout << "Hue0: Start petli" << endl;
	
	while(1){
		tStart = GetTickCount(); //czas na rozpoczeciu petli
		mPlanista->startCykl(); //Hue1

		//mPlanista.Running		//wskaznik na proces do wykonania

		supervisor->checkMessages();

		//Koniec operacji w tym cyklu
		tRzeczywisty(3, tStart); //Czekanie na koniec minimalnego czasu cyklu
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
