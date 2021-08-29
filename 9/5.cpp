/*
Да се креира класа Transakcija во која што ќе се чуваат информации за:

датумот на реализирање на банкарската трансакција:
ден (int)
месец (int)
година (int)
паричниот износ кој се однесува на трансакцијата (позитивен или негативен, тип double)
моменталната вредност на еврото во денари (static double EUR), иницијално поставен на 61
моменталната вредност на доларот во денари (static double USD), иницијално поставен на 50
За класата да се имплемтнираат соодветните конструктори, како и да се дефинираат следните четири чисто виртуелни методи:

double voDenari()
void pecati()
Трансакциите можат да бидат денарски и девизни (DenarskaTransakcija и DeviznaTransakcija). За девизните трансакции се чува дополнителна информација за валутата на трансакцијата (низа од три знаци). Дозволени валути за девизните транскации се USD и EUR.

За двете изведени класи да се напишат соодветните конструктори, деструктори и да се препокријат потребните методи.

Да се дефинира класа Smetka во која што ќе се чуваат информации за:

извршените трансакции (динамички алоцирана низа од покажувачи кон класата Transakcija)
број на извршените трансакции (int)
број на сметката (низа од 15 знаци)
почетно салдо во денари (double)
За класата Smetka да се имплементираат:

потребен конструктор (со два аргументи, видете во main), деструктор
оператор за додавање на нова трансакција во низата од трансакции +=
void izvestajVoDenari() - функција што печати информации за сметката во форматот:

Korisnikot so smetka: [број на сметката] ima momentalno saldo od [салдо на сметката пресметано во денари] MKD

void pecatiTransakcii() - функција што ги печати сите внесени трансакции
Да се креираат класи за следните исклучоци:

InvalidDateException којшто се фрла доколку при креирање на трансакција не се испочитувани правилата 1<=ден<=31 и 1<=месец<=12
NotSupportedCurrencyException којшто се фрла доколку при креирање на девизна трансакција се внесува вредност за валута што не е дозволена
Овие исклучоци да се фрлат и да се фатат таму каде што е потребно. Истите при фаќање треба да печатат пораки од следниот формат:

Invalid Date 32/12/2018
GBP is not a supported currency
*/
#include<iostream>
#include<cstring>

using namespace std;

class InvalidDateException
{
private:
    int den;
    int mesec;
    int godina;
public:
    InvalidDateException(int den, int mesec, int godina)
    {
        this->den = den;
        this->mesec = mesec;
        this->godina = godina;
    }

    void message()
    {
        cout << "Invalid Date " << den << "/" << mesec << "/" << godina << endl;
    }
};

class NotSupportedCurrencyException
{
private:
    char valuta[4];
public:
    NotSupportedCurrencyException(char *valuta)
    {
        strcpy(this->valuta, valuta);
    }

    void message()
    {
        cout << valuta << " is not a supported currency" << endl;
    }
};

class Transakcija
{
protected:
    int den;
    int mesec;
    int godina;
    double iznos;
    static double EUR;
    static double USD;
public:
    Transakcija(int den = 1, int mesec = 1, int godina = 1, double iznos = 0)
    {
        if (den < 1 || den > 31 || mesec < 1 || mesec > 12)
            throw InvalidDateException(den, mesec, godina);

        this->den = den;
        this->mesec = mesec;
        this->godina = godina;
        this->iznos = iznos;
    }

    virtual double voDenari() = 0;

    virtual void pecati() = 0;

    static void setEUR(double n)
    {
        Transakcija::EUR = n;
    }

    static void setUSD(double n)
    {
        Transakcija::USD = n;
    }
};

double Transakcija::EUR = 61;
double Transakcija::USD = 50;

class DenarskaTransakcija : public Transakcija
{
public:
    DenarskaTransakcija(int den = 0, int mesec = 0, int godina = 0, double iznos = 0) : Transakcija(den, mesec, godina,
                                                                                                    iznos)
    {}

    double voDenari()
    {
        return iznos;
    }

    void pecati()
    {
        cout << den << "/" << mesec << "/" << godina << " " << iznos << " MKD" << endl;
    }
};

class DeviznaTransakcija : public Transakcija
{
private:
    char valuta[4];
public:
    DeviznaTransakcija(int den = 0, int mesec = 0, int godina = 0, double iznos = 0, char *valuta = "") : Transakcija(
            den, mesec, godina, iznos)
    {
        if (strcmp(valuta, "EUR") != 0 && strcmp(valuta, "USD") != 0)
            throw NotSupportedCurrencyException(valuta);

        strcpy(this->valuta, valuta);
    }

    double voDenari()
    {
        if (!strcmp(valuta, "EUR"))
            return iznos * EUR;
        else
            return iznos * USD;
    }

    void pecati()
    {
        cout << den << "/" << mesec << "/" << godina << " " << iznos << " " << valuta << endl;
    }
};

class Smetka
{
private:
    Transakcija **t;
    int n;
    char *smetka;
    double saldo;
public:
    Smetka(char *smetka = "", double saldo = 0)
    {
        t = new Transakcija *[0];
        n = 0;
        this->smetka = new char[50];
        strcpy(this->smetka, smetka);
        this->saldo = saldo;
    }

    ~Smetka()
    {
        delete[] t;
        delete[] smetka;
    }

    Smetka &operator+=(Transakcija *tr)
    {
        Transakcija **temp = new Transakcija *[n + 1];

        for (int i = 0; i < n; i++)
            temp[i] = t[i];
        temp[n] = tr;

        delete[] t;
        t = temp;
        n++;

        return *this;
    }

    void izvestajVoDenari()
    {
        double s = saldo;

        for (int i = 0; i < n; i++)
            s += t[i]->voDenari();

        cout << "Korisnikot so smetka: " << smetka << " ima momentalno saldo od " << s << " MKD" << endl;
    }

    void pecatiTransakcii()
    {
        for (int i = 0; i < n; i++)
            t[i]->pecati();
    }
};

int main()
{

    Smetka s("300047024112789", 1500);

    int n, den, mesec, godina, tip;
    double iznos;
    char valuta[4];

    cin >> n;
    cout << "===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI===" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> tip >> den >> mesec >> godina >> iznos;
        if (tip == 2)
        {
            try
            {
                cin >> valuta;
                Transakcija *t = new DeviznaTransakcija(den, mesec, godina, iznos, valuta);
                s += t;
            }
            catch (NotSupportedCurrencyException &e)
            {
                e.message();
            }
            catch (InvalidDateException &e)
            {
                e.message();
            }
            //delete t;
        }
        else
        {
            try
            {
                Transakcija *t = new DenarskaTransakcija(den, mesec, godina, iznos);
                s += t;
            }
            catch (NotSupportedCurrencyException &e)
            {
                e.message();
            }
            catch (InvalidDateException &e)
            {
                e.message();
            }
            //delete t;
        }

    }
    cout << "===PECHATENJE NA SITE TRANSAKCII===" << endl;
    s.pecatiTransakcii();
    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI===" << endl;
    s.izvestajVoDenari();


    cout << "\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n" << endl;


    double newEUR, newUSD;
    cin >> newEUR >> newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI===" << endl;
    s.izvestajVoDenari();


    return 0;
}