#include <iostream>
#include <fstream>
 
using namespace std;



class CPRINT
{
private:
// Zmienna ta jest potrzebna do sprawdzenia czy uzadzenie jest zajete czy nie, gdyz nie mam dostepu do
//sprawdzenia wartosci semaforow, na ktorych wykonuje operacje.

	int zaj_print;  

		// Jesli zaj = 1 to znaczy ze trwa operacja ,
		//jesli zaj = 0 to znaczy ze urzadzenie jest wolne i mozna wykonac na nim operacje

protected:

public:

	CPRINT();
	void PRINT( char zapisywane[] );

};



