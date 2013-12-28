#include <iostream>
#include <fstream>
 
using namespace std;



class CPRINT
{
private:
// Zmienna ta jest potrzebna do sprawdzenia czy u¿¹dzenie jest zajête czy nie, gdyz nie mam dostêpu do
//sprawdzenia wartoœci semaforów, na których wykonuje operacjê.

	int zaj_print;  

		// Jeœ³i zaj = 1 to znaczy ¿e trwa operacja ,
		//jeœli zaj = 0 to znaczy ¿e urz¹dzenie jest wolne i mo¿na wykonaæ na nim operacjê

protected:

public:

	CPRINT();
	void PRINT( char zapisywane[] );

};



