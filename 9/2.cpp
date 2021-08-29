/*
Да се креира класа PositiveIntegers во која што ќе се чуваат информации за:

низа од позитивни броеви (>0) (динамички алоцирана низа од цели броеви)
број на елементи во низата
максимален капацитет на низата
За класата да се имплементираат:

потребниот конструктор (погледнете во главната функција како се креира објект од оваа класа)
метод void increaseCapacity(int c) којшто го зголемува максималниот капацитет на низата за бројот с
оператор за додавање на нов број во низата од позитивни броеви +=
број се додава ако и само ако
оператор за множење * за множење на низата со друг цел број
Пример, низата има објекти (1 2 3 4 5) и истата се множи со 2, резултатот ќе биде (1 2 3 4 5)*2 = (2 3 6 8 10)
оператор за делење \ за делење на низата до друг цел број
потребно е секој елемент од низата да биде делив со тој број, како и делителот не смее да биде нула.
оператор [] за пристап до елемент од низата
Потребно е да се дефинираат класи за исклучоци и секој од нив да има метод void message() којшто ќе принта соодветна порака кога исклучокот ќе биде фатен. Можните исклучоци се следните:

ArithmeticException (се фрла ако се проба да се дели со нула)
принта порака Division by zero is not allowed
NumbersNotDivisibleException (се фрла ако се проба да се дели низата со некој број, а барем еден елемент од низата не е делив со тој број)
принта порака Division by number [делителот] is not supported
ArrayFullException (се фрла ако се проба да се додади елемент во низа која и е исполнет максималниот капацитет)
принта порака The array is full. Increase the capacity
IndexOutOfBoundsException (се фрла доколку се проба да се пристапи до елемент од низата со несоодветен индекс)
принта порака Index [индексот] is out of bounds
NumberIsNotPositiveException (се фрла доколку се проба да се внесе во низата број што не е позитивен или е нула)
принта порака Number [бројот] is not positive integer.
*/
#include <iostream>
#include <cstring>

using namespace std;

class ArithmeticException
{
public:
    void message() const
    {
        cout << "Division by zero is not allowed" << endl;
    }
};

class NumbersNotDivisibleException
{
private:
    int n;
public:
    NumbersNotDivisibleException(int n)
    {
        this->n = n;
    }

    void message() const
    {
        cout << "Division by " << n << " is not supported" << endl;
    }
};

class ArrayFullException
{
public:
    void message()
    {
        cout << "The array is full. Increase the capacity" << endl;
    }
};

class IndexOutOfBoundsException
{
private:
    int n;
public:
    IndexOutOfBoundsException(int n)
    {
        this->n = n;
    }

    void message() const
    {
        cout << "Index " << n << " is out of bounds" << endl;
    }
};

class NumberIsNotPositiveException
{
private:
    int n;
public:
    NumberIsNotPositiveException(int n)
    {
        this->n = n;
    }

    void message()
    {
        cout << "Number " << n << " is not positive integer" << endl;
    }
};

class PositiveIntegers
{
private:
    int *array;
    int n;
    int max;
public:
    PositiveIntegers(int max = 0)
    {
        array = new int[max];
        n = 0;
        this->max = max;
    }

    PositiveIntegers(PositiveIntegers &pi)
    {
        array = new int[pi.max];
        for (int i = 0; i < pi.n; i++)
            array[i] = pi.array[i];
        n = pi.n;
        max = pi.max;
    }

    ~PositiveIntegers()
    {
        delete[] array;
    }

    PositiveIntegers &operator+=(int a)
    {
        if (n == max)
            throw ArrayFullException();

        if (a <= 0)
            throw NumberIsNotPositiveException(a);

        array[n] = a;
        n++;

        return *this;
    }

    PositiveIntegers &operator=(const PositiveIntegers &pi)
    {
        if (this == &pi)
            return *this;

        delete[] array;
        array = new int[pi.max];
        for (int i = 0; i < pi.n; i++)
            array[i] = pi.array[i];
        n = pi.n;
        max = pi.max;

        return *this;
    }

    PositiveIntegers operator*(int a)
    {
        PositiveIntegers pi(*this);

        for (int i = 0; i < n; i++)
            pi.array[i] *= a;

        return pi;
    }

    PositiveIntegers operator/(int a)
    {
        if (a == 0)
            throw ArithmeticException();

        for (int i = 0; i < n; i++)
            if (array[i] % a != 0)
                throw NumbersNotDivisibleException(a);

        PositiveIntegers pi(*this);

        for (int i = 0; i < n; i++)
            pi.array[i] /= a;

        return pi;
    }

    int &operator[](int a) const
    {
        if (a < 0 || a >= n)
            throw IndexOutOfBoundsException(a);
        else
            return array[a];
    }

    void increaseCapacity(int c)
    {
        int *t = new int[max + c];

        for (int i = 0; i < n; i++)
            t[i] = array[i];

        delete[] array;
        array = t;
        max += c;
    }

    void print()
    {
        cout << "Size: " << n << " Capacity: " << max << " Numbers: ";

        for (int i = 0; i < n; i++)
            cout << array[i] << " ";

        cout << endl;
    }
};

int main()
{

    int n, capacity;
    cin >> n >> capacity;
    PositiveIntegers pi(capacity);
    for (int i = 0; i < n; i++)
    {
        int number;
        cin >> number;
        try
        {
            pi += number;
        }
        catch (ArrayFullException &e)
        {
            e.message();
        }
        catch (NumberIsNotPositiveException &e)
        {
            e.message();
        }

    }
    cout << "===FIRST ATTEMPT TO ADD NUMBERS===" << endl;
    pi.print();
    int incCapacity;
    cin >> incCapacity;
    pi.increaseCapacity(incCapacity);
    cout << "===INCREASING CAPACITY===" << endl;
    pi.print();

    int n1;
    cin >> n1;
    for (int i = 0; i < n1; i++)
    {
        int number;
        cin >> number;
        try
        {
            pi += number;
        }
        catch (ArrayFullException &e)
        {
            e.message();
        }
        catch (NumberIsNotPositiveException &e)
        {
            e.message();
        }
    }
    cout << "===SECOND ATTEMPT TO ADD NUMBERS===" << endl;

    pi.print();
    PositiveIntegers pi1;

    cout << "===TESTING DIVISION===" << endl;

    try
    {
        pi1 = pi / 0;
        pi1.print();
    }
    catch (ArithmeticException &e)
    {
        e.message();
    }
    catch (NumbersNotDivisibleException &e)
    {
        e.message();
    }

    try
    {
        pi1 = pi / 1;
        pi1.print();
    }
    catch (ArithmeticException &e)
    {
        e.message();
    }
    catch (NumbersNotDivisibleException &e)
    {
        e.message();
    }

    try
    {
        pi1 = pi / 2;
        pi1.print();
    }
    catch (ArithmeticException &e)
    {
        e.message();
    }
    catch (NumbersNotDivisibleException &e)
    {
        e.message();
    }

    cout << "===TESTING MULTIPLICATION===" << endl;
    pi1 = pi * 3;
    pi1.print();


    cout << "===TESTING [] ===" << endl;
    try
    {
        cout << "PositiveIntegers[-1] = " << pi[-1] << endl;
    }
    catch (IndexOutOfBoundsException &e)
    {
        e.message();
    }
    try
    {
        cout << "PositiveIntegers[2] = " << pi[2] << endl;
    }
    catch (IndexOutOfBoundsException &e)
    {
        e.message();
    }
    try
    {
        cout << "PositiveIntegers[3] = " << pi[3] << endl;
    }
    catch (IndexOutOfBoundsException &e)
    {
        e.message();
    }
    try
    {
        cout << "PositiveIntegers[12] = " << pi[12] << endl;
    }
    catch (IndexOutOfBoundsException &e)
    {
        e.message();
    }


    return 0;
}