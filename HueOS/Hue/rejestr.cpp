#include "globLev1.h"

Rejestr::Rejestr(){
	for(int i=0;i<4;i++){
		rejestr[i] = 0;
	}

}

int Rejestr::getRejestr(int id){
	return rejestr[id-1];
}
void Rejestr::setRejestr(int id, int wartosc){
	rejestr[id-1] = wartosc;
}