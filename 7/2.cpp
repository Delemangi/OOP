/*
Да се дефинира апстрктна класа Number со следните чисто виртуелни методи:

double doubleValue() -ја враќа децималната вредност на даден број
int intValue()- ја враќа целобројната вредност на даден број
void print() - печати информации за бројот. (1 поен)
Од оваа класа да се изведат две класи:

Integer (во која што се чува еден број од тип int)
Double (во која што се чува еден број од тип double) (1 поен).
За двете изведени класи да се имплементираaт соодветен конструктори, како и да се препокријат методите од основната класа. (1 поени)

Да се преоптовари операторот == којшто ќе споредува два броеви според нивната вредност (објекти од класа Number) (1 поен)

Дополнително да се дефинира класа Numbers во која што ќе се чуваат:

динамички алоцирана низа од покажувачи кон објекти од класата Number
број на елементи во низата од покажувачи
За класата да се имплементира соодветен конструктор (default) , како и: (1 поени)

операторот += за додавање на броеви во низата од броеви (1 поен)
Бројот се додава ако и само ако сите броеви што се веќе додадени во низата се различни од него
функција void statistics() која што печати информации за броевите во низата: (2 поени)
Count of numbers: [број на броеви во низата

Sum of all numbers: [сума на сите броеви во низата]

Count of integer numbers: [број на цели броеви (Integer)]

Sum of integer numbers: [сума на сите цели броеви (Integer)]

Count of double numbers: [број на децимални броеви (Double)]

Sum of double numbers: [сума на сите децимални броеви (Double)]

функција void integersLessThan (Integer n) која што ги печати сите цели броеви помали од бројот n (1 поен)
функција void doublesBiggerThan (Double n) која што ги печати сите децимални броеви поголеми од бројот n (1 поен)
*/
#include<iostream>

using namespace std;

class Number
{
public:
    virtual double doubleValue() = 0;

    virtual int intValue() = 0;

    virtual void print() = 0;

public:
    Number()
    {}

    bool operator==(Number &n)
    {
        return doubleValue() == n.doubleValue() && intValue() == n.intValue();
    }
};

class Integer : public Number
{
private:
    int num;
public:
    Integer(int num) : Number()
    {
        this->num = num;
    }

    double doubleValue()
    {
        return (double) num;
    }

    int intValue()
    {
        return (int) num;
    }

    void print()
    {
        cout << "Integer: " << num << endl;
    }
};

class Double : public Number
{
private:
    double num;
public:
    Double(double num) : Number()
    {
        this->num = num;
    }

    double doubleValue()
    {
        return (double) num;
    }

    int intValue()
    {
        return (int) num;
    }

    void print()
    {
        cout << "Double: " << num << endl;
    }
};

class Numbers
{
private:
    Number **num;
    int n;
public:
    Numbers()
    {
        num = new Number *[0];
        n = 0;
    }

    ~Numbers()
    {
        delete[] num;
    }

    Numbers &operator+=(Number *number)
    {
        for (int i = 0; i < n; i++)
            if (*num[i] == *number)
                return *this;

        Number **temp = new Number *[n + 1];

        for (int i = 0; i < n; i++)
            temp[i] = num[i];
        temp[n] = number;

        delete[] num;
        num = temp;
        n++;

        return *this;
    }

    void statistics()
    {
        cout << "Count of numbers: " << n << endl;

        double s1 = 0;
        for (int i = 0; i < n; i++)
            s1 += num[i]->doubleValue();
        cout << "Sum of all numbers: " << s1 << endl;

        int s2 = 0, s3 = 0, s4 = 0;
        double s5 = 0;
        for (int i = 0; i < n; i++)
            if (dynamic_cast<Integer *>(num[i]))
            {
                s2++;
                s3 += num[i]->intValue();
            }
            else if (dynamic_cast<Double *>(num[i]))
            {
                s4++;
                s5 += num[i]->doubleValue();
            }
        cout << "Count of integer numbers: " << s2 << endl;
        cout << "Sum of integer numbers: " << s3 << endl;
        cout << "Count of double numbers: " << s4 << endl;
        cout << "Sum of double numbers: " << s5 << endl;
    };

    void integersLessThan(Integer integer)
    {
        bool ints = false;

        for (int i = 0; i < n; i++)
            if (dynamic_cast<Integer *>(num[i]) && num[i]->intValue() < integer.intValue())
            {
                num[i]->print();
                ints = true;
            }

        if (!ints)
            cout << "None" << endl;
    }

    void doublesBiggerThan(Double d)
    {
        bool ints = false;

        for (int i = 0; i < n; i++)
            if (dynamic_cast<Double *>(num[i]) && num[i]->doubleValue() > d.doubleValue())
            {
                num[i]->print();
                ints = true;
            }

        if (!ints)
            cout << "None" << endl;
    }
};

int main()
{

    int n;
    cin >> n;
    Numbers numbers;
    for (int i = 0; i < n; i++)
    {
        int type;
        double number;
        cin >> type >> number;
        if (type == 0)
        {//Integer object
            Integer *integer = new Integer((int) number);
            numbers += integer;
        }
        else
        {
            Double *doublee = new Double(number);
            numbers += doublee;
        }
    }

    int lessThan;
    double biggerThan;

    cin >> lessThan;
    cin >> biggerThan;

    cout << "STATISTICS FOR THE NUMBERS\n";
    numbers.statistics();
    cout << "INTEGER NUMBERS LESS THAN " << lessThan << endl;
    numbers.integersLessThan(Integer(lessThan));
    cout << "DOUBLE NUMBERS BIGGER THAN " << biggerThan << endl;
    numbers.doublesBiggerThan(Double(biggerThan));

    return 0;
}