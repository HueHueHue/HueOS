#include <iostream>
#include <string>
#include <windows.h>

using namespace std;
#include "pamiec.h"



/////////////////////////////////////////////////////////// obsluga listy cyklicznej

listka::listka()
{
	head = NULL;

}


listka::~listka()
{
	while (head) usun();
}

void listka::dodaj(unsigned short pierwszy_bajt, unsigned short rozmiar)
{
	lista * p = new lista;

	p->pierwszy_bajt = pierwszy_bajt;
	p->rozmiar = rozmiar;
	if (head)
	{
		p->next = head->next;
		head->next = p;
	}
	else p->next = p;
	head = p;
}


void listka::usun()
{
	if (head)
	{
		lista * p = head->next;
		head->pierwszy_bajt = p->pierwszy_bajt;
		head->rozmiar = p->rozmiar;
		head->next = p->next;
		if (p->next == p) head = NULL;
		delete p;
	}
}

void listka::wyswietl()
{
	lista *p = head;
	do
	{
		cout << p->pierwszy_bajt << endl;
		p = p->next;
	} while (p != head);


}

unsigned char listka::ile()
{
	lista *p = head;
	unsigned char licznik = 0;
	do
	{
		licznik++;
		p = p->next;

	} while (p != head);

	return licznik;
}
////////////////////////////////////////////////////////////////// konstruktor i destruktor


pamiec::pamiec()
{
	wolna_pamiec.dodaj(12, 500);
	zajeta_pamiec.dodaj(0, 12);
	semafor_pamieci = true;
	semafor_wolnej_pamieci = true;
	wypisz("Modul pamieci wita");

}

pamiec::~pamiec()
{
	wolna_pamiec.~listka();
	zajeta_pamiec.~listka();
	wypisz("Modul pamieci zegna");
}

///////////////////////////////////////////////////////////////// metody



void pamiec::sortuj_wolna_pamiec(lista* dodany)
{
	
	bool przerwij = false;
	lista* it = wolna_pamiec.head;
	wypisz("Sortowanie - wstawienie swiezo dodanego elementu w odpowiednie miejsce");
	do
	{
		if (dodany->rozmiar < it->rozmiar)
		{
			if (it == wolna_pamiec.head)
			{
				lista* tmp = wolna_pamiec.head;
				while (tmp->next != wolna_pamiec.head)
				{
					tmp = tmp->next;
				}
				wolna_pamiec.head = tmp;
				wolna_pamiec.dodaj(dodany->pierwszy_bajt, dodany->rozmiar);
				tmp = wolna_pamiec.head->next;
				wolna_pamiec.head = dodany;
				wolna_pamiec.usun();
				wolna_pamiec.head = tmp;

			}
			else
			{
				unsigned short t1, t2;
				t1 = it->pierwszy_bajt;
				t2 = it->rozmiar;
				it->pierwszy_bajt = dodany->pierwszy_bajt;
				it->rozmiar = dodany->rozmiar;
				lista* tmp = wolna_pamiec.head;
				wolna_pamiec.head = it;
				wolna_pamiec.dodaj(t1, t2);
				if (dodany->next == tmp)
				{
					wolna_pamiec.head = dodany;
					wolna_pamiec.usun();
					
				}
				else
				{
					wolna_pamiec.head = dodany;
					wolna_pamiec.usun();
				}
				
			}
			
			przerwij = true;
		}
		it = it->next;
	} while (it != wolna_pamiec.head&&przerwij==false);
	

}
void pamiec::scal_wolna_pamiec(lista* dodany)//przeprojektowac
{
	
	lista *it = dodany;
	lista *tmp = 0;
	lista* do_sortowania = dodany;
	bool przerwij = false;
	do// sprawdzanie czy w liscie jest dziura do polaczenia o wyzszych adresach
	{
		
		if (dodany->pierwszy_bajt + dodany->rozmiar == it->pierwszy_bajt)
		{
			wypisz("Scalenie z dziura ktora ma pierwszy bajt wiekszy");
			if (it == wolna_pamiec.head)
			{
				dodany->rozmiar += it->rozmiar;
				if (wolna_pamiec.head->next == dodany)
				{
					wolna_pamiec.usun();
					przerwij = true;
					dodany = wolna_pamiec.head;
					do_sortowania = dodany;
				}
				else
				{
					wolna_pamiec.usun();
					przerwij = true;
					do_sortowania = dodany;
				}
				
			}
			else
			{
				dodany->rozmiar += it->rozmiar;
				if (wolna_pamiec.head==it->next)
				{
					
					wolna_pamiec.head = it;
					if (wolna_pamiec.head->next == dodany)
						dodany = wolna_pamiec.head;
					wolna_pamiec.usun();
					przerwij = true;
					do_sortowania = dodany;
				}
				else
				{
					tmp = wolna_pamiec.head;
					wolna_pamiec.head = it;
					if (wolna_pamiec.head->next == dodany)
						dodany = wolna_pamiec.head;
					wolna_pamiec.usun();
					wolna_pamiec.head = tmp;
					przerwij = true;
					do_sortowania = dodany;
				}
				
			}
		}
		it = it->next;
	} while (it!=dodany&&przerwij==false);
	
	
	przerwij = false;
	
	
	do// sprawdzanie czy w liscie jest dziura do polaczenia o nizszych adresach
	{
		
		if (it->pierwszy_bajt + it->rozmiar == dodany->pierwszy_bajt)
		{
			wypisz("Scalenie z dziura ktora ma pierwszy bajt mniejszy");
			if (dodany == wolna_pamiec.head)
			{
				it->rozmiar += dodany->rozmiar;
				if (wolna_pamiec.head->next == it)// aby nie usunac wyjscia
				{
					przerwij = true;
					wolna_pamiec.usun();
					do_sortowania = wolna_pamiec.head;
				}
				else
				{

					wolna_pamiec.usun();
					przerwij = true;
					do_sortowania = it;
				}
				
			}
			else
			{
				it->rozmiar += dodany->rozmiar;
				tmp = wolna_pamiec.head;
				wolna_pamiec.head = dodany;
				if (wolna_pamiec.head->next == it)
				{
					wolna_pamiec.usun();
					do_sortowania = wolna_pamiec.head;
					przerwij = true;
					wolna_pamiec.head = tmp;
				}
				else
				{
					if (wolna_pamiec.head->next != tmp)
					{
						wolna_pamiec.usun();
						wolna_pamiec.head = tmp;
					}
					else
						wolna_pamiec.usun();
					przerwij = true;
					do_sortowania = it;
				}
				
			}
			
		}
		it = it->next;
	} while (it != dodany&& przerwij == false);
	
	wypisz("Przekazanie dziury do sortowania");
	sortuj_wolna_pamiec(do_sortowania);
}
void pamiec::wypisz(string a)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "Hue2: " << a << endl;
	SetConsoleTextAttribute( hOut, 0x07);
}


bool pamiec::zwolnij_pamiec(unsigned short pierwszy_bajt)
{
	wypisz("Zwalnianie pamieci");
	if (semafor_wolnej_pamieci == false)
	{
		wypisz("Semafor wolnej pamieci blokuje zwolenienie pamieci");
		return false;
	}
		
	semafor_wolnej_pamieci = false;
	wypisz("Ustawienie semafora wolnej pamieci na 0");
	unsigned char i = 0,ile=zajeta_pamiec.ile();
	while (zajeta_pamiec.head->pierwszy_bajt != pierwszy_bajt&&i<=ile)//szukanie w zajetej pamieci
	{
		zajeta_pamiec.head = zajeta_pamiec.head->next;
		i++;
	}
	if (i > ile)
	{
		wypisz("nie znaleziono takiego bloku w zajetej pamieci - blad");
		return false;
	}
	unsigned short rozmiar;
	rozmiar = zajeta_pamiec.head->rozmiar;
	zajeta_pamiec.usun();
	wypisz("Usuniecie z zajetej pamieci wybranego elementu");
	wypisz("Wstawienie tego elementu do listy wolnej pamieci i przekazanie je do metody scalania");
	wolna_pamiec.dodaj(pierwszy_bajt, rozmiar);
	scal_wolna_pamiec(wolna_pamiec.head);
	semafor_pamieci = true;
	wypisz("Ustawienie semafora wolnej pamieci na 1");
	wypisz("Ustawienie semafora pamieci na 1");
	semafor_wolnej_pamieci = true;
	return true;
}
unsigned short pamiec::zajmij_pamiec(unsigned short rozmiar)// moze uproszcze
{

	if (semafor_pamieci == false)
	{
		wypisz("Brakuje pamieci - powiadomil nas o tym semafor pamieci");
		return 0xFFFF;
	}

	lista *it = wolna_pamiec.head;// iteratorek
	lista *tmp = it;// wskaznik na najbardziej dopasowana dziure
	unsigned short roznica = 0xFFFF;//max wartosc


	do {
		it = it->next;
		if (it->rozmiar >= rozmiar&&it->rozmiar - rozmiar < roznica)
		{
			roznica = it->rozmiar - rozmiar;
			tmp = it;
		}
	} while (it != wolna_pamiec.head);

	//zajeta_pamiec.dodaj(tmp->pierwszy_bajt, rozmiar);



	if (roznica == 0)
	{
		wypisz("Znieleziono dziure o takiej wielkosci jaka potrzeba");
		unsigned short kopia = tmp->pierwszy_bajt;
		zajeta_pamiec.dodaj(tmp->pierwszy_bajt, rozmiar);
		lista *temp = wolna_pamiec.head;
		if (wolna_pamiec.head == tmp)
		{
			wolna_pamiec.usun();
		}
		else
		{
			if (wolna_pamiec.head == tmp->next)
			{
				wolna_pamiec.head = tmp;
				wolna_pamiec.usun();
			}
			else
			{
				wolna_pamiec.head = tmp;
				wolna_pamiec.usun();
				wolna_pamiec.head = temp;
			}

		}
		wypisz("Zwracanie pierwszego bajtu");
		return kopia;
	}
	else
	{
		if (roznica == 0xFFFF)
		{
			wypisz("Nie znaleziono odpowiedniej dziury - ustawienie semafora pamieci na 0");
			semafor_pamieci = false;
			return 0xFFFF;
		}
		else
		{
			wypisz("Znaleziono wieksza dziure niz potrzeba");
			zajeta_pamiec.dodaj(tmp->pierwszy_bajt, rozmiar);
			unsigned short kopia = tmp->pierwszy_bajt;
			tmp->pierwszy_bajt += rozmiar;
			tmp->rozmiar -= rozmiar;
			semafor_wolnej_pamieci = false;
			wypisz("Ustawienie semafora wolnej pamieci na 0");
			sortuj_wolna_pamiec(tmp);
			wypisz("Ustawienie semafora wolnej pamieci na 1");
			wypisz("Zwracanie pierwszego bajtu");
			semafor_wolnej_pamieci = true;
			return kopia;
		}

	}

}
bool pamiec::ustaw_bajt(unsigned short pierwszy_bajt, unsigned short indeks, unsigned char bajt)
{
	lista *it = zajeta_pamiec.head;
	bool	przerwij=false;
	do
	{
		it = it->next;
		if (it->pierwszy_bajt == pierwszy_bajt)
		{
			przerwij = true;
		}
		
	} while (it!=zajeta_pamiec.head&&przerwij==false);
	if (przerwij == true)
	{
		if (indeks < it->rozmiar)
		{
			//wypisz("Wpisano bajt do tablicy pamieci");
			tablica_pamieci[pierwszy_bajt + indeks] = bajt;
			return true;
		}
		else
		{
			wypisz("Niepowolany doostep do pamieci - przekroczona wartosc indeksu");
			return false;
		}
	}
	else
	{
		wypisz("Blad - brak odpowiedniego elementu w zajetej pamieci");
		return false;
	}
	
}
char pamiec::pobierz_bajt(unsigned short pierwszy_bajt, unsigned short indeks)
{
	char const blad = 0xFF;// kod bledu
	lista *it = zajeta_pamiec.head;
	bool	przerwij = false;
	do
	{
		it = it->next;
		if (it->pierwszy_bajt == pierwszy_bajt)
		{
			przerwij = true;
		}

	} while (it != zajeta_pamiec.head && przerwij == false);
	if (przerwij == true)
	{
		if (indeks < it->rozmiar)
		{
			return tablica_pamieci[pierwszy_bajt + indeks];
			wypisz("zwrocenie zadanego bajtu");
		}
		else
		{
			wypisz("Niepowolany doostep do pamieci - przekroczona wartosc indeksu");
			return blad;
		}
	}
	else
	{
		wypisz("Blad - brak odpowiedniego elementu w zajetej pamieci");
		return blad;
	}

}
