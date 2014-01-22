#include "../global.h"
#include "sysproces.h"
#include <vector>
#include "split.h"
#include "../Hue/globLev1.h"
#include "../HueHueHue/lev3.h"
#include "../HueHueHueHue/CPRINT.h"
#include "../HueHueHueHue/JOB.h"

class Supervisor : public Proces {
public:
	CPRINT drukarka1;
	CREAD czytnik1;
	Planista* mPlanista;
	Lev3* mPoz3;
	string names[3] = {"*IBSUP", "*IN", "*OUT"};

	Supervisor(Planista* mPlanista, Lev3* mPoz3);
	void init();
	void checkMessages();
};
