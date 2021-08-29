// Следете ги упатствата во кодот.
#include <iostream>

using namespace std;

class Shape
{
public:
    virtual void draw()
    {
        cout << "Drawing a shape.\n";
    }
};

class Rectangle : public Shape
{
public:
    void draw()
    {
        cout << "Drawing a rectangle.\n";
    }
};


int main()
{
    Shape *shape;

    Shape lol;
    shape = &lol;

    shape->draw();

    Rectangle cool;
    shape = &cool;

    shape->draw();

    return 0;
}