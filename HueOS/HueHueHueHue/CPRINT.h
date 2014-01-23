#ifndef CPRINT_h
#define CPRINT_h

// @ autor witkowski01



#include <iostream>
#include <fstream>
#include <string>

#include <windows.h>  // Biblioteki potrzebne do kolorow
#include <cstdlib>
 
using namespace std;



class CPRINT
{
private:
// Zmienna ta jest potrzebna do sprawdzenia czy uzadzenie jest zajete czy nie, gdyz nie mam dostepu do
//sprawdzenia wartosci semaforow, na ktorych wykonuje operacje.

	int zaj_print;
	string *tabl;
	HANDLE hOut;

		// Jesli zaj = 1 to znaczy ze trwa operacja ,
		//jesli zaj = 0 to znaczy ze urzadzenie jest wolne i mozna wykonac na nim operacje

protected:

public:

	CPRINT();
	void PRINT( char zapisywane[] );
	void wypisz(string a);
	void wyswietl();

};

#endif
