#include<iostream> // jedi govna keno
#include<iomanip>
#include<string>
#include<fstream>
#include<algorithm> // funkcija sort
#include <windows.h> // boje - janine duge
#include<ctime> // vrime

/*
	username: admin
	password: admin
*/

using namespace std;

int izbor;

void kratkiIspis(); // provjerit da li postoji

void promijeniBoju(int zeljenaBoja){                                        //  funkcija za manipulaciju boje teksta pri ispisu
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), zeljenaBoja); //  izvor: stackoverflow
}

string brk = "\n********************************************************************************\n";

void welcome(){				//pocetna funkcija
    cout << "================================================================================\n";
    promijeniBoju(2);
    cout << "|\t"<<setw(34)<<"WELCOME"<<setw(39)<<"|\n";
    promijeniBoju(7);
    cout << "================================================================================\n";
    cout << "|Ovo je program koji omogucava rad nad podacima karakteristicnim za automobile |"<<"\n";
    cout << "|\t\t    |Ovaj program je simulacija autosalona|"<<setw(22)<<"|\n";
    cout << "================================================================================\n";
}

ostream& boldiraj(ostream& os){  //  funkcija za otvaranje tagova za boldiranje teksta
    return os << "\e[1m";
}

ostream& ukloniBold(ostream& os){ //  funkcija za zatvaranje tagova za boldiranje
    return os << "\e[0m";
} // bezopasni parazit


float cijenaSaKamatom(float cijenaAuta, const float fixCijena, int brMjeseci=12){

    if(brMjeseci == 0){
        return cijenaAuta;
    }
    else{
        float m = fixCijena*1/100;
        cijenaAuta += m;
        return cijenaSaKamatom(cijenaAuta, fixCijena, brMjeseci - 1);
    }
}


enum nacinPlacanja {gotovina=1, karticno};

struct Datum{
    int dan, mjesec, godina;

    Datum(){
        dan = 0;
        mjesec = 0;
        godina = 0;
    }
};

struct Kupac{

    string ime;
    string prezime;
    string adresa;
    int brRacuna;
    nacinPlacanja nP;
    Datum datumKupovine;

    Kupac() : ime(""), prezime(""), adresa(""), brRacuna(0), nP(nacinPlacanja(1)) {}

    int unosKupcaZaKupovinu(){

    	cin.ignore();

    	char *Ime = new char[40];
    	char *Prezime = new char[40];
    	char *Adresa = new char[40];

    	cout<<"\tIme: ";
		cin.getline(Ime,40);

		cout<<"\tPrezime: ";
		cin.getline(Prezime,40);

		cout<<"\tAdresa: ";
		cin.getline(Adresa,40);

    	int x;
    	cout<<"\tNacin placanja: \n\t\t Gotovinom (1) \n\t\t Karticno (2)\n";

    	do{
    		cout<<"\tVas odabir: ";
    		cin >> x;
    		if(x<1 || x>2){
            	promijeniBoju(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	promijeniBoju(7);
			}
		}while(x<1 || x>2);


		ofstream lista("kupovina.txt", ios::app);

		lista<<"Podaci o kupcu:\n\n";

        ime = Ime;
		lista<<"Ime:			"<<ime<<endl;

		prezime = Prezime;
    	lista<<"Prezime:		"<<prezime<<endl;

        adresa = Adresa;
		lista<<"Adresa:			"<<adresa<<endl;

		switch(x){
    		case 1:
    			lista<<"Nacin placanja:		gotovinom"<<endl;
    			break;
    		case 2:
    			lista<<"Nacin placanja:		karticno"<<endl;

    			cout<<"\tBroj racuna: ";
    			cin>>this->brRacuna;

				lista<<"Broj racuna:		"<<brRacuna<<endl;

				//float cijena = cijenaSaKamatom(cijenaAuta);

                //cout << "\n\tUkupna cijena automobila nakon 12 rata: " << fixed << setprecision(2) << cijena << endl;

    			break;

		}
    	this->nP=(nacinPlacanja)x;

    	time_t now=time(0);
    	tm *ltm=localtime(&now);
    	lista<<"Datum kupovine:		"<<ltm->tm_mday<<"."<<1+ltm->tm_mon<<"."<<1900+ltm->tm_year<<"."<<endl;
    	lista<<"Vrijeme kupovine:	"<<1+ltm->tm_hour<<":"<<1+ltm->tm_min<<":"<<1+ltm->tm_sec<<endl;

    	this->datumKupovine.dan=ltm->tm_mday;
    	this->datumKupovine.mjesec=1+ltm->tm_mon;
    	this->datumKupovine.godina=1900+ltm->tm_year;

    	lista<<"\n**************************************************\n";
    	lista.close();

    	delete[] Ime;
    	delete[] Prezime;
    	delete[] Adresa;

    return x;

	} // gotovo

	void prijavaKupca(){
		system("cls");
		cout << "================================================================================\n";
  		cout << "| \t\tPrije nego sto nastavite istrazivati nasu ponudu\t\t|"<<"\n";
    	cout << "|\t\t    |Molimo Vas da unesete sljedece podatke|"<<setw(21)<<"|\n";
    	cout << "================================================================================\n";

        char *Ime = new char[40];
        char *Prezime = new char[40];

    	cin.ignore();

    	cout<<"\n\tIme: ";
		cin.getline(Ime,40);

		cout<<"\tPrezime: ";
		cin.getline(Prezime,40);


    	ofstream lista("logs.txt", ios::app);
    	lista<<"\nPodaci o posjetiocima:\n\n";

    	ime = Ime;
		lista<<"Ime:\t\t\t"<<ime<<endl;

		prezime = Prezime;
    	lista<<"Prezime:\t\t"<<prezime<<endl;

    	time_t now= time(0);
    	tm *ltm=localtime(&now);
    	lista<<"Datum pristupa:\t\t"<<ltm->tm_mday<<"."<<1+ltm->tm_mon<<"."<<1900+ltm->tm_year<<"."<<endl;
    	lista<<"Vrijeme pristupa:\t"<<ltm->tm_hour<<":"<<ltm->tm_min<<":"<<ltm->tm_sec<<endl;

    	lista<<"\n******************************************************\n";
    	lista.close();

        delete[] Ime;
        delete[] Prezime;
	} // dira

}; // dira

struct Motor{

    int konjskeSnage; //Emrah
    int kW;
    int kubikaza; //1600
    float jacinaMotora; //1.6

    Motor(): konjskeSnage(0), kW(0), kubikaza(0), jacinaMotora(0.0) {}

};

struct Auto{

    string proizvodjacAuta;
    string modelAuta;
    string zemljaPorijekla;
    string boja;

    int brVrata;
    int brStepeniPrenosa; //5+R
    int kilometraza;
    int godiste;

    float cijena;
    float potrosnja;

    bool jeRegistrovan;
    bool jeServisiran;
    bool imaKlimu;

    int stanje;         // 1-nov, 2-polovan
    int transmisija;    // 1-manual, 2-automatic
    int gorivo;         // 1-dizel, 2-benzin, 3-plin
    int pogon;          // 1-prednji, 2-zadnji, 3- 4x4

    Motor motor;

        Auto(){
            proizvodjacAuta = "";
            modelAuta = "";
            zemljaPorijekla = "";
            boja = "";
            brVrata = 0;
            brStepeniPrenosa = 0;
            kilometraza = 0;
            godiste = 0;
            cijena = 0.0;
            potrosnja = 0.0;
            jeRegistrovan = false;
            jeServisiran = false;
            imaKlimu = false;
            stanje = 0;
            transmisija = 0;
            gorivo = 0;
            pogon = 0;
        }

    Auto unosAuta(){

        Auto a;

        cin.ignore();

        cout << "\n\tIme proizvodjaca: ";   getline(cin, a.proizvodjacAuta);

        int provjera = 1;

        while(provjera == 1)
        {
        	for(int i=0;i<a.proizvodjacAuta.length();i++)
        	{
	        	if(isdigit(a.proizvodjacAuta.at(i)))
	        	{
	        		promijeniBoju(4);
	            	cout<<"\t\tPonovite unos: ";
	            	promijeniBoju(7);
	            	getline(cin, a.proizvodjacAuta);
	        		provjera = 1;
	        		break;
				}
				else
				{
					provjera = 0;
				}
			}
		}

        cout << "\tIme modela: ";           getline(cin, a.modelAuta);

        cout << "\tZemlja porijekla: ";     getline(cin, a.zemljaPorijekla);

        provjera = 1;

        while(provjera == 1) // napravit funkciju
        {
        	for(int i=0;i<a.zemljaPorijekla.length();i++)
        	{
	        	if(isdigit(a.zemljaPorijekla.at(i)))
	        	{
	        		promijeniBoju(4);
	            	cout<<"\t\tPonovite unos: ";
	            	promijeniBoju(7);
	            	getline(cin, a.zemljaPorijekla);
	        		provjera = 1;
	        		break;
				}
				else
				{
					provjera = 0;
				}
			}
		}

        cout << "\tBoja auta: ";            getline(cin, a.boja);

        provjera = 1;

        while(provjera == 1)
        {
        	for(int i=0;i<a.boja.length();i++)
        	{
	        	if(isdigit(a.boja.at(i)))
	        	{
	        		promijeniBoju(4);
	            	cout<<"\t\tPonovite unos: ";
	            	promijeniBoju(7);
	            	getline(cin, a.boja);
	        		provjera = 1;
	        		break;
				}
				else
				{
					provjera = 0;
				}
			}
		}

		cout << "\n\tBroj vrata: ";
        cin >> a.brVrata;

        while(a.brVrata < 2 || a.brVrata > 8)
		{
				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite broj vrata(2-8)!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

            	promijeniBoju(4);
            	cout<<"\t\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.brVrata;
		}


       	cout << "\tBroj stepeni prenosa: "; cin >> a.brStepeniPrenosa;

       	while(a.brStepeniPrenosa < 3 || a.brStepeniPrenosa > 10)
		{
				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite broj stepenog prenosa(3-10)!\n";
	        	    promijeniBoju(7);

					cin. get();

        		}

            	promijeniBoju(4);
            	cout<<"\t\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.brStepeniPrenosa;
		}

        cout << "\tKilometraza: ";          cin >> a.kilometraza;

    	while(a.kilometraza < 0 || a.kilometraza > 999999)
		{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite kilometrazu(0-999999)!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

            	promijeniBoju(4);
            	cout<<"\t\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.kilometraza;
		}

		cout << "\tGodiste: ";			cin >> a.godiste;

        while(a.godiste<1886 || a.godiste>2020)
		{

        		if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite godiste(1886-2020)!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

            promijeniBoju(4);
            cout<<"\t\tPonovite unos: ";
            promijeniBoju(7);
            cin >> a.godiste;
		}

		cout << "\tCijena: ";		cin >> a.cijena;

        while(a.cijena<0)
		{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite cijenu!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

            	promijeniBoju(4);
            	cout<<"\t\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.cijena;
		}

        cout << "\tPotrosnja na 100km: ";   cin >> a.potrosnja;

        while(a.potrosnja < 0 || a.potrosnja > 30)
		{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite potrosnju na 100km!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

            	promijeniBoju(4);
            	cout<<"\t\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.cijena;
		}

        cout << "\n\n\tZa sljedece unose koritite 1-DA, 0-NE\n";

		int izbor = 0;

        cout << "\t\tRegistrovan: ";    cin >> izbor;

        while(izbor>1 || izbor<0)
        {

        		if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite da li je automobil registrovan: 1-Da, 0-Ne!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

        	promijeniBoju(4);
            cout<<"\t\tPonovite unos: ";
            promijeniBoju(7);
            cin>>izbor;
		}

		if(izbor == 1)
		{
			a.jeRegistrovan = true;
		}
		else
		{
			a.jeRegistrovan = false;
		}

        cout << "\t\tServisiran: ";     cin >> izbor;

        while(izbor>1 || izbor<0)
        {

        		if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite da li je automobil servisiran: 1-Da, 0-Ne!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

        	promijeniBoju(4);
            cout<<"\t\tPonovite unos: ";
            promijeniBoju(7);
            cin>>izbor;
		}

		if(izbor == 1)
		{
			a.jeServisiran = true;
		}
		else
		{
			a.jeServisiran = false;
		}

        cout << "\t\tKlima: ";          cin >> izbor;

        while(izbor>1 || izbor<0)
        {

        		if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tUnijeli ste znak umjesto broja. Molimo unesite da li automobil ima klimu: 1-Da, 0-Ne!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

        	promijeniBoju(4);
            cout<<"\t\tPonovite unos: ";
            promijeniBoju(7);
            cin>>izbor;
		}

		if(izbor == 1)
		{
			a.imaKlimu = true;
		}
		else
		{
			a.imaKlimu = false;
		}

        cout << "\n\tSljedece karakteristike odaberite ponudjenim brojevima:\n";

        cout << "\n\t\tStanje (1-nov, 2-polovan): ";		cin >> a.stanje;

        while(a.stanje < 1 || a.stanje > 2)
		{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite: 1-nov, 2-polovan!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

            	promijeniBoju(4);
            	cout<<"\t\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.stanje;
		}

		cout << "\t\tGorivo (1-dizel, 2-benzin, 3-plin): ";			cin >> a.gorivo;

        while(a.gorivo < 1 || a.gorivo > 3)
		{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite: 1-dizel, 2-benzin, 3-plin!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

            	promijeniBoju(4);
            	cout<<"\t\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.gorivo;
		}

		cout << "\t\tPogon (1-prednji, 2-zadnji, 3-4x4): ";			cin >> a.pogon;

        while(a.pogon < 1 || a.pogon > 3)
		{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite: 1-prednji, 2-zadnji, 3-4x4!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

            	promijeniBoju(4);
            	cout<<"\t\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.pogon;
		}

		cout << "\t\tTransmisija (1-manual, 2-automatik): ";		cin >> a.transmisija;

        while(a.transmisija < 1 || a.transmisija > 2)
		{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite: 1-manual, 2-automatik!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

            	promijeniBoju(4);
            	cout<<"\t\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.transmisija;
            	cin. get();
		}



        cout << "\n\n\tKarakteristike motora:\n";

        cout << "\t\tKonjske snage: ";   cin >> a.motor.konjskeSnage;

        while(a.motor.konjskeSnage < 0)
		{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite konjske snage!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

            	promijeniBoju(4);
            	cout<<"\t\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.motor.konjskeSnage;
		}

        cout << "\t\tKilovati: ";        cin >> a.motor.kW;

        while(a.motor.kW < 0)
		{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tUnijeli ste znak umjesto broja. Molimo unesite kilovate!\n";
	        	    promijeniBoju(7);

					cin. get();
        		}

            	promijeniBoju(4);
            	cout<<"\t\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.motor.kW;
		}

        cout << "\t\tKubikaza: ";        cin >> a.motor.kubikaza;

        while(a.motor.kubikaza < 0)
		{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\tMolimo unesite kubikazu!\n";
	        	    promijeniBoju(7);

					cin. get();

        		}

            	promijeniBoju(4);
            	cout<<"\t\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.motor.kubikaza;
		}

        cout<<"\n--------------------------------------------------------------------------------\n";

        ofstream auta("auta.txt", ios::app);

            auta<<left<<setw(12)<<a.proizvodjacAuta;
            auta<<left<<setw(8)<<a.modelAuta;
            auta<<left<<setw(10)<<a.zemljaPorijekla;
            auta<<left<<setw(7)<<a.boja;
            auta<<left<<setw(3)<<a.brVrata;
            auta<<left<<setw(3)<<a.brStepeniPrenosa;
            auta<<left<<setw(9)<<a.kilometraza;
            auta<<left<<setw(6)<<a.godiste;
            auta<<left<<setw(8)<<a.cijena;
            auta<<left<<setw(6)<<a.potrosnja;
            auta<<left<<setw(3)<<a.jeRegistrovan;
            auta<<left<<setw(3)<<a.jeServisiran;
            auta<<left<<setw(3)<<a.imaKlimu;
            auta<<left<<setw(3)<<a.stanje;
            auta<<left<<setw(3)<<a.gorivo;
            auta<<left<<setw(3)<<a.pogon;
            auta<<left<<setw(3)<<a.transmisija;
            auta<<left<<setw(5)<<a.motor.konjskeSnage;
            auta<<left<<setw(5)<<a.motor.kW;
            auta<<left<<setw(6)<<a.motor.kubikaza<<endl;

		auta.close();

    return a;
    } // done, samo sa stajalista preglednosti mogle bi se ubacit 2 funkcije do 3

    void pregledAuta(Auto nizAuta[], int brAuta){

        for(int i=0; i<brAuta; i++){

            cout << "\n\t--------------------------------------\n";
            cout << "\t\t" <<setw(12)<< nizAuta[i].proizvodjacAuta << " " << nizAuta[i].modelAuta;
            cout << "\n\t--------------------------------------\n";

            cout << "\n\tIme proizvodjaca:	" << nizAuta[i].proizvodjacAuta;

            cout << "\n\tIme modela:		" << nizAuta[i].modelAuta;

            cout << "\n\tZemlja porijekla:	" << nizAuta[i].zemljaPorijekla;

            cout << "\n\tBoja auta:		" << nizAuta[i].boja;

            cout << "\n\tBroj vrata:		" << nizAuta[i].brVrata-1 << "/" <<nizAuta[i].brVrata;

            cout << "\n\tBroj stepeni prenosa:	" << nizAuta[i].brStepeniPrenosa << "+R";

            cout << "\n\tKilometraza:		" << nizAuta[i].kilometraza;

            cout << "\n\tGodiste: 		" << nizAuta[i].godiste << ".";

            cout << "\n\tCijena: 		" << nizAuta[i].cijena << " KM";

            cout << "\n\tPotrosnja na 100km:	" << nizAuta[i].potrosnja << "l";

            cout << "\n\tRegistrovan:		"; nizAuta[i].jeRegistrovan ? cout << "DA" : cout << "NE";

            cout << "\n\tServisiran:		"; (nizAuta[i].jeServisiran) ? cout << "DA" : cout << "NE";

            cout << "\n\tKlima:			"; nizAuta[i].imaKlimu ? cout << "DA" : cout << "NE";

            cout << "\n\n\tKarakteristike motora:";
            cout << "\n\t\tKonjske snage:	" << nizAuta[i].motor.konjskeSnage;

            cout << "\n\t\tKilovati: 	" << nizAuta[i].motor.kW << "kW";

            cout << "\n\t\tKubikaza: 	" << nizAuta[i].motor.kubikaza << "cc";

            nizAuta[i].motor.jacinaMotora=nizAuta[i].motor.kubikaza/1000.0F;

            cout << "\n\t\tJacina:		" << fixed << setprecision(1) << nizAuta[i].motor.jacinaMotora;

            cout << "\n\n\tStanje:		";
                switch(nizAuta[i].stanje){
                    case 1: cout << "Nov";
                        break;
                    case 2: cout << "Polovan";
                        break;
                 }

            cout << "\n\tGorivo:		";
                switch(nizAuta[i].gorivo){
                    case 1: cout << "Dizel";
                        break;
                    case 2: cout << "Benzin";
                        break;
                    case 3: cout << "Plin";
                        break;
                 }

            cout << "\n\tPogon:		";
                switch(nizAuta[i].pogon){
                    case 1: cout << "Prednji";
                        break;
                    case 2: cout << "Zadnji";
                        break;
                    case 3: cout << "4x4";
                        break;
                }

            cout << "\n\tTransmisija:	";
                switch(nizAuta[i].transmisija){
                    case 1: cout << "Manual\n";
                        break;
                    case 2: cout << "Automatik\n";
                        break;
                }

        }
        cout<<"\n"<<brk;
    }

}; // kraj struct

bool porediCijeneVeca(Auto a, Auto b){

    return a.cijena > b.cijena;
} // oki

bool porediCijeneManja(Auto a, Auto b){

    return a.cijena < b.cijena;
} // doki

void pretraziAuta(Auto nizAuta[], int brAuta){

    cout << "\n\tOdaberite neku opciju filtriranja";
    cout << "\n\t\t1. Sortiraj po cijeni(veca-manja)";
    cout << "\n\t\t2. Sortiraj po cijeni(manja-veca)";
    cout << "\n\t\t3. Pretrazi po cijeni";
    cout << "\n\t\t4. Pretrazi po imenu";
    cout << "\n\t\t5. Pretrazi po zemlji porijekla";
    cout << "\n\t\t6. Kombinovana pretraga";

    Auto a;

    cout << "\n\n\tVas izbor za pretragu: ";
        cin >> izbor;

    cout<<"\n--------------------------------------------------------------------------------\n";

    switch(izbor){
        case 1:
            sort(nizAuta, nizAuta+brAuta, porediCijeneVeca);
            a.pregledAuta(nizAuta,brAuta);
            break;

        case 2:
            sort(nizAuta, nizAuta+brAuta, porediCijeneManja);
            a.pregledAuta(nizAuta,brAuta);
            break;

        case 3:
        {
            cout << "\n\tUnesite minimalnu cijenu automobila: ";
            float minCijena;
            cin >> minCijena;

    		cout << "\n\tUnesite maksimalnu cijenu automobila: ";
            float maksCijena;
            cin >> maksCijena;

            Auto *autaPoCijeni = new Auto[brAuta];

            int br=0;

            for(int i=0; i<brAuta; i++){
                if(nizAuta[i].cijena > minCijena && nizAuta[i].cijena < maksCijena){
                    autaPoCijeni[br++] = nizAuta[i];
                }
            }

            cout << "\n\tLista automobila sa cijenom manjom od " <<maksCijena<< " KM i vecom od "<<minCijena<<"KM \n";
            if(br > 0){
                sort(autaPoCijeni, autaPoCijeni+br, porediCijeneVeca);    //  sortira se da ne bi doslo do random redanja po cijenama
                a.pregledAuta(autaPoCijeni, br);
            }
            else cout << "\n\t\tNema takvih automobila.";

            delete[] autaPoCijeni;
            break;
        }

        case 4:
        {
            string imeProizvodjaca;
            cout << "\n\tUnesite ime proizvodjaca po kojem zelite da pretrazite auta";
            cout << "\n\tIme proizvodjaca: ";
            cin.ignore();
            getline(cin, imeProizvodjaca);

            Auto *autaPoImenu = new Auto[brAuta];
            int br=0;

            for(int i=0; i<brAuta; i++){
                if(nizAuta[i].proizvodjacAuta == imeProizvodjaca){
                    autaPoImenu[br++] = nizAuta[i];
                }
            }

            cout << "\n\tLista auta po imenu proizvodjaca: " << imeProizvodjaca << "\n";

            if(br > 0)
                a.pregledAuta(autaPoImenu, br);
            else cout << "\n\t\tNema takvih automobila.";

            delete[] autaPoImenu;
            break;
        }

        case 5:
        {
            string zemlja;
            cout << "\n\tUnesite zemlju iz koje zelite da se prikazu auta";
            cout << "\n\tZemlja: ";
            cin.ignore();
            getline(cin, zemlja);

            Auto *autaPoZemlji=new Auto[brAuta];
            int br=0;

            for(int i=0; i<brAuta; i++){
                if(nizAuta[i].zemljaPorijekla == zemlja){
                    autaPoZemlji[br++] = nizAuta[i];
                }
            }
            cout << "\n\tLista auta iz zemlje: " << zemlja << "\n";

            if(br > 0)
                a.pregledAuta(autaPoZemlji, br);
            else cout << "\n\t\tNema takvih automobila.";

            delete[] autaPoZemlji;
            break;
        }

        case 6:
        {

            string imeProizvodjaca, bojaAuta;
            float cijenaAuta;
            int stanjeAuta, gorivoAuta;
            cin.ignore();

            cout << "\n\tUnesite ime proizvodjaca: ";		getline(cin, imeProizvodjaca);

            int provjera = 1;

	        while(provjera == 1)
	        {
	        	for(int i=0;i<imeProizvodjaca.length();i++)
	        	{
		        	if(isdigit(imeProizvodjaca.at(i)))
		        	{
		        		promijeniBoju(4);
		            	cout<<"\t\tPonovite unos: ";
		            	promijeniBoju(7);
		            	getline(cin, imeProizvodjaca);
		        		provjera = 1;
		        		break;
					}
					else
					{
						provjera = 0;
					}
				}
			}

            cout << "\n\tUnesite boju: ";		getline(cin, bojaAuta);

            provjera = 1;

	        while(provjera == 1)
	        {
	        	for(int i=0;i<bojaAuta.length();i++)
	        	{
		        	if(isdigit(bojaAuta.at(i)))
		        	{
		        		promijeniBoju(4);
		            	cout<<"\t\tPonovite unos: ";
		            	promijeniBoju(7);
		            	getline(cin, bojaAuta);
		        		provjera = 1;
		        		break;
					}
					else
					{
						provjera = 0;
					}
				}
			}

            cout << "\n\tUnesite cijenu: ";			cin >> cijenaAuta;

            while(cijenaAuta < 0)
            {
            	promijeniBoju(4);
		        cout<<"\t\tPonovite unos: ";
		        promijeniBoju(7);
		        cin >> cijenaAuta;
			}

            cout << "\n\tUnesite stanje auta (1-nov, 2-polovan): "; 		cin >> stanjeAuta;

            while(stanjeAuta<1 || stanjeAuta>2)
            {
            	promijeniBoju(4);
		        cout<<"\t\tPonovite unos: ";
		        promijeniBoju(7);
		        cin >> stanjeAuta;
			}

            cout << "\n\tUneiste gorivo (1-dizel, 2-benzin, 3-plin): "; 		cin >> gorivoAuta;

             while(gorivoAuta<1 || gorivoAuta>3)
            {
            	promijeniBoju(4);
		        cout<<"\t\tPonovite unos: ";
		        promijeniBoju(7);
		        cin >> gorivoAuta;
			}


            Auto *auta = new Auto[brAuta];
            int br=0;

            for(int i=0; i<brAuta; i++)
            {
                if(nizAuta[i].proizvodjacAuta == imeProizvodjaca && nizAuta[i].boja == bojaAuta && nizAuta[i].cijena
                   <= cijenaAuta && nizAuta[i].stanje == stanjeAuta && nizAuta[i].gorivo == gorivoAuta)
                {
                    auta[br++] = nizAuta[i];
                }
            }

            cout << "\n\tLista auta sa datim karakteristikama: \n";
            if(br>0){
                a.pregledAuta(auta, br);
            }
            else{
                cout << "\n\tNema takvih automobila";
            }

            delete[] auta;
            break;
        }

        default:

        	promijeniBoju(4);
            cout << "\n\tOdabrali ste nepostojecu opciju.";
            promijeniBoju(7);
    }
} // done

void ispisUplatnice(Auto nizAuta[], int br){

	Kupac k;
    string fajl = "uplatnica.txt";

    cout << "\n\tZelite li izvrsiti pretragu auta prije kupovine (y/n)? ";
    cin.ignore();
    char get = cin.get();

    if(get == 'y' || get == 'Y'){
        pretraziAuta(nizAuta, br);
    }

    cout << "\n\tIspod je lista auta. Izaberite redni broj auta koje zelite kupiti\n";

        for(int i=0; i<br; i++)
            cout << "\t\t" << i+1 << ". " << nizAuta[i].proizvodjacAuta << " " << nizAuta[i].modelAuta << " "
            << " " << nizAuta[i].motor.kW << " kW\n";


    	int izbor;

    	do{
    		cout<<"\n\tIzbareite vozilo koje zelite kupiti: ";
    		cin>>izbor;
		}while(izbor < 1 || izbor > br);


    cout << "\n\tUnesite svoje informacije: \n";
    int nacinP = k.unosKupcaZaKupovinu();

    if(nacinP == 2){

        ofstream uplatnica("uplatnica.txt");
        uplatnica << "------------------------------------------------------------\n";
        uplatnica << "\t\t\tAutosalon 'KEJ' d.o.o.:\n";
        uplatnica << "------------------------------------------------------------\n";
        uplatnica << "\t\tIme i prezime: " << k.ime << " " << k.prezime << endl;
        uplatnica << "\n\t\tINFORMACIJE O AUTOMOBILU: \n\tProizvodjac: " << nizAuta[izbor-1].proizvodjacAuta << "\n\tModel: " << nizAuta[izbor-1].modelAuta <<endl;
        uplatnica << "\n\t\tUkupni iznos: "<< cijenaSaKamatom(nizAuta[izbor-1].cijena, nizAuta[izbor-1].cijena) << " KM." << endl;
        uplatnica << "\n\t\t\tPotpis: _________________________\n";
        uplatnica << "------------------------------------------------------------\n";
        uplatnica << "\n\tTim Autosalona 'KEJ' Vam zeli sigurnu voznju\n";
        uplatnica << "------------------------------------------------------------\n";
        uplatnica.close();
    }
    else{

        ofstream uplatnica("uplatnica.txt");
        uplatnica << "------------------------------------------------------------\n";
        uplatnica << "\t\t\tAutosalon 'KEJ' d.o.o.:\n";
        uplatnica << "------------------------------------------------------------\n";
        uplatnica << "\t\tIme i prezime: " << k.ime << " " << k.prezime << endl;
        uplatnica << "\n\t\tINFORMACIJE O AUTOMOBILU: \n\tProizvodjac: " << nizAuta[izbor-1].proizvodjacAuta << "\n\tModel: " << nizAuta[izbor-1].modelAuta <<endl;
        uplatnica << "\n\t\tIznos: "<< nizAuta[izbor-1].cijena << " KM." << endl;
        uplatnica << "\n\t\t\tPotpis: _________________________\n";
        uplatnica << "------------------------------------------------------------\n";
        uplatnica << "\n\tTim Autosalona 'KEJ' Vam zeli sigurnu voznju\n";
        uplatnica << "------------------------------------------------------------\n";
        uplatnica.close();

    }


    promijeniBoju(2);
    cout << "\n\tUplatnica uspjesno snimnjena u " << fajl << endl;
	promijeniBoju(7);
}

void prikaziMeniA(){			//meni za admina tj prodavca
	system("cls");
    cout << "\t\t==============================================\n";
    cout << "\t\t|\t\t"<<setw(9)<<"MENI:"<<setw(22)<<"|\n";
    cout << "\t\t==============================================\n";
    cout << "\t\t|\t1. Unos automobila"<<setw(21)<<"|\n";
    cout << "\t\t|\t2. Pregled automobila"<<setw(18)<<"|\n";;
    cout << "\t\t|\t3. Pretraga automobila"<<setw(17)<<"|\n";
    cout << "\t\t|\t4. Ispis uplatnice"<<setw(21)<<"|\n";
    cout << "\t\t|\t5. Kraj"<<setw(32)<<"|\n";;
    cout << "\t\t==============================================\n";

} // dira

void prikaziMeniK(){			//meni za kupca
	system("cls");
    cout << "\t\t==============================================\n";
    cout << "\t\t|\t\t"<<setw(9)<<"MENI:"<<setw(22)<<"|\n";
    cout << "\t\t==============================================\n";
    cout << "\t\t|\t1. Pregled automobila"<<setw(18)<<"|\n";;
    cout << "\t\t|\t2. Pretraga automobila"<<setw(17)<<"|\n";
    cout << "\t\t|\t3. Kupovina automobila"<<setw(21)<<"|\n";
    cout << "\t\t|\t4. Kraj"<<setw(32)<<"|\n";;
    cout << "\t\t==============================================\n";
} // dira

void mainMeniK(Kupac k, Auto a){

		prikaziMeniK();

        int br=0;
    	Auto *nizAuta=new Auto[100];
		ifstream auta("auta.txt");

		while(auta>>nizAuta[br].proizvodjacAuta){

            auta>>nizAuta[br].modelAuta;
            auta>>nizAuta[br].zemljaPorijekla;
            auta>>nizAuta[br].boja;
            auta>>nizAuta[br].brVrata;
            auta>>nizAuta[br].brStepeniPrenosa;
            auta>>nizAuta[br].kilometraza;
            auta>>nizAuta[br].godiste;
            auta>>nizAuta[br].cijena;
            auta>>nizAuta[br].potrosnja;

            auta>>nizAuta[br].jeRegistrovan;
            auta>>nizAuta[br].jeServisiran;
            auta>>nizAuta[br].imaKlimu;

            auta>>nizAuta[br].stanje;
            auta>>nizAuta[br].gorivo;
            auta>>nizAuta[br].pogon;
            auta>>nizAuta[br].transmisija;

            auta>>nizAuta[br].motor.konjskeSnage;
            auta>>nizAuta[br].motor.kW;
            auta>>nizAuta[br].motor.kubikaza;

		 br++;
		} // dira


	    do{
    	    cout<<"\n--------------------------------------------------------------------------------\n";
	        cout << "\n\tVas izbor: ";
        	cin >> izbor;

    	    if(cin.fail()){ // lijek za infinity

        	    cin.cls();
    	        cin.ignore(1000, '\n');
	            system("cls");

            	cout<<"\n--------------------------------------------------------------------------------\n\n";
            	promijeniBoju(4);
        	    cout << "\tUnijeli ste znak umjesto broja. Molimo pokusajte ponovo\n";
        	    promijeniBoju(7);
    	        cout<<"\n--------------------------------------------------------------------------------\n\n";

	            prikaziMeniK();
            	continue;
        	}
                if(izbor<1 || izbor>4)
                {
                    promijeniBoju(4);
                    cout<<"\t\tPonovite unos"<<endl;
                    promijeniBoju(7);
                }

		}while(izbor<1 || izbor>4); // dira

    	    switch(izbor){
        	    case 1:
    	            system("cls");

	                cout << brk;
                	cout << boldiraj << "\n\t\t\t   Pregled svih automobila\n" << ukloniBold;
            	    cout << brk;

                    a.pregledAuta(nizAuta, br);
        	        cout << endl;

	                break;

            	case 2:
        	        system("cls");

    	            cout << brk;
	                cout << boldiraj << "\n\t\t\t     Pretraga automobila\n" << ukloniBold;
                	cout << brk;

                    pretraziAuta(nizAuta, br);
            	    cout << endl;

    	            break;

    	        case 3:
    	        	system("cls");
    	        	cout << brk;
	                cout << boldiraj << "\n\t\t\t     Kupovina automobila\n" << ukloniBold;
                	cout << brk;
                	ispisUplatnice(nizAuta, br);
    	        	break;

    	        case 4:
	                system("cls");
	                cout << brk;
					promijeniBoju(2);
            	    cout << boldiraj << "\n\t\tHvala Vam na posjeti! Prijatno i dovidjenja!\n" << ukloniBold ;
            	    promijeniBoju(7);
            	    cout<<brk;
        	        break;
    	    }

	        if(izbor==4)
			{
				system("exit");
			}
	        else
			{
	        	cin.ignore();
	            int get;

            	cout << "\n\t-------------------------";
        	    cout << "\n\t Izlaz (0)\n\t Nazad (1)";
        	    cout << "\n\t-------------------------";
        	    do{
					cout<<"\n\t\tVas odabir: ";
					cin>>get;
					if(get<0 || get>1){
            			promijeniBoju(4);
            			cout<<"\t\tPonovite unos"<<endl;
        	    		promijeniBoju(7);
					}
				}while(get<0 || get>1);
    	        cout<<"\n";
    	        cout<<"\n";

	            if(get==1){
            	    system("cls");
        	        mainMeniK(k, a);

    	        }else{
    	        	system("cls");
					cout << brk ;
					promijeniBoju(2);
            	    cout << boldiraj << "\n\t\tHvala Vam na posjeti! Prijatno i dovidjenja!\n" << ukloniBold;
            	    promijeniBoju(7);
            	    cout << brk;
        	        system("exit");
				}
			}
    delete[] nizAuta;
} //

void mainMeniA(Auto a){

    int br=0;
    Auto *nizAuta=new Auto[50];
    ifstream auta("auta.txt");

		while(auta>>nizAuta[br].proizvodjacAuta){

            auta>>nizAuta[br].modelAuta;
            auta>>nizAuta[br].zemljaPorijekla;
            auta>>nizAuta[br].boja;
            auta>>nizAuta[br].brVrata;
            auta>>nizAuta[br].brStepeniPrenosa;
            auta>>nizAuta[br].kilometraza;
            auta>>nizAuta[br].godiste;
            auta>>nizAuta[br].cijena;
            auta>>nizAuta[br].potrosnja;

            auta>>nizAuta[br].jeRegistrovan;
            auta>>nizAuta[br].jeServisiran;
            auta>>nizAuta[br].imaKlimu;

            auta>>nizAuta[br].stanje;
            auta>>nizAuta[br].gorivo;
            auta>>nizAuta[br].pogon;
            auta>>nizAuta[br].transmisija;

            auta>>nizAuta[br].motor.konjskeSnage;
            auta>>nizAuta[br].motor.kW;
            auta>>nizAuta[br].motor.kubikaza;

		 br++;
		}


    prikaziMeniA();

        do{
    	    cout<<"\n--------------------------------------------------------------------------------\n";
	        cout << "\n\tVas izbor: ";
        	cin >> izbor;

    	    if(cin.fail()){

        	    cin.cls();
    	        cin.ignore(1000,'\n');
	            system("cls");

            	cout<<"\n--------------------------------------------------------------------------------\n\n";
        	    cout << "\tUnijeli ste znak umjesto broja. Molimo pokusajte ponovo\n";
    	        cout<<"\n--------------------------------------------------------------------------------\n\n";

	            prikaziMeniA();
            	continue;
        	}
                if(izbor<1 || izbor>5)
                {
                    promijeniBoju(4);
                    cout<<"\t\tPonovite unos!"<<endl;
                    promijeniBoju(7);
                }

		}while(izbor<1 || izbor>5);

    	    switch(izbor){
	            case 1:
                	system("cls");

            	    cout<<brk;
        	        cout << boldiraj << "\n\t\t\t      Unos automobila\n" << ukloniBold;
    	            cout<<brk;

	                nizAuta[br++]=a.unosAuta();
                	cout << endl;
    	            break;

        	    case 2:
    	            system("cls");

	                cout << brk;
                	cout << boldiraj << "\n\t\t\t   Pregled svih automobila\n" << ukloniBold;
            	    cout << brk;

                    a.pregledAuta(nizAuta, br);
        	        cout << endl;

	                break;

            	case 3:
        	        system("cls");

    	            cout << brk;
	                cout << boldiraj << "\n\t\t\t     Pretraga automobila\n" << ukloniBold;
                	cout << brk;

                    pretraziAuta(nizAuta, br);
            	    cout << endl;

    	            break;

	            case 4:
            	    system("cls");

        	        cout << brk;
    	            cout << boldiraj << "\n\t\t\t      Ispis uplatnice\n" << ukloniBold;
	                cout << brk;

                    ispisUplatnice(nizAuta, br);
                	cout << endl;

        	        break;

    	        case 5:
	                system("cls");
	                cout << brk;
					promijeniBoju(2);
            	    cout << boldiraj << "\n\t\tHvala Vam na posjeti! Prijatno i dovidjenja!\n" << ukloniBold ;
            	    promijeniBoju(7);
            	    cout<<brk;
        	        break;
    	    }

	        if(izbor==5) system("exit");

	        else{
	        	cin.ignore();
	            int get;

            	cout << "\n\t-------------------------";
        	    cout << "\n\t0. Izlaz\n\t1. Nazad ";
        	    cout << "\n\t-------------------------";
        	    do{
					cout<<"\n\t\tVas odabir: ";
					cin>>get;
					if(get<0 || get>1){
            			promijeniBoju(4);
            			cout<<"\t\tPonovite unos"<<endl;
        	    		promijeniBoju(7);
					}
				}while(get<0 || get>1);

    	        cout<<"\n";
    	        cout<<"\n";

	            if(get==1){
            	    system("cls");
        	        mainMeniA(a);
    	        }else{
    	        	system("cls");
	                cout << brk;
					promijeniBoju(2);
            	    cout << boldiraj << "\n\t\tHvala Vam na posjeti! Prijatno i dovidjenja!\n" << ukloniBold ;
            	    promijeniBoju(7);
            	    cout<<brk;
        	        system("exit");
				}
			}
    delete[] nizAuta;
} // dira

int main(){
	welcome();
	cout<<"\n--------------------------------------------------------------------------------\n";

	Auto a;
	int izbor;

	cout<<"\tIzaberite na koji se sistem zelite prijaviti: \n\t\tKUPAC (1) \n\t\tRADNIK (2) \n\n";

	cout<<"\tVas izbor: ";
	cin>>izbor;

	while(izbor<1 || izbor>2)
	{
           	promijeniBoju(4);
           	cout<<"\t\tPonovite unos: ";
           	promijeniBoju(7);
           	cin>>izbor;
	}


	if(izbor==2){

		string username; //zadano je da bude admin
		string password; //zadano je da bude admin

		system("cls");
		int brPokusaja=0;

		do{
			cin.ignore();

			cout << "\n\n\n\t\t\tusername: ";
			getline(cin, username);
			cout << "\n\t\t\tpassword: ";
			cin >> password;
			brPokusaja++;

			if(username != "admin" && password != "admin" && brPokusaja<3){

				system("cls");
				promijeniBoju(4);
           		cout<<"\t\tNeisparvan unos";
           		promijeniBoju(7);
           		cout << "\t\t\t\tBroj pokusaja: " << 3-brPokusaja<<endl;

			}else if(password != "admin" && brPokusaja<3){

				system("cls");
				promijeniBoju(4);
           		cout << "\t\tNeispravan password";
           		promijeniBoju(7);
           		cout << "\t\t\t\tBroj pokusaja: " << 3-brPokusaja<<endl;

			}else if(username!="admin" && brPokusaja<3){

				system("cls");
				promijeniBoju(4);
           		cout << "\t\tNeispravan username";
           		promijeniBoju(7);
           		cout << "\t\t\t\tBroj pokusaja: " << 3-brPokusaja << endl;

			}
			if(brPokusaja==3){
				system("cls");
				main();
			}
		}while(username!="admin" || password!="admin");

        mainMeniA(a);

	}else{
        Kupac k;
		k.prijavaKupca();
		mainMeniK(k, a);
	}

cout<<"\n--------------------------------------------------------------------------------\n";
return 0;
}
