#include "global.h"
#include "Hue/globLev1.h"
void tRzeczywisty(float t, DWORD tStart);

int main() {
	setlocale(LC_ALL,"polish");
	
	Proces* startWszystkie = NULL; //proces od kt�rego zaczynam iterowa� po wszystkich. Na starcie ma by� chyba utworzony jeden kt�ry b�dzie mia� zawsze dzia�a�?
	Planista mPlanista(startWszystkie);

	DWORD tStart; //P�tla czasu rzeczywistego

	cout << "Hue0: Start p�tli" << endl;
	while(1){
		tStart = GetTickCount(); //czas na rozpocz�ciu p�tli
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