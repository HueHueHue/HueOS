// @autor witkowski01


#include "CREAD_File.h"




CREAD_File::CREAD_File()    //konstruktor i przypisanie poczatkowej wartosci zmiennej odpowiadajacej za sprawdzanie stanu.
{
        zaj_read = 0;
                hOut = GetStdHandle( STD_OUTPUT_HANDLE );
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
        wypisz(" ==> konstruktor READ wywolany!!! ");
        SetConsoleTextAttribute( hOut, 0x07);
}


string CREAD_File::READ_String_File(string nazwapliku)  // Funkcja READ1
{
        
        string dane;                        //zwracamy zero w razie nie powodzenia

// Tu nalezy podmienic na wlasciwa funkcje semafora od Michala
                //        user_semaphore( P ) ;       // Operacja ktora nalezy wykonac przed przystapieniem do operacji

                        if( zaj_read == 1 ){
                                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
                                wypisz(" Urzadzenie READ_File jest w tej chwili zajete!");
                                
                        }
        else 
        {
		SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
       

        zaj_read=1;
		wypisz("Otwieram i przeszukuje plik {" + nazwapliku + "}");
        fstream plik(nazwapliku,ios::in);            // co do bazy rozkazow to jest ona do stworzenia ale potrzebne sa dane od Pani Agnieszki.(Cytat J.B.)
				
				if(plik.is_open())
				{
					 getline(plik, dane);
				}
				else 
				{
						wypisz(" Nie mozna otworzyc pliku lub danych.");
				}
				plik.close();

        wypisz(dane + " powyzsza wartosc dane ktore zwroce");
			//	cout << "Hue4: " << dane << endl; wypisz( " powyzsza wartosc dane ktore zwroce \n");
        SetConsoleTextAttribute( hOut, 0x07);
        
        // Tu nalezy podmienic na wlasciwa funkcje semafora od Michala
          //        user_semaphore( V ) ;       // Operacja ktora nalezy wykonac po operacji ktora przywruci semafor do stanu sprzed operacji
        
        zaj_read=0;
        }

        return dane;
}

int CREAD_File::READ_Int_File(string nazwapliku)  // Funkcja READ1
{
        
        int dane;                        //zwracamy zero w razie nie powodzenia

// Tu nalezy podmienic na wlasciwa funkcje semafora od Michala
                //        user_semaphore( P ) ;       // Operacja ktora nalezy wykonac przed przystapieniem do operacji

                        if( zaj_read == 1 ){
                                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
                                wypisz(" Urzadzenie READ_File jest w tej chwili zajete!");
                                
                        }
        else 
        {
		SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
        
    

        zaj_read=1;
		wypisz(" Otwieram i przeszukuje plik "); cout << nazwapliku << endl;
        fstream plik(nazwapliku,ios::in);            // co do bazy rozkazow to jest ona do stworzenia ale potrzebne sa dane od Pani Agnieszki.(Cytat J.B.)
				
				if(plik.is_open())
				{
					 plik>>dane;
				}
				else 
				{
					wypisz(" Nie mozna otworzyc pliku lub nie znaleziono danych.");
				}
				plik.close();

        
				cout << "Hue4: " << dane << endl; wypisz(" powyzsza wartosc dane ktore zwroce \n ");
        SetConsoleTextAttribute( hOut, 0x07);
        
        // Tu nalezy podmienic na wlasciwa funkcje semafora od Michala
          //        user_semaphore( V ) ;       // Operacja ktora nalezy wykonac po operacji ktora przywruci semafor do stanu sprzed operacji
        
        zaj_read=0;
        }

        return dane;
}


void CREAD_File::wypisz(string a)
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Hue4: " << a << endl;
	SetConsoleTextAttribute(hOut, 0x07);
}