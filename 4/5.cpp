/*
Да се дефинира класа Pica за која ќе се чуваат податоци за:

име на пицата (низа од 15 знаци)
цена (цел број)
состојки (динамички алоцирана низа од знаци)
намалување на цената во проценти (цел број) - ако пицата не е на промоција намалувањето има вредност нула, во спротивно, вредност поголема од нула и не поголема од 100.
За потребите на оваа класа да се креираат потребните конструктори и да се напише соодветен деструктор. Дополнително за оваа класа да се дефинира функцијата:

pecati() - функција во која ќе се печатат податоците за пицата во следниот формат: име - состојки, цена.
istiSe(Pica p) - функција за споредба на две пици според состојките :
Да се дефинира класа Picerija во која се чуваат:

име (низа од максимум 15 знаци)
динмички алоцирана низа од објекти од класата Pica
број на пици (цел број)
За потребите на оваа класа да се дефинираат потребните конструктори и да се напише соодветен деструктор. Да се имплементираат и следниве методи:

dodadi (Pica P) - за додавање нова пица во пицеријата, но само ако не постои иста во низата (нема пица со исти состојки со пицата што треба да се додаде).
void piciNaPromocija() - се печатат сите пици од пицеријата што се на промоција во формат : име - состојки, цена, цена со попуст.
*/
#include <iostream>
#include <cstring>

using namespace std;

class Pica
{
private:
    char name[15];
    int price;
    char *ingredients;
    int discount;
public:
    Pica()
    {
        *name = '\0';
        price = 0;
        ingredients = new char[100];
        discount = 0;
    }

    Pica(char *name, int price, char *ingredients, int discount)
    {
        strcpy(this->name, name);
        this->price = price;
        this->ingredients = new char[100];
        strcpy(this->ingredients, ingredients);
        this->discount = discount;
    }

    //~Pica()
    //{
    //    delete[] ingredients;
    //}

    void pecati()
    {
        cout << name << " - " << ingredients << ", " << price << " " << price * (1 - discount / 100.0) << endl;
    }

    int getDiscount() const
    {
        return discount;
    }

    bool istiSe(Pica p)
    {
        if (!strcmp(ingredients, p.ingredients))
            return true;
        return false;
    }
};

class Picerija
{
private:
    char name[15];
    Pica *p;
    int n;
public:
    Picerija()
    {
        *name = '\0';
        p = new Pica[10];
        n = 0;
    }

    Picerija(char *name, Pica *p = nullptr, int n = 0)
    {
        strcpy(this->name, name);
        p = new Pica[10];
        this->n = n;

        if (n != 0)
            for (int i = 0; i < n; i++)
                this->p[i] = p[i];
    }

    //Picerija(Picerija &p) : Picerija(p.name, p.p, p.n)
    //{}

    //~Picerija()
    //{
    //    delete[] p;
    //}

    void dodadi(Pica pi)
    {
        for (int i = 0; i < n; i++)
            if (p[i].istiSe(pi))
                return;

        p[n] = pi;
        n++;
    }

    void piciNaPromocija()
    {
        for (int i = 0; i < n; i++)
            if (p[i].getDiscount() > 0)
                p[i].pecati();
    }

    void setIme(char *ime)
    {
        strcpy(name, ime);
    }

    char *getIme()
    {
        return name;
    }
};

int main()
{

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++)
    {
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2.dodadi(p);

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}
