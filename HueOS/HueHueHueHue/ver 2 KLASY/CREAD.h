#include<iostream>
#include<fstream>
#include <string>

using namespace std;



class CREAD
{
private:
	// Zmienna ta jest potrzebna do sprawdzenia czy u¿¹dzenie jest zajête czy nie, gdyz nie mam dostêpu do
//sprawdzenia wartoœci semaforów, na których wykonuje operacjê.
	
	
	int zaj_read;  

		// Jeœ³i zaj = 1 to znaczy ¿e trwa operacja ,
		//jeœli zaj = 0 to znaczy ¿e urz¹dzenie jest wolne i mo¿na wykonaæ na nim operacjê
		
protected:

public:
	CREAD();
	double READ( int numer_rozkazu );

};



/*

 CREAD.READ(2);
  przyk³ad wywo³ania funkcji READ

*/
