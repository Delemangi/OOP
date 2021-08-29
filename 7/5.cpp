/*
Да се креира хиерархиjа на класи за репрезентациjа на жичани инструменти. За потребите на оваа хиерархиjа да се дефинира класа ZicanInstrument од коjа ќе бидат изведени двете класи Mandolina и Violina.

Во класата ZicanInstrument се чуваат податоци за:

името на инструментот (низа од 20 знаци)
броjот на жици
основната цена на инструментот.
За класата Mandolina дополнително се чува неjзината форма (низа од 20 знаци).

За класата Violina дополнително се чува неjзината големина (децимален броj).

За секоjа изведените класи треба да се дефинираат соодветните конструктори и следните методи:

cena() за пресметување на цената на инструментот
основната цена на мандолината се зголемува за 15% доколку таа има форма во Неаполитански стил (вредноста на променливата форма е “Neapolitan”)
основната цена на виолината се зголемува за 10% ако неjзината големина има вредност 1/4 (0.25), односно за 20% ако неjзината големина има вредност 1 (1.00)
проптоварување на операторот ==, коj ги споредува жичаните инструменти според броjот на жици што го имаат
преоптоварување на операторот << за печатење на сите податоци за жичаните инструменти.
Да се напише функциjа pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **i, int n) коjа на влез прима жичан инструмент, низа од покажувачи кон жичани инструменти и броj на елементи во низата. Функциjата jа печати цената на сите жичани инструменти од низата кои имаат ист броj на жици како и инструментот проследен како прв аргумент на функциjата.
*/
#include <iostream>
#include <cstring>

using namespace std;

class ZicanInstrument
{
protected:
    char name[20];
    int strings;
    int price;
public:
    ZicanInstrument(char *name = "", int strings = 0, int price = 0)
    {
        strcpy(this->name, name);
        this->strings = strings;
        this->price = price;
    }

    bool operator==(ZicanInstrument &z) const
    {
        return strings == z.strings;
    }

    friend ostream &operator<<(ostream &out, ZicanInstrument &z)
    {
        out << z.name << " " << z.strings << " " << z.price << endl;

        return out;
    }

    virtual double cena() = 0;
};

class Mandolina : public ZicanInstrument
{
private:
    char form[20];
public:
    Mandolina(char *name = "", int strings = 0, int price = 0, char *form = "") : ZicanInstrument(name, strings, price)
    {
        strcpy(this->form, form);
    }

    double cena()
    {
        if (!strcmp("Neapolitan", form))
            return 1.15 * price;
        else
            return price;
    }
};

class Violina : public ZicanInstrument
{
private:
    double size;
public:
    Violina(char *name = "", int strings = 0, int price = 0, double size = 0) : ZicanInstrument(name, strings, price)
    {
        this->size = size;
    }

    double cena()
    {
        if (size == 0.25)
            return 1.1 * price;
        else if (size == 1)
            return 1.2 * price;
        else
            return price;
    }
};

void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **i, int n)
{
    for (int j = 0; j < n; j++)
        if (*i[j] == zi)
            cout << i[j]->cena() << endl;
}

int main()
{
    char ime[20];
    int brojZici;
    float cena;
    char forma[20];
    cin >> ime >> brojZici >> cena >> forma;
    Mandolina m(ime, brojZici, cena, forma);
    int n;
    cin >> n;
    ZicanInstrument **zi = new ZicanInstrument *[2 * n];
    for (int i = 0; i < n; ++i)
    {
        cin >> ime >> brojZici >> cena >> forma;
        zi[i] = new Mandolina(ime, brojZici, cena, forma);
    }
    for (int i = 0; i < n; ++i)
    {
        float golemina;
        cin >> ime >> brojZici >> cena >> golemina;
        zi[n + i] = new Violina(ime, brojZici, cena, golemina);
    }
    pecatiInstrumenti(m, zi, 2 * n);
    for (int i = 0; i < 2 * n; ++i)
    {
        delete zi[i];
    }
    delete[] zi;
    return 0;
}