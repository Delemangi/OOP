/*
Да се дефинира класа ParkingPlac во која се чуваат податоци за:

Адреса на плацот (низа од знаци, максимум 20),
Идентификациски број на плацот (динамичка низа од знаци),
Цена за паркирање за 1 час (цел број),
Заработка на паркинг плацот (цел број)
параметри потребни за дополнителниот дел од задачата:

Динамичка низа од класата Avtomobil
Број на паркирани автомобили во даден момент
За потребите на класата да се имплементираат :

соодветни конструктори и деструктор, и потребните get-функции (погледнете ги повиците во main функцијата)
функција pecati() за печатење на податоците за еден паркинг плац во следниот формат:

идентификациски_број адреса - X denari, ако X е заработката на паркинг плацот X не е 0

идентификациски_број адреса , ако X =0

функција platiCasovi(int casovi) која на заработката ја додава платената вредност за дадениот број на часови.

функција daliIstaAdresa(ParkingPlac p) во која се споредува дали дадениот паркинг плац е на иста адреса како паркинг плацот p.
Во дадената main функција прво се внесуваат n паркинг плацеви. Потоа се внесуваат m плаќања и на крај се печатат сите паркинг плацеви од низата кои имаат иста адреса со дадениот паркинг плац (објектот pCentar).

ДОПОЛНИТЕЛНО БАРАЊЕ

Дефинирајте класа Avtomobilво која се чуваат податоците за:

Бојата на автомобилот (низа од знаци, максимум 20)
Брендот на автомобилот (низа од знаци, максимум 20)
Моделот на автомобилот (низа од знаци, максимум 20)
За потребите на класата ќе треба да :

Се имплементира конструктор
Да го преоптоварите assignment operator-от
Понатака да пишете метод за класата ParkingPlac наречен parkirajVozilo(Avtomobil novoVozilo), неговата цел ќе биде да се паркира ново возило на паркингот во кој се повикува методот.

На крај ќе треба да се испечатат паркираните возила во еден паркинг преку методот pecatiParkiraniVozila() кој исто така треба да биде имплементиран во класата ParkingPlac.

Ориентирајте се според дадениот код во main методот за како се ова треба да го имплементирате.
*/
#include <bits/stdc++.h>

using namespace std;

class Avtomobil
{
private:
    char color[20];
    char brand[20];
    char model[20];
public:
    Avtomobil()
    {
        *color = '\0';
        *brand = '\0';
        *model = '\0';
    }

    Avtomobil(char *color, char *brand, char *model)
    {
        strcpy(this->color, color);
        strcpy(this->brand, brand);
        strcpy(this->model, model);
    }

    Avtomobil &operator=(const Avtomobil &other)
    {
        if (this == &other)
            return *this;

        strcpy(color, other.color);
        strcpy(brand, other.brand);
        strcpy(model, other.model);

        return *this;
    }

    const char *getColor() const
    {
        return color;
    }

    const char *getBrand() const
    {
        return brand;
    }

    const char *getModel() const
    {
        return model;
    }
};

class ParkingPlac
{
private:
    char address[50];
    char *id;
    int price;
    int profit;
    int n;
    Avtomobil *a;
public:
    ParkingPlac()
    {
        a = new Avtomobil[50];
        id = new char[50];
        *address = '\0';
        price = 0;
        profit = 0;
        n = 0;
    }

    ParkingPlac(char *address, char *id, int price)
    {
        a = new Avtomobil[50];
        this->id = new char[50];
        strcpy(this->address, address);
        strcpy(this->id, id);
        this->price = price;
        profit = 0;
        n = 0;
    }

    //~ParkingPlac()
    //{
    //    delete[] id;
    //    delete[] a;
    //}

    void platiCasovi(int c)
    {
        profit += c * price;
    }

    bool daliIstaAdresa(ParkingPlac p)
    {
        if (!strcmp(address, p.address))
            return true;
        return false;
    }

    void parkirajVozilo(Avtomobil av)
    {
        a[n] = av;
        n++;
    }

    void pecati()
    {
        cout << id << " " << address;

        if (profit)
            cout << " - " << profit << " denari" << endl;
        else
            cout << endl;
    }

    void pecatiParkiraniVozila()
    {
        cout << "Vo parkingot se parkirani slednite vozila:" << endl;
        for (int i = 0; i < n; i++)
            cout << i + 1 << "." << a[i].getColor() << " " << a[i].getBrand() << " " << a[i].getModel() << endl;
    }

    char *getId()
    {
        return id;
    }
};

int main()
{
    ParkingPlac p[100];
    int n, m;
    char adresa[50], id[50];
    int brojcasovi, cenacas;
    cin >> n;
    if (n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            cin.get();
            cin.getline(adresa, 50);
            cin >> id >> cenacas;

            ParkingPlac edna(adresa, id, cenacas);

            p[i] = edna;
        }

        //plakjanje
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> id >> brojcasovi;

            int findId = false;
            for (int j = 0; j < m; j++)
            {
                if (strcmp(p[j].getId(), id) == 0)
                {
                    p[j].platiCasovi(brojcasovi);
                    findId = true;
                }
            }
            if (!findId)
                cout << "Ne e platen parking. Greshen ID." << endl;
        }

        cout << "=========" << endl;
        ParkingPlac pCentar("Cvetan Dimov", "C10", 80);
        for (int i = 0; i < n; i++)
            if (p[i].daliIstaAdresa(pCentar))
                p[i].pecati();
    }
    else
    {

        ParkingPlac najdobarPlac("Mars", "1337", 1);
        int brVozila;
        cin >> brVozila;
        for (int i = 0; i < brVozila; ++i)
        {
            char boja[20];
            char brend[20];
            char model[20];

            cin >> boja >> brend >> model;
            Avtomobil novAvtomobil(boja, brend, model);
            najdobarPlac.parkirajVozilo(novAvtomobil);
        }
        if (brVozila != 0)
            najdobarPlac.pecatiParkiraniVozila();

    }
}