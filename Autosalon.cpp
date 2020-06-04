#include<iostream>		// biblioteke ukljucene za omogucen rad funkcija koje smo ukljucili u nas program
#include<iomanip>
#include<string>
#include<cstring>		// omogucen rad funkcija za manipulaciju sa stringovima
#include<fstream>		// omogucena maipulacija fajlovima
#include<algorithm>	    // za funkciju sort
#include <windows.h> 	// za boje - radi samo na windows OS-u
#include<ctime> 		// za koristenje funkcije za racunanje vremena

/*
	NAPOMENA: (za pristup admin mode-u potrebne sifre)
		username: admin
		password: admin
*/

using namespace std;

void promijeniBoju(int zeljenaBoja){                                        	//  funkcija za manipulaciju boje teksta pri ispisu
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), zeljenaBoja); 	//  izvor: stackoverflow
}

string brk = "\n********************************************************************************\n";

void welcome(){				//  funckija za ispis pocetne poruke
    cout << "================================================================================\n";
    promijeniBoju(2);
    cout << "|\t"<<setw(34)<<"WELCOME"<<setw(39)<<"|\n";
    promijeniBoju(7);
    cout << "================================================================================\n";
    cout << "|Ovo je program koji omogucava rad nad podacima karakteristicnim za automobile |"<<"\n";
    cout << "|\t\t    |Ovaj program je simulacija autosalona|"<<setw(22)<<"|\n";
    cout << "================================================================================\n";
}

//  Funkcije za boldiranje teksta
//  Boldiranje radi samo na linuxu, medjutim kada smo testirali u Dev-C++ nismo nailazili na greske
//  tako da smo odlucili ostaviti ove funkcije
ostream& boldiraj(ostream& os){  //  funkcija za otvaranje tagova za boldiranje teksta
    return os << "\e[1m";
}

ostream& ukloniBold(ostream& os){ //  funkcija za zatvaranje tagova za boldiranje
    return os << "\e[0m";
}

float cijenaSaKamatom(float cijenaAuta, const float fixCijena, int brMjeseci=12){	//rekurzivna funkcija za racunanje cijene ako se placa na 12 rata

    if(brMjeseci == 0){
        return cijenaAuta;
    }
    else{
        float m = fixCijena*1/100;
        cijenaAuta += m;
        return cijenaSaKamatom(cijenaAuta, fixCijena, brMjeseci - 1);
    }
}

enum nacinPlacanja {gotovina=1, karticno};	//enumeracija za nacin placanja

struct Datum{					//sturktura za datum
    int dan, mjesec, godina;

    Datum(){
        dan = 0;
        mjesec = 0;
        godina = 0;
    }
};

struct Kupac{			//sturktura za kupca

    string ime;
    string prezime;
    string adresa;
    int brRacuna;
    nacinPlacanja nP;
    Datum datumKupovine;

    Kupac() : ime(""), prezime(""), adresa(""), brRacuna(0), nP(nacinPlacanja(1)) {}	//konsturktori koristreni za postavljanje pocetne vrijednosti

    int unosKupcaZaKupovinu(){		//strukturalna funkcija za unos podataka o kupcu

    	cin.ignore();

    	char *Ime = new char[40];
    	char *Prezime = new char[40];
    	char *Adresa = new char[40];

    	cout<<"\tIme: ";
		cin.getline(Ime,40);

		bool provjera = true;

		while(provjera)
		{
			for(int i=0;i<strlen(Ime);i++)
			{
				if(isdigit(Ime[i]))
				{
					promijeniBoju(4);
					cout<<"\n\t\tUneseno ime sadrzi broj!!!"<<endl;
					promijeniBoju(7);
					cout<<"\n\tUnesite ime: ";
					cin.getline(Ime,40);
					provjera = true;
					break;
				}
				else
				{
					provjera = false;
				}
			}
		}

			for(int i=0;i<strlen(Ime);i++)
			{
				if(i==0)
				{
					if(Ime[i]>=97 && Ime[i]<=122)
					{
						Ime[i] = Ime[i] - 32;
					}
				}
				else
				{
					if(Ime[i]>=65 && Ime[i]<=90)
					{
						Ime[i] = Ime[i] + 32;
					}
				}

			}

		cout<<"\tPrezime: ";
		cin.getline(Prezime,40);

		provjera = true;

		while(provjera)
		{
			for(int i=0;i<strlen(Prezime);i++)
			{
				if(isdigit(Prezime[i]))
				{
					promijeniBoju(4);
					cout<<"\n\t\tUneseno ime sadrzi broj!!!"<<endl;
					promijeniBoju(7);
					cout<<"\n\tUnesite ime: ";
					cin.getline(Prezime,40);
					provjera = true;
					break;
				}
				else
				{
					provjera = false;
				}
			}
		}

			for(int i=0;i<strlen(Prezime);i++)
			{
				if(i==0)
				{
					if(Prezime[i]>=97 && Prezime[i]<=122)
					{
						Prezime[i] = Prezime[i] - 32;
					}
				}
				else
				{
					if(Prezime[i]>=65 && Prezime[i]<=90)
					{
						Prezime[i] = Prezime[i] + 32;
					}
				}

			}

		cout<<"\tAdresa: ";
		cin.getline(Adresa,40);

		for(int i=0;i<strlen(Adresa);i++)
			{
				if(i==0)
				{
					if(Adresa[i]>=97 && Adresa[i]<=122)
					{
						Adresa[i] = Adresa[i] - 32;
					}
				}
				else
				{
					if(Adresa[i]>=65 && Adresa[i]<=90)
					{
						Adresa[i] = Adresa[i] + 32;
					}
				}

			}

    	int x;
    	cout<<"\tNacin placanja: \n\t\t Gotovinom (1) \n\t\t Karticno (2)\n\tVas odabir: ";		cin>>x;

		while(x < 1 || x > 2)
		{
				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\n\tMolimo unesite nacin placanja: 1-gotovina, 2-karticno!\n";
	        	    cout<< "\tPritisnite ENTER da nastavite!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> x;
		}

		ofstream lista("kupovina.txt", ios::app);		//unos podataka u fajl kupovina.txt

		lista<<"Podaci o kupcu:\n\n";

        ime = Ime;
		lista<<"Ime:			"<<ime<<endl;

		prezime = Prezime;
    	lista<<"Prezime:		"<<prezime<<endl;

        adresa = Adresa;
		lista<<"Adresa:			"<<adresa<<endl;

		switch(x){
    		case 1:
    			lista<<"Nacin placanja:		Gotovinom"<<endl;
    			break;
    		case 2:
    			lista<<"Nacin placanja:		Karticno"<<endl;

    			cout<<"\tBroj racuna: ";
    			cin>>this->brRacuna;

    			while(this->brRacuna<1)
				{
					promijeniBoju(4);
            		cout<<"\n\tPonovite unos: ";
            		promijeniBoju(7);
            		cin >> this->brRacuna;
				}

				lista<<"Broj racuna:		"<<brRacuna<<endl;

    			break;

		}

    	this->nP=(nacinPlacanja)x;

    	time_t now=time(0);			//funkcije za racunanje vemena
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
	}

	void prijavaKupca(){		//sturkturalna funkcija za pracenje posjecivanja programa

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

		bool provjera = true;

		while(provjera)
		{
			for(int i=0;i<strlen(Ime);i++)
			{
				if(isdigit(Ime[i]))
				{
					promijeniBoju(4);
					cout<<"\n\t\tUneseno ime sadrzi broj!!!"<<endl;
					promijeniBoju(7);
					cout<<"\n\tUnesite ime: ";
					cin.getline(Ime,40);
					provjera = true;
					break;
				}
				else
				{
					provjera = false;
				}
			}
		}

			for(int i=0;i<strlen(Ime);i++)
			{
				if(i==0)
				{
					if(Ime[i]>=97 && Ime[i]<=122)
					{
						Ime[i] = Ime[i] - 32;
					}
				}
				else
				{
					if(Ime[i]>=65 && Ime[i]<=90)
					{
						Ime[i] = Ime[i] + 32;
					}
				}

			}

		cout<<"\tPrezime: ";
		cin.getline(Prezime,40);

		provjera = true;

		while(provjera)	//provjera za pravilnost unosa koristena na svim mjestima gdje je unos iskljucivo slovima
		{
			for(int i=0;i<strlen(Prezime);i++)
			{
				if(isdigit(Prezime[i]))
				{
					promijeniBoju(4);
					cout<<"\n\t\tUneseno prezime sadrzi broj!!!"<<endl;
					promijeniBoju(7);
					cout<<"\n\tUnesite ime: ";
					cin.getline(Prezime,40);
					provjera = true;
					break;
				}
				else
				{
					provjera = false;
				}
			}
		}

			for(int i=0;i<strlen(Prezime);i++)	//petlja koristena za pravilno unosenje podataka u fajl kako ne bi kasije bilo problema sa ucitavanjem istih
			{
				if(i==0)
				{
					if(Prezime[i]>=97 && Prezime[i]<=122)
					{
						Prezime[i] = Prezime[i] - 32;
					}
				}
				else
				{
					if(Prezime[i]>=65 && Prezime[i]<=90)
					{
						Prezime[i] = Prezime[i] + 32;
					}
				}
			}

    	ofstream lista("logs.txt", ios::app);		//unos podataka u fajl logs.txt
    	lista<<"\nPodaci o posjetiocu:\n\n";

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
	}

};

struct Motor{		//struktura motor

    int konjskeSnage;
    int kW;
    int kubikaza;
    float jacinaMotora;

    Motor(): konjskeSnage(0), kW(0), kubikaza(0), jacinaMotora(0.0) {}

};

struct Auto{		//struktura auto

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

    Auto unosAuta(){		//strukturalna funkcija za unos podataka

        Auto a;

        cin.ignore();

        cout << "\n\tIme proizvodjaca: ";   getline(cin, a.proizvodjacAuta);

        bool provjera = true;

        while(provjera)
        {
        	for(int i=0;i<a.proizvodjacAuta.length();i++)
        	{
	        	if(isdigit(a.proizvodjacAuta.at(i)))
	        	{
	        		promijeniBoju(4);
	        		cout<<"\n\tNe postoji proizvodjac sa brojevima u nazivu!"<<endl;
	            	cout<<"\n\tPonovite unos: ";
	            	promijeniBoju(7);
	            	getline(cin, a.proizvodjacAuta);
	        		provjera = true;
	        		break;
				}
				else
				{
					provjera = false;
				}
			}
		}

			for(int i=0;i<a.proizvodjacAuta.length();i++)
			{
				if(i==0)
				{
					if(a.proizvodjacAuta.at(i)>=97 && a.proizvodjacAuta.at(i)<=122)
					{
						a.proizvodjacAuta.at(i) = a.proizvodjacAuta.at(i) - 32;
					}
				}
				else
				{
					if(a.proizvodjacAuta.at(i)>=65 && a.proizvodjacAuta.at(i)<=90)
					{
						a.proizvodjacAuta.at(i) = a.proizvodjacAuta.at(i) + 32;
					}
				}

			}

        cout << "\tIme modela: ";           getline(cin, a.modelAuta);

        for(int i=0;i<a.modelAuta.length();i++)
			{
				if(a.modelAuta.at(i)>=97 && a.modelAuta.at(i)<=122)
				{
					a.modelAuta.at(i) = a.modelAuta.at(i) - 32;
				}

			}

        cout << "\tZemlja porijekla: ";     getline(cin, a.zemljaPorijekla);

        provjera = true;

        while(provjera)
        {
        	for(int i=0;i<a.zemljaPorijekla.length();i++)
        	{
	        	if(isdigit(a.zemljaPorijekla.at(i)))
	        	{
	        		promijeniBoju(4);
	        		cout<<"\n\tNe postoji zemlja sa brojevima u nazivu!"<<endl;
	            	cout<<"\n\tPonovite unos: ";
	            	promijeniBoju(7);
	            	getline(cin, a.zemljaPorijekla);
	        		provjera = true;
	        		break;
				}
				else
				{
					provjera = false;
				}
			}
		}

			for(int i=0;i<a.zemljaPorijekla.length();i++)
			{
				if(i==0)
				{
					if(a.zemljaPorijekla.at(i)>=97 && a.zemljaPorijekla.at(i)<=122)
					{
						a.zemljaPorijekla.at(i) = a.zemljaPorijekla.at(i) - 32;
					}
				}
				else
				{
					if(a.zemljaPorijekla.at(i)>=65 && a.zemljaPorijekla.at(i)<=90)
					{
						a.zemljaPorijekla.at(i) = a.zemljaPorijekla.at(i) + 32;
					}
				}

			}

        cout << "\tBoja auta: ";            getline(cin, a.boja);

        provjera = true;

        while(provjera)
        {
        	for(int i=0;i<a.boja.length();i++)
        	{
	        	if(isdigit(a.boja.at(i)))
	        	{
	        		promijeniBoju(4);
	        		cout<<"\n\tNe postoji boja sa brojevima u nazivu!"<<endl;
	            	cout<<"\n\tPonovite unos: ";
	            	promijeniBoju(7);
	            	getline(cin, a.boja);
	        		provjera = true;
	        		break;
				}
				else
				{
					provjera = false;
				}
			}
		}

        for(int i=0;i<a.boja.length();i++)
			{
				if(i==0)
				{
					if(a.boja.at(i)>=97 && a.boja.at(i)<=122)
					{
						a.boja.at(i) = a.boja.at(i) - 32;
					}
				}
				else
				{
					if(a.boja.at(i)>=65 && a.boja.at(i)<=90)
					{
						a.boja.at(i) = a.boja.at(i) + 32;
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
	        	    cout << "\n\tMolimo unesite broj vrata(2-8)!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite broj vrata(2-8)!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
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
	        	    cout << "\n\tMolimo unesite broj stepenog prenosa(3-10)!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();

        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite broj stepenog prenosa(3-10)!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
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
	        	    cout << "\n\tMolimo unesite kilometrazu(0-999999)!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite kilometrazu(0-999999)!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
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
	        	    cout << "\n\tMolimo unesite godiste(1886-2020)!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite godiste(1886-2020)!\n";
        			promijeniBoju(7);
				}

            promijeniBoju(4);
            cout<<"\n\tPonovite unos: ";
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
	        	    cout << "\n\tMolimo unesite cijenu!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite cijenu!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.cijena;
		}

        cout << "\tPotrosnja na 100km: ";
        cin >> a.potrosnja;

        while(a.potrosnja < 0)
		{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\n\tMolimo unesite potrosnju na 100km!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite potrosnju na 100km!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
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
	        	    cout << "\n\tMolimo unesite da li je automobil registrovan (1-Da, 0-Ne)!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite da li je automobil registrovan (1-Da, 0-Ne)!\n";
        			promijeniBoju(7);
				}

        	promijeniBoju(4);
            cout<<"\n\tPonovite unos: ";
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
	        	    cout << "\n\tMolimo unesite da li je automobil servisiran (1-Da, 0-Ne)!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite da li je automobil servisiran (1-Da, 0-Ne)!\n";
        			promijeniBoju(7);
				}

        	promijeniBoju(4);
            cout<<"\n\tPonovite unos: ";
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
	        	    cout << "\n\tUnijeli ste znak umjesto broja. Molimo unesite da li automobil ima klimu (1-Da, 0-Ne)!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tUnijeli ste znak umjesto broja. Molimo unesite da li automobil ima klimu (1-Da, 0-Ne)!\n";
        			promijeniBoju(7);
				}

        	promijeniBoju(4);
            cout<<"\n\tPonovite unos: ";
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

        cout << "\t\tStanje (1-nov, 2-polovan): ";		cin >> a.stanje;

        while(a.stanje < 1 || a.stanje > 2)
		{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\n\tMolimo unesite ispravno (1-nov, 2-polovan)!\n";
	        	    cout << "\n\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite (1-nov, 2-polovan)!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\t\tPonovite unos: ";
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
	        	    cout << "\n\tMolimo unesite ispravno (1-dizel, 2-benzin, 3-plin)!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite ispravno (1-dizel, 2-benzin, 3-plin)!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\t\tPonovite unos: ";
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
	        	    cout << "\n\tMolimo unesite ispravno (1-prednji, 2-zadnji, 3-4x4)!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite ispravno (1-prednji, 2-zadnji, 3-4x4)!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\t\tPonovite unos: ";
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
	        	    cout << "\n\tMolimo unesite ispravno (1-manual, 2-automatik)!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite ispravno (1-manual, 2-automatik)!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\t\tPonovite unos: ";
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
	        	    cout << "\n\tMolimo unesite konjske snage!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite konjske snage!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
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
	        	    cout << "\n\tUnijeli ste znak umjesto broja. Molimo unesite kilovate!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();
        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite kilovate!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
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
	        	    cout << "\t\tMolimo unesite kubikazu!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();

        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite kubikazu!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> a.motor.kubikaza;
		}

        cout<<"\n________________________________________________________________________________\n";

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
    }

    void pregledAuta(Auto nizAuta[], int brAuta){	//strukturalna funkcija za pregled auta

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

};

bool porediCijeneVeca(Auto a, Auto b){		//funkcija za poredjenje auta

    return a.cijena > b.cijena;
}

bool porediCijeneManja(Auto a, Auto b){		//funkcija za poredjenje auta

    return a.cijena < b.cijena;
}

void pretraziAuta(Auto nizAuta[], int brAuta){		//funkcija za pretragu auta

    cout << "\n\tOdaberite neku opciju filtriranja";
    cout << "\n\t\t1. Sortiraj po cijeni(veca-manja)";
    cout << "\n\t\t2. Sortiraj po cijeni(manja-veca)";
    cout << "\n\t\t3. Pretrazi po cijeni";
    cout << "\n\t\t4. Pretrazi po imenu";
    cout << "\n\t\t5. Pretrazi po zemlji porijekla";
    cout << "\n\t\t6. Kombinovana pretraga";

    Auto a;

    int izbor;

    cout << "\n\n\tVas izbor za pretragu: ";
        cin >> izbor;

    	while(izbor < 1 || izbor > 6)
		{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\n\tMolimo unesite izbor ispravno (1-6)!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();

        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite izbor ispravno (1-6)!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> izbor;
		}

    cout<<"\n________________________________________________________________________________\n";

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

        	while(minCijena<0)
			{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\n\tMolimo unesite ispravnu minimalnu cijenu!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();

        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite ispravnu minimalnu cijenu!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> minCijena;
			}

    		cout << "\n\tUnesite maksimalnu cijenu automobila: ";
            float maksCijena;
            cin >> maksCijena;

            while(maksCijena < 0 )
			{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\n\tMolimo unesite ispravnu maksimalnu cijenu!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();

        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite ispravnu maksimalnu cijenu!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> maksCijena;
			}

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
            string imeProizvodjaca; // uslov
            cout << "\n\tUnesite ime proizvodjaca po kojem zelite da pretrazite auta";
            cout << "\n\tIme proizvodjaca: ";
            cin.ignore();
            getline(cin, imeProizvodjaca);

            bool provjera = true;

	        while(provjera)
	        {
	        	for(int i=0;i<imeProizvodjaca.length();i++)
	        	{
		        	if(isdigit(imeProizvodjaca.at(i)))
		        	{
		        		promijeniBoju(4);
		        		cout<<"\n\tNe postoji proizvodjac sa brojevima u nazivu!"<<endl;
		            	cout<<"\n\tPonovite unos: ";
		            	promijeniBoju(7);
		            	getline(cin, imeProizvodjaca);
		        		provjera = true;
		        		break;
					}
					else
					{
						provjera = false;
					}
				}
			}

			for(int i=0;i<imeProizvodjaca.length();i++)
			{
				if(i==0)
				{
					if(imeProizvodjaca.at(i)>=97 && imeProizvodjaca.at(i)<=122)
					{
						imeProizvodjaca.at(i) = imeProizvodjaca.at(i) - 32;
					}
				}
				else
				{
					if(imeProizvodjaca.at(i)>=65 && imeProizvodjaca.at(i)<=90)
					{
						imeProizvodjaca.at(i) = imeProizvodjaca.at(i) + 32;
					}
				}

			}

            Auto *autaPoImenu = new Auto[brAuta];
            int br=0;

            for(int i=0; i<brAuta; i++){
                if(nizAuta[i].proizvodjacAuta == imeProizvodjaca){
                    autaPoImenu[br++] = nizAuta[i];
                }
            }

            cout << "\n\tLista auta po imenu proizvodjaca: " << imeProizvodjaca << "\n";

            if(br > 0){
                a.pregledAuta(autaPoImenu, br);
                cout << "\n\tPress ENTER to continue...";
            }
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

            bool provjera = true;

            while(provjera)
	        {
	        	for(int i=0;i<zemlja.length();i++)
	        	{
		        	if(isdigit(zemlja.at(i)))
		        	{
		        		promijeniBoju(4);
		        		cout<<"\n\tNe postoji proizvodjac sa brojevima u nazivu!"<<endl;
		            	cout<<"\n\tPonovite unos: ";
		            	promijeniBoju(7);
		            	getline(cin, zemlja);
		        		provjera = true;
		        		break;
					}
					else
					{
						provjera = false;
					}
				}
			}

			for(int i=0;i<zemlja.length();i++)
			{
				if(i==0)
				{
					if(zemlja.at(i)>=97 && zemlja.at(i)<=122)
					{
						zemlja.at(i) = zemlja.at(i) - 32;
					}
				}
				else
				{
					if(zemlja.at(i)>=65 && zemlja.at(i)<=90)
					{
						zemlja.at(i) = zemlja.at(i) + 32;
					}
				}

			}

            Auto *autaPoZemlji=new Auto[brAuta];
            int br=0;

            for(int i=0; i<brAuta; i++){
                if(nizAuta[i].zemljaPorijekla == zemlja){
                    autaPoZemlji[br++] = nizAuta[i];
                }
            }
            cout << "\n\tLista auta iz zemlje: " << zemlja << "\n";

            if(br > 0){
                a.pregledAuta(autaPoZemlji, br);
                cout << "\n\tPress ENTER to continue...";
            }
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

            bool provjera = true;

	        while(provjera)
	        {
	        	for(int i=0;i<imeProizvodjaca.length();i++)
	        	{
		        	if(isdigit(imeProizvodjaca.at(i)))
		        	{
		        		promijeniBoju(4);
		        		cout<<"\n\tIme proizvodjaca ne moze imati brojeve u sebi!"<<endl;
		            	cout<<"\n\tPonovite unos: ";
		            	promijeniBoju(7);
		            	getline(cin, imeProizvodjaca);
		        		provjera = true;
		        		break;
					}
					else
					{
						provjera = false;
					}
				}
			}

			for(int i=0;i<imeProizvodjaca.length();i++)
			{
				if(i==0)
				{
					if(imeProizvodjaca.at(i)>=97 && imeProizvodjaca.at(i)<=122)
					{
						imeProizvodjaca.at(i) = imeProizvodjaca.at(i) - 32;
					}
				}
				else
				{
					if(imeProizvodjaca.at(i)>=65 && imeProizvodjaca.at(i)<=90)
					{
						imeProizvodjaca.at(i) = imeProizvodjaca.at(i) + 32;
					}
				}

			}

            cout << "\n\tUnesite boju: ";		getline(cin, bojaAuta);

            provjera = true;

	        while(provjera)
	        {
	        	for(int i=0;i<bojaAuta.length();i++)
	        	{
		        	if(isdigit(bojaAuta.at(i)))
		        	{
		        		promijeniBoju(4);
		        		cout<<"\n\tNaziv boje ne moze imati brojeve u sebi!"<<endl;
		            	cout<<"\n\tPonovite unos: ";
		            	promijeniBoju(7);
		            	getline(cin, bojaAuta);
		        		provjera = true;
		        		break;
					}
					else
					{
						provjera = false;
					}
				}
			}

            cout << "\n\tUnesite cijenu: ";			cin >> cijenaAuta;

            while(cijenaAuta < 0 )
			{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\n\tMolimo unesite ispravnu cijenu auta!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();

        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite ispravnu cijenu auta!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> cijenaAuta;
			}

            cout << "\n\tUnesite stanje auta (1-nov, 2-polovan): "; 		cin >> stanjeAuta;

            while( stanjeAuta < 1 || stanjeAuta > 2 )
			{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\n\tMolimo unesite ispravno stanje auta (1-nov, 2-polovan)!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();

        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite ispravno stanje auta (1-nov, 2-polovan)!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> stanjeAuta;
			}

            cout << "\n\tUnesite gorivo (1-dizel, 2-benzin, 3-plin): "; 		cin >> gorivoAuta;

            while(gorivoAuta < 1 || gorivoAuta > 3 )
			{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\n\tMolimo unesite ispravnu opciju za gorivo (1-dizel, 2-benzin, 3-plin)!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();

        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite ispravnu opciju za gorivo: (1-dizel, 2-benzin, 3-plin)!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> gorivoAuta;
			}


            Auto *auta = new Auto[brAuta];
            int br=0;

            for(int i=0; i<brAuta; i++)
            {
                if((nizAuta[i].proizvodjacAuta == imeProizvodjaca) && (nizAuta[i].boja == bojaAuta) && (nizAuta[i].cijena
                   <= cijenaAuta) && (nizAuta[i].stanje == stanjeAuta) && (nizAuta[i].gorivo == gorivoAuta))
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
}

void ispisUplatnice(Auto nizAuta[], int br){

	Kupac k;
    string fajl = "uplatnica.txt";

    cout << "\n\tZelite li izvrsiti pretragu auta prije kupovine (y/n)? ";
    cin.ignore();
    string get;
    cin>>get;

    if(get == "y" || get == "Y"){
        pretraziAuta(nizAuta, br);
    }else{
        cout<<"\n";
    }

    cout << "\n\tIspod je lista auta. Izaberite redni broj auta koje zelite kupiti\n";

        for(int i=0; i<br; i++)
            cout << "\t\t" << i+1 << ". " << nizAuta[i].proizvodjacAuta << " " << nizAuta[i].modelAuta << " "
            << " " << nizAuta[i].motor.kW << " kW\n";

        cout << "\n________________________________________________________________________________\n";

        int izbor;

		cout<<"\n\tIzbareite vozilo koje zelite kupiti: ";
    	cin>>izbor;


    		while(izbor < 1 || izbor > br )
			{

				if(cin.fail())
				{

	        	    cin.cls();
	    	        cin.ignore(1000, '\n');

	            	promijeniBoju(4);
	        	    cout << "\n\tMolimo unesite ispravno izbor (1-"<<br<<")!\n";
	        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
	        	    promijeniBoju(7);

					cin. get();

        		}
        		else
        		{
        			promijeniBoju(4);
        			cout << "\n\tMolimo unesite ispravno izbor (1-"<<br<<")!\n";
        			promijeniBoju(7);
				}

            	promijeniBoju(4);
            	cout<<"\n\tPonovite unos: ";
            	promijeniBoju(7);
            	cin >> izbor;
			}


    cout << "\n\tUnesite svoje informacije: \n";
    int nacinP = k.unosKupcaZaKupovinu();

    if(nacinP == 2){

        ofstream uplatnica("uplatnica.txt");
        uplatnica << "-----------------------------------------------------------------------------------------\n";
        uplatnica << "\n\t\t\t\tAutosalon 'KEJ' d.o.o.\n\n";
        uplatnica << "-----------------------------------------------------------------------------------------\n";
        uplatnica << "\n\t\tIme i prezime: " << k.ime << " " << k.prezime << endl;
        uplatnica << "\n\n\t\tINFORMACIJE O AUTOMOBILU: \n\n\t\tProizvodjac: " << nizAuta[izbor-1].proizvodjacAuta << "\n\t\tModel: " << nizAuta[izbor-1].modelAuta <<endl;
        uplatnica << "\n\t\tIznos sa kamatama: "<< cijenaSaKamatom(nizAuta[izbor-1].cijena, nizAuta[izbor-1].cijena) << " KM." << endl;
        uplatnica << "\n\t\tMjesecna rata: "<< (nizAuta[izbor-1].cijena/12)+(nizAuta[izbor-1].cijena*1/100) << " KM." << endl;
        time_t now=time(0);
    	tm *ltm=localtime(&now);
    	uplatnica << "\n\t\tDatum kupovine: "<<ltm->tm_mday<<"."<<1+ltm->tm_mon<<"."<<1900+ltm->tm_year<<"."<<endl;
        uplatnica << "\n\n\n\t\t\t\t\t\tPotpis: _________________________\n\n";
        uplatnica << "-----------------------------------------------------------------------------------------\n";
        uplatnica << "\n\t\t\tTim Autosalona 'KEJ' Vam zeli sigurnu voznju!\n\n";
        uplatnica << "-----------------------------------------------------------------------------------------\n";
        uplatnica.close();
    }
    else{

        ofstream uplatnica("uplatnica.txt");
        uplatnica << "-----------------------------------------------------------------------------------------\n";
        uplatnica << "\n\t\t\t\tAutosalon 'KEJ' d.o.o.\n\n";
        uplatnica << "-----------------------------------------------------------------------------------------\n";
        uplatnica << "\t\tIme i prezime: " << k.ime << " " << k.prezime << endl;
        uplatnica << "\n\n\t\tINFORMACIJE O AUTOMOBILU: \n\n\t\tProizvodjac: " << nizAuta[izbor-1].proizvodjacAuta << "\n\t\tModel: " << nizAuta[izbor-1].modelAuta <<endl;
        uplatnica << "\n\t\tUkupni iznos: "<< nizAuta[izbor-1].cijena << " KM." << endl;
        time_t now=time(0);
    	tm *ltm=localtime(&now);
    	uplatnica << "\n\t\tDatum kupovine: "<<ltm->tm_mday<<"."<<1+ltm->tm_mon<<"."<<1900+ltm->tm_year<<"."<<endl;
        uplatnica << "\n\n\n\t\t\t\t\t\tPotpis: _________________________\n\n";
        uplatnica << "-----------------------------------------------------------------------------------------\n";
        uplatnica << "\n\t\t\tTim Autosalona 'KEJ' Vam zeli sigurnu voznju!\n\n";
        uplatnica << "-----------------------------------------------------------------------------------------\n";
        uplatnica.close();

    }


    promijeniBoju(2);
    cout << "\n\tUplatnica uspjesno snimljena u " << fajl << endl;
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

}

void prikaziMeniK(){			//meni za kupca
	system("cls");
    cout << "\t\t==============================================\n";
    cout << "\t\t|\t\t"<<setw(9)<<"MENI:"<<setw(22)<<"|\n";
    cout << "\t\t==============================================\n";
    cout << "\t\t|\t1. Pregled automobila"<<setw(18)<<"|\n";;
    cout << "\t\t|\t2. Pretraga automobila"<<setw(17)<<"|\n";
    cout << "\t\t|\t3. Kupovina automobila"<<setw(17)<<"|\n";
    cout << "\t\t|\t4. Ostavi feedback    "<<setw(17)<<"|\n";
    cout << "\t\t|\t5. Kraj"<<setw(32)<<"|\n";;
    cout << "\t\t==============================================\n";
}

void feedback(Kupac k){

    ofstream izlaz("feedback.txt", ios::app);

    string misljenje;

    cout << "\t______________________________________\n";
    cout << "\n\tOstavite vase misljenje o aplikaciji \n";
    cout << "\t______________________________________\n";
    cin.ignore();
    cout << "\n________________________________________________________________________________\n";
    cout << "\n\n\tFeedback: "; getline(cin, misljenje);

    izlaz << "\n_________________________________________________________________________________________\n";
    izlaz << "\n\n\tFeedback: " << misljenje << "\n";

    cout << "\n________________________________________________________________________________\n";

    int ocjena;
    cout << "\n\t________________________\n";
    cout << "\n\tOcijenite aplikaciju \n";
    cout << "\t________________________\n";

    cout << "\n\t\tOdlicno         ->  * * * * * [5]\n";
    cout << "\t\tDobro           ->  * * * *   [4]\n";
    cout << "\t\tProsjecno       ->  * * *     [3]\n";
    cout << "\t\tIspod prosjeka  ->  * *       [2]\n";
    cout << "\t\tLose            ->  *         [1]\n";

    cout << "\n\tOcjena: (1-5): "; cin >> ocjena;

    cout << "\n________________________________________________________________________________\n";

    izlaz << "\n\tOcjena: ";

    if (ocjena == 1) {

		izlaz << "1 [ lose ] " << endl;

	}

	if (ocjena == 2) {

		izlaz << "2 [ ispod prosjeka ] " << endl;

	}

	if (ocjena == 3) {

		izlaz << "3 [ prosjecno ] " << endl;

	}

	if (ocjena == 4) {

		izlaz << "4 [ Dobro ] " << endl;

	}

	if (ocjena == 5) {

		izlaz << "5 [ Odlicno ] " << endl;

	}

	cout << "\n\tZelite li ostati anonimni? (y/n): ";
	string odgovor;
	cin >> odgovor;

	if (odgovor == "n" || odgovor == "N") {

		izlaz << "\n\tKorisnik: " << k.ime <<  " " << k.prezime <<  endl;

	}
	if(odgovor == "y" || odgovor == "Y") {

		izlaz << "\n\tKorisnik je odabrao ostati anoniman." << endl;

	}

    cout << "\n________________________________________________________________________________\n";
	izlaz << "\n_________________________________________________________________________________________\n";
	izlaz << "\n*****************************************************************************************";


    izlaz.close();

}

void mainMeniK(Kupac k, Auto a){			//glavna funkcija za meni kupca

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
		}

		 int izbor;
		 int get;

	    do{
    	    cout<<"\n________________________________________________________________________________\n";
	        cout << "\n\tVas izbor: ";

        	cin >> izbor;

    	    if(cin.fail()){

        	    cin.cls();
    	        cin.ignore(1000, '\n');
	            system("cls");

            	cout<<"\n________________________________________________________________________________\n\n";
            	promijeniBoju(4);
        	    cout << "\tUnijeli ste znak umjesto broja. Molimo pokusajte ponovo\n";
        	    promijeniBoju(7);
    	        cout<<"\n________________________________________________________________________________\n\n";

	            prikaziMeniK();
            	continue;
        	}
                if(izbor<1 || izbor>5)
                {
                    promijeniBoju(4);
                    cout<<"\n\tPonovite unos"<<endl;
                    promijeniBoju(7);
                }

		}while(izbor<1 || izbor>5);

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
	                cout << boldiraj << "\n\t\t\t     Panel za feedback\n" << ukloniBold;
                	cout << brk;

                    feedback(k);

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

	        if(izbor==5){

                system("exit");

			}
	        else{
	        	cin.ignore();

            	cout << "\n\t-------------------------";
        	    cout << "\n\t0. Izlaz\n\t1. Nazad ";
        	    cout << "\n\t-------------------------";

	        	cout << "\n\tVas izbor: ";
        	    cin >> get;

        	    while(get < 0 || get > 1 )
				{

					if(cin.fail())
					{

		        	    cin.cls();
		    	        cin.ignore(1000, '\n');

		            	promijeniBoju(4);
		        	    cout << "\n\n\tMolimo unesite ispravno izbor (0 ili 1)!\n";
		        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
		        	    promijeniBoju(7);

						cin. get();

	        		}
	        		else
	        		{
	        			promijeniBoju(4);
	        			cout << "\n\n\tMolimo unesite ispravno izbor (0 ili 1)!\n";
	        			promijeniBoju(7);
					}

	            	promijeniBoju(4);
	            	cout<<"\n\tPonovite unos: ";
	            	promijeniBoju(7);
	            	cin >> get;
				}

    	        cout<<"\n";
    	        cout<<"\n";

	            if(get==1){
            	    system("cls");
        	        mainMeniK(k,a);
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
}

void mainMeniA(Auto a){			//funkcija za glavni meni Admina

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
    	int get;
    	int izbor;

        do{
    	    cout<<"\n________________________________________________________________________________\n";
	        cout << "\n\tVas izbor: ";
        	cin >> izbor;

    	    if(cin.fail()){

        	    cin.cls();
    	        cin.ignore(1000,'\n');
	            system("cls");

            	cout<<"\n________________________________________________________________________________\n\n";
        	    cout << "\tUnijeli ste znak umjesto broja. Molimo pokusajte ponovo\n";
    	        cout<<"\n________________________________________________________________________________\n\n";

	            prikaziMeniA();
            	continue;
        	}
                if(izbor<1 || izbor>5)
                {
                    promijeniBoju(4);
                    cout<<"\n\tPonovite unos!"<<endl;
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

            	cout << "\n\t-------------------------";
        	    cout << "\n\t0. Izlaz\n\t1. Nazad ";
        	    cout << "\n\t-------------------------";

	        	cout << "\n\tVas izbor: ";
        	    cin >> get;

        	    while(get < 0 || get > 1 )
				{

					if(cin.fail())
					{

		        	    cin.cls();
		    	        cin.ignore(1000, '\n');

		            	promijeniBoju(4);
		        	    cout << "\n\n\tMolimo unesite ispravno izbor (0 ili 1)!\n";
		        	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
		        	    promijeniBoju(7);

						cin. get();

	        		}
	        		else
	        		{
	        			promijeniBoju(4);
	        			cout << "\n\n\tMolimo unesite ispravno izbor (0 ili 1)!\n";
	        			promijeniBoju(7);
					}

	            	promijeniBoju(4);
	            	cout<<"\n\tPonovite unos: ";
	            	promijeniBoju(7);
	            	cin >> get;
				}

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
}

int main(){
	welcome();
	cout<<"\n________________________________________________________________________________\n";

	Auto a;
	int izbor;

	cout<<"\n\n\tIzaberite na koji se sistem zelite prijaviti: \n\t\tKUPAC (1) \n\t\tRADNIK (2) \n\n";

	cout<<"\tVas izbor: ";
	cin>>izbor;

	while(izbor < 1 || izbor > 2 )
	{

		if(cin.fail())
		{

       	    cin.cls();
   	        cin.ignore(1000, '\n');

           	promijeniBoju(4);
       	    cout << "\n\tMolimo unesite ispravno izbor (1 ili 2)!\n";
       	    cout << "\tZa nastavak pritisnite ENTER!"<<endl;
       	    promijeniBoju(7);

			cin. get();

   		}
   		else
   		{
   			promijeniBoju(4);
   			cout << "\n\tMolimo unesite ispravno izbor (1 ili 2)!\n";
   			promijeniBoju(7);
		}

           	promijeniBoju(4);
           	cout<<"\n\tPonovite unos: ";
           	promijeniBoju(7);
           	cin >> izbor;
	}


	if(izbor==2){

		string username; //zadano je da bude admin
		string password; //zadano je da bude admin

		system("cls");
		int brPokusaja=0;

		do{
			cin.ignore();

			cout << "\n\n\n\t\t\tusername: "; 	//provjera admina
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

        mainMeniA(a);	//poziv funkcije za meni

	}else{
        Kupac k;
		k.prijavaKupca();
		mainMeniK(k, a);	//poziv funkcije za meni
	}

cout<<"\n________________________________________________________________________________\n";
return 0;
}
