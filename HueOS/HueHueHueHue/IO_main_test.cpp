// @ autor witkowski01




#include "CPRINT.h"
#include "CREAD.h"
#include "CREAD_File.h"
using namespace  std;

int main()
{

	string dane1;
	CPRINT drukarka1;
	CREAD czytnik1;
	CREAD_File czytnik2;

	//JOB karta1;

	//drukarka1.PRINT("sdasdasd");
	//drukarka1.PRINT("adasskosand dasdasd sdjasdajdso");
	
	czytnik2.READ_String_File("dane.txt");
	czytnik2.READ_Int_File("dane.txt");
	czytnik1.READ_all("Job.job");
	czytnik1.READ();
	cout<<dane1<<endl;
	int i;
	cin >> i;
	return 0;

}