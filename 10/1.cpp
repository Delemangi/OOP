/*
Да се креира генеричка класа Array за работа со низи. Класата треба во себе да ги вклучи:

покажувач кон елементи од соодветниот тип
број на елементи во рамките на низата
Елементите во рамките на објектот треба динамички да се алоцираат. Класата треба да ги поддржува следниве методи:

void Erase() - ги брише сите елементи од низата
Т operator[](int i) - за пристап до соодветниот елемент во низата (вклучувајќи и проверка дали индексот е во границите)
int GetLength() - го враќа бројот на елементите во низата
Да се преоптовари operator<< (ostream) за работа со класата (да се претпостави дека елементите од низата го имаат преоптоварено операторот <<).

Надвор од класата да се напишат следниве функции:

void BubbleSort(Array<T> t&)  - ги сорира елементите користејќи го BubbleSort алгоритмот (да се претпостави дека операторот > e преоптоварен за елементите од класата).

Т Sum(Array<T> &) - ги сумира елементите (да се претпостави дека операторот += e преоптоварен за елементите од класата).

Т Average(Array<T>&) - користејќи ја функцијата за сума пресметува просечна вредност на елементите ( операторот / е преоптоварен за елементите)

bool Equal (Array<T>&, Array<M>&) - проверува дали низите се еднакви (се претпоставува дека операторот == е преоптоварен за соодветните класи)

bool Equal (Array <T>&, Array<double>& ) - која ќе изврши пацијална специјализација и ќе смета дека:
 - два елементи се исти ако и само ако се разликуваат за помалку од 0.1
 - разликата од просечната вредност на низите мора да е помала од 0.5.
*/
#include <iostream>
#include <cmath>
#include <cstdlib>


using namespace std;

class Exception
{
private:
    int i;
public:
    Exception(int i)
    {
        this->i = i;
    }

    void message() const
    {
        cout << i << " out of bounds" << endl;
    }
};

template<typename T>
class Array
{
private:
    T *array;
    int n;
public:
    Array(int n)
    {
        this->n = n;
        array = new T[n];
    }

    ~Array()
    {
        delete[] array;
    }

    T &operator[](int i)
    {
        if (i < 0 || i > n)
            throw Exception(i);

        return array[i];
    }

    friend ostream &operator<<(ostream &out, const Array &a)
    {
        out << "Array[0] = " << a.array[0];

        for (int i = 1; i < a.n; i++)
            out << ", Array[" << i << "] = " << a.array[i];

        out << endl;

        return out;
    }

    void Erase()
    {
        delete[] array;
        array = new T[0];
        n = 0;
    }

    int GetLength()
    {
        return n;
    }
};

template<typename T>
void BubbleSort(Array<T> &t)
{
    for (int i = 0; i < t.GetLength() - 1; i++)
        for (int j = 0; j < t.GetLength() - 1 - i; j++)
            if (t[j] > t[j + 1])
            {
                T temp;

                temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
}

template<typename T>
T Sum(Array<T> &t)
{
    T s = 0;

    for (int i = 0; i < t.GetLength(); i++)
        s += t[i];

    return s;
}

template<typename T>
T Average(Array<T> &t)
{
    return Sum(t) / t.GetLength();
}

template<typename T, typename M>
bool Equal(Array<T> &t, Array<M> &m)
{
    if (t.GetLength() != m.GetLength())
        return false;

    for (int i = 0; i < t.GetLength(); i++)
        if (t[i] != m[i])
            return false;

    return true;
}

template<typename T>
bool Equal(Array<T> &t, Array<double> &d)
{
    if (t.GetLength() != d.GetLength())
        return false;

    for (int i = 0; i < t.GetLength(); i++)
        if (abs(t[i] - d[i]) > 0.1)
            return false;

    if (abs(Average(t) - Average(d)) > 0.5)
        return false;

    return true;
}

int main()
{

    int n;
    double r;

    cin >> r;
    cin >> n;

    Array<int> anArray(n);
    Array<double> adArray(n);
    Array<int> intArray2(n);

    for (int nCount = 0; nCount < n; nCount++)
    {

        cin >> anArray[nCount];
        adArray[nCount] = anArray[nCount] + r;
    }

    BubbleSort(anArray);

    intArray2 = anArray;

    cout << "The arrays: " << endl;
    cout << anArray;
    cout << "and " << endl;
    cout << intArray2;
    cout << ((Equal(anArray, intArray2)) ? " ARE" : " ARE NOT") << " same!" << endl;
    cout << "The Average of the array adArray is: " << Average(adArray) << endl;

    cout << "The arrays: " << endl;
    cout << anArray;
    cout << "and " << endl;
    cout << adArray;
    cout << ((Equal(anArray, adArray)) ? " ARE" : " ARE NOT") << " same!";


    return 0;
}