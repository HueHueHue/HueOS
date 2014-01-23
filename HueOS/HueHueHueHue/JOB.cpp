// @autor witkowski01


#include "JOB.h"



JOB::JOB()
{
	    rozmiar = 5;

		 WorkspaceSize = "null";
		 IODevice = "null"; 
		 Data = "null";
		 Employer = "null";
		 /*
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );


		
		wypisz("==> konstruktor JOB wywolany!!! ");
	
	wypisz("Otwieram i analizuje karte $JOB ");

	ifstream bazadanych("Job.job",ios::in);     

	if(bazadanych.is_open())
	{
		tabl = new string[rozmiar];
		int numer_lini=0;
		string line; //zmienna przechowujaca tekst z lini karty $JOB

		wypisz("Rozpoczecie wczytywania pliku do bufora.");
		while((bazadanych.eof() != 1))
			{
				getline(bazadanych, line);
				tabl[numer_lini]=line;
				numer_lini++;
			}
		wypisz("Wczytywanie pliku do bufora zakonczone.");

		bazadanych.close();
	}
	

	else
	{
		cout<<"ERROR 01\nNie otwarto pliku."<<endl;	

		bazadanych.close();
	}

	bazadanych.close();

	SetConsoleTextAttribute( hOut, 0x07);   //Reset koloru do podstawowego*/

	
}
string JOB::JOB_nazwapliku(string nazwapliku)
{
	    rozmiar = 5;
		
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );


		
	wypisz("==> konstruktor JOB wywolany!!! ");
	
	wypisz("Otwieram i analizuje karte $JOB ");

	fstream bazadanych(nazwapliku,ios::in);     

	if(bazadanych.is_open())
	{
		tabl = new string[rozmiar];
		int numer_lini=0;
		string line; //zmienna przechowujaca tekst z lini karty $JOB

		wypisz("Rozpoczecie wczytywania pliku do bufora.");
		while((bazadanych.eof() != 1))
			{
				getline(bazadanych, line);
				tabl[numer_lini]=line;
				numer_lini++;
			}
		wypisz("Wczytywanie pliku do bufora zakonczone.");
	}


	else
	{
		wypisz("ERROR 01\nNie otwarto pliku.");	
	}
	SetConsoleTextAttribute( hOut, 0x07);   //Reset koloru do podstawowego

	bazadanych.close();
	return "2";
}

string	JOB::getWorkspaceSize() {

	WorkspaceSize = tabl[0];
		return WorkspaceSize;
	}


string	JOB::getIODevice() {

	IODevice = tabl[1];
		return IODevice;
	}


string	JOB::getData() {

	Data = tabl[2];
		return Data;
	}


string  JOB::getEmployer() {

	Employer = tabl[3];
		return Employer;

}


// Funkcja zwracajaca rozmiar pliku z danymi 
int JOB::getSize() {

	int size = 0;

	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );

	fstream bazadanych("Job.job",ios::in);    // Otwarcie pliku

	if(bazadanych.is_open())
	{
		 bazadanych.seekg(0, ios::end); // Przejœcie na koniec pliku
		 size = bazadanych.tellg();  // Sprawdzamy pozycjê, która odpowiada d³ugoœci pliku!
 
		 wypisz("D³ugoœæ pliku w bajtach wynosi: "); cout<< size << "." << endl;
	}
	else
	{
		wypisz("ERROR 01\nNie otwarto pliku JOB.");
	}
		SetConsoleTextAttribute( hOut, 0x07);  //Reset koloru do podstawowego

		 return size;
}


void JOB::wypisz(string a)
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Hue4: " << a << endl;
	SetConsoleTextAttribute(hOut, 0x07);
}