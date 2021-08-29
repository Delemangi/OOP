/*
Да се креира структура Воз во која се чуваат податоци за релацијата по која се движи возот (низа од најмногу 50 знаци), предвиден бројот на километри што треба да се поминат (реален број), како и бројот на патници во возот (цел број).

Потоа да се креирa структура ZeleznickaStanica во која се чуваат податоци за градот во кој се наоѓа (низа од 20 знаци), низа од возови што поаѓаат од станицата (најмногу 30) и бројот на возови (цел број).

Треба да се направи функција со потпис

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
во која се печати релацијата и бројот на километри на возот што поминува најкратка релација (најмалку километри), а поаѓа од железничката станица од градот што се проследува како влезен аргумент. Ако има повеќе возови со ист најмал број на километри, да се испечати релацијата на последниот таков.

Забелешка: Задачата да се реши во програмскиот јазик C++
*/
#include<iostream>
#include<cstring>

using namespace std;

class Voz
{
public:
    char rel[50];
    double km;
    int pass;
};

struct ZeleznickaStanica
{
    char city[20];
    Voz v[30];
    int n;
};

void najkratkaRelacija(ZeleznickaStanica *zs, int n, char *grad)
{
    double min = -1;
    int I = 0, J = 0;

    for (int i = 0; i < n; i++)
        if (strcmp(zs[i].city, grad) == 0)
            for (int j = 0; j < zs[i].n; j++)
                if (min == -1)
                    min = zs[i].v[j].km;
                else if (min >= zs[i].v[j].km)
                {
                    min = zs[i].v[j].km;
                    I = i;
                    J = j;
                }

    cout << "Najkratka relacija: " << zs[I].v[J].rel << " (" << zs[I].v[J].km << " km)";
}

int main()
{
    int n;
    cin >> n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i = 0; i < n; i++)
    {
        cin >> zStanica[i].city;
        cin >> zStanica[i].n;

        for (int j = 0; j < zStanica[i].n; j++)
        {
            cin >> zStanica[i].v[j].rel;
            cin >> zStanica[i].v[j].km;
            cin >> zStanica[i].v[j].pass;
        }
    }

    char grad[25];
    cin >> grad;

    najkratkaRelacija(zStanica, n, grad);
    return 0;
}