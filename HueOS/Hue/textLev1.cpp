#include "../global.h"

void textLev1(int id){
	string o = "Hue1: ";
	if(id>=0 && id <= 50){
		o += "B��d: ";
	} else {
		o += "Info: ";
	}
	switch(id){
	case 0:
		o += "Nieznany";
		break;
	case 51:
		o += "Brak proces�w na li�cie";
		break;
	default:
		o += "Nieznany (chyba programista si� machn��);";
	}
	
	HANDLE hOut;
	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hOut, 0x0C);

	cout << o << " [#" << id << "]" << endl;

	SetConsoleTextAttribute( hOut, 0x07);
}