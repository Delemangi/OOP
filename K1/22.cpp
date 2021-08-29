/*
Да се креира структура Proizvod во која се чуваат податоци за кодот напрозиводот (низа од 20 знаци), единична цена на производ (цел број), бројот на достапни производи кои ги има во еден магацин (цел број) .

Потоа да се креирa структура Narachka во која се чуваат податоци за името лицето кое ја прави нарачката (низи од 15 знаци), низа од Proizvodi (максимум 10) кои ги има во нарачката, низа од бројот на нарачани производи за секоја производ посебно (максимум10) и бројот на производи во нарачката .

Треба да се направи функција со потпис

void pecatiFaktura(Narachka n)

која што ќе ги отпечати една фактура за една нарачка (n) .

Во фактурата во првиот ред се печати: Faktura za XXXXX, каде XXXXX е името на лицето кое ја прави нарачката.

Ако сите производи може да се нарачаат печатат нарачаните производи, подредени по азбучен ред според кодот на производот. Во следните редови, во секој ред посебно се печати кодот на производот, единична цена на производот, број на нарачани производи и вкупната цена на производот (сите се одделени со едно празно место) . Исто така бројот на достапни производи од тој производ да се ажурира (да се намали за бројот на нарачани производи од тој производ). Во последниот ред да се отпечати: Vkupnata suma na fakturata e XXX, каде XXX е вкупната сума за цените за сите нарачани производи.

Ако постои производ кој не може да биде нарачан затоа што во магацинот не се достапни нарачаниот број производи тогаш не може да се изготви фактура за нарачката. На екранот да се отпечати: Fakturata ne moze da se izgotvi.
*/
#include <stdio.h>
#include <string.h>

//место за вашиот код

typedef struct Proizvod
{
    char code[20];
    int price;
    int n;
} Proizvod;

typedef struct Narachka
{
    char name[15];
    Proizvod p[10];
    int orders[10];
    int n;
} Narachka;

void pecatiFaktura(Narachka na)
{
    int total = 0;
    Proizvod temp;

    printf("Faktura za %s\n", na.name);

    for (int i = 0; i < na.n; i++)
        for (int j = 0; j < na.n - 1 - i; j++)
            if (*na.p[j].code > *na.p[j + 1].code ||
                (*na.p[j].code == *na.p[j + 1].code && na.p[j].code[1] > na.p[j + 1].code[1]))
            {
                temp = na.p[j];
                na.p[j] = na.p[j + 1];
                na.p[j + 1] = temp;
            }

    for (int i = 0; i < na.n; i++)
        if (na.orders[i] > na.p[i].n)
        {
            printf("Fakturata ne moze da se izgotvi");
            return;
        }
        else
        {
            printf("%s %d %d %d\n", na.p[i].code, na.p[i].price, na.orders[i], na.p[i].price * na.orders[i]);
            total += na.p[i].price * na.orders[i];
        }

    printf("Vkupnata suma na fakturata e %d", total);
}

int main()
{

    Narachka narachka;

    // внеси го името лицето кое ја прави нарачката
    scanf("%s", narachka.name);
    // внеси го бројот на порачани производи во нарачката
    scanf("%d", &narachka.n);

    int i;
    //за секој од нарачаните производи се внесуваат информации
    for (i = 0; i < narachka.n; ++i)
    {
        // внеси код
        scanf("%s", narachka.p[i].code);
        // внеси единицчна цена
        scanf("%d", &narachka.p[i].price);
        // внеси број на производи во магацин
        scanf("%d", &narachka.p[i].n);
    }
    //за секој производ се внесува колку такви производи се порачани во нарачката
    int j;
    for (j = 0; j < narachka.n; ++j)
    {
        //се внесува број на производи во нарачката
        scanf("%d", &narachka.orders[j]);
    }


    // повик на функцијата pecatiFaktura
    pecatiFaktura(narachka);


    return 0;
}