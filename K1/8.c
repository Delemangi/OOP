/*
Во програмскиот јазик C да се креира структура Laptop за опишување на спецификациите на даден преносен компјутер. Структурата треба да содржи: (5 поени)

Фирма која го произведува ( низа од 100 знаци)
Големина на монитор во инчи (реален број)
Дали е со touch или не (булова променлива)
Цена (цел број)
Да се креира структура ITStore, што содржи: (5 поени)

Име на продавницата (низа од 100 знаци)
Локација (низа од 100 знаци)
Низа од достапни лаптопи (низа од максимум 100 елементи од структурата Laptop)
Број на елементи во низата (цел број)
Да се креира функција print за печатење на информациите за сите лаптопи во една продавница во формат: (10 поени)

[Ime na prodavnicata] [Lokacija]
[Marka1] [dim_monitor1] [Cena1]
[Marka2] [dim_monitor2] [Cena2]
[Marka3] [dim_monitor3] [Cena3]
...
Да се креира функција najeftina_ponuda, што прима низа од променливи од типот ITStore и го печати името и локацијата на онаа продавница која нуди најевтин преносен компјутер и неговата цена. Најефтин преносен компјутер е оној што има најниска цена и плус опција за touch. Ако има повеќе такви продавници, се печати прво најдената.* (15 поени)*

Да се дополни функцијата main (10 поени).

Од тастатура се внесува бројот на продавници, па потоа за секоја продавница се внесуваат името и локацијата, а потоа бројот на компјутери, па за секој од компјутерите фирма која го произведува, големина на монитор, дали има touch и цена. Потоа се печатат сите внесени продавници и најевтината понуда.
*/
#include <stdio.h>

typedef struct Laptop
{
    char firm[100];
    float size;
    int touch;
    int price;
} Laptop;

typedef struct ITStore
{
    char name[100];
    char location[100];
    Laptop l[100];
    int n;
} ITStore;

void print(ITStore *s, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s %s\n", s[i].name, s[i].location);

        for (int j = 0; j < s[i].n; j++)
        {
            if (s[i].l[j].size == (int) s[i].l[j].size)
                printf("%s %d %d\n", s[i].l[j].firm, (int) s[i].l[j].size, s[i].l[j].price);
            else
                printf("%s %.1f %d\n", s[i].l[j].firm, s[i].l[j].size, s[i].l[j].price);
        }
    }
}

void najeftina_ponuda(ITStore *s, int n)
{
    int min = -1;
    int store;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < s[i].n; j++)
            if (s[i].l[j].touch == 1)
                if (min > s[i].l[j].price || min == -1)
                {
                    min = s[i].l[j].price;
                    store = i;
                }

    printf("Najeftina ponuda ima prodavnicata:\n%s %s\nNajniskata cena iznesuva: %d", s[store].name, s[store].location,
           min);
}

int main()
{
    ITStore s[100];
    int n;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", s[i].name);
        scanf("%s", s[i].location);
        scanf("%d", &s[i].n);

        for (int j = 0; j < s[i].n; j++)
        {
            scanf("%s", s[i].l[j].firm);
            scanf("%f", &s[i].l[j].size);
            scanf("%d", &s[i].l[j].touch);
            scanf("%d", &s[i].l[j].price);
        }
    }

    print(s, n);
    najeftina_ponuda(s, n);

    return 0;
}