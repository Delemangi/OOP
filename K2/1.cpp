/*
Издавачката куќа FINKI-Education издава онлајн и печатени книги. За секоја книга се чуваат податоци за ISBN бројот (низа од најмногу 20 знаци), насловот (низа од најмногу 50 знаци), авторот (низа од најмногу 30 знаци) и основната цена изразена во $ (реален број). Класата за опишување на книгите е апстрактна (5 поени).

За секоја онлајн книга дополнително се чуваат податоци за url од каде може да се симне (динамички резервирана низа од знаци) и големината изразена во MB (цел број). За секоја печатена книга дополнително се чуваат податоци за масата изразена во килограми (реален број) и дали ја има на залиха (логичка променлива). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

Метод bookPrice, за пресметување на продажната цена на книгата на следниот начин: (10 поени)

За онлајн книга - цената се зголемува за 20% од основната цена ако книгата е поголема од 20MB

За печатена книга - цената се зголемува за 15% од основната цена ако масата на книгата е поголема од 0.7kg

Преоптоварен оператор > за споредба на две книги од каков било вид според нивната цена. (5 поени)

Преоптоварен оператор << за печатење на податоците за книгите во формат: (5 поени)
Да се имплементира функција mostExpensiveBook со потпис:

void mostExpensiveBook (Book** books, int n)

во која се печати вкупниот број на онлајн, односно, печатени книги во проследената низа посебно. (5 поени) Потоа се наоѓа и печати најскапата книга. (5 поени)

Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)
*/
#include <iostream>
#include <cstring>

using namespace std;

class Book
{
protected:
    char ISBN[21];
    char title[50];
    char author[30];
    float price;
public:
    Book(char *ISBN, char *title, char *author, float price)
    {
        strcpy(this->ISBN, ISBN);
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->price = price;
    }

    friend ostream &operator<<(ostream &out, Book &b)
    {
        out << b.ISBN << ": " << b.title << ", " << b.author << " " << b.bookPrice() << endl;

        return out;
    }

    virtual float bookPrice() = 0;

    void setISBN(char *ISBN)
    {
        strcpy(this->ISBN, ISBN);
    }
};

class OnlineBook : public Book
{
private:
    char *url;
    int size;
public:
    OnlineBook(char *ISBN, char *title, char *author, float price, char *url, int size) : Book(ISBN, title, author,
                                                                                               price)
    {
        this->url = new char[50];
        strcpy(this->url, url);
        this->size = size;
    }

    ~OnlineBook()
    {
        delete[] url;
    }

    float bookPrice()
    {
        if (size > 20)
            return 1.2f * price;
        else
            return price;
    }
};

class PrintBook : public Book
{
private:
    float weight;
    bool inStock;
public:
    PrintBook(char *ISBN, char *title, char *author, float price, float weight, bool inStock) : Book(ISBN, title,
                                                                                                     author, price)
    {
        this->weight = weight;
        this->inStock = inStock;
    }

    float bookPrice()
    {
        if (weight > 0.7)
            return 1.15f * price;
        else
            return price;
    }
};

bool operator>(Book &b1, Book &b2)
{
    if (b1.bookPrice() > b2.bookPrice())
        return true;
    else
        return false;
}

void mostExpensiveBook(Book **books, int n)
{
    int online = 0;
    int print = 0;

    int index = 0;
    float max = books[0]->bookPrice();

    for (int i = 0; i < n; i++)
        if (dynamic_cast<OnlineBook *>(books[i]))
            online++;
        else if (dynamic_cast<PrintBook *>(books[i]))
            print++;

    for (int i = 0; i < n; i++)
        if (max < books[i]->bookPrice())
        {
            max = books[i]->bookPrice();
            index = i;
        }

    cout << "FINKI-Education" << endl;
    cout << "Total number of online books: " << online << endl;
    cout << "Total number of print books: " << print << endl;
    cout << "The most expensive book is: " << endl;
    cout << *books[index] << endl;
}

int main()
{

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1)
    {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++)
        {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2)
    {
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3)
    {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++)
        {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4)
    {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++)
        {

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1)
            {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else
            {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i < n; i++) delete books[i];
    delete[] books;
    return 0;
}
