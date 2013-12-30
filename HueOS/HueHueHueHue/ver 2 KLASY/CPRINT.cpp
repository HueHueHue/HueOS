#include "CPRINT.h"



CPRINT::CPRINT()
{
	zaj_print = 0 ;   //konstruktor i przypisanie poczatkowej wartosci zmiennej odpowiadajacej za sprawdzanie stanu.
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
		
	cout << "==> konstruktor PRINT wywolany!!! \n";
}



void CPRINT::PRINT( char zapisywane[] ){
		// Tu nalezy podmienic na wlasciwa funkcje semafora od Michala
		
	//	user_semaphore( P ) ;       // Operacja ktora nalezy wykonac przed przystapieniem do operacji
		if( zaj_print == 1 ){
		cout << "Urzadzenie PRINT jest w tej chwili zajete! \n";
	}
	else 
	{
		zaj_print=1;
		fstream wyniki;
		wyniki.open("wyniki.txt",std::ios::app | std::ios::ate);
		wyniki<<zapisywane<<endl;

		/*
		   PRINT( "AFdsafsdf");
		   Przyklad wywolania funkcji zapisu
		   */
		wyniki.close();
// Tu nalezy podmienic na wlasciwa funkcje semafora od Michala
	  	//	user_semaphore( V ) ;       // Operacja ktora nalezy wykonac po operacji ktora przywruci semafor do stanu sprzed operacji
		zaj_print=0;
	}
}