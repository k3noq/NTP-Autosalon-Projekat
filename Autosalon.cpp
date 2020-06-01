#include<iostream>			//otvorene potrebne biblioteke kako bi bila omogucena maksimalna funkcionalnost programa
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
//#include <windows.h>
#include<ncurses.h>
#include<ctime>

/*
	username: admin
	password: admin
*/

using namespace std;

//void //promijeniBoju(int zeljenaBoja){
//     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), zeljenaBoja);					//ovo smo nasli na internetu
//}

string brk = "\n********************************************************************************\n";	//bit ce koristena u nastavku za izbjegavanje ponavljanja

void welcome(){				//pocetna funkcija
    cout << "================================================================================\n";
    //promijeniBoju(2);
    cout << "|\t"<<setw(34)<<"WELCOME"<<setw(39)<<"|\n";
    //promijeniBoju(7);
    cout << "================================================================================\n";
    cout << "|Ovo je program koji omogucava rad nad podacima karakteristicnim za automobile |"<<"\n";
    cout << "|\t\t    |Ovaj program je simulacija autosalona|"<<setw(22)<<"|\n";
    cout << "================================================================================\n";
}

ostream& boldiraj(ostream& os){  //  funkcija za otvaranje tagova za boldiranje teksta
    return os << "\e[1m";       //  nisam siguran da li radi na windowsu, ako ne, obrisite
}

ostream& ukloniBold(ostream& os){ //  funkcija za zatvaranje tagova za boldiranje
    return os << "\e[0m";
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
    int godine;
    int brRacuna;
    nacinPlacanja nP;
    Datum datumKupovine;

    Kupac() : ime(""), prezime(""), adresa(""), godine(0), brRacuna(0), nP(nacinPlacanja(1)) {}

    void unosKupcaZaKupovinu(){
    	ofstream lista("kupovina.txt", ios::app);
    	lista<<"Podaci o kupcu:\n";

    	cout<<"Ime: ";
    	char *Ime = new char[40];
		cin.getline(Ime,40);
		ime = Ime;
		lista<<"Ime: "<<ime<<endl;

		cout<<"Prezime: ";
    	char *Prezime = new char[40];
		cin.getline(Prezime,40);
		prezime = Prezime;
    	lista<<"Prezime: "<<prezime<<endl;

		cout<<"Adresa: ";
    	char *Adresa = new char[40];
		cin.getline(Adresa,40);
		adresa = Adresa;
		lista<<"Adresa: "<<adresa<<endl;

    	cout<<"Broj racuna: ";
    	cin>>this->brRacuna;
    	lista<<"Broj racuna: "<<brRacuna<<endl;

    	int x;
    	cout<<"Nacin placanja: \n\t\t1. Gotovinom \n\t\t2. Karticno\n";
    	do{
    		cout<<"Vas odabir: ";
    		cin >> x;
    		if(x<1 || x>2){
            	//promijeniBoju(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	//promijeniBoju(7);
			}
		}while(x<1 || x>2);
		switch(x){
    		case 1:
    			lista<<"Nacin placanja: gotovinom"<<endl;
    			break;
    		case 2:
    			lista<<"Nacin placanja: karticno"<<endl;
    			break;
		}
    	this->nP=(nacinPlacanja)x;

    	time_t now=time(0);
    	tm *ltm=localtime(&now);
    	lista<<"Datum kupovine: "<<ltm->tm_mday<<"."<<1+ltm->tm_mon<<"."<<1900+ltm->tm_year<<"."<<endl;
    	lista<<"Vrijeme kupovine: "<<1+ltm->tm_hour<<":"<<1+ltm->tm_min<<":"<<1+ltm->tm_sec<<endl;

    	this->datumKupovine.dan=ltm->tm_mday;
    	this->datumKupovine.mjesec=1+ltm->tm_mon;
    	this->datumKupovine.godina=1900+ltm->tm_year;

    	lista<<"**************************************************\n";
    	lista.close();
	}

	void prijavaKupca(){
		system("clear");
		cout << "================================================================================\n";
  		cout << "| \t\tPrije nego sto nastavite istrazivati nasu ponudu\t\t|"<<"\n";
    	cout << "|\t\t    |Molimo Vas da unesete sljedece podatke|"<<setw(22)<<"|\n";
    	cout << "================================================================================\n";
		ofstream lista("logs.txt", ios::app);
    	lista<<"\nPodaci o posjetiocima:\n\n";
    	cin.ignore();
    	cout<<"\n\tIme: ";
    	char *Ime = new char[40];
		cin.getline(Ime,40);
		ime = Ime;
		lista<<"Ime:\t\t\t"<<ime<<endl;

		cout<<"\tPrezime: ";
    	char *Prezime = new char[40];
		cin.getline(Prezime,40);
		prezime = Prezime;
    	lista<<"Prezime:\t\t"<<prezime<<endl;

    	time_t now= time(0);
    	tm *ltm=localtime(&now);
    	lista<<"Datum pristupa:\t\t"<<ltm->tm_mday<<"."<<1+ltm->tm_mon<<"."<<1900+ltm->tm_year<<"."<<endl;
    	lista<<"Vrijeme pristupa:\t"<<ltm->tm_hour<<":"<<ltm->tm_min<<":"<<ltm->tm_sec<<endl;

    	lista<<"\n******************************************************\n";
    	lista.close();
	}

};

enum Stanje {nov = 1, polovan};
enum Gorivo {dizel = 1, benzin, plin};
enum Pogon  {prednji = 1, zadnji, _4x4};
enum Transmisija {manual = 1, automatic};

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

    Stanje stanje;
    Gorivo gorivo;
    Pogon pogon;
    Transmisija transmisija;

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
            stanje = (Stanje)1;
            gorivo = (Gorivo)1;
            pogon = (Pogon)1;
            transmisija = (Transmisija)1;
        }

    Auto unosAuta(){
        Auto a;

        ofstream auta("auta.txt", ios::app);

        cin.ignore();

        cout << "\n\tIme proizvodjaca: ";
            getline(cin, a.proizvodjacAuta);
            auta<<"\n"<<left<<setw(12)<<a.proizvodjacAuta;

        cout << "\tIme modela: ";
            getline(cin, a.modelAuta);
            auta<<left<<setw(8)<<a.modelAuta;

        cout << "\tZemlja porijekla: ";
            getline(cin, a.zemljaPorijekla);
            auta<<left<<setw(10)<<a.zemljaPorijekla;

        cout << "\tBoja auta: ";
            getline(cin, a.boja);
            auta<<left<<setw(7)<<a.boja;

        do{
        	cout << "\n\tBroj vrata(zajedno sa gepekom): ";
            	cin >> a.brVrata;
            if(a.brVrata!=3 && a.brVrata!=5){
            	//promijeniBoju(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	//promijeniBoju(7);
			}
		}while(a.brVrata!=3 && a.brVrata!=5);
		auta<<left<<setw(3)<<a.brVrata;

       	cout << "\tBroj stepeni prenosa: ";
            cin >> a.brStepeniPrenosa;
            auta<<left<<setw(3)<<a.brStepeniPrenosa;
        cout << "\tKilometraza: ";
            cin >> a.kilometraza;
            auta << left <<setw(9)<<a.kilometraza;
        do{
        	cout << "\tGodiste: ";
            	cin >> a.godiste;
            if(a.godiste<1886 || a.godiste>2020){
            	//promijeniBoju(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	//promijeniBoju(7);
			}
		}while(a.godiste<1886 || a.godiste>2020);
		auta<<left<<setw(6)<<a.godiste;

        do{
        	cout << "\tCijena: ";
     	       cin >> a.cijena;
     	    if(a.cijena<0){
            	//promijeniBoju(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	//promijeniBoju(7);
			}
		}while(a.cijena<0);
		auta<<left<<setw(8)<<a.cijena;

        cout << "\tPotrosnja na 100km: ";
            cin >> a.potrosnja;
            auta<<left<<setw(6)<<a.potrosnja;

        cout << "\n\n\tZa sljedece unose koritite 1-DA, 0-NE\n";
        cout << "\t\tRegistrovan: ";
            	cin >> a.jeRegistrovan;
		auta<<left<<setw(3)<<a.jeRegistrovan;
        cout << "\t\tServisiran: ";
            	cin >> a.jeServisiran;
		auta<<left<<setw(3)<<a.jeServisiran;
        cout << "\t\tKlima: ";
	            cin >> a.imaKlimu;
		auta<<left<<setw(3)<<a.imaKlimu;

        int x;
        cout << "\n\tSljedece karakteristike odaberite ponudjenim brojevima:\n";
        do{
        	cout << "\t\tStanje (1-nov, 2-polovan): ";
            	cin >> x;
            if(x<1 || x>2){
            	//promijeniBoju(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	//promijeniBoju(7);
			}
		}while(x<1 || x>2);
			a.stanje = (Stanje)x;
			auta<<left<<setw(3)<<a.stanje;
        do{
        	cout << "\t\tGorivo (1-dizel, 2-benzin, 3-plin): ";
            	cin >> x;
            if(x<1 || x>3){
            	//promijeniBoju(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	//promijeniBoju(7);
			}
		}while(x<1 || x>3);
			a.gorivo = (Gorivo)x;
			auta<<left<<setw(3)<<a.gorivo;
        do{
        	cout << "\t\tPogon (1-prednji, 2-zadnji, 3-4x4): ";
            	cin >> x;
            if(x<1 || x>3){
            	//promijeniBoju(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	//promijeniBoju(7);
			}
		}while(x<1 || x>3);
            a.pogon = (Pogon)x;
            auta<<left<<setw(3)<<a.pogon;
        do{
        	cout << "\t\tTransmisija (1-manual, 2-automatik): ";
            	cin >> x;
            if(x<1 || x>2){
            	//promijeniBoju(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	//promijeniBoju(7);
			}
		}while(x<1 || x>2);
            a.transmisija = (Transmisija)x;
            auta<<left<<setw(3)<<a.transmisija;

        cout << "\n\n\tKarakteristike motora:\n";
        cout << "\t\tKonjske snage: ";
            cin >> a.motor.konjskeSnage;
            auta<<left<<setw(5)<<a.motor.konjskeSnage;
        cout << "\t\tKilovati: ";
            cin >> a.motor.kW;
            auta<<left<<setw(5)<<a.motor.kW;
        cout << "\t\tKubikaza: ";
            cin >> a.motor.kubikaza;
            auta<<left<<setw(6)<<a.motor.kubikaza<<endl;
        cout<<"\n--------------------------------------------------------------------------------\n";
		auta.close();
    return a;
    }

    void pregledAuta(Auto nizAuta[], int brAuta){

        for(int i=0; i<brAuta; i++){

            cout << "\n\t--------------------------------------\n";
            cout << "\t\t" <<setw(12)<< nizAuta[i].proizvodjacAuta << " " << nizAuta[i].modelAuta;
            cout << "\n\t--------------------------------------\n";

            cout << "\n\tIme proizvodjaca:	" << left << nizAuta[i].proizvodjacAuta;

            cout << "\n\tIme modela:		" << left << nizAuta[i].modelAuta;

            cout << "\n\tZemlja porijekla:	" << left << nizAuta[i].zemljaPorijekla;

            cout << "\n\tBoja auta:		" << left << nizAuta[i].boja;

            cout << "\n\tBroj vrata:		" << left << nizAuta[i].brVrata-1 << "/" <<nizAuta[i].brVrata;

            cout << "\n\tBroj stepeni prenosa:	" << left << nizAuta[i].brStepeniPrenosa << "+R";

            cout << "\n\tKilometraza:		" << left << nizAuta[i].kilometraza;

            cout << "\n\tGodiste: 		" << left << nizAuta[i].godiste << ".";

            cout << "\n\tCijena: 		" << left << nizAuta[i].cijena << " KM";

            cout << "\n\tPotrosnja na 100km:	" << left << nizAuta[i].potrosnja << "l";

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

bool porediCijeneVeca(Auto a, Auto b){

    return a.cijena > b.cijena;
}

bool porediCijeneManja(Auto a, Auto b){

    return a.cijena < b.cijena;
}

void pretraziAuta(Auto nizAuta[], int brAuta){

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

    switch(izbor){
        case 1:
            sort(nizAuta, nizAuta+brAuta, porediCijeneVeca);
          //  a.pregledAuta(nizAuta,brAuta);
            break;

        case 2:
            sort(nizAuta, nizAuta+brAuta, porediCijeneManja);
           // a.pregledAuta(nizAuta,brAuta);
            break;

        case 3:
        {
            cout << "\n\tUnesite cijenu automobila: ";
            float cijena;
            cin >> cijena;

            Auto *autaPoCijeni = new Auto[brAuta];
            int br=0;

            for(int i=0; i<brAuta; i++){
                if(nizAuta[i].cijena <= cijena){
                    autaPoCijeni[br++] = nizAuta[i];
                }
            }

            cout << "\n\tLista automobila sa cijenom manjom od " <<cijena<< " KM \n";
            if(br > 0){
                sort(autaPoCijeni, autaPoCijeni+br, porediCijeneVeca);    //  sortira se da ne bi doslo do random redanja po cijenama
                //a.pregledAuta(autaPoCijeni, br);
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
            //if(br > 0)
                //a.pregledAuta(autaPoImenu, br);
            //else cout << "\n\t\tNema takvih automobila.";

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
            /*if(br > 0)
                a.pregledAuta(autaPoZemlji, br);
            else cout << "\n\t\tNema takvih automobila.";
*/
            delete[] autaPoZemlji;
            break;
        }

        case 6:
        {

            string imeProizvodjaca, bojaAuta;
            float cijenaAuta;
            int stanjeAuta, gorivoAuta;
            cin.ignore();

            cout << "\n\tUnesite ime proizvodjaca: ";
            getline(cin, imeProizvodjaca);

            cout << "\n\tUnesite boju: ";
            getline(cin, bojaAuta);

            cout << "\n\tUnesite cijenu: ";
            cin >> cijenaAuta;

            cout << "\n\tUnesite stanje auta (1-nov, 2-polovan): ";
            cin >> stanjeAuta;
            Stanje stanje = (Stanje)stanjeAuta;

            cout << "\n\tUneiste gorivo (1-dizel, 2-benzin, 3-plin): ";
            cin >> gorivoAuta;
            Gorivo gorivo = (Gorivo)gorivoAuta;


            Auto *auta = new Auto[brAuta];
            int br=0;

            for(int i=0; i<brAuta; i++){
                if(nizAuta[i].proizvodjacAuta == imeProizvodjaca && nizAuta[i].boja == bojaAuta && nizAuta[i].cijena <= cijenaAuta && nizAuta[i].stanje == stanje && nizAuta[i].gorivo == gorivo){
                    auta[br++] = nizAuta[i];
                }
            }

            cout << "\n\tLista auta sa datim karakteristikama: ";
            /*if(br > 0)
                a.pregledAuta(auta, br);
            else cout << "\n\t\tNema takvih automobila.";
*/
            delete[] auta;
            break;
        }

        default:
            cout << "\n\tOdabrali ste nepostojecu opciju.";
    }
}

/*void kratkiIspis(){
	Auto *a;
	int brAuta=0;
   	a=new Auto[2000];
	ifstream auta("auta.txt");
	while(auta>>setw(12)>>a[brAuta].proizvodjacAuta>>setw(8)>>a[brAuta].modelAuta
		>>setw(10)>>a[brAuta].zemljaPorijekla>>setw(7)>>a[brAuta].boja>>setw(3)
		>>a[brAuta].brVrata>>setw(9)>>a[brAuta].kilometraza>>setw(6)>>a[brAuta].godiste
		>>setw(8)>>a[brAuta].cijena>>setw(6)>>a[brAuta].potrosnja>>setw(3)
		>>a[brAuta].jeRegistrovan>>setw(3)>>a[brAuta].jeServisiran>>setw(3)>>a[brAuta].imaKlimu
		>>setw(3)>>a[brAuta].stanje>>setw(3)>>a[brAuta].gorivo>>setw(3)>>a[brAuta].pogon
		>>setw(3)>>a[brAuta].transmisija>>setw(5)>>a[brAuta].motor.konjskeSnage>>setw(5)
		>>a[brAuta].motor.kW>>setw(6)>>a[brAuta].motor.kubikaza) brAuta++;

	for(int i=0; i<brAuta; i++) cout << "\t\t" << i+1 << ". " << a[i]->proizvodjacAuta << " " << a[i]->modelAuta << " " << a[i]->motor.jacinaMotora << " " << a[i]->motor.kW << " kW\n";
}
*/
void ispisUplatnice(Auto nizAuta[], int br){

    cout << "\n\tZelite li izvrisiti pretragu auta prije kupovine (y/n)? ";
    cin.ignore();
    char get = cin.get();

    if(get == 'y' || get == 'Y'){
        pretraziAuta(nizAuta, br);
    }

    cout << "\n\tIspod je lista auta. Izaberite redni broj auta koje zelite kupiti\n";
 /*   for(int i=0; i<br; i++){
        kratkiIspis(&nizAuta[i], i);
    }
*/

/*

    string fajl = "uplatnica.txt";

    ofstream uplatnica("uplatnica.txt");

    uplatnica << "------------------------------------------------------------\n";
    uplatnica << "\t\t\tAutosalon 'KEJ' d.o.o.:\n";
    uplatnica << "------------------------------------------------------------\n";
    //uplatnica << "Ime i prezime: " << sifra << "\tPotrosac: " << tekst << "\tIznos "<< suma << " KM." << endl;
    uplatnica << "\n\t\t\tPotpis: _________________________\n";
    uplatnica << "------------------------------------------------------------\n";
    uplatnica.close();
    cout << "Uplatnica uspjesno snimnjena u " << fajl << endl;

*/

}

void prikaziMeniA(){			//meni za admina tj prodavca
	system("clear");
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
	system("clear");
    cout << "\t\t==============================================\n";
    cout << "\t\t|\t\t"<<setw(9)<<"MENI:"<<setw(22)<<"|\n";
    cout << "\t\t==============================================\n";
    cout << "\t\t|\t1. Pregled automobila"<<setw(18)<<"|\n";;
    cout << "\t\t|\t2. Pretraga automobila"<<setw(17)<<"|\n";
    cout << "\t\t|\t3. Ispis uplatnice"<<setw(21)<<"|\n";
    cout << "\t\t|\t4. Kraj"<<setw(32)<<"|\n";;
    cout << "\t\t==============================================\n";
}

int main(){
	welcome();
	cout<<"\n--------------------------------------------------------------------------------\n";

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

            int zaStanje, zaGorivo, zaPogon, zaTransmisiju;
//            if(nizAuta[br].stanje == 1) nizAuta[br].stanje=(Stanje)1;
//            else nizAuta[br].stanje=(Stanje)2;

            zaStanje = nizAuta[br].stanje;
            zaGorivo = nizAuta[br].gorivo;
            zaPogon = nizAuta[br].pogon;
            zaTransmisiju = nizAuta[br].transmisija;

//            zaStanje=(Stanje)zaStanje;
//            zaGorivo=(Gorivo)zaGorivo;
//            zaPogon=(Pogon)zaPogon;
//            zaTransmisiju=(Transmisija)zaTransmisiju;

            auta>>zaStanje;
            auta>>zaGorivo;
            auta>>zaPogon;
            auta>>zaTransmisiju;

            auta>>nizAuta[br].motor.konjskeSnage;
            auta>>nizAuta[br].motor.kW;
            auta>>nizAuta[br].motor.kubikaza;

		 br++;
		}

	Auto a;
	int izbor;

	cout<<"\tIzaberite na koji se sistem zelite prijaviti: \n\t\tKUPAC (1) \n\t\tRADNIK (2) \n\n";

	do{
		cout<<"\tVas izbor: ";
		cin>>izbor;
		if(izbor<1 || izbor>2){
           	//promijeniBoju(4);
           	cout<<"\t\tPonovite unos"<<endl;
           	//promijeniBoju(7);
		}
	}while(izbor<1 || izbor>2);


	if(izbor==2){

		string username; //zadano je da bude admin
		string password; //zadano je da bude admin

		system("clear");
		int brPokusaja=0;
		do{
			cin.ignore();
			cout<<"\n\n\n\t\t\tusername: ";
			getline(cin, username);
			cout<<"\n\t\t\tpassword: ";
			cin>>password;
			brPokusaja++;
			if(username!="admin" && password!="admin" && brPokusaja<3){
				system("clear");
				//promijeniBoju(4);
           		cout<<"\t\tNeisparvan unos";
           		//promijeniBoju(7);
           		cout<<"\t\t\t\tBroj pokusaja: "<<3-brPokusaja<<endl;
			}else if(password!="admin" && brPokusaja<3){
				system("clear");
				//promijeniBoju(4);
           		cout<<"\t\tNeispravan password";
           		//promijeniBoju(7);
           		cout<<"\t\t\t\tBroj pokusaja: "<<3-brPokusaja<<endl;
			}else if(username!="admin" && brPokusaja<3){
				//promijeniBoju(4);
           		cout<<"\t\tNeispravan username";
           		//promijeniBoju(7);
           		cout<<"\t\t\t\tBroj pokusaja: "<<3-brPokusaja<<endl;
			}
			if(brPokusaja==3){
				system("clear");
				main();
			}
		}while(username!="admin" || password!="admin");

		prikaziMeniA();

		//Auto *nizAuta=new Auto[50];
		//int br=0;
		bool prviPut=true;

	    do{
    	    cout<<"\n--------------------------------------------------------------------------------\n";
	        cout << "\n\tVas izbor: ";
        	cin >> izbor;

    	    if(cin.fail()){

        	    cin.clear();
    	        cin.ignore(1000,'\n');
	            system("clear");

            	cout<<"\n--------------------------------------------------------------------------------\n\n";
        	    cout << "\tUnijeli ste znak umjesto broja. Molimo pokusajte ponovo\n";
    	        cout<<"\n--------------------------------------------------------------------------------\n\n";

	            prikaziMeniA();
            	continue;
        	}
        	if(izbor<1 || izbor>5){
        		//promijeniBoju(4);
           		cout<<"\t\tPonovite unos"<<endl;
        	    //promijeniBoju(7);
			}
		}while(izbor<1 || izbor>5);

    	    switch(izbor){
	            case 1:
                	system("clear");

            	    cout<<brk;
        	        cout << boldiraj << "\n\t\t\t      Unos automobila\n" << ukloniBold;
    	            cout<<brk;

	                nizAuta[br++]=a.unosAuta();
                	cout << endl;

            	    prviPut=false;

    	            break;

        	    case 2:
    	            system("clear");

	                cout << brk;
                	cout << boldiraj << "\n\t\t\t   Pregled svih automobila\n" << ukloniBold;
            	    cout << brk;

//        	        if(prviPut){
//    	                cout << "\n\tNema automobila za prikazati. Molimo prvo unesite neki automobil\n";
//	                    cout << "\t------------------------------------------------------------------\n" ;
//                    	cout << brk;
//                	}else
                    a.pregledAuta(nizAuta, br);
        	        cout << endl;

	                break;

            	case 3:
        	        system("clear");

    	            cout << brk;
	                cout << boldiraj << "\n\t\t\t     Pretraga automobila\n" << ukloniBold;
                	cout << brk;

//            	    if(prviPut){
//        	            cout << "\n\tNema automobila za pretrazivati. Molimo prvo unesite neki automobil\n";
//    	                cout << "\t-------------------------------------------------------------------";
//	                }
//                	else
                    pretraziAuta(nizAuta, br);
            	    cout << endl;

    	            break;

	            case 4:
            	    system("clear");

        	        cout << brk;
    	            cout << boldiraj << "\n\t\t\t      Ispis uplatnice\n" << ukloniBold;
	                cout << brk;

//                	if(prviPut){
//            	        cout << "\n\tNema automobila za kupiti. Nemoguce izdati uplatnicu\n";
//        	            cout << brk;
//    	            }
//	                else
                    ispisUplatnice(nizAuta, br);
                	cout << endl;

        	        break;

    	        case 5:
	                system("clear");
	                cout << brk;
					//promijeniBoju(2);
            	    cout << boldiraj << "\n\t\tHvala Vam na posjeti! Prijatno i dovidjenja!\n" << ukloniBold ;
            	    //promijeniBoju(7);
            	    cout<<brk;
        	        break;
    	    }

	        if(izbor==5) system("exit");
	        else{
	        	cin.ignore();
	            int get;

            	cout << "\n\t-----------------------------------------";
        	    cout << "\n\t\tIzlaz (0)\n\t\tDalje(1) ";
        	    do{
					cout<<"\n\tVas odabir: ";
					cin>>get;
					if(get<0 || get>1){
            			//promijeniBoju(4);
            			cout<<"\t\tPonovite unos"<<endl;
        	    		//promijeniBoju(7);
					}
				}while(get<0 || get>1);
    	        cout<<"\n";
    	        cout<<"\n";

	            if(get==1){
            	    system("clear");
        	        prikaziMeniK();
    	        }else{
    	        	system("clear");
	                cout << brk;
					//promijeniBoju(2);
            	    cout << boldiraj << "\n\t\tHvala Vam na posjeti! Prijatno i dovidjenja!\n" << ukloniBold ;
            	    //promijeniBoju(7);
            	    cout<<brk;
        	        system("exit");
				}
			}



	    delete[] nizAuta;

	}else{
		Kupac k;
		k.prijavaKupca();
		prikaziMeniK();

//		Auto *nizAuta=new Auto[50];
//		int br=0;
//		bool prviPut=true;

	    do{
    	    cout<<"\n--------------------------------------------------------------------------------\n";
	        cout << "\n\tVas izbor: ";
        	cin >> izbor;

    	    if(cin.fail()){

        	    cin.clear();
    	        cin.ignore(1000,'\n');
	            system("clear");

            	cout<<"\n--------------------------------------------------------------------------------\n\n";
        	    cout << "\tUnijeli ste znak umjesto broja. Molimo pokusajte ponovo\n";
    	        cout<<"\n--------------------------------------------------------------------------------\n\n";

	            prikaziMeniK();
            	continue;
        	}
        	if(izbor<1 || izbor>4){
        		//promijeniBoju(4);
            	cout<<"\t\tPonovite unos"<<endl;
        		//promijeniBoju(7);
			}
		}while(izbor<1 || izbor>4);

    	    switch(izbor){
        	    case 1:
    	            system("clear");

	                cout << brk;
                	cout << boldiraj << "\n\t\t\t   Pregled svih automobila\n" << ukloniBold;
            	    cout << brk;

//        	        if(prviPut){
//    	                cout << "\n\tNema automobila za prikazati. Molimo prvo unesite neki automobil\n";
//	                    cout << "\t------------------------------------------------------------------\n" ;
//                    	cout << brk;
//                	}
//            	    else
                    a.pregledAuta(nizAuta, br);
        	        cout << endl;

	                break;

            	case 2:
        	        system("clear");

    	            cout << brk;
	                cout << boldiraj << "\n\t\t\t     Pretraga automobila\n" << ukloniBold;
                	cout << brk;

//            	    if(prviPut){
//        	            cout << "\n\tNema automobila za pretrazivati. Molimo prvo unesite neki automobil\n";
//    	                cout << "\t-------------------------------------------------------------------";
//	                }
//                	else
                    pretraziAuta(nizAuta, br);
            	    cout << endl;

    	            break;

    	        case 3:
    	        	system("clear");
    	        	cout << brk;
	                cout << boldiraj << "\n\t\t\t     Kupovina automobila\n" << ukloniBold;
                	cout << brk;
                	ispisUplatnice(nizAuta, br);
    	        	break;

    	        case 4:
	                system("clear");
	                cout << brk;
					//promijeniBoju(2);
            	    cout << boldiraj << "\n\t\tHvala Vam na posjeti! Prijatno i dovidjenja!\n" << ukloniBold ;
            	    //promijeniBoju(7);
            	    cout<<brk;
        	        break;
    	    }

	        if(izbor==4) system("exit");

	        else{
	        	cin.ignore();
	            int get;

            	cout << "\n\t-----------------------------------------";
        	    cout << "\n\t\tIzlaz (0)\n\t\tDalje(1) ";
        	    do{
					cout<<"\n\tVas odabir: ";
					cin>>get;
					if(get<0 || get>1){
            			//promijeniBoju(4);
            			cout<<"\t\tPonovite unos"<<endl;
        	    		//promijeniBoju(7);
					}
				}while(get<0 || get>1);
    	        cout<<"\n";
    	        cout<<"\n";

	            if(get==1){
            	    system("clear");
        	        prikaziMeniK();

    	        }else{
    	        	system("clear");
					cout << brk ;
					//promijeniBoju(2);
            	    cout << boldiraj << "\n\t\tHvala Vam na posjeti! Prijatno i dovidjenja!\n" << ukloniBold;
            	    //promijeniBoju(7);
            	    cout << brk;
        	        system("exit");
				}
			}



	    delete[] nizAuta;
	}


cout<<"\n--------------------------------------------------------------------------------\n";
return 0;
}
