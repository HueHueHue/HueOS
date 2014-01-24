#include "globLev1.h"

Rejestr::Rejestr(){
	for(int i=0;i<4;i++){
		rejestr[i] = 0;
	}
	textLev1(1, "Rejestr zostal utworzony");
	wyswietl();
}

int Rejestr::getRejestr(int id){
	return rejestr[id-1];
}
void Rejestr::setRejestr(int id, int wartosc){
	rejestr[id-1] = wartosc;
}

void Rejestr::wyswietl(){
	HANDLE hOut;
	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hOut, 0x0C);
	cout << "Hue1: Stan rejestrow" << endl;
	for(int i=0;i<4;i++){
		cout << "	" << i+1 << "	=	" << rejestr[i] << endl;
	}
	SetConsoleTextAttribute( hOut, 0x07);
}