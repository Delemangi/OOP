/*
Креирајте класа Rabotnik која во себе содржи:

ime (низа од максимум 30 знаци)
prezime (низа од максимум 30 знаци)
plata (целобројна вредност)
За оваа класа да се креираат default конструктор и конструктор со аргументи. Да се имплементираат и следните методи:

getPlata() која ја враќа платата на работникот
pecati() која ги печати името, презимето и платата.
Креирајте класа Fabrika во која има:

rabotnik [100] (низа од вработени)
brojVraboteni (целобројна вредност)
Во класата имплементирајте ги следните методи:

pecatiVraboteni() ги печати сите вработени
pecatiSoPlata(int plata) ги печати сите вработени со плата поголема или еднаква на дадената во аргументот(int plata).
Во главната функција се внесуваат податоци за n вработени. Притоа прво се внесува n, па податоците за сите n вработени. Во последниот ред се чита минималната плата.

На излез да се прикажат прво сите вработени, а потоа само оние со поголема плата од минималната. Треба да се корисатат методите pecatiVraboteni и pecatiSoPlata!
*/
#include <bits/stdc++.h>

using namespace std;

class Rabotnik
{
private:
    char name[30];
    char surname[30];
    int salary;
public:
    Rabotnik()
    {
        *name = '\0';
        *surname = '\0';
        salary = 0;
    }

    Rabotnik(char *name, char *surname, int salary)
    {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->salary = salary;
    }

    int getSalary() const
    {
        return salary;
    }

    void print()
    {
        cout << name << " " << surname << " " << salary << endl;
    }
};

class Fabrika
{
private:
    Rabotnik r[100];
    int n;
public:
    Fabrika(Rabotnik *r, int n)
    {
        this->n = n;
        for (int i = 0; i < n; i++)
            this->r[i] = r[i];
    }

    void print()
    {
        cout << "Site vraboteni: " << endl;

        for (int i = 0; i < n; i++)
            r[i].print();
    }

    void printSalary(int salary)
    {
        cout << "Vraboteni so plata povisoka od " << salary << " :" << endl;

        for (int i = 0; i < n; i++)
            if (r[i].getSalary() > salary)
                r[i].print();
    }
};

int main()
{
    int n;
    int salary;
    int min;
    char name[30];
    char surname[30];
    Rabotnik r[100];

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> name >> surname >> salary;
        r[i] = Rabotnik(name, surname, salary);
    }
    cin >> min;

    Fabrika f(r, n);

    f.print();
    f.printSalary(min);

    return 0;
}