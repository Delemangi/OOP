/*
Да се креира класата Zichara во која ќе се чуваат информации за:

место (динамичко алоцирано поле од знаци)
цена на дневна карта (цел број)
Да се креира класа PlaninarskiDom во која се чуваат информации за:

име (статичко поле од најмногу 15 знаци)
цени по сезони (поле од 2 цели броеви кои ја претставуваат цената за спиење за еден ден во планинарскиот дом во двете различни сезони. Секој планинарски дом има две сезони: летна и зимска. Летната сезона почнува на 1ви април и завршува до 1ви сепмтември. На пример цената за престој на 24ти Јули ќе биде сместена во полето со индекс 0 - каде е сместена цената за летната сезона)
класа на планинарскиот дом (еден знак кој може да има вредност од A до F, каде A е најдобра класа)
дали има жичара (bool-тип)
жичарата на планинарскиот дом (покажувач кон објект од класата Zichara)
За дадените класи дефинирајте ги потребните: конструктори, деструктори, set и get методи. Оптоварете го соодветно операторот =. (20 поени)

Да се оптоварат:

операторот -- (префискен) за намалување на класата на планинарскиот дом (во класата PlaninarskiDom). Да се запази дека за планинарскиот дом најмала класа е F. (5 поени)
операторот << за печатење на објект одPlaninarskiDom. (5 поени)
операторот <= за одредување дали планинарскиот дом има класа помала или еднаква со дадениот знак (споредба на планинарски дом со знак). (5 поени)
Формат на печатење на информации за еден планинарски дом:

Pelister klasa:A so zichara //ако има жичара
Korab klasa:B //ако нема жичара
Во класата PlaninarskiDom да се имплементира функција со име presmetajDnevenPrestoj со која се пресметува цената за дневен престој во планинарскиот дом за даден ден и месец во годината. Ако планинарскиот дом има жичара во цената за дневен престој влегува и дневната карта за жичарата. Функцијата враќа void (не враќа ништо). Првиот аргумент на функцијата е денот (1-31), а вториот е месецот (1-12) за кои се пресметува цената. Третиот аргумент е цената за дневен престој која ќе се пресмета во функцијата. Доколку денот или месецот се невалидни да се фрли соодветен исклучок со кој се справуваме во main-функцијата. Да се земе дека секој месец има 31 ден. (15 поени)

Дадена е main-функција во која се користат класите Zichara и PlaninarskiDom. Без таа да се менува креирајте ги опишаните класи.
*/
#include<iostream>
#include<string.h>

using namespace std;

class Zichara
{
private:
    char *place;
    int price;

public:
    Zichara()
    {
        place = nullptr;
        price = 0;
    }

    Zichara(char *place1, int price1)
    {
        place = new char[50];
        price = price1;
    }

    int getPrice()
    {
        return price;
    };
};

class PlaninarskiDom
{
private:
    char name[15];
    int prices[2];
    char type;
    bool zichara;
    Zichara *z;

public:
    PlaninarskiDom()
    {
        z = nullptr;
    }

    PlaninarskiDom(char *name1, const int *prices1, char type1)
    {
        strcpy(name, name1);
        prices[0] = prices1[0];
        prices[1] = prices1[1];
        type = type1;
        zichara = false;
        z = nullptr;
    }

    void setZichara(Zichara &r)
    {
        z = &r;
        zichara = true;
    }

    PlaninarskiDom &operator=(const PlaninarskiDom &other)
    {
        if (this == &other)
            return *this;

        strcpy(name, other.name);
        prices[0] = other.prices[0];
        prices[1] = other.prices[1];
        type = other.type;
        zichara = other.zichara;
        z = other.z;

        return *this;
    }

    PlaninarskiDom &operator--()
    {
        if (type == 'F')
            return *this;

        type++;

        return *this;
    }

    friend ostream &operator<<(ostream &os, const PlaninarskiDom &other)
    {
        os << other.name << " klasa:" << other.type;

        if (other.zichara)
            os << " so Zichara" << endl;
        else
            os << endl;

        return os;
    }

    bool operator<=(char c) const
    {
        if (type >= c)
            return true;
        return false;
    }

    void presmetajDnevenPrestoj(int day, int month, int &pr)
    {
        pr = 0;

        if (zichara)
            pr += z->getPrice();

        if (month < 1 || month > 12 || day < 1 || day > 31)
            throw -1;

        if ((month >= 4 && month <= 8) || month == 9 && day == 1)
            pr += prices[0];
        else
            pr += prices[1];
    }
};


int main()
{

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15], mestoZichara[30], klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin >> imePlaninarskiDom;
    for (int i = 0; i < 2; i++) cin >> ceni[i];
    cin >> klasa;
    cin >> daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara)
    {
        cin >> mestoZichara >> dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom, ceni, klasa);
        Zichara r(mestoZichara, dnevnakartaZichara);
        pom.setZichara(r);
        p = pom;
    }
    else
    {
        PlaninarskiDom *pok = new PlaninarskiDom(imePlaninarskiDom, ceni, klasa);
        p = *pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den, mesec;
    cin >> den >> mesec;
    try
    {
        p.presmetajDnevenPrestoj(den, mesec, cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout << "Informacii za PlaninarskiDomot:" << endl;
        cout << p;
        if (p <= 'D')
            cout << "Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout << "Cenata za " << den << "." << mesec << " e " << cena; //се печати цената за дадениот ден и месец
    }
    catch (int)
    {
        cout << "Mesecot ili denot e greshno vnesen!";
    }

    return 0;
}
