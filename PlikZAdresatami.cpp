#include "PlikZAdresatami.h"

bool PlikZAdresatami::czyPlikJestPusty()
{
    fstream plikZAdresatami;
    plikZAdresatami.seekg(0, ios::end);
    if (plikZAdresatami.tellg() == 0)
        return false;
    else
        return true;
}
void PlikZAdresatami::dopiszAdresataDoPliku(Adresat adresat)
{
    string liniaZDanymiAdresata = "";
    fstream plikZAdresatami;
    plikZAdresatami.open(nazwaPlikuZAdresatami, ios::app);

    if (plikZAdresatami.is_open() == true)
    {
        liniaZDanymiAdresata = zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);

        if (czyPlikJestPusty() == true)
        {
            plikZAdresatami << liniaZDanymiAdresata << endl;
        }
        else
        {
            plikZAdresatami << endl << liniaZDanymiAdresata ;
        }
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
    }
    plikZAdresatami.close();
}
int PlikZAdresatami::pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    int pozycjaRozpoczeciaIdUzytkownika = daneJednegoAdresataOddzielonePionowymiKreskami.find_first_of('|') + 1;
    int idUzytkownika = MetodyPomocnicze::konwersjaStringNaInt(MetodyPomocnicze::pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdUzytkownika));
    return idUzytkownika;
}
vector<Adresat> PlikZAdresatami::wczytajAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika)
{
    Adresat adresat;
    vector <Adresat> adresaci;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    string daneOstaniegoAdresataWPliku = "";
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuZAdresatami, ios::in);

    if (plikTekstowy.is_open() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            if(idZalogowanegoUzytkownika == pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
                adresaci.push_back(adresat);
            }
        }
        daneOstaniegoAdresataWPliku = daneJednegoAdresataOddzielonePionowymiKreskami;
        plikTekstowy.close();
    }
    else
        cout << "Nie udalo sie otworzyc pliku i wczytac danych." << endl;

    return adresaci;
}
Adresat PlikZAdresatami::pobierzDaneAdresata(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    Adresat adresat;
    int pozycja;

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawId(stoi(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja)));
    daneJednegoAdresataOddzielonePionowymiKreskami = daneJednegoAdresataOddzielonePionowymiKreskami.substr(pozycja + 1, daneJednegoAdresataOddzielonePionowymiKreskami.length());

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawIdUzytkownika(stoi(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja)));
    daneJednegoAdresataOddzielonePionowymiKreskami = daneJednegoAdresataOddzielonePionowymiKreskami.substr(pozycja + 1, daneJednegoAdresataOddzielonePionowymiKreskami.length());

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawImie(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja));
    daneJednegoAdresataOddzielonePionowymiKreskami = daneJednegoAdresataOddzielonePionowymiKreskami.substr(pozycja + 1, daneJednegoAdresataOddzielonePionowymiKreskami.length());

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawNazwisko(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja));
    daneJednegoAdresataOddzielonePionowymiKreskami = daneJednegoAdresataOddzielonePionowymiKreskami.substr(pozycja + 1, daneJednegoAdresataOddzielonePionowymiKreskami.length());

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawNumerTelefonu(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja));
    daneJednegoAdresataOddzielonePionowymiKreskami = daneJednegoAdresataOddzielonePionowymiKreskami.substr(pozycja + 1, daneJednegoAdresataOddzielonePionowymiKreskami.length());

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawEmail(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja));

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawAdres(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja));

    return adresat;
}
string PlikZAdresatami::zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat)
{
    string liniaZDanymiAdresata = "";

    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzId()) + '|';
    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzIdUzytkownika()) + '|';
    liniaZDanymiAdresata += adresat.pobierzImie() + '|';
    liniaZDanymiAdresata += adresat.pobierzNazwisko() + '|';
    liniaZDanymiAdresata += adresat.pobierzNumerTelefonu() + '|';
    liniaZDanymiAdresata += adresat.pobierzEmail() + '|';
    liniaZDanymiAdresata += adresat.pobierzAdres() + '|';

    return liniaZDanymiAdresata;
}

