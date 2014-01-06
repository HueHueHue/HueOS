#include "CREAD.h"




CREAD::CREAD()    //konstruktor i przypisanie poczatkowej wartosci zmiennej odpowiadajacej za sprawdzanie stanu.
{
	zaj_read = 0;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
	cout << "==> konstruktor READ wywolany!!! \n";
	SetConsoleTextAttribute( hOut, 0x07);
}


double CREAD::READ( int numer_rozkazu )  // Funkcja READ1
{
	
	double adres_rozkazu=0;			//zwracamy zero w razie nie powodzenia

// Tu nalezy podmienic na wlasciwa funkcje semafora od Michala
		//	user_semaphore( P ) ;       // Operacja ktora nalezy wykonac przed przystapieniem do operacji

			if( zaj_read == 1 ){
				SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
				cout << "Urzadzenie READ jest w tej chwili zajete!";
				
			}
	else 
	{
	
		double liczba ;

	zaj_read=1;
	std::cout<<"Otwieram i przeszukuje baze rozkazow \n";
	fstream bazarozkazow("rozkazy.roz",ios::in);            // co do bazy rozkazow to jest ona do stworzenia ale potrzebne sa dane od Pani Agnieszki.(Cytat J.B.)
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
		cout<<"Nie mozna otworzyc pliku lub nie znaleziono rozkazu."<<endl;
	}
	bazarozkazow.close();

	
	cout <<adres_rozkazu<<endl<<" powyzsza wartosc to odnaleziony adres rozkazu ktory zwroce \n \n";
	SetConsoleTextAttribute( hOut, 0x07);
	
	// Tu nalezy podmienic na wlasciwa funkcje semafora od Michala
  	//	user_semaphore( V ) ;       // Operacja ktora nalezy wykonac po operacji ktora przywruci semafor do stanu sprzed operacji
	
	zaj_read=0;
	}

	return adres_rozkazu;
}