/*
Да се дефинира класата Pesna во која се чуваат информации за (5 поени):

име на песна (динамички алоцирано поле од знаци)
времетраење на песната во минути
тип на песна кој може да биде: поп, рап или рок (енумерација tip)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (10 поени)

Дополнително за оваа класа да се дефинира методот:

pecati() - функција во која ќе се печатат одделени со цртичка(-): името на песната во наводници и времетраењето на песната со постфикс min. (5 поени)
Да се креира класата CD во која се чуваат информации за (5 поени):

низа од песни снимени на CD-то (Поле од најмногу 10 објекти од класата Pesna )
број на песни снимени на CD-то
максимално времетраење на песните на CD-то (во минути)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (5 поени)

Дополнително за оваа класа да се дефинираат методите:

dodadiPesna (Pesna p) - со кој се додава песната p на CDто, но само ако има доволно преостанато место (земајќи го предвид максималното времетраење на песните на CDто и времетраењата на песните на CD-то) и ако има помалку од 10 песни на CD-то. (10 поени)
pecatiPesniPoTip(tip t) – со кој се печатат информациите за сите песни од тип t (поп, рап или рок). (10 поени)
Комплетна функционалност (5 поени).
*/
#include <iostream>
#include <cstring>

using namespace std;

enum tip
{
    pop,
    rap,
    rock
};

class Pesna
{
private:
    char *ime;
    int minuti;
    tip kojtip;
public:
    Pesna() = default;

    Pesna(char *ime1, int minuti1, tip kojtip1)
    {
        ime = new char[50];
        strcpy(ime, ime1);
        minuti = minuti1;
        kojtip = kojtip1;
    }

    //Pesna(Pesna &p1) : Pesna(p1.ime, p1.minuti, p1.kojtip){}

    //~Pesna()
    //{
    //    delete[] this->ime;
    //}

    void pecati()
    {
        cout << "&quot;" << ime << "&quot;-" << minuti << "min";
    }

    tip getTip()
    {
        return kojtip;
    }

    int getMinuti()
    {
        return minuti;
    }
};

class CD
{
private:
    Pesna p[10];
    int pesni;
    int minuti;
public:
    CD() = default;

    CD(int minuti1)
    {
        minuti = minuti1;
        pesni = 0;
    }

    void dodadiPesna(Pesna p1)
    {
        int current = 0;

        for (int i = 0; i < pesni; i++)
            current += p[i].getMinuti();

        if (pesni < 10 && current + p1.getMinuti() <= minuti)
        {
            p[pesni] = p1;
            pesni++;
        }
    }

    void pecatiPesniPoTip(tip t)
    {
        for (int i = 0; i < pesni; i++)
            if (p[i].getTip() == t)
                p[i].pecati();
    }

    Pesna getPesna(int i)
    {
        return p[i];
    }

    int getBroj()
    {
        return pesni;
    }
};

int main()
{
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if (testCase == 1)
    {
        cout << "===== Testiranje na klasata Pesna ======";
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime, minuti, (tip) kojtip);
        p.pecati();
    }
    else if (testCase == 2)
    {
        cout << "===== Testiranje na klasata CD ======";
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if (testCase == 3)
    {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======";
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if (testCase == 4)
    {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======";
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);

    }
    else if (testCase == 5)
    {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======";
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);

    }

    return 0;
}