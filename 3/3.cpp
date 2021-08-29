/*
Во оваа задача потребно е да се внесат податоци за насловна страница на списание.

За претставување на насловната страница напишете класа FrontPage која ќе содржи:

објект од класата NewsArticle која ја претставува насловната вест на страницата
цена (float price) со предодредена вредност 0
број на издание на списанието (int editionNumber) со предодредена вредност 0
За класата FrontPage напишете предодреден (default) конструктор и конструктор со параметри. Класата NewsArticle треба да содржи:

објект од класата Category која ја претставува категоријата во која спаѓа веста
наслов од максимум 30 знаци (char title[30]) со предодредена вредност untitled
За класата NewsArticle напишете предодреден конструктор и конструктор со параметри.

Класата Category треба да содржи име од максимум 20 знаци (char name[20]) со предодредена вредност unnamed.

За сите класи треба да напишете соодветен метод за печатење print().

Внимајте на редоследот на параметрите во конструкторите. Не го менувајте main методот.

За категоријата се печати само името: Category: [name].

За веста се печати насловот, па категоријата во нов ред:

Title: [title]

category.print()

За насловната страница се печати цената и изданието во прв ред, па веста во втор:

Price: [price], Edition number: [editionNumber]

article.print()
*/
#include<iostream>
#include<cstring>

using namespace std;

class Category
{
private:
    char name[20];
public:
    Category(char *name = "unnamed")
    {
        strcpy(this->name, name);
    }

    void print()
    {
        cout << "Category: " << name << endl;
    }
};

class NewsArticle
{
private:
    Category c;
    char title[30];
public:
    NewsArticle()
    {
        strcpy(title, "untitled");
    }

    NewsArticle(Category c, char *title = "untitled")
    {
        this->c = c;
        strcpy(this->title, title);
    }

    void print()
    {
        cout << "Article title: " << title << endl;
        c.print();
    }
};

class FrontPage
{
private:
    NewsArticle n;
    float price;
    int editionNumber;
public:
    FrontPage()
    {
        editionNumber = 0;
        price = 0;
    }

    FrontPage(NewsArticle n, float price, int editionNumber = 0)
    {
        this->n = n;
        this->price = price;
        this->editionNumber = editionNumber;
    }

    void print()
    {
        cout << "Price: " << price << ", Edition number: " << editionNumber << endl;
        n.print();
    }
};

int main()
{
    char categoryName[20];
    char articleTitle[30];
    float price;
    int editionNumber;

    int testCase;
    cin >> testCase;


    if (testCase == 1)
    {
        int iter;
        cin >> iter;
        while (iter > 0)
        {
            cin >> categoryName;
            cin >> articleTitle;
            cin >> price;
            cin >> editionNumber;
            Category category(categoryName);
            NewsArticle article(category, articleTitle);
            FrontPage frontPage(article, price, editionNumber);
            frontPage.print();
            iter--;
        }
    }
    else if (testCase == 2)
    {
        cin >> categoryName;
        cin >> price;
        cin >> editionNumber;
        Category category(categoryName);
        NewsArticle article(category);
        FrontPage frontPage(article, price, editionNumber);
        frontPage.print();
    }// test case 3
    else if (testCase == 3)
    {
        cin >> categoryName;
        cin >> articleTitle;
        cin >> price;
        Category category(categoryName);
        NewsArticle article(category, articleTitle);
        FrontPage frontPage(article, price);
        frontPage.print();
    }
    else
    {
        FrontPage frontPage = FrontPage();
        frontPage.print();
    }
    return 0;
}