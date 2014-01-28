#include "global.h"
#include "Hue/globLev1.h"
#include "HueHueHue/lev3.h"
#include "HueHue/pamiec.h"
#include "HueHueHueHueHue/supervisor.h"
#include "HueHueHueHueHue/split.h"
void tRzeczywisty(float t, DWORD tStart);
void decyzja(Planista* mPlanista, Rejestr* mRejestr, pamiec* opamiec, Supervisor* mSupervisor);


int main() {
	cout << "Hue0:				Start systemu" << endl;
	cout << "		###   ###   ##   ##   #######          ####" << endl;
	cout << "		###   ###   ##   ##   ##         ###  # " << endl;
	cout << "		#########   ##   ##   #######   #   #  ####" << endl;
	cout << "		###   ###   ### ###   ##        #   #      #" << endl;
	cout << "		###   ###    #####    #######    ###   ####" << endl;

	cin.ignore(INT_MAX, '\n');
	cout << "Hue0: Inicjowanie klas.." << endl;
	cout << endl << "Hue0: Lev1" << endl;
	//1
	int licznikJednostek = 0;
	Proces* procesList = new Proces(0, "Proces bezczynnosciowy", 0); //proces od ktorego zaczynam iterowac po wszystkich.
	procesList->blocked = 1;
	Rejestr* mRejestr = new Rejestr();
	Planista* mPlanista = new Planista(procesList, mRejestr);
	//1
	cout << endl << "Hue0: Lev2" << endl;
	//2
	pamiec *opamiec = new pamiec();
	//2
	cout << endl << "Hue0: Lev3" << endl;
	//3
	Lev3* mPoz3 = new Lev3(procesList,mRejestr,opamiec);
	//3
	cout << endl << "Hue0: Lev5" << endl;
	//5
	Supervisor* supervisor = new Supervisor(mPlanista, mPoz3, opamiec, mRejestr);
	supervisor->init();
	//5

	DWORD tStart; //Petla czasu rzeczywistego

	cout << endl << endl << "Hue0:			<<<<< Start petli >>>>>" << endl << endl;
	cout << string(80, '-') << endl;
	cout << endl;

	while(1){
		licznikJednostek++;
		cout << "Hue0:		Start jednostki czasowej [ " << licznikJednostek << " ]." << endl;
		tStart = GetTickCount(); //czas na rozpoczeciu petli
		mPlanista->startCykl(); //Hue1

		supervisor->execute(mPlanista->Running);

		supervisor->checkMessages();

		//Koniec operacji w tym cyklu
		//tRzeczywisty(5, tStart); //Czekanie na koniec minimalnego czasu cyklu, tryb AUTO

		decyzja(mPlanista, mRejestr, opamiec, supervisor); //Tryb manualny
	}

	return 0;
}




////////////
// Czekanie na koniec minimalnego czasu cyklu - funkcja
void tRzeczywisty(float t, DWORD tStart){
	DWORD tTeraz;
	do{
			tTeraz = GetTickCount();
		} while(tTeraz - tStart < t*1000);
	cout << "Hue0: Koniec jednostki czasu" << endl;

	cout << string(80, '-') << endl;
	cout << endl;
}
//
////////////

void wyswietlKomendy();
void decyzja(Planista* mPlanista, Rejestr* mRejestr, pamiec* opamiec, Supervisor* mSupervisor){
	cout << "Hue0: Koniec jednostki czasu" << endl;
	string line;
	vector<string> x;
	bool end = false;
	cout << string(80, '-') << endl;
	do {
		cout << endl;
		cout << "> Wprowadz komende (<ENTER> - nastepna jednostka, help - komendy)" << endl << "> ";
		
		getline(cin, line);
		x = split(line, ' ');
		cout << endl;
		if (x.size() == 0) {
			end = true;
		} else if (x[0] == "help") {
			wyswietlKomendy();
		} else if(x[0] == "load") {
			if (x.size() == 2) {
				mSupervisor->loadJob(x[1]);
			} else {
				cout << "Nieprawidlowa liczba argumentow." << endl;
			}
		} else if(x[0] == "pamiec") {
			opamiec->wyswietl_tablice_pamieci_dziesietnie();
		} else if(x[0] == "pamiec16") {
			opamiec->wyswietl_tablice_pamieci_szesnastkowo();
		} else if(x[0] == "pcb") {
			mPlanista->wyswietl();
		} else if (x[0] == "rejestr") {
			mRejestr->wyswietl();
		} else if (x[0] == "drukarka") {
			mSupervisor->wyswietlDrukarka1();
		} else if (x[0] == "wyczyscDrukarka") {
			mSupervisor->wyczyscDrukarka1();
		} else {
			cout << "Zla komenda" << endl;
			end = false;
		}
		cout << string(80, '-') << endl;
	} while(end == false);
}

void wyswietlKomendy(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 0x0F);
	cout << "> Dostepne komendy:" << endl; 

	
	cout << " >	";
	SetConsoleTextAttribute(hOut, 0x12);
	cout << "<ENTER>"; SetConsoleTextAttribute(hOut, 0x07);
	cout<<"		-zaczyna kolejna jendnostke czasu systemu" << endl;

	SetConsoleTextAttribute(hOut, 0x0C);
	cout << "1> pcb"; SetConsoleTextAttribute(hOut, 0x07);
	cout<<"			-wyswietla procesy na liscie glownej" << endl;

	SetConsoleTextAttribute(hOut, 0x0C);
	cout << "1> rejestr"; SetConsoleTextAttribute(hOut, 0x07);
	cout<<"		-wyswietla stan rejestru" << endl;

	
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "2> pamiec"; SetConsoleTextAttribute(hOut, 0x07);
	cout<<"		-wyswietla zawartosc pamieci" << endl;

	
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); 
	cout << "2> pamiec16"; SetConsoleTextAttribute(hOut, 0x07);
	cout<<"		-wyswietla zawartosc pamieci w postaci szesnastkowej" << endl;
	
	
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "4> drukarka"; SetConsoleTextAttribute(hOut, 0x07);
	cout<<"		-wyswietla 10 wydrukowanych danych" << endl;

	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "4> wyczyscDrukarka"; SetConsoleTextAttribute(hOut, 0x07);
	cout << "	-czysci plik druku" << endl;
	
	SetConsoleTextAttribute(hOut, 0x0D);
	cout << "5> load"; SetConsoleTextAttribute(hOut, 0x07);
	cout<<"			-zacznij wczytywac nowy proces" << endl;

}