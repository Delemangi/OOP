/*
Да се дефинира апстрактна класа Employee којашто ќе содржи име на вработениот, години и работно искуство во години (integer). Да се дефинираат чисти виртуелни функции plata() и bonus() (double).

Од класата Employee да се изведе класа SalaryEmployee која покрај основните информации содржи и информација за основната плата. Бонусот на овие работници се пресметува како процент од основната плата, а процентот е бројот на години со работно искуство. На пример ако работеле 10 години, бонусот е 10 проценти од основната плата. Вкупната плата се пресметува како основната плата плус бонусот.

Од класата Employee исто така да се изведе класа HourlyEmployee која покрај основните информации содржи информација и за вкупниот број на часови кои ги одработил работникот и платата по час. Вкупната плата се пресметува како бројот на часови помножен со платата по час плус бонусот, додека бонусот се пресметува на следниот начин: За секој час над 320-тиот се добива 50 проценти од платата по час.

Од класата Employee на крај се изведува класата Freelancer која покрај основните информации содржи и број на проекти на кои работел вработениет и низа со суми кои ги добил за тие проекти (double). По направени 5 проекти, за секој нареден вработените добиваат бонус од 1000 денари. Вкупната плата на овој тип на вработени изнесува вкупната сума добиена од сите проекти плус бонусот.

Да се преоптовари операторот == кој ќе прима два објекти од класата Employee и ќе ги споредува според тоа дали имаат ист број на години и дали добиваат ист бонус.

Да се дефинира класа Company која ќе содржи информации за името на компанијата, бројот на вработени, и динамична низа од покажувачи од класата Employee или Employee **. За потребите на оваа класа треба да се дефинира конструктор кој прима само еден аргумент - името на компанијата, да се преоптовари операторот += и да се дефинираат следните методи:

double vkupnaPlata() - метод којшто ја враќа вкупната плата на сите вработени во компанијата
double filtriranaPlata(Employee * emp) - метод којшто ја враќа платата само на работниците кои се еднакви со дадениот вработен (според оператор ==)
void pecatiRabotnici() - метод којшто печати по колку вработени има од секој тип на работници во компанијата, а форматот на печатење можете да го видите од тест примерите
Hint: За потребите на последниот метод можете да искористите статички членови и статички функции во секоја од класата, dynamic_cast, виртуелна функција која ќе ја преоптоварите во секоја од класите или нешто друго по ваша желба.
*/
#include <iostream>
#include <cstring>

using namespace std;

class Employee
{
protected:
    char name[50];
    int age;
    int experience;
public:
    Employee(char *name = "", int age = 0, int experience = 0)
    {
        strcpy(this->name, name);
        this->age = age;
        this->experience = experience;
    }

    bool operator==(Employee &e)
    {
        return (age == e.age && bonus() == e.bonus());
    }

    virtual double bonus() = 0;

    virtual double plata() = 0;
};

class SalaryEmployee : public Employee
{
private:
    int basic;
public:
    SalaryEmployee(char *name = "", int age = 0, int experience = 0, int basic = 0) : Employee(name, age, experience)
    {
        this->basic = basic;
    }

    double bonus()
    {
        return (basic * experience) / 100.0;
    }

    double plata()
    {
        return basic + bonus();
    }
};

class HourlyEmployee : public Employee
{
public:
    int hours;
    int wage;
public:
    HourlyEmployee(char *name = "", int age = 0, int experience = 0, int hours = 0, int wage = 0) : Employee(name, age,
                                                                                                             experience)
    {
        this->hours = hours;
        this->wage = wage;
    }

    double bonus()
    {
        if (hours > 320)
            return (hours - 320) * wage * 0.5;
        else
            return 0;
    }

    double plata()
    {
        return hours * wage + bonus();
    }
};

class Freelancer : public Employee
{
private:
    int projects;
    double salary[50];
public:
    Freelancer(char *name = "", int age = 0, int experience = 0, int projects = 0, double *salary = 0) : Employee(
            name, age, experience)
    {
        this->projects = projects;
        for (int i = 0; i < projects; i++)
            this->salary[i] = salary[i];
    }

    double bonus()
    {
        if (projects > 5)
            return (projects - 5) * 1000;
        else
            return 0;
    }

    double plata()
    {
        double s = bonus();

        for (int i = 0; i < projects; i++)
            s += salary[i];

        return s;
    }
};

class Company
{
private:
    char name[50];
    int employees;
    Employee **e;
public:
    Company(char *name = "")
    {
        strcpy(this->name, name);
        employees = 0;
        e = new Employee *[0];
    }

    ~Company()
    {
        delete[] e;
    }

    Company &operator+=(Employee *emp)
    {
        Employee **temp = new Employee *[employees + 1];

        for (int i = 0; i < employees; i++)
            temp[i] = e[i];
        temp[employees] = emp;

        delete[] e;
        e = temp;
        employees++;

        return *this;
    }

    double vkupnaPlata()
    {
        double s = 0;

        for (int i = 0; i < employees; i++)
            s += e[i]->plata();

        return s;
    }

    double filtriranaPlata(Employee *emp)
    {
        double s = 0;

        for (int i = 0; i < employees; i++)
            if (*e[i] == *emp)
                s += e[i]->plata();

        return s;
    }

    void pecatiRabotnici()
    {
        int s = 0, h = 0, f = 0;

        for (int i = 0; i < employees; i++)
        {
            SalaryEmployee *salary = dynamic_cast<SalaryEmployee *>(e[i]);
            HourlyEmployee *hourly = dynamic_cast<HourlyEmployee *>(e[i]);
            Freelancer *free = dynamic_cast<Freelancer *>(e[i]);

            if (dynamic_cast<SalaryEmployee *>(e[i]))
                s++;
            else if (dynamic_cast<HourlyEmployee *>(e[i]))
                h++;
            else if (dynamic_cast<Freelancer *>(e[i]))
                f++;
        }

        cout << "Vo kompanijata " << name << " rabotat: " << endl;
        cout << "Salary employees: " << s << endl;
        cout << "Hourly employees: " << h << endl;
        cout << "Freelancers: " << f << endl;
    }
};

int main()
{

    char name[50];
    cin >> name;
    Company c(name);

    int n;
    cin >> n;

    char employeeName[50];
    int age;
    int experience;
    int type;

    for (int i = 0; i < n; ++i)
    {
        cin >> type;
        cin >> employeeName >> age >> experience;

        if (type == 1)
        {
            int basicSalary;
            cin >> basicSalary;
            c += new SalaryEmployee(employeeName, age, experience, basicSalary);
        }

        else if (type == 2)
        {
            int hoursWorked;
            int hourlyPay;
            cin >> hoursWorked >> hourlyPay;
            c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
        }

        else
        {
            int numProjects;
            cin >> numProjects;
            double projects[10];
            for (int i = 0; i < numProjects; ++i)
            {
                cin >> projects[i];
            }
            c += new Freelancer(employeeName, age, experience, numProjects, projects);
        }
    }

    c.pecatiRabotnici();
    cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
    Employee *emp = new HourlyEmployee("Petre_Petrov", 31, 6, 340, 80);
    cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

    delete emp;
}