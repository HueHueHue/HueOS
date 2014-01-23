#ifndef JOB_h
#define JOB_h

// @autor witkowski01


#include<iostream>
#include<fstream>
#include <string>

#include <windows.h> // Biblioteki potrzebne do kolorow
#include <cstdlib>


using namespace std;

//  Karta $JOB jest reprezentowana przez plik tekstowy i ma okreœlon¹ strukturê:	
// - WorkspaceSize: Wielkoœæ pamiêci roboczej.
// - Urz¹dzenie wejœcia (pierwsze czy drugie)
// - Data: Dane do przekazania.
// - Employer:  Kto wydaje rozkazy

class JOB {
	
private:
		string WorkspaceSize;
		string IODevice; 
		string Data;
		string Employer;
		int rozmiar;
		string *tabl;

		HANDLE hOut;  // Zmienna odpowiedzialna za przetrzymanie koloru.
	
public:
		JOB();
		string JOB_nazwapliku(string nazwapliku);

		void wypisz(string a);
		//Mozliwosc wywo³ania akcji karty JOB bez pliku karta a za pomoca ponizszej funkcji z parametrami.
		void Job (string WorkspaceSize, string IODevice, string Data, string Employer){

			this ->WorkspaceSize=WorkspaceSize;
			this ->IODevice=IODevice;
			this ->Data=Data;
			this ->Employer=Employer;
	}
	
	    string getWorkspaceSize();

	    string getIODevice();

	    string getData();

		string getEmployer();

		int getSize();

};

#endif