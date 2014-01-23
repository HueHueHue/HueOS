// @ autor witkowski01



#include "CPRINT.h"




CPRINT::CPRINT()
{
	zaj_print = 0 ;   //konstruktor i przypisanie poczatkowej wartosci zmiennej odpowiadajacej za sprawdzanie stanu.
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
		
	cout << "Hue4: ==> konstruktor PRINT wywolany!!! \n";
	SetConsoleTextAttribute( hOut, 0x07);  //Reset koloru do podstawowego
}



void CPRINT::PRINT( char zapisywane[] ){
		
	// Tu nalezy podmienic na wlasciwa funkcje semafora od Hue1
		//	user_semaphore( P ) ;       // Operacja ktora nalezy wykonac przed przystapieniem do operacji

	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );


	if( zaj_print == 1 ){
		cout << "Hue4: Urzadzenie PRINT jest w tej chwili zajete! \n";
	}
	else 
	{
		zaj_print=1;
		fstream wyniki;

		wyniki.open("wyniki.txt",std::ios::app | std::ios::ate); // otwarcie pliku
		if(wyniki.is_open())	
		{
			cout<<"Hue4: Otwieram plik zapisu wyniki.txt ."<<endl;
			wyniki<<zapisywane<<endl;

		   /*
		   PRINT( "AFdsafsdf");
		   Przyklad wywolania funkcji zapisu
		   */

			wyniki.close();
			cout<<"Hue4: Zamykam plik zapisu wyniki.txt ."<<endl;
		}
		else
	{
		cout<<"Hue4: ERROR 01\nNie otwarto pliku PRINT."<<endl;	
	}
// Tu nalezy podmienic na wlasciwa funkcje semafora od Hue1
	  	//	user_semaphore( V ) ;       // Operacja ktora nalezy wykonac po operacji ktora przywruci semafor do stanu sprzed operacji
		zaj_print=0;
	}
SetConsoleTextAttribute( hOut, 0x07);  //Reset koloru do podstawowego
}