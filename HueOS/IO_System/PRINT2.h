#include <iostream>
#include <fstream>
 using namespace std;


// Zmienna ta jest potrzebna do sprawdzenia czy u¿¹dzenie jest zajête czy nie, gdyz nie mam dostêpu do
//sprawdzenia wartoœci semaforów, na których wykonuje operacjê.

int zaj_P2=0;

		// Jeœ³i zaj = 1 to znaczy ¿e trwa operacja ,
		//jeœli zaj = 0 to znaczy ¿e urz¹dzenie jest wolne i mo¿na wykonaæ na nim operacjê

void PRINT2( char zapisywane[] ){
// Tu nale¿y podmieniæ na w³aœciw¹ funkcjê semafora od Michala
		//	user_semaphore( P ) ;       // Operacja któr¹ nale¿y wykonaæ przed przyst¹pieniem do operacji
	if( zaj_P2 == 1 ){
		cout << "Urz¹dzenie PRINT2 jest w tej chwili zajête!";
	}
	else 
	{
		zaj_P2=1;
		fstream wyniki;
		wyniki.open("wyniki2.txt",std::ios::app | std::ios::ate);
		wyniki<<zapisywane<<endl;

		/*
		   PRINT2(zaj_P2, "AFdsafsdf");
		   Przyk³ad wywo³ania funkcji zapisu
		   */
		

	wyniki.close();
// Tu nale¿y podmieniæ na w³aœciw¹ funkcjê semafora od Michala
	  	//	user_semaphore( V ) ;       // Operacja któr¹ nale¿y wykonaæ po operacji która przywruci semafor do stanu sprzed operacji
	zaj_P2=0;
	}
}