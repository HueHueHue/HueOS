#include <iostream>
#include <fstream>
 
using namespace std;



class CPRINT
{
private:
// Zmienna ta jest potrzebna do sprawdzenia czy u��dzenie jest zaj�te czy nie, gdyz nie mam dost�pu do
//sprawdzenia warto�ci semafor�w, na kt�rych wykonuje operacj�.

	int zaj_print;  

		// Je��i zaj = 1 to znaczy �e trwa operacja ,
		//je�li zaj = 0 to znaczy �e urz�dzenie jest wolne i mo�na wykona� na nim operacj�

protected:

public:

	CPRINT();
	void PRINT( char zapisywane[] );

};



