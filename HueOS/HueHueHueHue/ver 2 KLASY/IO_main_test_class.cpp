#include "CPRINT.h"
#include "CREAD.h"
using namespace  std;

int main()
{
	CPRINT drukarka1;
	CREAD czytnik1;

	drukarka1.PRINT("sdasdasd");
	drukarka1.PRINT("adasskosand dasdasd sdjasdajdso");
	
	czytnik1.READ(2);

	int i;
	cin >> i;
	return 0;

}