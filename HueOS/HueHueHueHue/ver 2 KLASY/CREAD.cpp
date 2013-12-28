#include "CREAD.h"




CREAD::CREAD()   //konstruktor i przypisanie pocz¹tkowej wartoœci zmiennej odpowiadaj¹cej za sprawdzanie stanu.
{
	zaj_read = 0;
	cout << "==> konstruktor READ wywo³any!!! \n";
}


double CREAD::READ( int numer_rozkazu )  // Funkcja READ1
{
	
	double adres_rozkazu=0;			//zwracamy zero w razie nie powodzenia

// Tu nale¿y podmieniæ na w³aœciw¹ funkcjê semafora od Michala
		//	user_semaphore( P ) ;       // Operacja któr¹ nale¿y wykonaæ przed przyst¹pieniem do operacji

			if( zaj_read == 1 ){
				cout << "Urz¹dzenie READ jest w tej chwili zajête!";
			}
	else 
	{
	
		double liczba ;

	zaj_read=1;
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
	
	zaj_read=0;
	}

	return adres_rozkazu;
}