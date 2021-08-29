/*
Да се имплементира класа List во којашто ќе се чуваат информации за:

броеви што се дел од листата (динамички алоцирана низа од цели броеви)
бројот на броеви што се дел од листата
За класата да се дефинираат следните методи:

конструктор (со аргументи), copy-конструктор, деструктор, оператор =
void pecati()метод што ќе ги печати информациите за листата во форматот: [број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
int sum() метод што ја враќа сумата на елементите во листата
double average() метод што ќе го враќа просекот на броевите во листата
Дополнително, креирајте класата ListContainer, во која што ќе се чуваат информации за:

низа од листи (динамички алоцирана низа од објекти од класата List)
број на елементи во низата од листи (цел број)
број на обиди за додавање на листа во контејнерот (цел број првично поставен на нула)
За класата потребно е да ги дефинирате следните методи:

конструктор (default), copy-конструктор, деструктор, оператор =
void pecati() метод што ќе ги печати информациите за контејнерот во форматот: List number: [реден број на листата] List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
доколку контејнерот е празен се печати само порака The list is empty.
void addNewList(List l) метод со којшто се додава листа во контејнерот
Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
int sum() метод што ја враќа сумата на сите елементи во сите листи
double average() метод што го враќа просекот на сите елементи во сите листи во контејнерот
*/
#include <iostream>

using namespace std;

int MAX = 50;

class List
{
private:
    int *a;
    int n;
public:
    List()
    {
        a = nullptr;
        n = 0;
    }

    List(const int *a1, int n1)
    {
        a = new int[n1];
        for (int i = 0; i < n1; i++)
            a[i] = a1[i];
        n = n1;
    }

    List(const List &l1) : List(l1.a, l1.n)
    {}

    ~List()
    {
        delete[] a;
    }

    List &operator=(const List &other)
    {
        if (this == &other)
            return *this;

        delete[] a;
        a = new int[other.n];

        for (int i = 0; i < other.n; i++)
            a[i] = other.a[i];

        n = other.n;

        return *this;
    }

    void pecati()
    {
        cout << n << ": ";
        for (int i = 0; i < n; i++)
            cout << a[i] << " ";

        cout << "sum: " << sum() << " average: " << average() << endl;
    }

    int sum()
    {
        int s = 0;

        for (int i = 0; i < n; i++)
            s += a[i];

        return s;
    }

    double average()
    {
        return (double) sum() / n;
    }

    int getN() const
    {
        return n;
    }
};

class ListContainer
{
private:
    List *l;
    int n;
    int obidi;
public:
    ListContainer()
    {
        l = new List[MAX];
        n = 0;
        obidi = 0;
    };

    ListContainer(List *l1, int n1, int obidi1)
    {
        l = new List[MAX];

        for (int i = 0; i < n; i++)
            l[i] = l1[i];
        n = n1;
        obidi = obidi1;
    }

    ListContainer(ListContainer &l1) : ListContainer(l1.l, l1.n, l1.obidi)
    {}

    ~ListContainer()
    {
        delete[] l;
    }

    ListContainer &operator=(const ListContainer &other)
    {
        if (this == &other)
            return *this;

        delete[] l;
        l = new List[MAX];

        for (int i = 0; i < other.n; i++)
            l[i] = other.l[i];
        n = other.n;
        obidi = other.obidi;

        return *this;
    }

    void print()
    {
        if (n == 0)
            cout << "The list is empty" << endl;
        else
        {
            for (int i = 0; i < n; i++)
            {
                cout << "List number: " << i + 1 << " List info: ";
                l[i].pecati();
            }
            cout << "Sum: " << sum() << " Average: " << average() << endl;
            cout << "Successful attempts: " << n << " Failed attempts: " << obidi - n << endl;
        }
    }

    void addNewList(List l1)
    {
        obidi++;

        for (int i = 0; i < n; i++)
            if (l[i].sum() == l1.sum())
                return;

        l[n] = l1;
        n++;
    }

    int sum()
    {
        int s = 0;

        for (int i = 0; i < n; i++)
            s += l[i].sum();

        return s;
    }

    double average()
    {
        int a = 0;

        for (int i = 0; i < n; i++)
            a += l[i].getN();

        return (double) sum() / a;
    }
};

int main()
{

    ListContainer lc;
    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        int n;
        int niza[100];

        cin >> n;

        for (int j = 0; j < n; j++)
        {
            cin >> niza[j];

        }

        List l = List(niza, n);

        lc.addNewList(l);
    }


    int testCase;
    cin >> testCase;

    if (testCase == 1)
    {
        cout << "Test case for operator =" << endl;
        ListContainer lc1;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1 = lc;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1.sum();
        lc1.average();

    }
    else
    {
        lc.print();
    }
}