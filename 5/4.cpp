/*
Да се креира класа за претставување на планинарско друштво во која ќе се чуваат информации за името на друштвото (динамички алоцирана низа од знаци), број на поминати тури (цел број) и број на членови во планинарското друштво (цел број). За оваа класа да се напише:

оператор + за собирање на две друштва што како резултат враќа друштво со број на членови еднаков на збирот од членовите од двете друштва, а останатите атрибути на резултантното друштво ги добиваат вредностите на соодветните атрибути од друштвото со поголем број на членови

оператори >, < за споредба во однос на бројот на членови во планинарските друштва

оператор << за печатење на информациите за планинарското друштво

Да се напише функција што на влез прима низа од планинарски друштва и вкупен број на друштва во низата и го печати планинарското друштво што има најголем број на членови .
*/
#include <iostream>
#include <cstring>

using namespace std;

class PlDrustvo
{
private:
    char *name;
    int tourists;
    int members;
public:
    PlDrustvo()
    {
        name = new char[100];
        tourists = 0;
        members = 0;
    }

    PlDrustvo(char *name, int tourists, int members)
    {
        this->name = new char[100];
        strcpy(this->name, name);
        this->tourists = tourists;
        this->members = members;
    }

    PlDrustvo operator+(const PlDrustvo &other)
    {
        PlDrustvo p;

        if (members > other.members)
            p = PlDrustvo(name, tourists, members + other.members);
        else
            p = PlDrustvo(other.name, other.tourists, members + other.members);

        return p;
    }

    bool operator<(const PlDrustvo &other) const
    {
        if (members < other.members)
            return true;
        return false;
    }

    bool operator>(const PlDrustvo &other) const
    {
        if (members > other.members)
            return true;
        return false;
    }

    friend ostream &operator<<(ostream &out, const PlDrustvo &other)
    {
        out << "Ime: " << other.name << " Turi: " << other.tourists << " Clenovi: " << other.members << endl;

        return out;
    }

    int getMembers()
    {
        return members;
    }
};

void najmnoguClenovi(PlDrustvo pDrustvo[3], int n)
{
    int index = 0;
    int max = pDrustvo[0].getMembers();
    for (int i = 0; i < n; i++)
        if (max < pDrustvo[i].getMembers())
        {
            max = pDrustvo[i].getMembers();
            index = i;
        }

    cout << "Najmnogu clenovi ima planinarskoto drustvo: " << pDrustvo[index];
}

int main()
{
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i = 0; i < 3; i++)
    {
        char ime[100];
        int brTuri;
        int brClenovi;
        cin >> ime;
        cin >> brTuri;
        cin >> brClenovi;
        PlDrustvo p(ime, brTuri, brClenovi);
        drustva[i] = p;

    }

    pl = drustva[0] + drustva[1];
    cout << pl;

    najmnoguClenovi(drustva, 3);

    return 0;
}