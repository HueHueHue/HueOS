#include "../global.h"
#include "../Hue/globLev1.h"
#include "../HueHueHue/lev3.h"
#include "sysproces.h"
#include <vector>
#include "interpreter.h"
#include "split.h"
#include "../HueHueHueHue/CPRINT.h"
#include "../HueHueHueHue/CREAD_File.h"
#include "../HueHueHueHue/JOB.h"

class Supervisor {
public:
	CPRINT drukarka1;
	CREAD_File czytnik1;
	Planista* mPlanista;
	Lev3* mPoz3;
	static const char * const names[3];

	Supervisor(Planista* mPlanista, Lev3* mPoz3);
	void init();
	void checkMessages();
};
