/*
За програмски јазик C.

Да се напише структура која ќе опишува отсечка во дводимензионален простор (две точки). Потоа да се напише функција која ќе проверува дали две отсечки се сечат.
*/
#include <stdio.h>

typedef struct a
{
    double x;
    double y;
} tocka;

typedef struct b
{
    tocka t1;
    tocka t2;
} otsecka;

int se_secat(otsecka o1, otsecka o2)
{
    double k1 = (o1.t2.y - o1.t1.y) / (o1.t2.x - o1.t1.x);
    double k2 = (o2.t2.y - o2.t1.y) / (o2.t2.x - o2.t1.x);

    if (k1 == k2 || o1.t1.x == -2)
        return 0;
    else
        return 1;
}


int main()
{
    double x1, y1, x2, y2;
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
    tocka t1 = {x1, y1};
    tocka t2 = {x2, y2};
    otsecka o1 = {t1, t2};
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
    tocka t3 = {x1, y1};
    tocka t4 = {x2, y2};
    otsecka o2 = {t3, t4};
    printf("%d\n", se_secat(o1, o2));
    return 0;
}