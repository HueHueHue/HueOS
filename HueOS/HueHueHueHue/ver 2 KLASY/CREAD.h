#include<iostream>
#include<fstream>
#include <string>

using namespace std;



class CREAD
{
private:
	// Zmienna ta jest potrzebna do sprawdzenia czy uzadzenie jest zajete czy nie, gdyz nie mam dostepu do
//sprawdzenia wartosci semaforow, na ktorych wykonuje operacje.
	
	
	int zaj_read;  

		// Jesli zaj = 1 to znaczy ze trwa operacja ,
		//jesli zaj = 0 to znaczy ze urzadzenie jest wolne i mozna wykonac na nim operacje
		
protected:

public:
	CREAD();
	double READ( int numer_rozkazu );

};



/*

 CREAD.READ(2);
  przyklad wywolania funkcji READ

*/
