/*
Да се дефинира класа Agol, во која се чуваат информации за:

степени, минути и секунди (int)
Во класата да се реализираат:

конструктор по потреба
методи за поставување на вредности на атрибутите на класата (set методи)
метод за пресметување на вредноста на аголот во секунди
Да се дефинира и метод за проверување на тоа дали внесениот агол е валиден, односно дали се внесени соодветни вредности за атрибутите (во границите кои ги дозволуваат).
*/
#include <iostream>

using namespace std;

class Agol
{
private:
    int deg;
    int min;
    int sec;
public:
    int getSekundi()
    {
        return sec;
    }

    void set_stepeni(int deg1)
    {
        deg = deg1;
    }

    void set_minuti(int min1)
    {
        min = min1;
    }

    void set_sekundi(int sec1)
    {
        sec = sec1;
    }

    int to_sekundi()
    {
        return this->deg * 3600 + this->min * 60 + this->sec;
    }
};

int proveri(int deg, int min, int sec)
{
    if (deg > 360 || min >= 60 || min < 0 || sec >= 60 || sec < 0)
        return 0;
    else
        return 1;
}

bool changeOfSeconds(Agol a, int sec)
{
    return a.getSekundi() != sec;
}

int main()
{
    Agol a1;
    int deg, min, sec;
    cin >> deg >> min >> sec;

    if (proveri(deg, min, sec))
    {

        a1.set_stepeni(deg);
        a1.set_minuti(min);
        a1.set_sekundi(sec);
        cout << a1.to_sekundi();
        if (changeOfSeconds(a1, sec))
            cout << "Ne smeete da gi menuvate sekundite vo ramkite na klasata!" << endl;

    }
    else
        cout << "Nevalidni vrednosti za agol";

    return 0;
}
