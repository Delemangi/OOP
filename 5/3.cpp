/*
Да се напише класа за матрица. Во класата се чуваат елементите од матрицата од тип float (матрица со максимална димензија [10]x[10]) и големината на матрицата (број на редици и колони). За оваа класа да се преоптоварат следните оператори:

оператор + за собирање матрица со број
оператор - за одземање на матрици
оператор * за множење на матрици
операторот >> за внесување на елементите на матрицата
операторот << за печатење на елементите на матрицата
Во главната функција да се креираат објекти A, B и C со подразбирливиот конструктор на класата Matrica. Од стандарден влез да се прочитаат нивните вредности. Да се отпечати вредноста на изразот A-(B*C)+2 на стандарден излез.

Да се претпостави дека секогаш матриците ќе бидат квадратни со ист број на редици и колони.
*/
#include <iostream>

using namespace std;

class Matrica
{
private:
    float a[10][10] = {0};
    int rows;
    int columns;
public:
    explicit Matrica(int rows = 0, int columns = 0)
    {
        this->rows = rows;
        this->columns = columns;
    }

    Matrica operator+(float n)
    {
        Matrica m;
        m.rows = rows;
        m.columns = columns;

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                m.a[i][j] += a[i][j] + n;

        return m;
    }

    Matrica operator-(const Matrica &other)
    {
        Matrica m;
        m.rows = rows;
        m.columns = columns;

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                m.a[i][j] += a[i][j] - other.a[i][j];

        return m;
    }

    Matrica operator*(const Matrica &other)
    {
        Matrica m;
        m.rows = rows;
        m.columns = columns;

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                for (int k = 0; k < columns; k++)
                    m.a[i][j] += a[i][k] * other.a[k][j];

        return m;
    }

    friend ostream &operator<<(ostream &out, const Matrica &other)
    {
        for (int i = 0; i < other.rows; i++)
        {
            for (int j = 0; j < other.columns; j++)
                out << other.a[i][j] << " ";
            out << endl;
        }

        return out;
    }

    friend istream &operator>>(istream &in, Matrica &other)
    {
        in >> other.rows >> other.columns;
        for (int i = 0; i < other.rows; i++)
            for (int j = 0; j < other.columns; j++)
                in >> other.a[i][j];

        return in;
    }
};

//vashiot kod ovde

int main()
{
    Matrica A, B, C;
    cin >> A >> B >> C;
    Matrica D = B * C;
    Matrica R = A - D + 2;
    cout << R;
}