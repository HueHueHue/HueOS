#include <iostream>


struct lista
{
	lista * next;
	unsigned short pierwszy_bajt, rozmiar;
};

class list
{
public:
	lista * head;  // punkt wejœcia do listy

	list();        // konstruktor
	~list();       // destruktor

	void	 wyswietl();
	void     dodaj(unsigned short pierwszy_bajt, unsigned short rozmiar);
	void     usun();
	unsigned char	 ile();
};

/*struct lista_czekajacych_procesow
{
unsigned char id_procesu;
unsigned short rozmiar;
};

struct proces_i_pierwszy_bajt
{
	unsigned short pierwszy_bajt;
	unsigned char id_procesu;
};*/

class pamiec
{
private:
	list wolna_pamiec, zajeta_pamiec;
	char tablica_pamieci[512];
	bool semafor_wolnej_pamieci, semafor_pamieci;
	void sortuj_wolna_pamiec();
	void scal_wolna_pamiec();
public:
	pamiec();
	~pamiec();
	unsigned short zajmnij_pamiec(unsigned short rozmiar);//do uzycia podczas powstawania procesu, gdy zwrocone jest 0xFFFF oznacza ze brak wolnej pamieci, zwracany pierwszy bajt- index tablicy pamieci
	void zwolnij_pamiec(unsigned short pierwszy_bajt);// gdy proces umiera, moze zmienie na bool, dla wiekszekj kontroli
	char pobierz_bajt(unsigned short pierwszy_bajt, unsigned short indeks);//czytanie pamieci dokladnie bajtu, chyba jako blad dostępu użyje wartość 0xFF
	bool ustaw_bajt(unsigned short pierwszy_bajt, unsigned short indeks, char bajt);// zapisywanie do pamieci, jesli prawda zapis sie powiodł

};