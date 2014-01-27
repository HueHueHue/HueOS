// @ autor witkowski01



#include "CPRINT.h"




CPRINT::CPRINT()
{
	zaj_print = 0 ;   //konstruktor i przypisanie poczatkowej wartosci zmiennej odpowiadajacej za sprawdzanie stanu.
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
		
	cout << "Hue4: ==> konstruktor PRINT wywolany!!! \n";
	SetConsoleTextAttribute( hOut, 0x07);  //Reset koloru do podstawowego
}



void CPRINT::PRINT( char zapisywane[] ){
		
	// Tu nalezy podmienic na wlasciwa funkcje semafora od Hue1
		//	user_semaphore( P ) ;       // Operacja ktora nalezy wykonac przed przystapieniem do operacji

	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );


	if( zaj_print == 1 ){
		cout << "Hue4: Urzadzenie PRINT jest w tej chwili zajete! \n";
	}
	else 
	{
		zaj_print=1;
		fstream wyniki;

		wyniki.open("wyniki.txt",std::ios::app | std::ios::ate); // otwarcie pliku
		if(wyniki.is_open())	
		{
			wypisz(" Otwieram plik zapisu wyniki.txt .");
			wyniki<<zapisywane<<endl;

		   /*
		   PRINT( "AFdsafsdf");
		   Przyklad wywolania funkcji zapisu
		   */

			wyniki.close();
			wypisz(" Zamykam plik zapisu wyniki.txt .");
		}
		else
	{
		wypisz(" ERROR 01\nNie otwarto pliku PRINT.");	
	}
// Tu nalezy podmienic na wlasciwa funkcje semafora od Hue1
	  	//	user_semaphore( V ) ;       // Operacja ktora nalezy wykonac po operacji ktora przywruci semafor do stanu sprzed operacji
		zaj_print=0;
	}
SetConsoleTextAttribute( hOut, 0x07);  //Reset koloru do podstawowego
}

void CPRINT::wypisz(string a)
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Hue4: " << a << endl;
	SetConsoleTextAttribute(hOut, 0x07);
}


void CPRINT::wyswietl(){

	int rozmiar = 10;
	tabl = new string[rozmiar];
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Ostatnie " << rozmiar << " wydrukowanych danych" << endl;

	fstream bazadanych("wyniki.txt", ios::in);

	if (bazadanych.is_open())
	{

		int numer_lini = 0;
		string line; //zmienna przechowujaca tekst z lini karty $JOB

		//wypisz("Rozpoczecie wczytywania pliku do bufora przed wyswietleniem druku.");
		while (numer_lini < rozmiar)
		{
			if(bazadanych.eof())
				break;
			getline(bazadanych, line);
			tabl[numer_lini] = line;
			numer_lini++;
		}

		//wypisz("Wczytywanie pliku do bufora wyswietlania druku zakonczone.");
			for (int i = 0; i < rozmiar; i++)
			{
				cout.width( 3 );
				cout << i+1;
				cout << " | " << tabl[i] << endl;
			}
	}else{
		wypisz("ERROR 01\nNie otwarto pliku wynikowego.");
	}

	bazadanych.close();

	SetConsoleTextAttribute(hOut, 0x07);
}

void CPRINT::wyczyscDrukarka(){

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	

	fstream bazadanych;

	if (bazadanych.is_open())
	{
		bazadanych.close();
	}
	bazadanych.open("wyniki.txt", ios::out | ios::trunc);

	
		wypisz("Czyszczenie pliku drukarki.");
	

	bazadanych.close();

	SetConsoleTextAttribute(hOut, 0x07);
}