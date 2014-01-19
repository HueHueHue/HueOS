// @autor witkowski01


#include<iostream>
#include<fstream>
#include <string>

#include <windows.h> // Biblioteki potrzebne do kolorow
#include <cstdlib>


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
		*tabl = new string[rozmiar];
		int numer_lini=0;


		cout <<"Rozpoczecie wczytywania pliku do bufora.\n";
		while((plik.eof() != 1))
			{
				getline(plik, line);
				tabl[numer_lini]=line;
				numer_lini++;
			}
		cout <<"Wczytywanie pliku do bufora zakonczone.\n";
	}
	plik.close();

	else
	{
		cout<<"ERROR 01\nNie otwarto pliku."<<endl;	
	}

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

	stream bazadanych("Job.job",ios::in);    // Otwarcie pliku

	if(bazadanych.is_open())
	{
		 bazadanych.seekg(0, ios::end); // Przejœcie na koniec pliku
		 size = bazadanych.tellg();  // Sprawdzamy pozycjê, która odpowiada d³ugoœci pliku!
 
		 cout << "D³ugoœæ pliku w bajtach wynosi: " << size << "." << endl;
	}
	else
	{
		cout<<"ERROR 01\nNie otwarto pliku."<<endl;	
	}


		 return size;
}