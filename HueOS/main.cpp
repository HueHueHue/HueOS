#include "global.h"
#include "Hue/globLev1.h"
#include "HueHueHue/lev3.h"
void tRzeczywisty(float t, DWORD tStart);

int main() {
	
	Proces* procesList = NULL; //proces od ktorego zaczynam iterowac po wszystkich. Na starcie ma byc chyba utworzony jeden ktory bedzie mial zawsze dzialal?
	
	Planista mPlanista(procesList);
	Lev3 mPoz3(procesList);
	DWORD tStart; //Petla czasu rzeczywistego

	cout << "Hue0: Start petli" << endl;
	
	while(1){
		tStart = GetTickCount(); //czas na rozpoczeciu petli
		mPlanista.startCykl(); //Hue1

		mPlanista.test();
		//Koniec operacji w tym cyklu
		tRzeczywisty(1, tStart); //Czekanie na koniec minimalnego czasu cyklu
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
}
//
////////////