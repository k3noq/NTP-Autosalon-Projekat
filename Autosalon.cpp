#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>

using namespace std;

string brk = "\n********************************************************************************\n";

void welcome(){
    cout << "================================================================================\n";
    cout << "|\t"<<setw(34)<<"WELCOME"<<setw(39)<<"|\n";
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

enum nacinPlacanja {cash=1, rate, lizing};

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

        cin.ignore();

        cout << "\n\tIme proizvodjaca: ";
            getline(cin, a.proizvodjacAuta);
        cout << "\n\tIme modela: ";
            getline(cin, a.modelAuta);
        cout << "\n\tZemlja porijekla: ";
            getline(cin, a.zemljaPorijekla);
        cout << "\n\tBoja auta: ";
            getline(cin, a.boja);

        cout << "\n\tBroj vrata: ";
            cin >> a.brVrata;
        cout << "\n\tBroj stepeni prenosa: ";
            cin >> a.brStepeniPrenosa;
        cout << "\n\tKilometraza: ";
            cin >> a.kilometraza;
        cout << "\n\tGodiste: ";
            cin >> a.godiste;
        cout << "\n\tCijena: ";
            cin >> a.cijena;
        cout << "\n\tPotrosnja na 100km: ";
            cin >> a.potrosnja;

        cout << "\n\n\tZa sljedece unose koritite 1-DA, 0-NE\n";
        cout << "\n\tRegistrovan? ";
            cin >> a.jeRegistrovan;
        cout << "\n\tServisiran? ";
            cin >> a.jeServisiran;
        cout << "\n\tKlima? ";
            cin >> a.imaKlimu;

        int x;
        cout << "\n\tSljedece karakteristike odaberite ponuđenim brojevima:\n";
        cout << "\n\tStanje (1-nov, 2-polovan): ";
            cin >> x;
            a.stanje = (Stanje)x;
        cout << "\n\tGorivo (1-dizel, 2-benzin, 3-plin): ";
            cin >> x;
            a.gorivo = (Gorivo)x;
        cout << "\n\tPogon (1-prednji, 2-zadnji, 3-4x4): ";
            cin >> x;
            a.pogon = (Pogon)x;
        cout << "\n\tTransmisija (1-manual, 2-automatik): ";
            cin >> x;
            a.transmisija = (Transmisija)x;

        cout << "\n\n\tKarakteristike motora:\n";
        cout << "\n\tKonjske snage: ";
            cin >> a.motor.konjskeSnage;
        cout << "\n\tKilovati: ";
            cin >> a.motor.kW;
        cout << "\n\tKubikaza: ";
            cin >> a.motor.kubikaza;
        cout<<"\n--------------------------------------------------------------------------------\n";

    return a;
    }

    void pregledAuta(Auto nizAuta[], int br){

        for(int i=0; i<br; i++){

            cout << "\n\t--------------------------------------\n";
            cout << "\t\t" <<setw(12)<< nizAuta[i].proizvodjacAuta << " " << nizAuta[i].modelAuta;
            cout << "\n\t--------------------------------------\n";

            cout << "\n\tIme proizvodjaca: " << nizAuta[i].proizvodjacAuta;

            cout << "\n\tIme modela: " << nizAuta[i].modelAuta;

            cout << "\n\tZemlja porijekla: " << nizAuta[i].zemljaPorijekla;

            cout << "\n\tBoja auta: " << nizAuta[i].boja;

            cout << "\n\tBroj vrata: " << nizAuta[i].brVrata-1 << "/" <<nizAuta[i].brVrata;

            cout << "\n\tBroj stepeni prenosa: " << nizAuta[i].brStepeniPrenosa << "+R";

            cout << "\n\tKilometraza: " << nizAuta[i].kilometraza;

            cout << "\n\tGodiste: " << nizAuta[i].godiste << ".";

            cout << "\n\tCijena: " << nizAuta[i].cijena << " KM";

            cout << "\n\tPotrosnja na 100km: " << nizAuta[i].potrosnja << "l";

            cout << "\n\t\tRegistrovan? "; nizAuta[i].jeRegistrovan ? cout << "DA" : cout << "NE";

            cout << "\n\t\tServisiran? "; (nizAuta[i].jeServisiran) ? cout << "DA" : cout << "NE";

            cout << "\n\t\tKlima? "; nizAuta[i].imaKlimu ? cout << "DA" : cout << "NE";

            cout << "\n\n\tKarakteristike motora:\n";
            cout << "\n\tKonjske snage: " << nizAuta[i].motor.konjskeSnage;

            cout << "\n\tKilovati: " << nizAuta[i].motor.kW << "kW";

            cout << "\n\tKubikaza: " << nizAuta[i].motor.kubikaza << "cc";

            nizAuta[i].motor.jacinaMotora=nizAuta[i].motor.kubikaza/1000.0F;

            cout << "\n\tJacina: " << fixed << setprecision(1) << nizAuta[i].motor.jacinaMotora;

            cout << "\n\t\tStanje: ";
                switch(nizAuta[i].stanje){
                    case 1: cout << "Nov";
                        break;
                    case 2: cout << "Polovan";
                        break;
                 }

            cout << "\n\t\tGorivo: ";
                switch(nizAuta[i].gorivo){
                    case 1: cout << "Dizel";
                        break;
                    case 2: cout << "Benzin";
                        break;
                    case 3: cout << "Plin";
                        break;
                 }

            cout << "\n\t\tPogon: ";
                switch(nizAuta[i].pogon){
                    case 1: cout << "Prednji";
                        break;
                    case 2: cout << "Zadnji";
                        break;
                    case 3: cout << "4x4";
                        break;
                }

            cout << "\n\t\tTransmisija: ";
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




//    string fajl = "uplatnica.txt";
//
//    ofstream uplatnica("uplatnica.txt");
//
//    uplatnica << "------------------------------------------------------------\n";
//    uplatnica << "\t\t\tAutosalon 'ABS' d.o.o.:\n";
//    uplatnica << "------------------------------------------------------------\n";
//    uplatnica << "ID: " << sifra << "\tPotrosac: " << tekst << "\tIznos "<< suma << " KM." << endl;
//    uplatnica << "\n\t\t\tPotpis: _________________________\n";
//    uplatnica << "------------------------------------------------------------\n";
//    uplatnica.close();
//    cout << "Uplatnica uspjesno snimnjena u " << fajl << endl;
//
//

}

void prikaziMeni(){

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

int main(){
welcome();
cout<<"\n--------------------------------------------------------------------------------\n";

Auto a;
int izbor;

prikaziMeni();

Auto *nizAuta=new Auto[50];
int br=0;
bool prviPut=true;

    do{
        cout<<"\n--------------------------------------------------------------------------------\n";
        cout << "\n\tVas izbor: ";
        cin >> izbor;

        if(cin.fail()){

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            system("clear");

            cout<<"\n--------------------------------------------------------------------------------\n\n";
            cout << "\tUnijeli ste znak umjesto broja. Molimo pokusajte ponovo\n";
            cout<<"\n--------------------------------------------------------------------------------\n\n";

            prikaziMeni();
            continue;
        }


        switch(izbor){
            case 1:
                system("clear");

                cout<<brk;
                cout << boldiraj << "\n\t\t\t      Unos automobila\n" << ukloniBold;
                cout<<brk;

                nizAuta[br++]=a.unosAuta();
                cout << endl;

                prviPut=false;
                //system("pause");
                break;

            case 2:
                system("clear");

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
                system("clear");

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
                system("clear");

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
                system("clear");

                cout << brk << boldiraj << "\n\t\tHvala Vam na posjeti! Prijatno i dovidjenja!\n" << ukloniBold <<brk;
                //system("pause");
                exit(0);

            default:
                cout << "\n\tOdabrali ste nepostojecu opciju. Molimo pokusajte ponovo.\n";
        }

            cin.ignore(); char get;

            cout << "\n\t-----------------------------------------";
            cout << "\n\tDa li zelite ponovni prikaz menija (y/n)? "; cin>>get;
            cout<<"\n";

            if(get=='y' || get=='Y'){
                system("clear");
                prikaziMeni();
            }

    }while(izbor != 5);

delete[] nizAuta;

cout<<"\n--------------------------------------------------------------------------------\n";
return 0;
}
