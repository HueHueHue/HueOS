// @autor witkowski01




#include "CREAD.h"




CREAD::CREAD()    //konstruktor i przypisanie poczatkowej wartosci zmiennej odpowiadajacej za sprawdzanie stanu.
{
	zaj_read = 0;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
	cout << "Hue4: ==> konstruktor READ wywolany!!! \n";
	SetConsoleTextAttribute( hOut, 0x07);  //Reset koloru do podstawowego
}


string CREAD::READ(  )  // Funkcja READ1
{
	
	string rozkaz;			//zwracamy zero w razie nie powodzenia

		// Tu nalezy podmienic na wlasciwa funkcje semafora od Hue1
		//	user_semaphore( P ) ;       // Operacja ktora nalezy wykonac przed przystapieniem do operacji

			if( zaj_read == 1 )
			{
				SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
				cout << "Hue4: Urzadzenie READ jest w tej chwili zajete!";
				
			}
	else 
	{
	

		zaj_read=1;

		SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );

	std::cout<<"Hue4: Otwieram i wykonuje READ \n";

	//Stara nie uzyta funkcja zostawiam nie usuwac
/*	fstream bazarozkazow("rozkazy.roz",ios::in);       
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
	*/
	

	 rozkaz = job.getData() ;


	cout << "Hue4: " <<rozkaz<<endl<<" powyzsza wartosc to rozkaz ktore zwroce \n \n";

	SetConsoleTextAttribute( hOut, 0x07);  //Reset koloru do podstawowego
	
	// Tu nalezy podmienic na wlasciwa funkcje semafora od Hue1
  	//	user_semaphore( V ) ;       // Operacja ktora nalezy wykonac po operacji ktora przywruci semafor do stanu sprzed operacji
	
	zaj_read=0;
	}

	return rozkaz;
}


string CREAD::READ_all(  )  // Funkcja READ_all czyta wszystko z karty $JOB plik
{
	
	string rozkaz;			//zwracamy zero w razie nie powodzenia

		// Tu nalezy podmienic na wlasciwa funkcje semafora od Hue1
		//	user_semaphore( P ) ;       // Operacja ktora nalezy wykonac przed przystapieniem do operacji

			if( zaj_read == 1 )
			{
				SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
				cout << "Hue4: Urzadzenie READ jest w tej chwili zajete!";
				
			}
	else 
	{
	

		zaj_read=1;

		SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );

	 cout<<"Hue4: Otwieram i wykonuje READ_all \n";
	

	 rozkaz = job.getData() ;   // Zwracam tylko ta dana ale do bufora zapisuje wszystkie
		
	 Rozmiar_job = job.getWorkspaceSize() ;
	 IOurzadzenie = job.getIODevice() ; 
	 Dane = job.getData() ;
	 zleceniodawca = job.getEmployer() ;
	


	cout <<"Hue4: "<<rozkaz<<endl<<" powyzsza wartosc to dane ktory zwroce \n \n";

	SetConsoleTextAttribute( hOut, 0x07);  //Reset koloru do podstawowego
	
	// Tu nalezy podmienic na wlasciwa funkcje semafora od Hue1
  	//	user_semaphore( V ) ;       // Operacja ktora nalezy wykonac po operacji ktora przywruci semafor do stanu sprzed operacji
	
	zaj_read=0;
	}

	return rozkaz;
}


string CREAD::READ_all(string nazwapliku){

	string nazwapliku1 = nazwapliku;
	string rozkaz = "0";			//zwracamy zero w razie nie powodzenia

	JOB *a= new JOB();
	a->JOB_nazwapliku(nazwapliku1);

		// Tu nalezy podmienic na wlasciwa funkcje semafora od Hue1
		//	user_semaphore( P ) ;       // Operacja ktora nalezy wykonac przed przystapieniem do operacji

			if( zaj_read == 1 )
			{
				SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
				cout << "Hue4: Urzadzenie READ jest w tej chwili zajete!";
				
			}
	else 
	{
	

		zaj_read=1;

		SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );

	cout<<"Hue4: Otwieram i wykonuje READ_all \n";
	

	 rozkaz = a->getData() ;   // Zwracam tylko ta dana ale do bufora zapisuje wszystkie
		
	 Rozmiar_job = a->getWorkspaceSize() ;
	 IOurzadzenie = a->getIODevice() ; 
	 Dane = a->getData() ;
	 zleceniodawca = a->getEmployer() ;
	


	cout <<"Hue4: " <<rozkaz<<endl<<" powyzsza wartosc to dane ktory zwroce \n \n";

	SetConsoleTextAttribute( hOut, 0x07);  //Reset koloru do podstawowego
	
	// Tu nalezy podmienic na wlasciwa funkcje semafora od Hue1
  	//	user_semaphore( V ) ;       // Operacja ktora nalezy wykonac po operacji ktora przywruci semafor do stanu sprzed operacji
	
	zaj_read=0;
	}

	return rozkaz;

}

void CREAD::READ_all(string WorkspaceSize, string IODevice, string Data, string Employer){

	string rozkaz = "0";

	string rozmiarpracy1 = WorkspaceSize;
	string IDUrzadzenia1 = IODevice;
	string dane1 = Data;
	string zleceniodawca1 = Employer;
		

	JOB *a= new JOB();
	a->Job (rozmiarpracy1 , IDUrzadzenia1 , dane1 , zleceniodawca1);

		// Tu nalezy podmienic na wlasciwa funkcje semafora od Hue1
		//	user_semaphore( P ) ;       // Operacja ktora nalezy wykonac przed przystapieniem do operacji

			if( zaj_read == 1 )
			{
				SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
				cout << "Hue4: Urzadzenie READ jest w tej chwili zajete!";
				
			}
	else 
	{
	

		zaj_read=1;

		SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );

	cout<<"Hue4: Otwieram i wykonuje READ_all bez pliku \n";
	

	 rozkaz = a->getData() ;   // Zwracam tylko ta dana ale do bufora zapisuje wszystkie
		
	 Rozmiar_job = a->getWorkspaceSize() ;
	 IOurzadzenie = a->getIODevice() ; 
	 Dane = a->getData() ;
	 zleceniodawca = a->getEmployer() ;
	


	cout <<"Hue4: "<<rozkaz<<endl<<" powyzsza wartosc to dane ktory zwroce \n \n";

	SetConsoleTextAttribute( hOut, 0x07);  //Reset koloru do podstawowego
	
	// Tu nalezy podmienic na wlasciwa funkcje semafora od Hue1
  	//	user_semaphore( V ) ;       // Operacja ktora nalezy wykonac po operacji ktora przywruci semafor do stanu sprzed operacji
	
	zaj_read=0;
	}

	

}




// Jesli chcemy uzyskac inne dane uzyc ponizszysz operacji ale tylko pod warunkiem wykonania READ_all !!!!
string CREAD::READ_all_returnWorkaspceSize(){

	string WorkaspceSize;

	WorkaspceSize = job.getWorkspaceSize();

return WorkaspceSize;
}
string CREAD::READ_all_returnIODevice(){

	string IODevice;

	IODevice = job.getIODevice();

return IODevice;
}
string CREAD::READ_all_returnData(){

	string Data;

	Data = job.getData();

return Data;
}
string CREAD::READ_all_returnEmployer(){
	
	string Employer;

	Employer = job.getEmployer();

return Employer;
}