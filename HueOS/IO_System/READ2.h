#include<iostream>
#include<fstream>
#include <string>

using namespace std;



// Zmienna ta jest potrzebna do sprawdzenia czy u��dzenie jest zaj�te czy nie, gdyz nie mam dost�pu do
//sprawdzenia warto�ci semafor�w, na kt�rych wykonuje operacj�.

int zaj_R2=0;

		// Je��i zaj = 1 to znaczy �e trwa operacja ,
		//je�li zaj = 0 to znaczy �e urz�dzenie jest wolne i mo�na wykona� na nim operacj�

/*

  READ2(zaj_R2,2);
  przyk�ad wywo�ania funkcji READ

*/

double READ( int numer_rozkazu )  // Funkcja READ1
{
	
	double adres_rozkazu=0;			//zwracamy zero w razie nie powodzenia
// Tu nale�y podmieni� na w�a�ciw� funkcj� semafora od Michala
		//	user_semaphore( P ) ;       // Operacja kt�r� nale�y wykona� przed przyst�pieniem do operacji

			if( zaj_R2 == 1 )
			{
				cout << "Urz�dzenie READ2 jest w tej chwili zaj�te!";
			}
	else 
	{
			double liczba ;

	zaj_R2=1;
	std::cout<<"Otwieram i przeszukuj� baz� rozkaz�w \n";
	fstream bazarozkazow("rozkazy.roz",ios::in);           // co do bazy rozkaz�w to jest ona do stworzenia ale potrzebne s� dane od Pani Agnieszki.(Cytat J.B.)
	if(bazarozkazow.is_open())
	{
		while(!bazarozkazow.eof()){
		bazarozkazow >> liczba;
       		if(numer_rozkazu == liczba)
			{
				bazarozkazow >> liczba;
				adres_rozkazu=liczba;          
			}			
		}
	}
	else 
	{
		cout<<"Nie mo�na otworzy� pliku lub nie znaleziono rozkazu."<<endl;
	}
	bazarozkazow.close();

	
	cout <<adres_rozkazu<<endl<<" powy�sza warto�� to odnaleziony adres rozkazu kt�ry zwr�c� \n \n";
// Tu nale�y podmieni� na w�a�ciw� funkcj� semafora od Michala
  	//	user_semaphore( V ) ;       // Operacja kt�r� nale�y wykona� po operacji kt�ra przywruci semafor do stanu sprzed operacji
	zaj_R2=0;
	}


			return adres_rozkazu;
}