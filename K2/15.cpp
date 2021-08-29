/*
Дадена е дел од дефиниција на класата StudentKurs. За секој студент кој слуша некој курс се чуваат информации за неговото име (низа од знаци), оценка од писмен дел (цел број) и дали студентот сака да биде испрашуван и усно (булова променлива).

Оцената за писмениот дел е вредност од 1 до МАX. MAX има почетна вредност 10 која е иста е за сите и може да се промени со соодветна функција setMAX(). (5 поени)

Кај оние студенти кои сакаат да бидат испрашувани усно и добиваат и описна оценка. Имплементирај соодветна класа StudentKursUsno во која се чуваат дополнителни информации за описна оценка на усното испрашување (динамичко алоцирана низа од знаци). Описни оценки може да бидат: odlicen, dobro, losho.... Ако описната оценка е odlicen тогаш оцената ќе биде најмногу за оценки 2 повисока од оценката од писмениот дел, ако е dobro оценката ќе биде најмногу за 1 повисока, а ако е losho за 1 пониска. Ако студентот добие некоја друга описна оценка, неговата оценка ќе остане иста со оценката од писмениот дел.

Во класите StudentKurs и StudentKursUsno треба да се имплементираат потребните конструктори, функции за поставување и преземање и деструктор. (5 поени)

За сите објекти од класите треба да се обезбедат следните функции:

преоптоварен оператор << во кој се печатат информации за студентот на курсот во формат: Ime --- ocenka (5 поени)
оcenka() – ја враќа оценката на студентот на курсот (5 поени)
Во класата StudentKursUsno дефинирај ја функцијата:

преоптоварен оператор += за поставување на описна оценка на студентот(5 поени)
Ако се направи обид да се внесе описна оценка во која покрај букви има и други знаци треба да се фрли исклучок (објект од класата BadInputException). Фатете го исклучокот во главната функција каде што е потребно. Откако ќе го фатите отпечатете соодветна порака за грешка (Greshna opisna ocenka) и справете се со исклучокот така што тие знаци ќе отстранат од стрингот со описната оценка (ако описната оценка била dо1ba0r ќе се промени во dоbar). (10 поени)

Дадена е дел од дефиницијата на класата KursFakultet во која се чуваат информаци за името на курсот (низа од 30 знаци) и за студентите запишани на курсот (низа од 20 покажувачи кон класата StudentKurs) како и бројот на студенти запишани на курсот.

Еден студент кој запишал некој курс ќе го положи курсот ако има барем MINOCENKA. Вредноста MINOCENKA е членка на класата StudentKurs и има фиксна вредност 6 која не може да се промени. (5 поени)

Во класата KursFakultet имплементирај ги функциите:

функција pecatiStudenti() во која се печатат сите студенти кои го положиле курсот, секој во посебен ред. Претходно во првиот ред се печати: Kursot XXXXX go polozile: (5 поени).

функција postaviOpisnaOcenka(char * ime, char* opisnaOcenka) во која на студентот на курсот со даденото име му се поствува описна оценка. Ако тоа не е можно функцијата не прави ништо (15 поени).

Комплетна функционалност (5 поени)
*/
#include<iostream>
#include<cstring>

using namespace std;

class BadInputException
{
public:
    static void message()
    {
        cout << "Greshna opisna ocenka" << endl;
    }
};

class StudentKurs
{
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
    static int MAX;
public:
    StudentKurs(const char *ime, const int finalenIspit)
    {
        strcpy(this->ime, ime);
        this->ocenka = finalenIspit;
        this->daliUsno = false;
    }

    StudentKurs(const StudentKurs &s)
    {
        strcpy(this->ime, s.ime);
        this->ocenka = s.ocenka;
        this->daliUsno = s.daliUsno;
    }

    virtual ~StudentKurs()
    {}

    friend ostream &operator<<(ostream &out, const StudentKurs &s)
    {
        out << s.ime << " --- " << s.getOcenka() << endl;

        return out;
    }

    static void setMAX(int a)
    {
        MAX = a;
    }

    virtual int getOcenka() const
    {
        return ocenka;
    }

    const char *getIme() const
    {
        return ime;
    }

    bool getDaliUsno() const
    {
        return daliUsno;
    }

    static int getMax()
    {
        return MAX;
    }
};

int StudentKurs::MAX = 10;

class StudentKursUsno : public StudentKurs
{
private:
    char *usno;
public:
    StudentKursUsno(const char *ime, const int finalenIspit) : StudentKurs(ime, finalenIspit)
    {
        this->usno = new char[10];
        *usno = '\0';
        daliUsno = true;
    }

    StudentKursUsno(const StudentKursUsno &s) : StudentKurs(s)
    {
        this->usno = new char[10];
        *usno = '\0';
        daliUsno = true;
    }

    ~StudentKursUsno()
    {
        delete[] usno;
    }

    StudentKursUsno &operator+=(char *o)
    {
        for (int i = 0; i < strlen(o); ++i)
            if (!isalpha(o[i]))
                throw BadInputException();

        delete[] usno;
        usno = new char[10];
        strcpy(usno, o);

        return *this;
    }

    int getOcenka() const
    {
        if (!strcmp(usno, "odlicen"))
            if (StudentKurs::getOcenka() + 2 < MAX)
                return StudentKurs::getOcenka() + 2;
            else
                return MAX;
        else if (!strcmp(usno, "dobro"))
            if (StudentKurs::getOcenka() + 1 < MAX)
                return StudentKurs::getOcenka() + 1;
            else
                return MAX;
        else if (!strcmp(usno, "losho"))
            if (StudentKurs::getOcenka() - 1 < MAX)
                return StudentKurs::getOcenka() - 1;
            else
                return MAX;
        else
            return StudentKurs::getOcenka();
    }
};

class KursFakultet
{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
    const static int MINOCENKA = 6;
public:
    KursFakultet(char *naziv, StudentKurs **studenti, int broj)
    {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++)
        {
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno())
            {
                this->studenti[i] = new StudentKursUsno(*dynamic_cast<StudentKursUsno *>(studenti[i]));
            }
            else this->studenti[i] = new StudentKurs(*studenti[i]);
        }
        this->broj = broj;
    }

    ~KursFakultet()
    {
        for (int i = 0; i < broj; i++) delete studenti[i];
    }

    void pecatiStudenti() const
    {
        cout << "Kursot " << naziv << " go polozile:" << endl;
        for (int i = 0; i < broj; ++i)
            if (studenti[i]->getOcenka() >= MINOCENKA)
                cout << *studenti[i];
    }

    void postaviOpisnaOcenka(char *ime, char *o)
    {
        for (int i = 0; i < broj; ++i)
            if (studenti[i]->getDaliUsno())
                if (!strcmp(ime, studenti[i]->getIme()))
                    *dynamic_cast<StudentKursUsno *>(studenti[i]) += o;
    }
};

int main()
{

    StudentKurs **niza;
    int n, m, ocenka;
    char ime[30], opisna[10];
    bool daliUsno;
    cin >> n;
    niza = new StudentKurs *[n];
    for (int i = 0; i < n; i++)
    {
        cin >> ime;
        cin >> ocenka;
        cin >> daliUsno;
        if (!daliUsno)
            niza[i] = new StudentKurs(ime, ocenka);
        else
            niza[i] = new StudentKursUsno(ime, ocenka);
    }

    KursFakultet programiranje("OOP", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete[] niza;
    cin >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> ime >> opisna;

        try
        {
            programiranje.postaviOpisnaOcenka(ime, opisna);
        }
        catch (BadInputException)
        {
            BadInputException::message();

            for (int j = 0; j < strlen(opisna); ++j)
                if (!isalpha(opisna[j]))
                {
                    for (int k = j; k < strlen(opisna) - 1; ++k)
                        opisna[k] = opisna[k + 1];

                    opisna[strlen(opisna) - 1] = '\0';
                }

            programiranje.postaviOpisnaOcenka(ime, opisna);
        }
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
