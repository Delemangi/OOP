/*
Да се имплементира класа Trud во која се чуваат информации за: (5 поени)

вид на труд (еден знак и тоа C за конференциски труд, J за труд во списание)
година на издавање (цел број).
Да се имплементира класа Student во која се чува: (5 поени)

името на студентот (низа од најмногу 30 карактери)
индекс (цел број)
година на упис (цел број)
листа на оцени од положени предмети (низа од цели броеви)
број на положени предмети (цел број)
За оваа класа да се имплементираат следните методи:

функција rang() што пресметува просек од положените испити на студентот (5 поени)
оператор << за печатење на студентот во формат: (5 поени)

Индекс Име Година на упис ранг

Да се имплементира класа PhDStudent во која покрај основните информации за студентот дополнително се чува: (5 поени)

листа од објавени трудови (динамички резервирана низа од објекти од класата Trud)
бројот на трудови (цел број)
Во оваа класа да се препокрие соодветно функцијата rang() така што на просекот од положените испити ќе се додаде и збирот од поените од објавените трудови на PhD студентот. Во зависност од видот на трудот, секој универзитет има посебен начин на бодување на трудовите. Начинот на бодување е ист за сите PhD студенти. Иницијално да се смета дека конференциски труд се бодува со 1 поен, а труд во списание со 3 поени. Универзитетот има можност да ги менува вредностите на бодовите. (5 поени + 5 поени)

За оваа класа да се обезбеди:

оператор += за додавање нов објект од класата Trud во листата (5 поени). Ако се направи обид да се внесе труд што е издаден порано од годината на упис на студентот да се фрли исклучок (објект од класата Exception). Справувањето со исклучокот треба да се реализира во главната функција main каде што е потребно, но и во конструктор ако е потребно. Ако бил генериран исклучок треба да се отпечати соодветна порака за грешка "Ne moze da se vnese dadeniot trud", а новиот труд нема да се внесе во листата на трудови од студентот. (10 поени)
Напомена: Сите променливи на класите се чуваат како приватни.

Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)
*/
#include <iostream>
#include <cstring>

using namespace std;

class Exception
{
public:
    static void message()
    {
        cout << "Ne moze da se vnese dadeniot trud" << endl;
    }
};

class Trud
{
private:
    char tip;
    int god;
public:
    Trud(char tip = 0, int god = 0)
    {
        this->tip = tip;
        this->god = god;
    }

    friend istream &operator>>(istream &in, Trud &t)
    {
        in >> t.tip >> t.god;

        return in;
    }

    char getTip() const
    {
        return tip;
    }

    int getGod() const
    {
        return god;
    }
};

class Student
{
private:
    char ime[30];
    int indeks;
    int upis;
    int oceni[50];
    int n;
public:
    Student(const char *ime = "", int indeks = 0, int upis = 0, int *oceni = NULL, int n = 0)
    {
        strcpy(this->ime, ime);
        this->indeks = indeks;
        this->upis = upis;
        for (int i = 0; i < n; ++i)
            this->oceni[i] = oceni[i];
        this->n = n;
    }

    friend ostream &operator<<(ostream &out, const Student &s)
    {
        out << s.indeks << " " << s.ime << " " << s.upis << " " << s.rang() << endl;

        return out;
    }

    virtual double rang() const
    {
        double s = 0;

        for (int i = 0; i < n; i++)
            s += oceni[i];

        return s / n;
    }

    int getUpis() const
    {
        return upis;
    }

    int getIndeks() const
    {
        return indeks;
    }
};

class PhDStudent : public Student
{
private:
    Trud *t;
    int n_tr;
    static int c;
    static int j;
public:
    PhDStudent(const char *ime = "", int indeks = 0, int upis = 0, int *oceni = NULL, int n = 0, Trud *t = NULL,
               int n_tr = 0) : Student(ime, indeks, upis, oceni, n)
    {
        this->t = new Trud[n_tr];
        for (int i = 0; i < n_tr; ++i)
            try
            {
                if (t[i].getGod() < upis)
                    throw Exception();
                else
                    this->t[i] = t[i];
            }
            catch (Exception)
            {
                Exception::message();
            }
        this->n_tr = n_tr;
    }

    ~PhDStudent()
    {
        delete[] t;
    }

    PhDStudent &operator+=(Trud &tr)
    {
        if (tr.getGod() < getUpis())
            throw Exception();

        Trud *temp = new Trud[n_tr + 1];

        for (int i = 0; i < n_tr; ++i)
            temp[i] = t[i];
        temp[n_tr] = tr;

        delete[] t;
        t = temp;
        n_tr++;

        return *this;
    }

    static void setC(int a)
    {
        c = a;
    }

    static void setJ(int a)
    {
        j = a;
    }

    double rang() const
    {
        double s = Student::rang();

        for (int i = 0; i < n_tr; ++i)
            if (t[i].getTip() == 'j' || t[i].getTip() == 'J')
                s += j;
            else if (t[i].getTip() == 'c' || t[i].getTip() == 'C')
                s += c;

        return s;
    }
};

int PhDStudent::c = 1;
int PhDStudent::j = 3;

int main()
{
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1)
    {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++)
        {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2)
    {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++)
        {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0)
            {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else
            {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++)
                {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        bool found = false;

        for (int i = 0; i < m; ++i)
            if (dynamic_cast<PhDStudent *>(niza[i]) && niza[i]->getIndeks() == indeks)
            {
                *dynamic_cast<PhDStudent *>(niza[i]) += t;
                found = true;
            }

        if (!found)
            cout << "Ne postoi PhD student so indeks " << indeks << endl;

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3)
    {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++)
        {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0)
            {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else
            {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++)
                {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        for (int i = 0; i < m; ++i)
            if (dynamic_cast<PhDStudent *>(niza[i]) && niza[i]->getIndeks() == indeks)
                *dynamic_cast<PhDStudent *>(niza[i]) += t;

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4)
    {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++)
        {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5)
    {
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++)
        {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0)
            {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else
            {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++)
                {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        try
        {
            for (int i = 0; i < m; ++i)
                if (dynamic_cast<PhDStudent *>(niza[i]) && niza[i]->getIndeks() == indeks)
                    *dynamic_cast<PhDStudent *>(niza[i]) += t;
        }
        catch (Exception)
        {
            Exception::message();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6)
    {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++)
        {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0)
            {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else
            {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++)
                {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setC(conf);
        PhDStudent::setJ(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}