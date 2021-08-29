/*
Да се креира класа за опишување на еден сервис за мобилни уреди. За секој мобилен телефон се чуваат податоци за модел (низа од 100 знаци), тип на уред (смартфон или компјутер), потребни часови за основна проверка (децимален број), година на производство (цел број). (5 поени)

Сите уреди имаат исто времетраење за основна проверка и истата изнесува 1 час. Оваа вредност може да се смени со одлука на сервисот. Дополнително, уредите кои се понови од 2015 година имаат потреба од дополнителени 1.5 часа за проверка. При проверка, лаптопите имаат потреба од дополнителни 2 часа за софтверска дијагностика (5 поени).

За оваа класа да се имплементира оператор << за печатење на уред во формат:

[modelnauredotl]
[tipnaured] [casovizaproverka]

Каде часовите за проверка се оние од основната проверка+ дополнителни 2 часа доколку уредот е понов од 2015 + 2 часа доколу уредот е лаптоп (5 поени)

Да се креира класа MobileServis во која се чува адреса (низа од 100 знаци), низа од уреди (динамички алоцирана низа) и број на уреди.(5 поени)

За класата да се обезбедат:

operatoror+= за додавање на нов уред во сервисот.(5 поени) Не смее да се дозволи годината на производство на уредот да биде поголема од 2019 или помала од 2000. Ако се направи обид за додавање на уред со невалидна година, треба да се генерира исклучок InvalidProductionDate. (10 поени)

Функција pecatiUredi со која се печатат сите уреди со времето потребно за нивната проверка во сервисот (5 поени).

Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (5 поени)
*/
#include <iostream>
#include <cstring>

using namespace std;
enum tip
{
    Mobilen, Laptop
};

char Tip[][8] = {"Mobilen", "Laptop"};

class InvalidProductionDate
{
public:
    static void message()
    {
        cout << "Невалидна година на производство" << endl;
    }
};

class Device
{
private:
    char ime[100];
    tip tip_ured;
    static double proverka_casovi;
    int godina;
public:
    Device(const char *ime = "", tip tip_ured = Mobilen, int godina = 0)
    {
        strcpy(this->ime, ime);
        this->tip_ured = tip_ured;
        this->godina = godina;
    }

    friend ostream &operator<<(ostream &out, const Device &d)
    {
        out << d.ime << endl;
        out << Tip[d.tip_ured] << " " << d.proverka() << endl;

        return out;
    }

    static void setPocetniCasovi(double proverkaCasovi)
    {
        Device::proverka_casovi = proverkaCasovi;
    }

    double proverka() const
    {
        double s = 0;

        if (godina > 2015)
            s += 2;

        if (tip_ured == Laptop)
            s += 2;

        return s + Device::proverka_casovi;
    }

    int getGodina() const
    {
        return godina;
    }
};

class MobileServis
{
private:
    char adresa[100];
    Device *d;
    int n;
public:
    MobileServis(const char *adresa = "")
    {
        strcpy(this->adresa, adresa);
        d = new Device[0];
        n = 0;
    }

    MobileServis &operator+=(Device &de)
    {
        try
        {
            if (de.getGodina() < 2000 || de.getGodina() > 2019)
                throw InvalidProductionDate();
        }
        catch (InvalidProductionDate)
        {
            InvalidProductionDate::message();
            return *this;
        }

        auto *temp = new Device[n + 1];

        for (int i = 0; i < n; i++)
            temp[i] = d[i];
        temp[n] = de;

        delete[] d;
        d = temp;
        n++;

        return *this;
    }

    void pecatiCasovi()
    {
        cout << "Ime: " << adresa << endl;

        for (int i = 0; i < n; i++)
            cout << d[i];
    }
};

double Device::proverka_casovi = 1;

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1)
    {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (tip)
                tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2)
    {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)
                    tipDevice, godina);
            t += tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3)
    {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)
                    tipDevice, godina);
            t += tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 4)
    {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)
                    tipDevice, godina);
            t += tmp;
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5)
    {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)
                    tipDevice, godina);

            t += tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6)
    {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)
                    tipDevice, godina);
            t += tmp;
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

