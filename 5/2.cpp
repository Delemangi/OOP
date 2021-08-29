/*
Потребно е да се напише класа за работа со комплексни броеви ComplexNumber. Во неа се чуваат две променливи кои можат да бидат децимални броеви. Едната го претставува реалниот дел од комплексниот број - real, а другата имагинарниот дел - imaginary. За класата да се напише:

конструктор со параметри и со предодредени вредности - нули
метод со потпис double module() кој го враќа модулот на комплексниот број. Модул се пресметува според следната формула:

sqrt(pow(real, 2) + pow(imaginary, 2))

Дополнително, потребно е да се преоптоварат следниве оператори:

оператор за доделување вредност =
оператор за печатење на стандарден излез << кој ќе го печати бројот во формат [real]+[imaginary]i. Доколку реалниот дел е 0, се печати само [imaginary]i, a доколку имагинарниот дел е 0, се печати само [real].
оператор за собирање на комплексни броеви +. Резултатот е нов комплексен број, чиј реален и имагинарен дел се збир од соодветните делови од собироците
оператор за одземање на комплексни броеви -. Резултатот е нов комплексен број, чиј реален и имагинарен дел се разлика од соодветните делови од собироците
оператор за множење на комплексни броеви *. Резултатот е нов комплексен број, чиј реален и имагинарен дел се производ од соодветните делови од множителите
оператор за делење на комплексни броеви /. Резултатот е нов комплексен број, чиј реален и имагинарен дел се количник од соодветните делови од делителите
оператор за еднаквост на комплексни броеви ==. Два комплексни броеви се еднакви ако и само ако се еднакви нивните реални и имагинарни делови
оператори за споредба на комплексни броеви > и <. Комплексните броеви се споредуваат според вредноста на нивниот реален дел. Ако тој е еднаков, тогаш се споредуваат според вредноста на имагинарниот дел
Целосна функционалност на класата носи (5 поени).

Потоа, потребно е да се напише класа за работа со равенки од комплексни броеви Equation. Во неа ќе се чуваат динамички алоцирана низа од комплексни броеви (објекти од класата ComplexNumber) и динамички алоцирана низа од знаци char - аритметички оператори за операции меѓу броевите.

Следно, треба да се преоптовари операторот за читање од стандарден влез >> кој ќе чита податоци за равенката. Прво се вчитуваат податоци за еден комплексен број (прво реален па имагинарен дел), па оператор, па повторно комплексен број, повторно оператор итн. сѐ додека не се прочита знакот =. Со вчитување на знакот = (на местото за оператор) читањето од влез завршува (2 поени).

За класата да се напишат и следниве методи:

ComplexNumber result() кој ќе го врати резултатот од равенката. При пресметувањето на резултатот сите аритметички оператори (+, -, *, /) имаат еднаква предност, т.е. не треба да внимавате да извршувате множење пред собирање или слично, туку ги извршувате операциите во оној редослед во кој сте ги добиле при вчитување од стандарден влез. (2 поени)
double sumModules() кој ќе врати збир од модулите на сите комплексни броеви во равенката. (1 поен)
Забелешка: Не го менувајте почетниот код!
*/
#include<iostream>
#include<cmath>

using namespace std;

class ComplexNumber
{
private:
    double r;
    double i;
public:
    explicit ComplexNumber(double r = 0, double i = 0)
    {
        this->r = r;
        this->i = i;
    }

    ComplexNumber &operator=(const ComplexNumber &other)
    {
        if (this == &other)
            return *this;

        r = other.r;
        i = other.i;

        return *this;
    }

    ComplexNumber operator+(const ComplexNumber &other) const
    {
        return ComplexNumber(r + other.r, i + other.i);
    }

    ComplexNumber operator-(const ComplexNumber &other) const
    {
        return ComplexNumber(r - other.r, i - other.i);
    }

    ComplexNumber operator*(const ComplexNumber &other) const
    {
        return ComplexNumber(r * other.r, i * other.i);
    }

    ComplexNumber operator/(const ComplexNumber &other) const
    {
        return ComplexNumber(r / other.r, i / other.i);
    }

    bool operator==(const ComplexNumber &other) const
    {
        if (r == other.r && i == other.i)
            return true;
        return false;
    }

    bool operator<(const ComplexNumber &other) const
    {
        if (r < other.r)
            return true;
        else if (r > other.r)
            return false;
        else
        {
            if (i < other.i)
                return true;
            else
                return false;
        }
    }

    bool operator>(const ComplexNumber &other) const
    {
        if (r > other.r)
            return true;
        else if (r < other.r)
            return false;
        else
        {
            if (i > other.i)
                return true;
            else
                return false;
        }
    }

    friend ostream &operator<<(ostream &out, const ComplexNumber &other)
    {
        if (other.r > 0 && other.i > 0)
            out << other.r << "+" << other.i << "i" << endl;
        else if (other.r > 0 && other.i == 0)
            out << other.r << endl;
        else if (other.r == 0 && other.i > 0)
            out << other.i << "i" << endl;

        return out;
    }

    double module()
    {
        return sqrt(r * r + i * i);
    }
};

class Equation
{
private:
    ComplexNumber *c;
    char *operators;
    int n;
public:
    explicit Equation(int n = 0)
    {
        c = new ComplexNumber[100];
        operators = new char[100];
        this->n = n;
    }

    friend istream &operator>>(istream &in, Equation &other)
    {
        int i = 0;
        double a[2];
        char op;

        while (other.operators[i] != '=')
        {
            in >> a[0] >> a[1] >> op;
            other.c[i] = ComplexNumber(a[0], a[1]);
            other.operators[i] = op;
            i++;
            if (op == '=')
                break;
        }

        other.n = i;
        return in;
    }

    ComplexNumber result()
    {
        ComplexNumber t = c[0];

        for (int i = 0; i < n; i++)
        {
            if (operators[i] == '+')
                t = t + c[i + 1];
            else if (operators[i] == '-')
                t = t - c[i + 1];
            else if (operators[i] == '*')
                t = t * c[i + 1];
            else if (operators[i] == '/')
                t = t / c[i + 1];
            else if (operators[i] == '=')
                break;
        }

        return t;
    }

    double sumModules()
    {
        double s = 0;

        for (int i = 0; i < n; i++)
            s += c[i].module();

        return s;
    }
};
// Не го менувајте main методот.

int main()
{
    int testCase;
    double real, imaginary;
    ComplexNumber first, second, result;

    cin >> testCase;

    if (testCase <= 8)
    {
        cin >> real;
        cin >> imaginary;
        first = ComplexNumber(real, imaginary);
        cin >> real;
        cin >> imaginary;
        second = ComplexNumber(real, imaginary);
    }

    if (testCase == 1)
    {
        cout << "===== OPERATOR + =====" << endl;
        result = first + second;
        cout << result;
    }
    else if (testCase == 2)
    {
        cout << "===== OPERATOR - =====" << endl;
        result = first - second;
        cout << result;
    }
    else if (testCase == 3)
    {
        cout << "===== OPERATOR * =====" << endl;
        result = first * second;
        cout << result;
    }
    else if (testCase == 4)
    {
        cout << "===== OPERATOR / =====" << endl;
        result = first / second;
        cout << result;
    }
    else if (testCase == 5)
    {
        cout << "===== OPERATOR == =====" << endl;
        cout << first;
        cout << second;
        if (first == second)
            cout << "EQUAL" << endl;
        else
            cout << "NOT EQUAL" << endl;
    }
    else if (testCase == 6)
    {
        cout << "===== OPERATOR > =====" << endl;
        cout << first;
        cout << second;
        if (first > second)
            cout << "FIRST GREATER THAN SECOND" << endl;
        else
            cout << "FIRST LESSER THAN SECOND" << endl;
    }
    else if (testCase == 7)
    {
        cout << "===== OPERATOR < =====" << endl;
        cout << first;
        cout << second;
        if (first < second)
            cout << "FIRST LESSER THAN SECOND" << endl;
        else
            cout << "FIRST GREATER THAN SECOND" << endl;
    }
    else if (testCase == 8)
    {
        cout << "===== MODULE =====" << endl;
        double module = first.module();
        cout << first;
        cout << "Module: " << module << endl;
        cout << second;
        module = second.module();
        cout << "Module: " << module << endl;
    }
    else if (testCase == 9)
    {
        cout << "===== OPERATOR >> & SUM OF MODULES =====" << endl;
        Equation equation;
        cin >> equation;
        cout << equation.sumModules();
    }
    else if (testCase == 10)
    {
        cout << "===== EQUATION RESULT =====" << endl;
        Equation equation;
        cin >> equation;
        result = equation.result();
        cout << result;
    }
    return 0;
}