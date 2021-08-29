/*
Да се дефинира класа Film, во која ќе се чуваат информации за:

име низа од 100 знаци
режисер низа од 50 знаци
жанр низа од 50 знаци
година цел број
Сите променливи треба да бидат приватни. Соодветно во рамките на класата да се дефинираат:

default конструктор и конструктор со аргументи
метод за печатење на информациите за филмот
Дополнително да се реализира надворешна функција:

void pecati_po_godina(Film *f, int n, int godina) која ќе прима аргумент низа од филмови, вкупниот број на филмови и година, а треба да ги отпечати само филмовите кои се направени во дадената година.
*/
#include <iostream>
#include <cstring>

using namespace std;

class Film
{
private:
    char *ime;
    char *reziser;
    char *zanr;
    int godina;
public:
    Film() = default;

    Film(char *ime1, char *reziser1, char *zanr1, int godina1)
    {
        ime = new char[100];
        reziser = new char[50];
        zanr = new char[50];

        strcpy(ime, ime1);
        strcpy(reziser, reziser1);
        strcpy(zanr, zanr1);
        godina = godina1;
    }

    int get_godina()
    {
        return godina;
    }

    char *get_ime()
    {
        return ime;
    }

    char *get_reziser()
    {
        return reziser;
    }

    char *get_zanr()
    {
        return zanr;
    }
};

void pecati_po_godina(Film *f, int n, int godina)
{
    for (int i = 0; i < n; ++i)
        if (f[i].get_godina() == godina)
        {
            cout << "Ime: " << f[i].get_ime() << endl;
            cout << "Reziser: " << f[i].get_reziser() << endl;
            cout << "Zanr: " << f[i].get_zanr() << endl;
            cout << "Godina: " << f[i].get_godina() << endl;
        }
}

int main()
{
    int n;
    cin >> n;
    Film *film = new Film[n];
    for (int i = 0; i < n; ++i)
    {
        char ime[100];
        char reziser[50];
        char zanr[50];
        int godina;
        cin >> ime;
        cin >> reziser;
        cin >> zanr;
        cin >> godina;
        film[i] = Film(ime, reziser, zanr, godina);
    }
    int godina;
    cin >> godina;
    pecati_po_godina(film, n, godina);
    return 0;
}