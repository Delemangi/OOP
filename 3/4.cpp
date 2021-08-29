/*
Во оваа задача е потребно да уредите даден дом со маси. Креирајте класа Masa со следниве атрибути:

должина (целобројна вредност)
ширина (целобројна вредност)
конструктор со и без параметри и метода pecati().

Креирајте класа Soba која содржи:

маса (објект од класата Маса)
должина на собата (целобројна вредност)
ширина на собата (целобројна вредност)
конструктор со и без параметри и метода pecati() во која се повикува и pecati() за објектот Masa.

Креирајте класа Kukja со атрибути:

соба (објект од класата Soba)
адреса (низа од 50 знаци), и соодветни методи.
конструктор со и без параметри, деструктор и метода pecati() во која се повикува и pecati() за објектот Soba.
*/
//vasiot kod ovde
#include <iostream>
#include <cstring>

using namespace std;

class Masa
{
private:
    int length;
    int width;
public:
    Masa()
    {
        length = 0;
        width = 0;
    }

    Masa(int length, int width)
    {
        this->length = length;
        this->width = width;
    }

    void pecati()
    {
        cout << "Masa: " << length << " " << width << endl;
    }
};

class Soba
{
private:
    Masa m;
    int length;
    int width;
public:
    Soba()
    {
        length = 0;
        width = 0;
    }

    Soba(int width, int length, Masa m)
    {
        this->m = m;
        this->length = length;
        this->width = width;
    }

    void pecati()
    {
        cout << "Soba: " << width << " " << length << " ";
        m.pecati();
    }
};

class Kukja
{
private:
    Soba s;
    char address[30];
public:
    Kukja()
    {}

    Kukja(Soba s, char *address)
    {
        this->s = s;
        strcpy(this->address, address);
    }

    ~Kukja()
    {}

    void pecati()
    {
        cout << "Adresa: " << address << " ";
        s.pecati();
    }
};

//ne smee da se menuva main funkcijata!
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int masaSirina, masaDolzina;
        cin >> masaSirina;
        cin >> masaDolzina;
        Masa m(masaSirina, masaDolzina);
        int sobaSirina, sobaDolzina;
        cin >> sobaSirina;
        cin >> sobaDolzina;
        Soba s(sobaSirina, sobaDolzina, m);
        char adresa[30];
        cin >> adresa;
        Kukja k(s, adresa);
        k.pecati();
    }

    return 0;
}