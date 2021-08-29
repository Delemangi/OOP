/*
Да се дефинира класа Ekipa за коjа се чуваат следниве информации:

името на екипата (низа од наjмногу 15 знаци)
броj на порази
броj на победи
За оваа класа да се дефинира метод pecati() коjа ги печати податоците за екипаta. Од оваа класа да се изведe новa класa, FudbalskaEkipa.

За фудбалската екипа дополнително се чуваат информации за:

вкупниот броj на црвени картони
вкупниот броj жолти картони
броjот на нерешени натпревари
За фудбалската екипа да се преоптовари методот pecati(), така што покрај останатите информации, ќе се испечатат и бројот на нерешени резултати и вкупен број на поени во формат: Име на екипа, броj на победи, броj на порази, броj на нерешени натпревари и вкупен броj на поени (за победа фудбалската екипа добива 3 поени, додека за нерешен резултата, 1 поен);
*/
#include <iostream>
#include<cstring>

using namespace std;

class Ekipa
{
protected:
    char ime[15];
    int porazi;
    int pobedi;
public:
    void pecati()
    {
        cout << "Ime: " << ime << " Pobedi: " << pobedi << " Porazi: " << porazi;
    }
};

class FudbalskaEkipa : public Ekipa
{
private:
    int crveni;
    int zolti;
    int nereseni;
public:
    FudbalskaEkipa(char *ime, int pobedi, int porazi, int crveni, int zolti, int nereseni)
    {
        strcpy(this->ime, ime);
        this->pobedi = pobedi;
        this->porazi = porazi;
        this->crveni = crveni;
        this->zolti = zolti;
        this->nereseni = nereseni;
    }

    void pecati()
    {
        Ekipa::pecati();
        cout << " Nereseni: " << nereseni << " Poeni: " << pobedi * 3 + nereseni << endl;
    }
};

int main()
{
    char ime[15];
    int pob, por, ck, zk, ner;
    cin >> ime >> pob >> por >> ck >> zk >> ner;
    FudbalskaEkipa f1(ime, pob, por, ck, zk, ner);
    f1.pecati();
    return 0;
}