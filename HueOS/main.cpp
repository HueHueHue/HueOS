#include "global.h"
#include "proces.h"
#include "semafor.h"
#include "planista.h"

int main() {
	cout << "Ahoj, przygodo!" << endl;

	Proces* startWszystkie = NULL;

	Planista mPlanista(startWszystkie);

	while(1){
		mPlanista.startCykl();

	}

	return 0;
}
