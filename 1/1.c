/*
За програмски јазик C.

Да се напише програма во која од стандарден влез се вчитува N (бројот на производи), а потоа се вчитуваат податоците за N производи (име, цена, количина). Програмата треба на стандарден излез да ја отпечати листата на купени производи и вкупната сума која треба да се плати во следниот облик (пример):

1. Flips    10.00 x 3 = 30.00
2. CocaCola 75.00 x 2 = 150.00
3. ChokoBanana  5.00 x 10 = 50.00
Total: 230.00
*/
#include <stdio.h>

typedef struct asdf
{
    char name[15];
    float price;
    float amount;
} p;

int main()
{
    int n;
    float total = 0;
    p a[20];

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%s %f %f", a[i].name, &a[i].price, &a[i].amount);

    for (int i = 0; i < n; i++)
    {
        printf("%d. %s\t%.2f x %.1f = %.2f\n", i + 1, a[i].name, a[i].price, a[i].amount, a[i].price * a[i].amount);
        total += a[i].price * a[i].amount;
    }

    printf("Total: %.2f", total);
}