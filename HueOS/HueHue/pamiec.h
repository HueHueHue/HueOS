#include <iostream>
#include <string>
using namespace std;

struct lista
{
	lista * next;
	unsigned short pierwszy_bajt, rozmiar;
};

class listka
{
public:
	lista * head;  // punkt wejœcia do listy

	listka();        // konstruktor
	~listka();       // destruktor

	void	 wyswietl();
	void     dodaj(unsigned short pierwszy_bajt, unsigned short rozmiar);
	void     usun();
	unsigned char	 ile();
};



class pamiec
{
private:
	listka wolna_pamiec, zajeta_pamiec;
	unsigned char tablica_pamieci[512];
	bool semafor_wolnej_pamieci, semafor_pamieci;
	void sortuj_wolna_pamiec(lista* dodany);
	void scal_wolna_pamiec(lista* dodany);
	void wypisz(string a);
public:
	pamiec();
	~pamiec();
	unsigned short zajmij_pamiec(unsigned short rozmiar);//do uzycia podczas powstawania procesu, gdy zwrocone jest 0xFFFF oznacza ze brak wolnej pamieci, zwracany pierwszy bajt- index tablicy pamieci
	bool zwolnij_pamiec(unsigned short pierwszy_bajt);// gdy proces umiera, jesli zwrocone true - powiodlo sie, jezeli nie semafor blokuje dostep do wolnej pamieci - malo prawdopodobne
	char pobierz_bajt(unsigned short pierwszy_bajt, unsigned short indeks);//czytanie pamieci dokladnie bajtu, jako bład wartosc 0xFF
	bool ustaw_bajt(unsigned short pierwszy_bajt, unsigned short indeks, unsigned char bajt);// zapisywanie do pamieci, jesli prawda zapis sie powiodl

}; 
