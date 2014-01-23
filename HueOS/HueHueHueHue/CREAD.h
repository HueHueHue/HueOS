#ifndef CREAD_h
#define CREAD_h

// @ autor witkowski01




#include<iostream>
#include<fstream>
#include <string>

#include <windows.h> // Biblioteki potrzebne do kolorow
#include <cstdlib>


#include "Job.h"   // zawiera: using namespace std;

using namespace std;


class CREAD
{
private:
// Zmienna ta jest potrzebna do sprawdzenia czy uzadzenie jest zajete czy nie, gdyz nie mam dostepu do
//sprawdzenia wartosci semaforow, na ktorych wykonuje operacje.
		
	int zaj_read;
	// Jesli zaj = 1 to znaczy ze trwa operacja ,
	//jesli zaj = 0 to znaczy ze urzadzenie jest wolne i mozna wykonac na nim operacje


	JOB job;

	HANDLE hOut;

		string Rozmiar_job;
		string IOurzadzenie; 
		string Dane;
		string zleceniodawca;
		int rozmiar_pliku;


		
		
protected:

public:
	CREAD();

	void wypisz(string a);

	string READ(  ); // czytanie rozkazu z $JOB z pliku !!!
	string READ_all(); // czytanie wszystkiego z pliku karty $JOB  i zwracanie pola Dane !!!
	string READ_all(string nazwapliku);
	void READ_all(string WorkspaceSize, string IODevice, string Data, string Employer);


	// Jesli chcemy uzyskac inne dane uzyc ponizszysz operacji ale tylko pod warunkiem wykonania READ_all !!!!
	string READ_all_returnWorkaspceSize();
	string READ_all_returnIODevice();
	string READ_all_returnData();
	string READ_all_returnEmployer();

};



/*

 CREAD.READ();
  przyklad wywolania funkcji READ

*/


#endif