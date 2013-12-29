#include<iostream>
#include<fstream>
#include <string>

using namespace std;



// Zmienna ta jest potrzebna do sprawdzenia czy uzadzenie jest zajete czy nie, gdyz nie mam dostepu do
//sprawdzenia wartosci semaforow, na ktorych wykonuje operacje.

int zaj_R1=0;

		// Jesli zaj = 1 to znaczy ze trwa operacja ,
		//jesli zaj = 0 to znaczy ze urzadzenie jest wolne i mozna wykonac na nim operacje


/*

  READ1(zaj_R1,2);
  przyklad wywolania funkcji READ

*/

double READ1( int numer_rozkazu )  // Funkcja READ1
{
	
	double adres_rozkazu=0;			//zwracamy zero w razie nie powodzenia
// Tu nalezy podmienic na wlasciwa funkcje semafora od Michala
		//	user_semaphore( P ) ;       // Operacja ktora nalezy wykonac przed przystapieniem do operacji

			if( zaj_R1 == 1 ){
				cout << "Urzadzenie READ1 jest w tej chwili zajete!";
			}
	else 
	{
	
		double liczba ;

	zaj_R1=1;
	std::cout<<"Otwieram i przeszukuje baze rozkazow \n";
	fstream bazarozkazow("rozkazy.roz",ios::in);           // co do bazy rozkazow to jest ona do stworzenia ale potrzebne sa dane od Pani Agnieszki.(Cytat J.B.)
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
// Tu nalezy podmienic na wlasciwa funkcje semafora od Michala
  	//	user_semaphore( V ) ;       // Operacja ktora nalezy wykonac po operacji ktora przywruci semafor do stanu sprzed operacji
	zaj_R1=0;
	}


			return adres_rozkazu;
}