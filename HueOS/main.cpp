#include "global.h"
#include "Hue/globLev1.h"
void tRzeczywisty(float t, DWORD tStart);

int main() {
	setlocale(LC_ALL,"polish");
	
	Proces* startWszystkie = NULL; //proces od którego zaczynam iterowaæ po wszystkich. Na starcie ma byæ chyba utworzony jeden który bêdzie mia³ zawsze dzia³a³?
	Planista mPlanista(startWszystkie);

	DWORD tStart; //Pêtla czasu rzeczywistego

	cout << "Hue0: Start pêtli" << endl;
	while(1){
		tStart = GetTickCount(); //czas na rozpoczêciu pêtli
		mPlanista.startCykl(); //Hue1


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