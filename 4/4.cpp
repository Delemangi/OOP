/*
Да се дефинира класата Film во која се чуваат информации за:

име на филмот (динамички алоцирано поле од знаци)
мемориската зафатнина на филмот изразена во MB
жанр на филмот кој може да биде: акција, комедија или драма (енумерација zanr)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата.

Дополнително за оваа класа да се дефинира функцијата:

pecati() - функција во која ќе се печатат одделени со цртичка(-): мемориска зафатнина на филмот со постфикс MB и името на филмот во наводници.
Да се креира класата DVD во која се чуваат информации за :

низа од филмови снимени на DVD-то (Поле од најмногу 5 објекти од класата Film )
број на филмови снимени на DVD-то
меморискиот капацитет на DVD-то (во MB)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата.

Дополнително за оваа класа да се дефинираат методите:

dodadiFilm (Film f) - со кој се додава филмот f на DVDто, но само ако има доволно преостанато место (земајќи го предвид меморискиот капацитет на DVD-то и мемориската зафатнина на снимените филмови) и притоа да има помалку од 5 филмови на DVD-то.
pecatiFilmoviDrugZanr(zanr z) – со кој се печатат информациите за сите филмови кои НЕ се од жанрот zanr (акција, комедија или драма).
(дополнително барање):float procentNaMemorijaOdZanr(zanr z)- со кој се пресметува процентот на меморијата која ја зафаќаат филмовите од жанр z на DVD-то.
*/
#include <iostream>
#include <cstring>

using namespace std;

enum zanr
{
    akcija, komedija, drama
};

class Film
{
private:
    char *name;
    int size;
    zanr type;
public:
    Film()
    {
        name = new char[50];
        size = 0;
    }

    Film(char *name, int size, zanr type)
    {
        this->name = new char[50];
        strcpy(this->name, name);
        this->size = size;
        this->type = type;
    }

    //~Film()
    //{
    //    delete[] name;
    //}

    void pecati()
    {
        cout << size << "MB-\"" << name << "\"" << endl;
    }

    zanr getType() const
    {
        return type;
    }

    int getSize() const
    {
        return size;
    }
};

class DVD
{
private:
    Film f[5];
    int n;
    int size;
public:
    DVD()
    {
        n = 0;
        size = 0;
    }

    DVD(int size)
    {
        n = 0;
        this->size = size;
    }

    void dodadiFilm(Film film)
    {
        if (film.getSize() > size || n == 5)
            return;

        f[n] = film;
        n++;
        size -= film.getSize();
    }

    Film getFilm(int i)
    {
        return f[i];
    }

    int getBroj()
    {
        return n;
    }

    void pecatiFilmoviDrugZanr(zanr zanr)
    {
        for (int i = 0; i < n; i++)
            if (f[i].getType() != zanr)
                f[i].pecati();
    }

    double procentNaMemorijaOdZanr(zanr zanr)
    {
        int total = 0;
        int z = 0;

        for (int i = 0; i < n; i++)
        {
            total += f[i].getSize();

            if (f[i].getType() == zanr)
                z += f[i].getSize();
        }

        return 100.0 * z / total;
    }
};

int main()
{
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1)
    {
        cout << "===== Testiranje na klasata Film ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
        Film f(ime, memorija, (zanr) kojzanr);
        f.pecati();
    }
    else if (testCase == 2)
    {
        cout << "===== Testiranje na klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getFilm(i)).pecati();
    }
    else if (testCase == 3)
    {
        cout << "===== Testiranje na metodot dodadiFilm() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getFilm(i)).pecati();
    }
    else if (testCase == 4)
    {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    }
    else if (testCase == 5)
    {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    }
    else if (testCase == 6)
    {
        cout << "===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata DVD =====" << endl;
        DVD omileno(40);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        cout << "Procent na filmovi od dadeniot zanr iznesuva: " << omileno.procentNaMemorijaOdZanr((zanr) kojzanr)
             << "%\n";

    }

    return 0;
}