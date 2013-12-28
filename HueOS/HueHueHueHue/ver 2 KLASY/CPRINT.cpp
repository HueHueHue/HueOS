#include "CPRINT.h"



CPRINT::CPRINT()
{
	zaj_print = 0 ;   //konstruktor i przypisanie pocz�tkowej warto�ci zmiennej odpowiadaj�cej za sprawdzanie stanu.
	cout << "==> konstruktor PRINT wywo�any!!! \n";
}



void CPRINT::PRINT( char zapisywane[] ){
		// Tu nale�y podmieni� na w�a�ciw� funkcj� semafora od Michala
		
	//	user_semaphore( P ) ;       // Operacja kt�r� nale�y wykona� przed przyst�pieniem do operacji
	if( zaj_print == 1 ){
		cout << "Urz�dzenie PRINT jest w tej chwili zaj�te! \n";
	}
	else 
	{
		zaj_print=1;
		fstream wyniki;
		wyniki.open("wyniki.txt",std::ios::app | std::ios::ate);
		wyniki<<zapisywane<<endl;

		/*
		   PRINT( "AFdsafsdf");
		   Przyk�ad wywo�ania funkcji zapisu
		   */
		wyniki.close();
// Tu nale�y podmieni� na w�a�ciw� funkcj� semafora od Michala
	  	//	user_semaphore( V ) ;       // Operacja kt�r� nale�y wykona� po operacji kt�ra przywruci semafor do stanu sprzed operacji
		zaj_print=0;
	}
}