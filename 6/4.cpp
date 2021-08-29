/*
Да се развие класа Nediviznina за коjа се чуваат следниве информации:

адреса (динамички алоцирана низа од знаци)
квадратура (цел боj)
цена за квадрат (цел боj)
За оваа класа да се имплементираат соодветните конструктори и следните методи:

cena() коj ќе jа враќа цената на недвижнината (квадратура * цена-за-квадрат)
pecati() коj ќе ги испечати сите информации за истата
danokNaImot() коj го ваќа данокот што се плаќа за недвижнината, а истиот се пресметува како 5% од цената на недвижнината.
Од оваа класа да се изведе класа Vila за коjа дополнително се чува данок на луксуз (цел боj, пр. 10%). За оваа класа да се преоптоварат методите:

pecati()
danokNaImot() со тоа што пресметаниот данок се зголемува процентуално за данокот на луксуз.
И за двете класи треба да се преоптовари operator >>.
*/
#include <iostream>
#include <cstring>

using namespace std;

class Nedviznina
{
protected:
    char *address;
    int area;
    int price;
public:
    Nedviznina()
    {
        address = new char[100];
        area = 0;
        price = 0;
    }

    ~Nedviznina()
    {
        delete[] address;
    }

    friend istream &operator>>(istream &in, Nedviznina &n)
    {
        in >> n.address >> n.area >> n.price;

        return in;
    }

    int cena()
    {
        return area * price;
    }

    double danokNaImot()
    {
        return 0.05 * cena();
    }

    char *getAdresa()
    {
        return address;
    }

    void pecati()
    {
        cout << address << ", Kvadratura: " << area << ", Cena po Kvadrat: " << price << endl;
    }
};

class Vila : public Nedviznina
{
private:
    int danok;
public:
    Vila(int danok = 0) : Nedviznina()
    {
        this->danok = danok;
    }

    friend istream &operator>>(istream &in, Vila &v)
    {
        in >> v.address >> v.area >> v.price >> v.danok;

        return in;
    }

    double danokNaImot()
    {
        return cena() * (danok + 5) / 100.0;
    };

    void pecati()
    {
        cout << address << ", Kvadratura: " << area << ", Cena po Kvadrat: " << price << ", Danok na luksuz: " << danok
             << endl;
    }
};

int main()
{
    Nedviznina n;
    Vila v;
    cin >> n;
    cin >> v;
    n.pecati();
    cout << "Danok za: " << n.getAdresa() << ", e: " << n.danokNaImot() << endl;
    v.pecati();
    cout << "Danok za: " << v.getAdresa() << ", e: " << v.danokNaImot() << endl;
    return 0;
}