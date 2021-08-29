/*
Потребно е да се имплементираат класи File (датотека) и Folder (директориум) за работа со едноставен податочен систем.

Во класата File треба да се чуваат следниве податоци:

Име на датотеката (динамички алоцирана низа од знаци)
Екстензија на датотеката (енумерација со можни вредности: txt, pdf, exe)
Име на сопственикот на датотеката (динамички алоцирана низа од знаци)
Големина на датотеката (цел број на мегабајти)
Дополнително, во класата потребно е да се напишат и:

Конструктор без параметри
Конструктор со параметри
Конструктор за копирање
Деструктор
Преоптоварување на операторот =
Метод за печатење на информациите за една датотека (видете го излезот од тест примерите за структурата на печатење) - print()
Метод за проверка на еднаквост помеѓу две датотеки со потпис bool equals(const File & that) кој ќе враќа true ако датотеките имаат исто име, екстензија и сопственик
Метод за споредба на типот помеѓу две датотеки со потпис bool equalsType(const File & that) кој ќе враќа true ако датотеките се од ист тип, т.е. имаат исто име и екстензија
Во класата Folder треба да се чуваат следниве податоци:

Име на директориумот (динамички алоцирана низа од знаци)
Број на датотеки во него (на почеток директориумот е празен)
Динамички алоцирана низа од датотеки, објекти од класата File
Дополнително, во класата потребно е да се напишат и:

Конструктор со потпис Folder(const char* name)
Деструктор
Метод за печатење на информациите за еден директориум (видете го излезот од тест примерите за структурата на печатење) - print()
Метод за бришење на датотека од директориумот со потпис void remove(const File & file) кој ќе ја избрише првата датотека од директориумот која е еднаква според equals методот
Метод за додавање на датотека во директориумот со потпис void add(const File & file) кој ќе додава датотеката во директориумот
Не го менувајте почетниот код.
*/
#include<iostream>
#include<cstring>

using namespace std;

enum Extension
{
    pdf, txt, exe
};

char ex[3][4] = {"pdf", "txt", "exe"};

class File
{
private:
    char *name;
    Extension ext;
    char *owner;
    int size;

public:
    File()
    {
        this->name = new char[100];
        this->owner = new char[100];
    }

    File(char *name1, char *owner1, int size1, Extension ext1)
    {
        this->name = new char[100];
        this->owner = new char[100];

        strcpy(this->name, name1);
        strcpy(this->owner, owner1);
        this->size = size1;
        this->ext = ext1;
    }

    File(const File &other) : File(other.name, other.owner, other.size, other.ext)
    {}

    ~File()
    {
        delete[] this->name;
        delete[] this->owner;
    }

    File &operator=(const File &other)
    {
        if (this == &other)
        {
            return *this;
        }

        strcpy(this->name, other.name);
        strcpy(this->owner, other.owner);
        this->size = other.size;
        this->ext = other.ext;

        return *this;
    }

    void print()
    {
        cout << "File name: " << this->name << "." << ex[this->ext] << endl;
        cout << "File owner: " << this->owner << endl;
        cout << "File size: " << this->size << endl;
    }

    bool equals(const File &other)
    {
        if (strcmp(this->name, other.name) == 0)
            if (strcmp(this->owner, other.owner) == 0)
                if (this->ext == other.ext)
                    return true;
        return false;
    }

    bool equalsType(const File &other)
    {
        if (strcmp(this->name, other.name) == 0)
            if (this->ext == other.ext)
                return true;
        return false;
    }
};

class Folder
{
private:
    char *name;
    int files;
    File *f;
public:
    Folder(const char *name1)
    {
        this->name = new char[100];
        this->files = 0;
        this->f = new File[100];
        strcpy(this->name, name1);
    }

    ~Folder()
    {
        delete[] this->name;
        delete[] this->f;
    }

    void print()
    {
        cout << "Folder name: " << this->name << endl;

        for (int i = 0; i < files; i++)
            this->f[i].print();
    }

    void remove(const File &other)
    {
        for (int i = 0; i < this->files; i++)
            if (this->f[i].equals(other))
            {
                for (int j = i; j < files - 1; j++)
                    this->f[j] = this->f[j + 1];

                files--;
                break;
            }
    }

    void add(const File &other)
    {
        this->f[files] = other;
        files++;
    }
};

int main()
{
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1)
    {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2)
    {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3)
    {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4)
    {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0)
        {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else
    {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0)
        {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}