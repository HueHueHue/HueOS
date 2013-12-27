#include "global.h"
#include "Hue/proces.h"
#include "Hue/planista.h"

int main() {
	cout << "Ahoj, przygodo!" << endl;

	Proces* startWszystkie = NULL;

	Planista mPlanista(startWszystkie);

	while(1){
		mPlanista.startCykl();

	}

	return 0;
}
