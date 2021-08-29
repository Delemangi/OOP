/*
Да се дефинира класа Potpisuvac во која се чуваат информации за:

име (низа од максимум 20 знаци)
презиме (низа од максимум 20 знаци)
ЕМБГ (низа од максимум 14 знаци)
За класата да се дефинира copy конструктор, default конструктор и конструктор со аргументи.

Да се дефинира класа Dogovor, во која се чуваат информации за:

број на договор (int),
категорија на договор (низа од 50 знаци),
поле од 3 потпишувачи на договорот (објекти од класата Potpisuvac)
Во класата да се додаде метод кој ќе проверува дали постојат два исти потпишувачи (имаат ист ЕМБГ).
*/
#include <iostream>
#include <cstring>

using namespace std;

class Potpisuvac
{
private:
    char name[20];
    char surname[20];
    char embg[14];
public:
    Potpisuvac()
    {
        *name = '\0';
        *surname = '\0';
        *embg = '\0';
    }

    Potpisuvac(const char *name, const char *surname, const char *embg)
    {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        strcpy(this->embg, embg);
    }

    const char *getEmbg()
    {
        return embg;
    }

    Potpisuvac(const Potpisuvac &p) : Potpisuvac(p.name, p.surname, p.embg)
    {}
};

class Dogovor
{
private:
    int n;
    char cat[20];
    Potpisuvac p[3];
public:
    Dogovor(int n, char *cat, Potpisuvac *p)
    {
        this->n = n;
        strcpy(this->cat, cat);
        for (int i = 0; i < 3; i++)
            this->p[i] = p[i];
    }

    bool proverka()
    {
        for (int i = 0; i < 3; i++)
            for (int j = i + 1; j < 3; j++)
                if (strcmp(p[i].getEmbg(), p[j].getEmbg()) == 0)
                    return true;
        return false;
    }
};

int main()
{
    char embg[14], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> embg >> ime >> prezime;
        Potpisuvac p1(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p2(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p3(ime, prezime, embg);
        cin >> broj >> kategorija;
        Potpisuvac p[3];
        p[0] = p1;
        p[1] = p2;
        p[2] = p3;
        Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl;
        if (d.proverka())
            cout << "Postojat potpishuvaci so ist EMBG" << endl;
        else
            cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}