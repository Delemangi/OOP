/*
Во оваа задача треба да се внесат и испечатат податоци за автомобили.

За еден автомобил (објект од класата Car) се чуваат следниве податоци:

сопственик (објект од класата Person)
датум на купување (објект од класата Date)
цена (float price), предодредена вредност 0
За класата Car потребно е да се напише метод за печатење print() и метод за добивање на цената getPrice().

Класата Date содржи три цели броеви (int year, month, day) кои претставуваат датум. За неа треба да се напише метод за печатење print(), предодреден (default) конструктор, конструктор со параметри и конструктор за копирање.

Класата Person содржи име и презиме (низи од максимум 20 знаци, со предодредени вредности not specified), предодреден конструктор, конструктор со параметри и метод за печатење print().

Методот за печатење кај класата Person изгледа вака: [name] [lastName].

Методот за печатење кај класата Date изгледа вака: [year].[month].[day].

Методот за печатење кај класата Car изгледа вака:

owner.print()

date.print()

Price: [price]

Покрај тоа, потребно е да се напише метод cheaperThan(Car* cars, int numCars, float price) кој ќе ги испечати сите објекти Car од низата cars со големина numCars чија цена е помала од price.
*/
#include<iostream>
#include<cstring>

using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;
public:
    Date()
    {
        day = 0;
        month = 0;
        year = 0;
    }

    Date(int day, int month, int year)
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    Date(const Date &d) : Date(d.day, d.month, d.year)
    {}

    void print() const
    {
        cout << day << "." << month << "." << year << endl;
    }
};

class Person
{
private:
    char name[20];
    char surname[20];
public:
    Person()
    {
        strcpy(name, "not specified");
        strcpy(surname, "not specified");
    }

    Person(char *name, char *surname)
    {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
    }

    Person(Person &p) : Person(p.name, p.surname)
    {}

    void print()
    {
        cout << name << " " << surname << endl;
    }
};

class Car
{
private:
    Person p;
    Date d;
    float price;
public:
    Car() = default;

    Car(Person p, Date d, float price)
    {
        this->p = p;
        this->d = d;
        this->price = price;
    }

    void print()
    {
        p.print();
        d.print();
        cout << "Price: " << price << endl;
    }

    float getPrice() const
    {
        return price;
    }
};

void cheaperThan(Car *cars, int n, float price)
{
    for (int i = 0; i < n; i++)
        if (cars[i].getPrice() < price)
            cars[i].print();
}

int main()
{
    char name[20];
    char lastName[20];
    int year;
    int month;
    int day;
    float price;

    int testCase;
    cin >> testCase;

    if (testCase == 1)
    {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);

        cin >> year;
        cin >> month;
        cin >> day;
        Date date(year, month, day);

        cin >> price;
        Car car(lik, date, price);

        car.print();
    }
    else if (testCase == 2)
    {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);

        cin >> year;
        cin >> month;
        cin >> day;
        Date date(Date(year, month, day));

        cin >> price;
        Car car(lik, date, price);
        car.print();
    }
    else
    {
        int numCars;
        cin >> numCars;

        Car cars[10];
        for (int i = 0; i < numCars; i++)
        {
            cin >> name;
            cin >> lastName;
            Person lik(name, lastName);

            cin >> year;
            cin >> month;
            cin >> day;
            Date date(year, month, day);

            cin >> price;
            cars[i] = Car(lik, date, price);
        }
        float priceLimit;
        cin >> priceLimit;
        cheaperThan(cars, numCars, priceLimit);
    }


    return 0;
}