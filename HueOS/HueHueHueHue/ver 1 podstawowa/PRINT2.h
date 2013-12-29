#include <iostream>
#include <fstream>
 using namespace std;


// Zmienna ta jest potrzebna do sprawdzenia czy uzadzenie jest zajete czy nie, gdyz nie mam dostepu do
//sprawdzenia wartosci semaforow, na ktorych wykonuje operacje.

int zaj_P2=0;

		// Jesli zaj = 1 to znaczy ze trwa operacja ,
		//jesli zaj = 0 to znaczy ze urzadzenie jest wolne i mozna wykonac na nim operacje

void PRINT2( char zapisywane[] ){
// Tu nalezy podmienic na wlasciwa funkcje semafora od Michala
		//	user_semaphore( P ) ;       // Operacja ktora nalezy wykonac przed przystapieniem do operacji
	if( zaj_P2 == 1 ){
		cout << "Urzadzenie PRINT2 jest w tej chwili zajete!";
	}
	else 
	{
		zaj_P2=1;
		fstream wyniki;
		wyniki.open("wyniki2.txt",std::ios::app | std::ios::ate);
		wyniki<<zapisywane<<endl;

		/*
		   PRINT2(zaj_P2, "AFdsafsdf");
		   Przyklad wywolania funkcji zapisu
		   */
		

	wyniki.close();
// Tu nalezy podmienic na wlasciwa funkcje semafora od Michala
	  	//	user_semaphore( V ) ;       // Operacja ktora nalezy wykonac po operacji ktora przywruci semafor do stanu sprzed operacji
	zaj_P2=0;
	}
}