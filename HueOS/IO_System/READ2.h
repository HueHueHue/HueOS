#include<iostream>
#include<fstream>
#include <string>

using namespace std;



// Zmienna ta jest potrzebna do sprawdzenia czy u¿¹dzenie jest zajête czy nie, gdyz nie mam dostêpu do
//sprawdzenia wartoœci semaforów, na których wykonuje operacjê.

int zaj_R2=0;

		// Jeœ³i zaj = 1 to znaczy ¿e trwa operacja ,
		//jeœli zaj = 0 to znaczy ¿e urz¹dzenie jest wolne i mo¿na wykonaæ na nim operacjê

/*

  READ2(zaj_R2,2);
  przyk³ad wywo³ania funkcji READ

*/

double READ( int numer_rozkazu )  // Funkcja READ1
{
	
	double adres_rozkazu=0;			//zwracamy zero w razie nie powodzenia
// Tu nale¿y podmieniæ na w³aœciw¹ funkcjê semafora od Michala
		//	user_semaphore( P ) ;       // Operacja któr¹ nale¿y wykonaæ przed przyst¹pieniem do operacji

			if( zaj_R2 == 1 )
			{
				cout << "Urz¹dzenie READ2 jest w tej chwili zajête!";
			}
	else 
	{
			double liczba ;

	zaj_R2=1;
	std::cout<<"Otwieram i przeszukujê bazê rozkazów \n";
	fstream bazarozkazow("rozkazy.roz",ios::in);           // co do bazy rozkazów to jest ona do stworzenia ale potrzebne s¹ dane od Pani Agnieszki.(Cytat J.B.)
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
		cout<<"Nie mo¿na otworzyæ pliku lub nie znaleziono rozkazu."<<endl;
	}
	bazarozkazow.close();

	
	cout <<adres_rozkazu<<endl<<" powy¿sza wartoœæ to odnaleziony adres rozkazu który zwrócê \n \n";
// Tu nale¿y podmieniæ na w³aœciw¹ funkcjê semafora od Michala
  	//	user_semaphore( V ) ;       // Operacja któr¹ nale¿y wykonaæ po operacji która przywruci semafor do stanu sprzed operacji
	zaj_R2=0;
	}


			return adres_rozkazu;
}