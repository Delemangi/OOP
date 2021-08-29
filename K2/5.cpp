/*
Да се креира класа Customer за опишување на купувачи на една книжара. За секој купувач се чуваат податоци за:

името (низа од 50 знаци),
електронска адреса (низа од 50 знаци),
вид на купувач (стандардни, лојални или вип),
основен попуст (цел број изразен во проценти),
дополнителен попуст (цел број изразен во проценти) и
број на купени производи. (5 поени)
Сите лојални купувачи со покажување на клуб картичка имаат право на основниот попуст при купување од книжарата. Основниот попуст е ист за сите лојални купувачи и изнесува 10%. Оваа вредност може да се смени со одлука на раководството на книжарата. Дополнителниот попуст е фиксен и може да го користат само вип купувачите и изнесува 20%. Стандардните купувачи немаат право на попуст (5 поени).

За оваа класа да се имплементира оператор << за печатење на купувач во формат:

[ime_na_kupuvac]
[email_na_kupuvac]
[broj_na_proizvodi]
[vid_na_kupuvac] [popust_sto_moze_da_go_koristi]
каде попустот е 0% ако купувачот е стандарден, вредноста на основниот попуст, ако е лојален или збир од основниот и дополнителниот попуст, ако купувачот е вип. (5 поени)

Да се креира класа за онлајн книжара FINKI-bookstore во која се чува низа од регистрирани купувачи (динамички алоцирана низа) и број на купувачи. (5 поени) За класата да се обезбедат:

operator+= (10 поени) за додавање купувач во листата од купувачи, но само ако веќе не е дел од неа (ако во листата нема купувач со иста електронска адреса). Ако во листата постои корисник со иста електронска адреса, треба да се генерира исклучок UserExistsException. Потребно е да се обезбеди справување со исклучокот во функцијата main на означеното место. Во ваква ситуација се печати порака "The user already exists in the list" (5 поени).
Функција update со која сите стандардни купувачи со купени повеќе од 5 производи стануваат лојални, а сите лојални купувачи со над 10 купени производи, стануваат вип (5 поени).
Оператор << за печатење на информациите за сите регистрирани купувачи (5 поени).
Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (10 поени)
*/
#include <iostream>
#include <cstring>

#define MAX 50
using namespace std;

enum typeC
{
    standard, loyal, vip
};

char type[][9] = {"standard", "loyal", "vip"};

class UserExistsException
{
public:
    static void message()
    {
        cout << "The user already exists in the list!" << endl;
    }
};

class Customer
{
private:
    char name[MAX];
    char email[MAX];
    typeC tC;
    int numProducts;
    static int discount;
    static int additional_discount;
public:
    Customer()
    {

    }

    Customer(char *name, char *email, typeC tC, int numProducts)
    {
        strcpy(this->name, name);
        strcpy(this->email, email);
        this->tC = tC;
        this->numProducts = numProducts;
    }

    friend ostream &operator<<(ostream &out, const Customer &c)
    {
        out << c.name << endl << c.email << endl << c.numProducts << endl << type[c.tC] << " ";

        if (c.tC == 0)
            cout << "0";
        else if (c.tC == 1)
            cout << discount;
        else
            cout << discount + additional_discount;

        return out << endl;
    }

    bool operator==(Customer &c)
    {
        return !strcmp(email, c.email);
    }

    static void setDiscount1(int a)
    {
        discount = a;
    }

    typeC getTc() const
    {
        return tC;
    }

    int getNumProducts() const
    {
        return numProducts;
    }

    void setTc(typeC tC)
    {
        Customer::tC = tC;
    }
};

class FINKI_bookstore
{
private:
    Customer **c;
    int n;
public:
    FINKI_bookstore()
    {
        this->c = new Customer *[0];
        this->n = 0;
    }

    FINKI_bookstore &operator+=(Customer &cu)
    {
        for (int i = 0; i < n; i++)
            if (*c[i] == cu)
                throw UserExistsException();

        auto temp = new Customer *[n + 1];

        for (int i = 0; i < n; i++)
            temp[i] = c[i];
        temp[n] = &cu;

        delete[] c;
        c = temp;
        n++;

        return *this;
    }

    friend ostream &operator<<(ostream &out, FINKI_bookstore &f)
    {
        for (int i = 0; i < f.n; i++)
            out << *f.c[i];

        return out;
    }

    void setCustomers(Customer *cu, int n)
    {
        this->n = n;
        delete[] c;
        c = new Customer *[n];

        for (int i = 0; i < n; i++)
            c[i] = &cu[i];
    }

    void update()
    {
        for (int i = 0; i < n; i++)
            if (c[i]->getTc() == (typeC) 0 && c[i]->getNumProducts() > 5)
                c[i]->setTc((typeC) 1);
            else if (c[i]->getTc() == (typeC) 1 && c[i]->getNumProducts() > 10)
                c[i]->setTc((typeC) 2);
    }
};

int Customer::discount = 10;
int Customer::additional_discount = 20;

int main()
{
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1)
    {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2)
    {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3)
    {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i)
        {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4)
    {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i)
        {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc += c;

        cout << fc;
    }

    if (testCase == 5)
    {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i)
        {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;

        try
        {
            Customer c(name, email, (typeC) tC, numProducts);
            fc += c;
        }
        catch (UserExistsException)
        {
            UserExistsException::message();
        }

        cout << fc;
    }

    if (testCase == 6)
    {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i)
        {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
