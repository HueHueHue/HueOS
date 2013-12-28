#include "CREAD.h"




CREAD::CREAD()   //konstruktor i przypisanie pocz�tkowej warto�ci zmiennej odpowiadaj�cej za sprawdzanie stanu.
{
	zaj_read = 0;
	cout << "==> konstruktor READ wywo�any!!! \n";
}


double CREAD::READ( int numer_rozkazu )  // Funkcja READ1
{
	
	double adres_rozkazu=0;			//zwracamy zero w razie nie powodzenia

// Tu nale�y podmieni� na w�a�ciw� funkcj� semafora od Michala
		//	user_semaphore( P ) ;       // Operacja kt�r� nale�y wykona� przed przyst�pieniem do operacji

			if( zaj_read == 1 ){
				cout << "Urz�dzenie READ jest w tej chwili zaj�te!";
			}
	else 
	{
	
		double liczba ;

	zaj_read=1;
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
	
	zaj_read=0;
	}

	return adres_rozkazu;
}