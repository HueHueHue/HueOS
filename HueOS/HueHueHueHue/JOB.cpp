// @autor witkowski01


#include "JOB.h"



JOB::JOB()
{
	    rozmiar = 5;
		
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );

		
		
	cout << "==> konstruktor JOB wywolany!!! \n";
	
	std::cout<<"Otwieram i analizuje karte $JOB \n";

	fstream bazadanych("Job.job",ios::in);     

	if(bazadanych.is_open())
	{
		tabl = new string[rozmiar];
		int numer_lini=0;
		string line; //zmienna przechowujaca tekst z lini karty $JOB

		cout <<"Rozpoczecie wczytywania pliku do bufora.\n";
		while((bazadanych.eof() != 1))
			{
				getline(bazadanych, line);
				tabl[numer_lini]=line;
				numer_lini++;
			}
		cout <<"Wczytywanie pliku do bufora zakonczone.\n";
	}


	else
	{
		cout<<"ERROR 01\nNie otwarto pliku."<<endl;	
	}
	SetConsoleTextAttribute( hOut, 0x07);   //Reset koloru do podstawowego

	bazadanych.close();
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
		 bazadanych.seekg(0, ios::end); // Przej�cie na koniec pliku
		 size = bazadanych.tellg();  // Sprawdzamy pozycj�, kt�ra odpowiada d�ugo�ci pliku!
 
		 cout << "D�ugo�� pliku w bajtach wynosi: " << size << "." << endl;
	}
	else
	{
		cout<<"ERROR 01\nNie otwarto pliku JOB."<<endl;	
	}
		SetConsoleTextAttribute( hOut, 0x07);  //Reset koloru do podstawowego

		 return size;
}