/*
Да се дефинира класа Vozilo која ќе содржи информација за неговата маса (децимален број), ширина и висина (цели броеви).

Од оваа класа да се изведе класата Автомобил во која како дополнителна информација се чува информацијата за бројот на врати (цел број).

Од класата возило да се изведе и класата Автобус во која се чуваат информации и за бројот на патници кои може да ги пренесува.

Од класата возило да се изведе класата Камион во која се чуваат информации и за максималната маса која може да се товари на него (децимална вредност).

За сите класи да се креираат погодни контруктори, како и set и get функции.

Да се дефинира класа ParkingPlac за која се чува динамичко алоцирано поле од покажувачи кон Vozilo, како и бројот на елементи во полето. Во оваа класа да се дефинираат:

конструктор
деструктор
операторот += за додавање на ново возило (аргументот е покажувач кон Vozilo)
функција float presmetajVkupnaMasa() со која се пресметува вкупната маса на сите возила во паркинг плацот
функција int brojVozilaPoshirokiOd(int l) со која се пресметува бројот на возила кои се пошироки од дадената вредност
функција void pecati() со која се печати: Brojot na avtomobili e X, brojot na avtobusi e Y i brojot na kamioni e Z.
функција int pogolemaNosivostOd(Vozilo& v) во која се враќа бројот на сите камиони кои имаат носивост поголема од масата на возилото предадено како аргумент.
Да се дефинира виртуелна функција int vratiDnevnaCena() во класата Vozilo и истата да се преоптовари во сите изведени класи. За секој автомобил со помалку од 5 врати дневната цена е 100, а инаку е 130 денари. За секој камион цената се пресметува со формулата: (masa+nosivost)*0.02. За секој автобус цената е 5 денари по лице кое може да се пренесува.

Во класата ParkingPlac да се додаде следната функција: - функција int vratiDnevnaZarabotka() со која се враќа дневната заработка од сите возила на паркингот.
*/
#include<iostream>

using namespace std;

class Vozilo
{
protected:
    double mass;
    int width;
    int height;
public:
    Vozilo(double mass = 0, int width = 0, int height = 0)
    {
        this->mass = mass;
        this->width = width;
        this->height = height;
    }

    virtual int vratiDnevnaCena() = 0;

    double getMass()
    {
        return mass;
    }

    int getWidth()
    {
        return width;
    }

    int getHeight()
    {
        return height;
    }
};

class Avtomobil : public Vozilo
{
private:
    int doors;
public:
    Avtomobil(double mass, int width, int height, int doors) : Vozilo(mass, width, height)
    {
        this->doors = doors;
    }

    int vratiDnevnaCena()
    {
        if (doors < 5)
            return 100;
        else
            return 130;
    }

    int getDoors()
    {
        return doors;
    }
};

class Avtobus : public Vozilo
{
private:
    int passengers;
public:
    Avtobus(double mass, int width, int height, int passengers) : Vozilo(mass, width, height)
    {
        this->passengers = passengers;
    }

    int vratiDnevnaCena()
    {
        return 5 * passengers;
    }

    int getPassengers()
    {
        return passengers;
    }
};

class Kamion : public Vozilo
{
private:
    double max;
public:
    Kamion(double mass, int width, int height, double max) : Vozilo(mass, width, height)
    {
        this->max = max;
    }

    int vratiDnevnaCena()
    {
        return (mass + max) * 0.02;
    }

    double getMax()
    {
        return max;
    }
};

class ParkingPlac
{
private:
    Vozilo **v;
    int n;
public:
    ParkingPlac()
    {
        v = new Vozilo *[0];
        n = 0;
    }

    ~ParkingPlac()
    {
        delete[] v;
    }

    ParkingPlac &operator+=(Vozilo *voz)
    {
        Vozilo **temp = new Vozilo *[n + 1];

        for (int i = 0; i < n; i++)
            temp[i] = v[i];
        temp[n] = voz;

        delete[] v;
        v = temp;
        n++;

        return *this;
    }

    double presmetajVkupnaMasa()
    {
        double s = 0;

        for (int i = 0; i < n; i++)
            s += v[i]->getMass();

        return s;
    }

    int brojVozilaPoshirokiOd(int l)
    {
        int s = 0;

        for (int i = 0; i < n; i++)
            if (v[i]->getWidth() > l)
                s++;

        return s;
    }

    int pogolemaNosivostOd(Vozilo &voz)
    {
        int s = 0;

        for (int i = 0; i < n; i++)
            if (dynamic_cast<Kamion *>(v[i]) && v[i]->getMass() > voz.getMass())
                s++;

        return s;
    }

    int vratiDnevnaZarabotka()
    {
        int s = 0;

        for (int i = 0; i < n; i++)
            s += v[i]->vratiDnevnaCena();

        return s;
    }

    void pecati()
    {
        int avtomobili = 0, avtobusi = 0, kamioni = 0;

        for (int i = 0; i < n; i++)
            if (dynamic_cast<Avtomobil *>(v[i]))
                avtomobili++;
            else if (dynamic_cast<Avtobus *>(v[i]))
                avtobusi++;
            else if (dynamic_cast<Kamion *>(v[i]))
                kamioni++;

        cout << "Brojot na avtomobili e " << avtomobili << ", brojot na avtobusi e " << avtobusi
             << " i brojot na kamioni e " << kamioni << "." << endl;
    }
};

int main()
{
    ParkingPlac p;

    int n;
    cin >> n;
    int shirina, visina, broj;
    float masa, nosivost;
    for (int i = 0; i < n; i++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            cin >> masa >> shirina >> visina >> broj;
            Avtomobil *a = new Avtomobil(masa, shirina, visina, broj);
            p += a;
        }
        if (type == 2)
        {
            cin >> masa >> shirina >> visina >> broj;
            p += new Avtobus(masa, shirina, visina, broj);
        }
        if (type == 3)
        {
            cin >> masa >> shirina >> visina >> nosivost;
            p += new Kamion(masa, shirina, visina, nosivost);
        }
    }

    p.pecati();

    cout << "\nZarabotkata e " << p.vratiDnevnaZarabotka() << endl;
    cout << "Vkupnata masa e " << p.presmetajVkupnaMasa() << endl;
    cout << "Brojot poshiroki od 5 e " << p.brojVozilaPoshirokiOd(5) << endl;
    Avtomobil a(1200, 4, 3, 5);
    cout << "Brojot na kamioni so nosivost pogolema od avtomobilot e " << p.pogolemaNosivostOd(a) << endl;
}