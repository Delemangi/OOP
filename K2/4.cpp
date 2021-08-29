/*
Да се креира апстрактна класа Pizza за опишување пици. (5 поени) За секоја пица се чуваат следните информации:

име (низа од максимум 20 знаци)
состојки (низа од максимум 100 знаци)
основна цена (реален број)
Од оваа класа да се изведат класите FlatPizza и FoldedPizza за опишување на рамни и преклопени пици соодветно (5 поени).

За секоја рамна пица дополнително се чува големина (enum - една од три можности: мала, голема и фамилијарна). За секоја преклопена пица дополнително се чува информација дали тестото е од бело брашно или не (boolean).

За секоја пица треба да се обезбеди метод за пресметување на нејзината продажна цена:

цената на рамната пица се пресметува така што основната цена се зголемува за 10%, 30% и 50% за мала, голема и фамилијарна пица соодветно.
цената на преклопената пица се пресметува така што основната цена се зголемува за 10% ако е тестото е од бело брашно, а во спротивно за 30%. (10 поени)
Да се преоптоварат следните оператори:

оператор << - за печатење сите податоци за пиците во следниов формат:

За рамна пица:[име]: [состојки], [големина] - [продажната цена на пицата]. 
За преклопена пица: [име]: [состојки], [wf - ако е со бело брашно / nwf - ако не е со бело брашно] - [продажната цена на пицата]
(5 поени)

оператор < - за споредување на пиците од каков било вид според нивната продажна цена. (5 поени)
Да се дефинира глобална функција еxpensivePizza што на влез прима низа од покажувачи кон објекти од класата Pizza и нивниот број, а како резултат ги печати информациите за пицата со највисока продажна цена. Ако има повеќе пици со иста највисока цена, се печати првата. (10 поени)

Да се дефинираат потребните конструктори и методи во класите за правилно функционирање на програмата. (5 поени)
*/
#include <cstring>
#include <iostream>

using namespace std;
enum Size
{
    small, large, family
};

class Pizza
{
protected:
    char name[20];
    char ingredients[100];
    float inPrice;
public:
    Pizza(const char *name = "", const char *ingredients = "", float inPrice = 0)
    {
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->ingredients[49] = '\0';
        this->inPrice = inPrice;
    }

    virtual double price() = 0;

    friend ostream &operator<<(ostream &out, Pizza &p);

    bool operator<(Pizza &p);
};

class FlatPizza : public Pizza
{
private:
    Size size;
public:
    FlatPizza(const char *name = "", const char *ingredients = "", float inPrice = 0, Size size = small) : Pizza(name,
                                                                                                                 ingredients,
                                                                                                                 inPrice)
    {
        this->size = size;
    }

    double price()
    {
        if (size == small)
            return inPrice * 1.1;
        else if (size == family)
            return inPrice * 1.3;
        else
            return inPrice * 1.5;
    }

    Size getSize() const
    {
        return size;
    }
};

class FoldedPizza : public Pizza
{
private:
    bool wf;
public:
    FoldedPizza(const char *name = "", const char *ingredients = "", float inPrice = 0) : Pizza(name, ingredients,
                                                                                                inPrice)
    {
        wf = true;
    }

    double price()
    {
        if (wf)
            return inPrice * 1.1;
        else
            return inPrice * 1.3;
    }

    void setWhiteFlour(bool w)
    {
        this->wf = w;
    }

    bool isWf() const
    {
        return wf;
    }
};

void expensivePizza(Pizza **pPizza, int p);

ostream &operator<<(ostream &out, Pizza &p)
{
    out << p.name << ": " << p.ingredients << ", ";

    if (dynamic_cast<FlatPizza *>(&p))
    {
        if (dynamic_cast<FlatPizza *>(&p)->getSize() == small)
            cout << "small";
        else if (dynamic_cast<FlatPizza *>(&p)->getSize() == large)
            cout << "large";
        else
            cout << "family";
    }
    else if (dynamic_cast<FoldedPizza *>(&p))
    {
        if (dynamic_cast<FoldedPizza *>(&p)->isWf())
            out << "wf";
        else
            out << "nwf";
    }

    out << " - " << p.price() << endl;

    return out;
}

bool Pizza::operator<(Pizza &p)
{
    return price() < p.price();
}

void expensivePizza(Pizza **p, int pizzas)
{
    double max = p[0]->price();
    int index = 0;

    for (int i = 0; i < pizzas; ++i)
        if (max < p[i]->price())
        {
            max = p[i]->price();
            index = i;
        }

    cout << *p[index];
}

int main()
{
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1)
    {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    }
    else if (test_case == 2)
    {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        int s;
        cin >> s;
        FlatPizza fp(name, ingredients, inPrice, (Size) s);
        cout << fp;

    }
    else if (test_case == 3)
    {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    }
    else if (test_case == 4)
    {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    }
    else if (test_case == 5)
    {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp1;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp2;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout << "Lower price: " << endl;
        if (*fp1 < *fp2)
            cout << fp1->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp1 < *fp3)
            cout << fp1->price() << endl;
        else cout << fp3->price() << endl;

        if (*fp4 < *fp2)
            cout << fp4->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp3 < *fp4)
            cout << fp3->price() << endl;
        else cout << fp4->price() << endl;

    }
    else if (test_case == 6)
    {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j)
        {

            cin >> pizza_type;
            if (pizza_type == 1)
            {
                cin.get();
                cin.getline(name, 20);

                cin.getline(ingredients, 100);
                cin >> inPrice;
                int s;
                cin >> s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size) s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2)
            {

                cin.get();
                cin.getline(name, 20);
                cin.getline(ingredients, 100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza(name, ingredients, inPrice);
                if (j % 2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi, num_p);


    }
    return 0;
}