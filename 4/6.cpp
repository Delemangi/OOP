/*
Фирмата FINKI Cloud има потреба од решение за управување со image датотеките од различните оперативни системи кои ги користат при сетирање на нови сервери. За таа цел потребно е да се дефинираат следниве класи:

OperativenSistem
Во класата OperativenSistem треба да се чуваат следниве податоци:

име на оперативниот систем (динамички алоцирана низа од знаци)
верзија (float)
тип (енумерација со можни вредности LINUX, UNIX, WINDOWS)
големина (во GB) (float)
Дополнително, во рамките на класата потребно е да се дефинира:

конструктори со и без параметри
copy constructor
destructor
преоптоварување на операторот =
метод за печатење на информациите - void pecati() (видете го излезот од тест примерите за структурата)
метод за проверка на еднаквост помеѓу два оперативни системи (два оперативни системи се еднакви ако имаат исто име, верзија, тип и големина) - bool ednakviSe(const OperativenSistem &os)
метод за споредба на верзии помеѓу два оперативни система - int sporediVerzija(const OperativenSistem &os), кој ќе враќа 0 доколку верзиите се исти, -1 доколку верзијата на оперативниот систем од аргументот е поголема и 1 во преостанатиот случај.
метод за проверка дали два оперативни системи се од иста фамилија. Два оперативни системи се од иста фамилија доколку имаат исто име и се од ист тип. bool istaFamilija(const OperativenSistem &sporedba)
Repozitorium
Во класата Repozitorium треба да се чуваат следниве податоци:

име на репозиториумот (низа од 20 знака)
динамички алоцирана низа од OperativenSistem
број на оперативни системи кои моментално се наоѓаат во репозиториумот (int)
Дополнително, во рамките на класата потребно е да се дефинира:

конструктор Repozitorium(const char *ime)
деструктор
метод void pecatiOperativniSistemi() кој ќе ги печати сите оперативни системи кои се дел од репозиториумот
метод void izbrishi(const OperativenSistem &operativenSistem) кој ќе го избрише оперативниот систем проследен како аргумент, доколку тој се наоѓа во репозиториумот. Да се користи методот ednakviSe за споредба на два оперативни система.
метод за додавање на оперативен систем (void dodadi(const OperativenSistem &nov)) кој ќе го има следново однесување:
Доколку веќе постои оперативен систем од иста фамилија (да се користи методот за проверка на фамилија) кој е постар од проследениот оперативен систем, тогаш постоечкиот оперативен систем се заменува со новиот.
Во секој друг случај, проследениот оперативен систем се додава како дополнителен во репозиториумот.
*/
#include <iostream>
#include <cstring>

using namespace std;

enum Tip
{
    LINUX, UNIX, WINDOWS
};

class OperativenSistem
{
private:
    char *name;
    float version;
    Tip OS;
    float size;
public:
    OperativenSistem()
    {
        name = new char[100];
    }

    OperativenSistem(char *name1, float version1, Tip OS1, float GB1)
    {
        this->name = new char[100];
        this->version = version1;
        this->OS = OS1;
        this->size = GB1;

        strcpy(name, name1);
    }

    OperativenSistem(const OperativenSistem &other) : OperativenSistem(other.name, other.version, other.OS, other.size)
    {}

    ~OperativenSistem()
    {
        delete[] this->name;
    }

    OperativenSistem &operator=(const OperativenSistem &other)
    {
        if (this == &other)
            return *this;

        strcpy(this->name, other.name);
        this->version = other.version;
        this->OS = other.OS;
        this->size = other.size;

        return *this;
    }

    void pecati()
    {
        cout << "Ime: " << this->name << " Verzija: " << this->version << " Tip: " << OS << " Golemina:" << size << "GB"
             << endl;
    }

    bool ednakviSe(const OperativenSistem &other)
    {
        if (strcmp(this->name, other.name) == 0 && this->version == other.version && this->OS == other.OS &&
            this->size == other.size)
            return true;
        return false;
    }

    int sporediVerzija(const OperativenSistem &other)
    {
        if (this->version == other.version)
            return 0;
        else if (this->version > other.version)
            return 1;
        else
            return -1;
    }

    bool istaFamilija(const OperativenSistem &other)
    {
        if (strcmp(this->name, other.name) == 0 && this->OS == other.OS)
            return true;
        return false;
    }

    void setVersion(float f)
    {
        this->version = f;
    }

    float getVersion()
    {
        return version;
    }

    void setSize(float size1)
    {
        size = size1;
    }

    float getSize()
    {
        return size;
    }
};

class Repozitorium
{
private:
    char name[20];
    OperativenSistem *os;
    int n;
public:
    Repozitorium()
    {
        os = new OperativenSistem[10];
    }

    Repozitorium(char *name1)
    {
        strcpy(this->name, name1);
        os = new OperativenSistem[10];
        n = 1;
    }

    ~Repozitorium()
    {
        delete[] this->os;
    }

    void pecatiOperativniSistemi()
    {
        cout << "Repozitorium: " << this->name << endl;
        for (int i = 1; i < n; i++)
            this->os[i].pecati();
    }

    void izbrishi(const OperativenSistem &other)
    {
        for (int i = 0; i < n; i++)
            if (this->os[i].ednakviSe(other))
            {
                for (int j = i; j < n - 1; j++)
                    this->os[j] = os[j + 1];

                n--;
                break;
            }
    }

    void dodadi(OperativenSistem other)
    {
        for (int i = 0; i < n; i++)
            if (this->os[i].istaFamilija(other) && this->os[i].sporediVerzija(other) == -1)
            {
                this->os[i].setVersion(other.getVersion());
                this->os[i].setSize(other.getSize());
                return;
            }

        this->os[n] = other;
        n++;
    }
};

int main()
{
    char repoName[20];
    cin >> repoName;
    Repozitorium repozitorium = Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin >> brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i < brojOperativniSistemi; i++)
    {
        cin >> ime;
        cin >> verzija;
        cin >> tip;
        cin >> golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin >> ime;
    cin >> verzija;
    cin >> tip;
    cin >> golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
    cout << "=====Brishenje na operativen sistem=====" << endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}