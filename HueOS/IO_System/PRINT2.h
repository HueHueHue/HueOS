#include <iostream>
#include <fstream>
 using namespace std;


// Zmienna ta jest potrzebna do sprawdzenia czy u��dzenie jest zaj�te czy nie, gdyz nie mam dost�pu do
//sprawdzenia warto�ci semafor�w, na kt�rych wykonuje operacj�.

int zaj_P2=0;

		// Je��i zaj = 1 to znaczy �e trwa operacja ,
		//je�li zaj = 0 to znaczy �e urz�dzenie jest wolne i mo�na wykona� na nim operacj�

void PRINT2( char zapisywane[] ){
// Tu nale�y podmieni� na w�a�ciw� funkcj� semafora od Michala
		//	user_semaphore( P ) ;       // Operacja kt�r� nale�y wykona� przed przyst�pieniem do operacji
	if( zaj_P2 == 1 ){
		cout << "Urz�dzenie PRINT2 jest w tej chwili zaj�te!";
	}
	else 
	{
		zaj_P2=1;
		fstream wyniki;
		wyniki.open("wyniki2.txt",std::ios::app | std::ios::ate);
		wyniki<<zapisywane<<endl;

		/*
		   PRINT2(zaj_P2, "AFdsafsdf");
		   Przyk�ad wywo�ania funkcji zapisu
		   */
		

	wyniki.close();
// Tu nale�y podmieni� na w�a�ciw� funkcj� semafora od Michala
	  	//	user_semaphore( V ) ;       // Operacja kt�r� nale�y wykona� po operacji kt�ra przywruci semafor do stanu sprzed operacji
	zaj_P2=0;
	}
}