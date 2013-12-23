#include <iostream>

using namespace std;
#include "pamiec.h"



/////////////////////////////////////////////////////////////////////////////////

list::list()
{
	head = NULL;
}


list::~list()
{
	while (head) usun();
}

void list::dodaj(unsigned short pierwszy_bajt, unsigned short rozmiar)
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


void list::usun()
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

void list::wyswietl()
{
	lista *p = head;
	do
	{
		cout << p->pierwszy_bajt << endl;
		p = p->next;
	} while (p != head);


}

unsigned char list::ile()
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
//////////////////////////////////////////////////////////////////


pamiec::pamiec()
{
	wolna_pamiec.dodaj(0, 512);

}

pamiec::~pamiec()
{
	wolna_pamiec.~list();
	zajeta_pamiec.~list();
}

void pamiec::zwolnij_pamiec(unsigned short pierwszy_bajt)//dokoñczyc
{
	//wolna_pamiec.dodaj(miejsce->pierwszy_bajt, miejsce->rozmiar);
	while (zajeta_pamiec.head->pierwszy_bajt != pierwszy_bajt)
	{
		zajeta_pamiec.head = zajeta_pamiec.head->next;
	}
	unsigned short rozmiar;
	rozmiar = zajeta_pamiec.head->rozmiar;
	zajeta_pamiec.usun();

	// tu dalej cos bedzie
}

unsigned short pamiec::zajmnij_pamiec(unsigned short rozmiar)// moze uproszcze
{

	if (semafor_pamieci == false)
	{

		return 0xFFFF;
	}

	lista *it = wolna_pamiec.head;// iteratorek
	lista *tmp = it;
	unsigned short roznica = 0xFFFF;


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

		unsigned short kopia = tmp->pierwszy_bajt;
		zajeta_pamiec.dodaj(tmp->pierwszy_bajt, rozmiar);
		lista *temp = wolna_pamiec.head;
		if (wolna_pamiec.head == tmp)
		{
			wolna_pamiec.usun();
		}
		else
		{
			wolna_pamiec.head = tmp;
			wolna_pamiec.usun();
			wolna_pamiec.head = temp;
		}

		return kopia;
	}
	else
	{
		if (roznica == 0xFFFF)
		{

			semafor_pamieci = false;
			return 0xFFFF;
		}
		else
		{
			zajeta_pamiec.dodaj(tmp->pierwszy_bajt, rozmiar);
			unsigned short kopia = tmp->pierwszy_bajt;
			tmp->pierwszy_bajt += rozmiar;
			tmp->rozmiar -= rozmiar;
			return kopia;
		}

	}

}


bool pamiec::ustaw_bajt(unsigned short pierwszy_bajt, unsigned short indeks, char bajt)//zrobi sie
{

	return true;
}

char pamiec::pobierz_bajt(unsigned short pierwszy_bajt, unsigned short indeks)
{


	return 0;
}


///////////////////////////////////////////////////////////////

void pamiec::scal_wolna_pamiec()//przeprojektowac
{
	lista *it = wolna_pamiec.head;
	lista *it2 = wolna_pamiec.head;

	unsigned short ile = wolna_pamiec.ile();
	for (unsigned short i = 0; i < ile; i++)
	{
		it = it->next;
		if (wolna_pamiec.head->pierwszy_bajt + wolna_pamiec.head->rozmiar == it->pierwszy_bajt)
		{
			wolna_pamiec.head->rozmiar += it->rozmiar;

		}
	}
	it = wolna_pamiec.head;
	for (unsigned short i = 0; i < ile; i++)
	{

	}

}

void sortuj_wolna_pamiec()
{



}
