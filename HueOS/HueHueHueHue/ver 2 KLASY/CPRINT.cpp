#include "CPRINT.h"



CPRINT::CPRINT()
{
	zaj_print = 0 ;   //konstruktor i przypisanie pocz¹tkowej wartoœci zmiennej odpowiadaj¹cej za sprawdzanie stanu.
	cout << "==> konstruktor PRINT wywo³any!!! \n";
}



void CPRINT::PRINT( char zapisywane[] ){
		// Tu nale¿y podmieniæ na w³aœciw¹ funkcjê semafora od Michala
		
	//	user_semaphore( P ) ;       // Operacja któr¹ nale¿y wykonaæ przed przyst¹pieniem do operacji
	if( zaj_print == 1 ){
		cout << "Urz¹dzenie PRINT jest w tej chwili zajête! \n";
	}
	else 
	{
		zaj_print=1;
		fstream wyniki;
		wyniki.open("wyniki.txt",std::ios::app | std::ios::ate);
		wyniki<<zapisywane<<endl;

		/*
		   PRINT( "AFdsafsdf");
		   Przyk³ad wywo³ania funkcji zapisu
		   */
		wyniki.close();
// Tu nale¿y podmieniæ na w³aœciw¹ funkcjê semafora od Michala
	  	//	user_semaphore( V ) ;       // Operacja któr¹ nale¿y wykonaæ po operacji która przywruci semafor do stanu sprzed operacji
		zaj_print=0;
	}
}