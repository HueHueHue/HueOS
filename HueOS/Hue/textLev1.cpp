#include "../global.h"

void textLev1(bool dziala, string wiadomosc){
	string o = "Hue1: ";
	if(dziala){
		o += "Info: ";
	} else {
		o += "Blad: ";
	}
	o += wiadomosc;

	HANDLE hOut;
	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hOut, 0x0C);

	cout << o  << endl;

	SetConsoleTextAttribute( hOut, 0x07);
}