/*
Да се дефинира класа Ucesnik за учесник во маратон за кој ќе се чуваат информации за:

име (динамички алоцирана низа од знаци)
пол (bool)
возраст (цел број) (5 поени).
За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени)

Дополнително за оваа класа да се преоптоварат:

оператор за споредување > (споредува двајца учесници според возраста) (5 поени)
операторот за проследување на излезен тек << кој ќе ги печати името, полот (машки/женски) и возраста, секој во посебен ред. (5 поени)
Да се дефинира класа Maraton за кој се чуваат:

локација (низа од максимум 100 знаци)
низа од Ucesnik објекти (динмички алоцирана низа од објекти од класата Ucesnik)
број на учесници (цел број) (5 поени).
За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени) Исто така да се имплементираат следните методи:

оператор += за додавање нов Ucesnik на маратонот Maraton. (10 поени)
prosecnoVozrast() вреќа просечена возраст на учесниците на маратонот (5 поени)
pecatiPomladi(Ucesnik &u) ги печати сите учесници помлади од учесникот проследен како аргумент на методот. (5 поени)
*/
#include <iostream>
#include <cstring>

using namespace std;

class Ucesnik
{
private:
    char *name;
    bool gender;
    int age;
public:
    Ucesnik() = default;

    Ucesnik(char *name1, bool gender1, int age1)
    {
        name = new char[100];
        strcpy(name, name1);
        gender = gender1;
        age = age1;
    }

    ~Ucesnik()
    {
        delete[] name;
    }

    int operator>(Ucesnik &other) const
    {
        if (this == &other || this->age > other.age)
            return 0;
        return 1;
    }

    int operator==(Ucesnik &other) const
    {
        if (this == &other)
            return 1;
        return 0;
    }

    int getAge() const
    {
        return age;
    }

    char *getName() const
    {
        return name;
    }

    bool getGender() const
    {
        return gender;
    }
};

class Maraton
{
private:
    char location[100];
    Ucesnik *u;
    int n;
public:
    Maraton() = default;

    Maraton(char *location1)
    {
        strcpy(location, location1);
        u = new Ucesnik[100];
        n = 0;
    }

    ~Maraton()
    {
        delete[] u;
    }

    Maraton &operator+=(const Ucesnik &other)
    {
        u[n] = other;
        n++;

        return *this;
    }

    float prosecnoVozrast()
    {
        int s = 0;

        for (int i = 0; i < n; i++)
            s += u[i].getAge();

        return (float) s / (float) n;
    }

    void pecatiPomladi(Ucesnik &c)
    {
        for (int i = 0; i < n - 1; i++)
            if (u[i] == c)
                continue;
            else if (u[i] > c)
            {
                cout << u[i].getName() << endl;
                if (u[i].getGender() == 1)
                    cout << "mashki" << endl;
                else
                    cout << "zhenski" << endl;
                cout << u[i].getAge() << endl;
            }
    }
};

int main()
{
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik *[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for (int i = 0; i < n; ++i)
    {
        delete u[i];
    }
    delete[] u;
    return 0;
}