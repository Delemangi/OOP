/*
Во една игротека има 2 типа играчки: топки и коцки. Коцките и топките се опишани со параметри како што се:

боја (char *)
густина (int).
Дополнително за топките се знае и радиусот (int), додека за коцките целосните димензии (висина, ширина и длабочина – int).

За секоја од класите треба да се дефинираат методи getMasa() и getVolumen(). Масата на играчката се пресметува како производ од волуменот и густината на играчката. За PI користете ја вредноста 3.14.

Во функцијата main да се декларира променлива kupche што претставува динамички алоцирана низа кон Igrachka. Во зависност од првиот влезен параметар се внесуваат објекти од класите Topka или Kocka (1 - се внесува топка, 2 - се внесува коцка).

Од тастатура да се внесат податоци за коцката на Петра Kocka petra. Во главната функција во да се отпечатат:

Да се отпечати DA ако вкупната маса на сите играчки е поголема од масата на играчката на Петра, а NE во спротивно.
Разликата по апсолутна вредност на волуменот на играчката со максимален волумен во купчето и волуменот на коцката на Петра. Форматот е:

Razlikata e: {razlika}
Задачата да се реши со тоа што класите Kocka и Topka ќе наследуваат од класите Forma и Igrachka.

Дополнителни барања:

Во класата Igrachka да се додаде уште една чисто виртуелна функција float getPlostina(). Истата да се имплементира во класите Kocka и Topka
Во главната функција, дополнително да се испечати и: Разликата по апсолутна вредност на плоштината на играчката со минимална плоштина во купчето и плоштината на коцката на Петра во истиот формат како и второто барање погоре.
*/
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Igrachka
{
public:
    Igrachka()
    {}

    virtual float getVolumen() = 0;

    virtual float getMasa() = 0;

    virtual float getPlostina() = 0;
};

class Forma
{
protected:
    char boja[100];
    int gustina;
public:
    Forma(char *boja = "", int gustina = 0)
    {
        strcpy(this->boja, boja);
        this->gustina = gustina;
    }
};

class Kocka : public Igrachka, public Forma
{
private:
    int height;
    int width;
    int depth;
public:
    Kocka(int height = 0, int width = 0, int depth = 0, char *boja = "", int gustina = 0)
            : Igrachka(), Forma(boja, gustina)
    {
        this->height = height;
        this->width = width;
        this->depth = depth;
    }

    float getMasa()
    {
        return gustina * getVolumen();
    }

    float getVolumen()
    {
        return (float) height * (float) width * (float) depth;
    }

    float getPlostina()
    {
        return 2 * height * width + 2 * height * depth + 2 * width * depth;
    }
};

class Topka : public Igrachka, public Forma
{
private:
    int radius;
public:
    Topka(int radius = 0, char *boja = "", int gustina = 0) : Igrachka(), Forma(boja, gustina)
    {
        this->radius = radius;
    }

    float getMasa()
    {
        return (float) gustina * getVolumen();
    }

    float getVolumen()
    {
        return (4.0f / 3.0f) * 3.14f * radius * radius * radius;
    }

    float getPlostina()
    {
        return 4.0f * 3.14f * radius * radius;
    }
};

int main()
{
    int n;
    int t;
    char boja[30];
    int gustina;
    int radius;
    int height;
    int width;
    int depth;

    cin >> n;

    Igrachka **kupche = new Igrachka *[n];

    for (int i = 0; i < n; i++)
    {
        cin >> t;

        if (t == 1)
        {
            cin >> boja >> gustina >> radius;

            kupche[i] = new Topka(radius, boja, gustina);
        }
        else
        {
            cin >> boja >> gustina >> height >> width >> depth;

            kupche[i] = new Kocka(height, width, depth, boja, gustina);
        }
    }

    cin >> boja >> gustina >> height >> width >> depth;

    Kocka petra(height, width, depth, boja, gustina);

    float mass = 0;
    float max = kupche[0]->getVolumen();
    float min = kupche[0]->getVolumen();

    for (int i = 0; i < n; i++)
    {
        mass += kupche[i]->getMasa();

        if (max < kupche[i]->getVolumen())
            max = kupche[i]->getVolumen();

        if (min > kupche[i]->getPlostina())
            min = kupche[i]->getPlostina();
    }

    if (petra.getMasa() < mass)
        cout << "DA" << endl;
    else
        cout << "NE" << endl;

    cout << "Razlikata e: " << abs(max - petra.getVolumen()) << endl;

    cout << "Razlikata e: " << abs(min - petra.getPlostina()) << endl;

    delete[] kupche;

    return 0;
}