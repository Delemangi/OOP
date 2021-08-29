/*
(40 поени)

Да се креира класа Patnik во која се чуваат податоци за патниците на еден воз и тоа: име (низа од максимум 100 знаци), класа на вагон во која се вози (цел број 1 или 2) и велосипед (булова променлива).

За оваа класа да се преоптоварат:

Оператор << - за печатење на информациите за патникот во формат:
Име на патник

Бројот на класата (1 или 2)

Дали има велосипед?

Потоа да се креира клaса Voz во која се чува: крајна дестинација (низа од максимум 100 знаци), динамички алоцирана низа од објекти од класата Patnik, како и број на елементи во низата (цел број), број на дозволени велосипеди (цел број).

За класата да се обезбедат:

Оператор += – за додавање нов патник во воз. Патник со велосипед ќе може да се качи во воз само ако возот го дозволува тоа.
Оператор << - за печатење на крајната дестинација до која вози и листата на патници
Функција со потпис: patniciNemaMesto(). Со оваа функција се пресметува вкупниот број на патници (од 1-ва класа и 2-ра класа) за кои нема место да влезат во возот со велосипед. Притоа треба да се внимава дека во пресметувањето на вкупниот број патници со велосипеди кои ќе влезат во возот прво треба да се земат предвид патниците од 1-ва класа, а потоа се дозволува да влегуваат патниците од 2-ра класа се додека не се достигне максималниот број на дозволени велосипеди во возот. На крај се печати бројот на патници со велосипеди кои остануваат (не влегуваат во возот) од 1-ва класа, а потоа од 2-ра класа.
*/
#include<iostream>
#include<cstring>

using namespace std;

class Patnik
{
private:
    char name[100];
    int type;
    bool bike;
public:
    Patnik() = default;

    Patnik(char *name1, int type1, bool bike1)
    {
        strcpy(this->name, name1);
        this->type = type1;
        this->bike = bike1;
    }

    friend ostream &operator<<(ostream &out, Patnik &other)
    {
        out << other.name << endl << other.type << endl << other.bike << endl;

        return out << endl;
    }

    int getType() const
    {
        return this->type;
    }

    bool isBike() const
    {
        return this->bike;
    }
};

class Voz
{
private:
    char dest[100]{};
    Patnik *p;
    int n;
    int bikes;
    int t1;
    int t2;
public:
    Voz(char *dest1, int bikes1)
    {
        strcpy(this->dest, dest1);
        this->bikes = bikes1;
        this->n = 0;
        this->p = new Patnik[50];
        this->t1 = 0;
        this->t2 = 0;
    }

    Voz &operator+=(Patnik &other)
    {
        this->p[n] = other;
        this->n++;

        return *this;
    }

    friend ostream &operator<<(ostream &out, Voz &other)
    {
        out << other.dest << endl;

        if (other.bikes == 0)
        {
            for (int i = 0; i < other.n; i++)
                if (!other.p[i].isBike())
                    out << other.p[i];
        }
        else
        {
            for (int i = 0; i < other.n; i++)
                if (other.p[i].isBike())
                    if (other.p[i].getType() == 1)
                        if (other.bikes > 0)
                            other.bikes--;
                        else
                            other.t1++;

            for (int i = 0; i < other.n; i++)
                if (other.p[i].isBike())
                    if (other.p[i].getType() == 2)
                        if (other.bikes > 0)
                            other.bikes--;
                        else
                            other.t2++;

            for (int i = 0; i < other.n; i++)
                out << other.p[i];
        }

        return out;
    }

    void patniciNemaMesto()
    {
        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << t1 << endl;
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << t2 << endl;
    }
};


int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++)
    {
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
