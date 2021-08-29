/*
Сите елементи кои ги превезуваат камионите имаат одредена маса. Имплементирајте апстрактна класа ImaMasa од која што ќе наследуваат сите класи кои имаат маса. Во оваа класа треба да се дефинираат методите:

double vratiMasa() враќа маса изразена во kg
void pecati() печати информации за соодветниот објект
Нека еден камион превезува пијалоци и тоа: пакет сокови и пакет вина. Да се дефинираат класите PaketSok и PaketVino кои ги имплементираат методите од апстрактната класа ImaMasa. При тоа да се земе предвид дека класите PaketSok и PaketVino се изведени од класата PaketPijalok. Притоа да се земат дадените податоци:

Класа PaketPijalok:

членови:
volumenEden double
kolicina int
методи:
double vratiMasa()
void pecati()
int getKolicina()
Класа PaketSok:

членови:
volumenEden double
kolicina int
daliGaziran bool
методи:
double vratiMasa()
void pecati()
Класа PaketVino:

членови:
volumenEden double
kolicina int
procentAlkohol double
методи:
double vratiMasa()
double getProcentAlkohol()
void pecati()
Еден пијалок има маса пресметана како производ на волуменот и густината (0.8kg/dm3) и масата на амбалажата (0.2kg). Овие податоци за густината и за масата на амбалажата да се стават како статички податоци за класата PaketPijalok. Масата на пакетот е производ на масата на еден пијалок и количината на пијалоци која ја има во пакетот. Соковите кои не се газирани имаат дополнителна маса од 0.1kg по пијалок. За вината, масата се добива како производ од масата на пакетот пресметан по правилата за секој пијалок помножен со коефициентот: (0.9+procentAlkohol).

Покрај овие класи, да се имплементира класата Kamion. За еден камион се чуваат информации за:

регистрацијата char*
возачот char*
елементите кои ги превезува камионот (низа од покажувачи од ImaMasa)
Во класата Kamion покрај методите set и get дефинирајте ги и следните методи:

Kamion(char* ) конструктор со кој се генерира празен камион (без товар) и само возач
void registriraj(char*) се додава регистрацијата на камионот
void dodadiElement(ImaMasa) се додава нов елемент во камионот
double vratiVkupnaMasa() се враќа вкупната маса на товарот кој го пренесува камионот
void pecati() се печатат сите елементи во камионот заедно со регистрацијата и името на возачот
Kamion pretovar(char* , char* ) се врши претовар во нов камион, но во новиот покрај тоа што се менуваат регистрацијата и името на возачот (аргументи), се отстранува пакетот со најголема маса.
Со помош на правилата за справување со исклучоци да се модифицира програмата така што ќе се запазат следните правила: - Регистрацијата има 8 карактери, така што првите два и последните два мора да бидат букви. Да се определи каде ќе се фрли соодветниот исклучок. Онаму каде што ќе се фати исклучокот, ќе се отпечати "Pogresno vnesena registracija!".
*/
#include <iostream>
#include <cstring>

using namespace std;

class RegistrationErrorException
{
private:
    char *errorMessage;
public:
    RegistrationErrorException(const char *errorMessage)
    {
        this->errorMessage = new char[strlen(errorMessage) + 1];
        strcpy(this->errorMessage, errorMessage);
    }

    RegistrationErrorException(const RegistrationErrorException &ree)
    {
        this->errorMessage = new char[strlen(ree.errorMessage) + 1];
        strcpy(this->errorMessage, ree.errorMessage);
    }

    RegistrationErrorException &operator=(const RegistrationErrorException &ree)
    {
        if (this != &ree)
        {
            delete[] this->errorMessage;
            this->errorMessage = new char[strlen(ree.errorMessage) + 1];
            strcpy(this->errorMessage, ree.errorMessage);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const RegistrationErrorException &ree)
    {
        return out << ree.errorMessage << endl;
    }

    ~RegistrationErrorException()
    { delete[] errorMessage; }
};

class ImaMasa
{
public:
    virtual const double vratiMasa() const = 0;

    virtual const void pecati() const = 0;

    virtual ~ImaMasa()
    {}
};

class PaketPijalok : virtual public ImaMasa
{
protected:
    static const double gustina;
    static const double masaNaAmbalazha;
    double volumenEden;
    int kolicina;
public:
    PaketPijalok(const double volumenEden, const int kolicina)
    {
        this->volumenEden = volumenEden;
        this->kolicina = kolicina;
    }

    const double vratiMasa() const
    {
        return (volumenEden * gustina + masaNaAmbalazha) * getKolicina();
    }

    const int getKolicina() const
    {
        return kolicina;
    }

    virtual ~PaketPijalok()
    {}
};

const double PaketPijalok::gustina = 0.8;
const double PaketPijalok::masaNaAmbalazha = 0.2;

class PaketSok : public PaketPijalok
{
private:
    bool daliGaziran;
public:
    PaketSok(const double volumenEden, const int kolicina, const bool daliGaziran)
            : PaketPijalok(volumenEden, kolicina)
    {
        this->daliGaziran = daliGaziran;
    }

    const void pecati() const
    {
        cout << "Paket sok" << endl;
        cout << "kolicina " << getKolicina() << ", so po " << volumenEden * gustina <<
             " l(dm3)" << endl;
    }

    const double vratiMasa() const
    {
        if (!daliGaziran)
            return PaketPijalok::vratiMasa() + (0.1 * getKolicina());
        return PaketPijalok::vratiMasa();
    }
};

class PaketVino : public PaketPijalok
{
private:
    double procentAlkohol;
public:
    PaketVino(const double volumenEden, const int kolicina, const double procentAlkohol)
            : PaketPijalok(volumenEden, kolicina)
    {
        this->procentAlkohol = procentAlkohol;
    }

    const double vratiMasa() const
    {
        return PaketPijalok::vratiMasa() * (0.9 + procentAlkohol);
    }

    const void pecati() const
    {
        cout << "Paket vino" << endl;
        cout << "kolicina " << getKolicina() << ", " << procentAlkohol * 100 << "% alkohol od po "
             << volumenEden * gustina << " l(dm3)" << endl;
    }

    const double getProcentAlkohol() const
    {
        return procentAlkohol;
    }
};

class Kamion
{
private:
    char *registracija;
    char *vozac;
    ImaMasa *d[5];
    int num_elements;
public:
    Kamion(const char *vozac)
    {
        this->vozac = new char[strlen(vozac) + 1];
        strcpy(this->vozac, vozac);
        this->registracija = NULL;
        this->num_elements = 0;
    }

    Kamion(const char *registracija, const char *vozac)
    {
        this->vozac = new char[strlen(vozac) + 1];
        strcpy(this->vozac, vozac);
        this->registracija = new char[strlen(registracija) + 1];
        strcpy(this->registracija, registracija);
        this->num_elements = 0;
    }

    Kamion(const Kamion &k)
    {
        this->num_elements = k.num_elements;
        this->vozac = new char[strlen(k.vozac) + 1];
        strcpy(this->vozac, k.vozac);
        this->registracija = new char[strlen(k.registracija) + 1];
        strcpy(this->registracija, k.registracija);
        for (int i = 0; i < k.num_elements; ++i)
        {
            this->d[i] = k.d[i];
        }
    }

    Kamion &operator=(const Kamion &k)
    {
        if (this != &k)
        {
            this->num_elements = k.num_elements;

            delete[] this->vozac;
            this->vozac = new char[strlen(k.vozac) + 1];
            strcpy(this->vozac, k.vozac);

            delete[] this->registracija;
            this->registracija = new char[strlen(k.registracija) + 1];
            strcpy(this->registracija, k.registracija);

            for (int i = 0; i < k.num_elements; ++i)
            {
                this->d[i] = k.d[i];
            }
        }
        return *this;
    }

    const void registriraj(const char *registracija)
    {
        this->registracija = new char[strlen(registracija) + 1];
        strcpy(this->registracija, registracija);
    }

    const void dodadiElement(ImaMasa *e)
    {
        d[num_elements++] = e;
    }

    const double vratiVkupnaMasa()
    {
        double vkupno = 0.00;
        for (int i = 0; i < num_elements; ++i)
        {
            vkupno += d[i]->vratiMasa();
        }
        return vkupno;
    }

    const void pecati() const
    {
        cout << "Kamion so registracija " << getRegistracija() << " i vozac " << getVozac()
             << " prenesuva: " << endl;
        for (int i = 0; i < num_elements; ++i)
        {
            d[i]->pecati();
        }
    }

    Kamion &pretovar(const char *registracija, const char *vozac)
    {
        delete[] this->vozac;
        this->vozac = new char[strlen(vozac) + 1];
        strcpy(this->vozac, vozac);

        delete[] this->registracija;
        this->registracija = new char[strlen(registracija) + 1];
        strcpy(this->registracija, registracija);

        ImaMasa *max = d[0];
        for (int i = 1; i < num_elements; ++i)
        {
            if (max->vratiMasa() < d[i]->vratiMasa())
                max = d[i];
        }

        int newLength = 0;
        for (int i = 0, j = 0; i < num_elements; ++i)
        {
            if (d[i]->vratiMasa() != max->vratiMasa())
            {
                d[j++] = d[i];
                newLength++;
            }
        }
        this->num_elements = newLength;
        return *this;
    }

    const char *getVozac() const
    {
        return vozac;
    }

    const char *getRegistracija() const
    {
        return registracija;
    }

    ~Kamion()
    {
        delete[] vozac;
        delete[] registracija;
    }
};

int main()
{
    char ime[20], reg[9];
    double vol;
    int kol;
    bool g;
    double proc;
    int counter;

    cin >> reg;
    cin >> ime;
    try
    {
        counter = 0;
        for (int i = 0; i < strlen(reg); ++i)
        {
            if (isalpha(reg[i]))
                counter++;
        }
        if (counter != 4)
            throw RegistrationErrorException("Pogresno vnesena registracija");
        Kamion A(reg, ime);
        ImaMasa **d = new ImaMasa *[5];
        cin >> vol >> kol;
        cin >> g;
        d[0] = new PaketSok(vol, kol, g);
        cin >> vol >> kol;
        cin >> proc;
        d[1] = new PaketVino(vol, kol, proc);
        cin >> vol >> kol;
        cin >> proc;
        d[2] = new PaketVino(vol, kol, proc);
        cin >> vol >> kol;
        cin >> g;
        d[3] = new PaketSok(vol, kol, g);
        cin >> vol >> kol;
        cin >> proc;
        d[4] = new PaketVino(vol, kol, proc);

        A.dodadiElement(d[0]);
        A.dodadiElement(d[1]);
        A.dodadiElement(d[2]);
        A.dodadiElement(d[3]);
        A.dodadiElement(d[4]);
        A.pecati();
        cout << "Vkupna masa: " << A.vratiVkupnaMasa() << endl;
        cin >> reg;
        cin >> ime;
        try
        {
            counter = 0;
            for (int i = 0; i < strlen(reg); ++i)
            {
                if (isalpha(reg[i]))
                    counter++;
            }
            if (counter != 4)
                throw RegistrationErrorException("Pogresno vnesena registracija");
            Kamion B = A.pretovar(reg, ime);
            B.pecati();
            cout << "Vkupna masa: " << B.vratiVkupnaMasa() << endl;
            for (int i = 0; i < 5; ++i)
                delete d[i];
            delete[] d;
        }
        catch (RegistrationErrorException &ree)
        {
            cout << ree;
        }
    }
    catch (RegistrationErrorException &ree)
    {
        cout << ree;
    }
    return 0;
}