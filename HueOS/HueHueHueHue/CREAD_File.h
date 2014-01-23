#ifndef CREAD_File_h
#define CREAD_File_h

// @autor witkowski01



#include<iostream>
#include<fstream>
#include <string>

#include <windows.h>
#include <cstdlib>

using namespace std;



class CREAD_File
{
private:
        // Zmienna ta jest potrzebna do sprawdzenia czy uzadzenie jest zajete czy nie, gdyz nie mam dostepu do
//sprawdzenia wartosci semaforow, na ktorych wykonuje operacje.
        
        
        int zaj_read;
        HANDLE hOut;

                // Jesli zaj = 1 to znaczy ze trwa operacja ,
                //jesli zaj = 0 to znaczy ze urzadzenie jest wolne i mozna wykonac na nim operacje
                
protected:

public:
        CREAD_File();
        int READ_Int_File(string nazwapliku);
		string READ_String_File(string nazwapliku);

};



/*

 CREAD_File.READ_File(2);
  przyklad wywolania funkcji READ_File

*/

#endif