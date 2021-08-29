/*
--

Потребно е да конструирате абстракна класа Shape со само еден параметар:

страна (int)
Конструктори:

Shape()
Shape(int a)
И виртуелните методи:

double plostina()
void pecati()
int getType()
Од таа класа вие треба да конструирате 3 изведени класи:

Square
Circle
Triangle
Изведените класи немаат дополнителни парамтери, туку ја наследуваат страната од Shape

Конструктори:

Конструкторот на изведените класи ќе зема еден аругмент, страната на фигурата.

При пишување на конструкторот на изведените класи да се искористи констукторот на родител класата

Методи:

Секоја од класите си има своја формула за plostina() соодветна за нивната геометриска фигура

Формула за плоштина на квадрат а * a
Формула за плоштина на круг 3.14 * a * a
Формула за плоштина на триаголник (sqrt(3)/4) * side * side
За pecati() методот упатете се кон outputot за тест случајите.

getType() методот треба да враќа:

1 за Square
2 за Circle
3 за Triangle
Поени: 5

--

Дефинирајте го методот void checkNumTypes(Shape** niza, int n) така што ќе испечати во три реда колку квадрати, кругови и триаголници има во низата.

Поени: 2

--

Покрај тоа треба да ја допишете Main класата така што ќе алоцирате динамичка низа од покажувачи кон класата Shape.

Потоа кај секој покажувач од низата зависно од дадениот input да алоцирате објект од една од трите изведени класи.

Input:

Прво се добива n - големината на динамичката низа. Потоа n пати се добиваат пар цели броеви t i a, каде што t е типот на објектот и а е страната на објектот.

Пример:

3

1 3 //квадрат со страна со должина 3

2 2 //круг со страна со должина 2

3 1 //триаголник со страна со должина 1

Поени: 3

--
*/
#include <iostream>
#include <cmath>

using namespace std;

class Shape
{
protected:
    int side;
public:
    Shape(int side = 0)
    {
        this->side = side;
    }

    virtual double plostina() = 0;

    virtual int getType() = 0;

    virtual void pecati() = 0;
};

class Square : public Shape
{
public:
    Square(int side = 0) : Shape(side)
    {}

    double plostina()
    {
        return side * side;
    }

    int getType()
    {
        return 1;
    }

    void pecati()
    {
        cout << "Kvadrat so plostina = " << plostina() << endl;
    }
};

class Circle : public Shape
{
public:
    Circle(int side = 0) : Shape(side)
    {}

    double plostina()
    {
        return 3.14 * side * side;
    }

    int getType()
    {
        return 2;
    }

    void pecati()
    {
        cout << "Krug so plostina = " << plostina() << endl;
    }
};

class Triangle : public Shape
{
public:
    Triangle(int side = 0) : Shape(side)
    {}

    double plostina()
    {
        return sqrt(3) / 4 * side * side;
    }

    int getType()
    {
        return 3;
    }

    void pecati()
    {
        cout << "Triagolnik so plostina = " << plostina() << endl;
    }
};

void checkNumTypes(Shape **shape, int n)
{
    int t = 0, c = 0, s = 0;

    for (int i = 0; i < n; i++)
    {
        if (shape[i]->getType() == 1)
        {
            s++;
        }
        else if (shape[i]->getType() == 2)
        {
            c++;
        }
        else if (shape[i]->getType() == 3)
        {
            t++;
        }
    }

    cout << "Broj na kvadrati vo nizata = " << s << endl;
    cout << "Broj na krugovi vo nizata = " << c << endl;
    cout << "Broj na triagolnici vo nizata = " << t << endl;
}

int main()
{
    int n;
    cin >> n;

    Shape **shape = new Shape *[n];

    int classType;
    int side;

    for (int i = 0; i < n; ++i)
    {
        cin >> classType;
        cin >> side;

        if (classType == 1)
            shape[i] = new Square(side);
        else if (classType == 2)
            shape[i] = new Circle(side);
        else if (classType == 3)
            shape[i] = new Triangle(side);
    }

    for (int i = 0; i < n; ++i)
        shape[i]->pecati();

    checkNumTypes(shape, n);
    
    return 0;
}