#include<iostream>			//otvorene potrebne biblioteke kako bi bila omogucena maksimalna funkcionalnost programa
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include <windows.h>
#include<ctime>

/*
	username: admin
	password: admin
*/

using namespace std;

void changeColor(int desiredColor){
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}

string brk = "\n********************************************************************************\n";	//bit ce koristena u nastavku za izbjegavanje ponavljanja

void welcome(){				//pocetna funkcija
    cout << "================================================================================\n";
    changeColor(2);
    cout << "|\t"<<setw(34)<<"WELCOME"<<setw(39)<<"|\n";
    changeColor(7);
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
            	changeColor(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	changeColor(7);
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
    	
    	lista<<"**************************************************\n";
    	lista.close();
	}
	
	void prijavaKupca(){
		system("cls");
		cout << "================================================================================\n";
  		cout << "| \t\tPrije nego sto nastavite istrazivati nasu ponudu\t\t|"<<"\n";
    	cout << "|\t\t    |Molimo Vas da unesete sljedece podatke|"<<setw(22)<<"|\n";
    	cout << "================================================================================\n";
		ofstream lista("kupci.txt", ios::app);
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
            auta<<a.boja<<" ";

        do{
        	cout << "\n\tBroj vrata(zajedno sa gepekom): ";
            	cin >> a.brVrata;
            if(a.brVrata!=3 && a.brVrata!=5){
            	changeColor(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	changeColor(7);
			}
		}while(a.brVrata!=3 && a.brVrata!=5);
		auta<<a.brVrata<<" ";
		
       	cout << "\tBroj stepeni prenosa: ";
            cin >> a.brStepeniPrenosa;
        cout << "\tKilometraza: ";
            cin >> a.kilometraza;
        do{
        	cout << "\tGodiste: ";
            	cin >> a.godiste;
            if(a.godiste<1886 || a.godiste>2020){
            	changeColor(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	changeColor(7);
			}
		}while(a.godiste<1886 || a.godiste>2020);
        do{
        	cout << "\tCijena: ";
     	       cin >> a.cijena;
     	    if(a.cijena<0){
            	changeColor(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	changeColor(7);
			}
		}while(a.cijena<0);
        cout << "\tPotrosnja na 100km: ";
            cin >> a.potrosnja;
		
        cout << "\n\n\tZa sljedece unose koritite 1-DA, 0-NE\n";
        do{
        	cout << "\t\tRegistrovan: ";
            	cin >> a.jeRegistrovan;
            if(a.jeRegistrovan<0 || a.jeRegistrovan>1){
            	changeColor(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	changeColor(7);
			}
		}while(a.jeRegistrovan<0 || a.jeRegistrovan>1);
		cin.clear();
        do{
        	cout << "\t\tServisiran: ";
            	cin >> a.jeServisiran;
            if(a.jeServisiran<0 || a.jeServisiran>1){
            	changeColor(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	changeColor(7);
			}
		}while(a.jeServisiran<0 || a.jeServisiran>1);
		cin.clear();
        do{
        	cout << "\t\tKlima: ";
	            cin >> a.imaKlimu;
	        if(a.imaKlimu<0 || a.imaKlimu>1){
            	changeColor(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	changeColor(7);
			}
		}while(a.imaKlimu<0 || a.imaKlimu>1);
		
        int x;
        cout << "\n\tSljedece karakteristike odaberite ponuđenim brojevima:\n";
        do{
        	cout << "\t\tStanje (1-nov, 2-polovan): ";
            	cin >> x;
            if(x<1 || x>2){
            	changeColor(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	changeColor(7);
			}
		}while(x<1 || x>2);
            a.stanje = (Stanje)x;
        do{
        	cout << "\t\tGorivo (1-dizel, 2-benzin, 3-plin): ";
            	cin >> x;
            if(x<1 || x>3){
            	changeColor(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	changeColor(7);
			}
		}while(x<1 || x>3);
            a.gorivo = (Gorivo)x;
        do{
        	cout << "\t\tPogon (1-prednji, 2-zadnji, 3-4x4): ";
            	cin >> x;
            if(x<1 || x>3){
            	changeColor(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	changeColor(7);
			}
		}while(x<1 || x>3);
            a.pogon = (Pogon)x;
        do{
        	cout << "\t\tTransmisija (1-manual, 2-automatik): ";
            	cin >> x;
            if(x<1 || x>2){
            	changeColor(4);
            	cout<<"\t\tPonovite unos"<<endl;
            	changeColor(7);
			}
		}while(x<1 || x>2);
            a.transmisija = (Transmisija)x;

        cout << "\n\n\tKarakteristike motora:\n";
        cout << "\t\tKonjske snage: ";
            cin >> a.motor.konjskeSnage;
        cout << "\t\tKilovati: ";
            cin >> a.motor.kW;
        cout << "\t\tKubikaza: ";
            cin >> a.motor.kubikaza;
        cout<<"\n--------------------------------------------------------------------------------\n";

    return a;
    }

    void pregledAuta(Auto nizAuta[], int br){

        for(int i=0; i<br; i++){

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
            a.pregledAuta(nizAuta,brAuta);
            break;

        case 2:
            sort(nizAuta, nizAuta+brAuta, porediCijeneManja);
            a.pregledAuta(nizAuta,brAuta);
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
            if(br > 0)
                a.pregledAuta(auta, br);
            else cout << "\n\t\tNema takvih automobila.";

            delete[] auta;
            break;
        }

        default:
            cout << "\n\tOdabrali ste nepostojecu opciju.";
    }
}

void kratkiIspis(Auto *a, int i){
    cout << "\t\t" << i+1 << ". " << a->proizvodjacAuta << " " << a->modelAuta << " " << a->motor.jacinaMotora << " " << a->motor.kW << " kW\n";
}

void ispisUplatnice(Auto nizAuta[], int br){

    cout << "\n\tZelite li izvrisiti pretragu auta prije kupovine (y/n)? ";
    cin.ignore();
    char get = cin.get();

    if(get == 'y' || get == 'Y'){
        pretraziAuta(nizAuta, br);
    }

    cout << "\n\tIspod je lista auta. Izaberite redni broj auta koje zelite kupiti\n";
    for(int i=0; i<br; i++){
        kratkiIspis(&nizAuta[i], i);
    }


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
    cout << "\t\t|\t4. Kraj"<<setw(32)<<"|\n";;
    cout << "\t\t==============================================\n";

}

int main(){
	welcome();
	cout<<"\n--------------------------------------------------------------------------------\n";

	Auto a;
	int izbor;
	
	cout<<"\tIzaberite na koji se sistem zelite prijaviti: \n\t\tKUPAC (1) \n\t\tRADNIK (2) \n\n";
	
	do{
		cout<<"\tVas izbor: ";
		cin>>izbor;
		if(izbor<1 || izbor>2){
           	changeColor(4);
           	cout<<"\t\tPonovite unos"<<endl;
           	changeColor(7);
		}
	}while(izbor<1 || izbor>2);
	
	if(izbor==2){
		
		string username; //zadano je da bude admin
		string password; //zadano je da bude admin
		
		system("cls");
		int brPokusaja=0;
		do{
			cin.ignore();
			cout<<"\n\n\n\t\t\tusername: ";
			getline(cin, username);
			cout<<"\n\t\t\tpassword: ";
			cin>>password;
			brPokusaja++;
			if(username!="admin" && password!="admin" && brPokusaja<3){
				system("cls");
				changeColor(4);
           		cout<<"\t\tNeisparvan unos";
           		changeColor(7);
           		cout<<"\t\t\t\tBroj pokusaja: "<<3-brPokusaja<<endl;
			}else if(password!="admin" && brPokusaja<3){
				system("cls");
				changeColor(4);
           		cout<<"\t\tNeispravan password";
           		changeColor(7);
           		cout<<"\t\t\t\tBroj pokusaja: "<<3-brPokusaja<<endl;
			}else if(username!="admin" && brPokusaja<3){
				changeColor(4);
           		cout<<"\t\tNeispravan username";
           		changeColor(7);
           		cout<<"\t\t\t\tBroj pokusaja: "<<3-brPokusaja<<endl;
			}
			if(brPokusaja==3){
				system("cls");
				main();
			}
		}while(username!="admin" || password!="admin");
		
		prikaziMeniA();

		Auto *nizAuta=new Auto[50];
		int br=0;
		bool prviPut=true;

	    do{
    	    cout<<"\n--------------------------------------------------------------------------------\n";
	        cout << "\n\tVas izbor: ";
        	cin >> izbor;

    	    if(cin.fail()){
	
        	    cin.clear();
    	        cin.ignore(1000,'\n');
	            system("cls");

            	cout<<"\n--------------------------------------------------------------------------------\n\n";
        	    cout << "\tUnijeli ste znak umjesto broja. Molimo pokusajte ponovo\n";
    	        cout<<"\n--------------------------------------------------------------------------------\n\n";

	            prikaziMeniA();
            	continue;
        	}


    	    switch(izbor){
	            case 1:
                	system("cls");

            	    cout<<brk;
        	        cout << boldiraj << "\n\t\t\t      Unos automobila\n" << ukloniBold;
    	            cout<<brk;

	                nizAuta[br++]=a.unosAuta();
                	cout << endl;

            	    prviPut=false;
        	        //system("pause");
    	            break;
	
        	    case 2:
    	            system("cls");

	                cout << brk;
                	cout << boldiraj << "\n\t\t\t   Pregled svih automobila\n" << ukloniBold;
            	    cout << brk;

        	        if(prviPut){
    	                cout << "\n\tNema automobila za prikazati. Molimo prvo unesite neki automobil\n";
	                    cout << "\t------------------------------------------------------------------\n" ;
                    	cout << brk;
                	}
            	    else a.pregledAuta(nizAuta, br);
        	        cout << endl;

    	            //system("pause");
	                break;

            	case 3:
        	        system("cls");

    	            cout << brk;
	                cout << boldiraj << "\n\t\t\t     Pretraga automobila\n" << ukloniBold;
                	cout << brk;

            	    if(prviPut){
        	            cout << "\n\tNema automobila za pretrazivati. Molimo prvo unesite neki automobil\n";
    	                cout << "\t-------------------------------------------------------------------";
	                }
                	else pretraziAuta(nizAuta, br);
            	    cout << endl;

        	        //system("pause");
    	            break;

	            case 4:
            	    system("cls");

        	        cout << brk;
    	            cout << boldiraj << "\n\t\t\t      Ispis uplatnice\n" << ukloniBold;
	                cout << brk;

                	if(prviPut){
            	        cout << "\n\tNema automobila za kupiti. Nemoguce izdati uplatnicu\n";
        	            cout << brk;
    	            }
	                else ispisUplatnice(nizAuta, br);
                	cout << endl;

            	    //system("pause");
        	        break;

    	        case 5:
	                system("cls");
	                cout << brk;
					changeColor(2);
            	    cout << boldiraj << "\n\t\tHvala Vam na posjeti! Prijatno i dovidjenja!\n" << ukloniBold ;
            	    changeColor(7);
            	    cout<<brk;
        	        break;
                
            	default:
        	        cout << "\n\tOdabrali ste nepostojecu opciju. Molimo pokusajte ponovo.\n";
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
            			changeColor(4);
            			cout<<"\t\tPonovite unos"<<endl;
        	    		changeColor(7);
					}
				}while(get<0 || get>1);
    	        cout<<"\n";
    	        cout<<"\n";

	            if(get==1){
            	    system("cls");
        	        prikaziMeniK();
    	        }else{
    	        	system("cls");
					changeColor(13);
            	    cout << brk << boldiraj << "\n\t\tHvala Vam na posjeti! Prijatno i dovidjenja!\n" << ukloniBold <<brk;
            	    changeColor(7);
        	        system("exit");
				}
			}
	
	    }while(izbor != 5);
	    
	    delete[] nizAuta;
	    
	}else{
		Kupac k;
		k.prijavaKupca();
		prikaziMeniK();
		
		Auto *nizAuta=new Auto[50];
		int br=0;
		bool prviPut=true;

	    do{
    	    cout<<"\n--------------------------------------------------------------------------------\n";
	        cout << "\n\tVas izbor: ";
        	cin >> izbor;

    	    if(cin.fail()){
	
        	    cin.clear();
    	        cin.ignore(1000,'\n');
	            system("cls");

            	cout<<"\n--------------------------------------------------------------------------------\n\n";
        	    cout << "\tUnijeli ste znak umjesto broja. Molimo pokusajte ponovo\n";
    	        cout<<"\n--------------------------------------------------------------------------------\n\n";

	            prikaziMeniK();
            	continue;
        	}


    	    switch(izbor){
        	    case 1:
    	            system("cls");

	                cout << brk;
                	cout << boldiraj << "\n\t\t\t   Pregled svih automobila\n" << ukloniBold;
            	    cout << brk;

        	        if(prviPut){
    	                cout << "\n\tNema automobila za prikazati. Molimo prvo unesite neki automobil\n";
	                    cout << "\t------------------------------------------------------------------\n" ;
                    	cout << brk;
                	}
            	    else a.pregledAuta(nizAuta, br);
        	        cout << endl;

    	            //system("pause");
	                break;

            	case 2:
        	        system("cls");

    	            cout << brk;
	                cout << boldiraj << "\n\t\t\t     Pretraga automobila\n" << ukloniBold;
                	cout << brk;

            	    if(prviPut){
        	            cout << "\n\tNema automobila za pretrazivati. Molimo prvo unesite neki automobil\n";
    	                cout << "\t-------------------------------------------------------------------";
	                }
                	else pretraziAuta(nizAuta, br);
            	    cout << endl;

        	        //system("pause");
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
					changeColor(2);
            	    cout << boldiraj << "\n\t\tHvala Vam na posjeti! Prijatno i dovidjenja!\n" << ukloniBold ;
            	    changeColor(7);
            	    cout<<brk;
        	        break;
                
            	default:
        	        cout << "\n\tOdabrali ste nepostojecu opciju. Molimo pokusajte ponovo.\n";
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
            			changeColor(4);
            			cout<<"\t\tPonovite unos"<<endl;
        	    		changeColor(7);
					}
				}while(get<0 || get>1);
    	        cout<<"\n";
    	        cout<<"\n";

	            if(get==1){
            	    system("cls");
        	        prikaziMeniK();
    	        }else{
    	        	system("cls");
					changeColor(3);
            	    cout << brk << boldiraj << "\n\t\tHvala Vam na posjeti! Prijatno i dovidjenja!\n" << ukloniBold <<brk;
            	    changeColor(7);
        	        system("exit");
				}
			}
	
	    }while(izbor<1 || izbor>4);
	    
	    delete[] nizAuta;
	}


cout<<"\n--------------------------------------------------------------------------------\n";
return 0;
}
