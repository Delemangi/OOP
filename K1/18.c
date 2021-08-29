/*
Да се креира структура SkiLift во која се чуваат податоци за името на ски лифтот (низа од 15 знаци), максимален број на корисници што може да опслужи на едно возење, дали е пуштен во функција.

Потоа да се креирa структура SkiCenter во која се чуваат податоци за името на скијачкиот центар, држава во која се наоѓа (низи од 20 знаци), низа од ски лифтови (макс 20) што ги има и број на ски лифтови.

Треба да се направи функција со потпис

void najgolemKapacitet(SkiCenter *sc, int n)
која што ќе го отпечати ски центарот што има најголем капацитет за опслужување скијачи (вкупниот број на скијачи кои може да се опслужуваат во еден момент вкупно на сите ски лифтови во центарот). Доколку два ски центри имаат ист капацитет, тогаш се печати оној кој има поголем број на ски лифтови. Притоа треба да се испечатат во посебен ред името, државата и капацитетот на ски центарот. Кога се пресметува капацитет на еден ски центар во предвид се земаат само ски лифтовите кои се поставени дека се во функција.
*/
//STARTER
/*
#include<stdio.h>
#include<string.h>


int main()
{
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		//vnesi ime
		//vnesi drzava
		//vnesi broj na liftovi
        
		
        //za sekoj ski lift vnesi:
			//vnesi ime
            //vnesi maksimalen broj korisnici
            //vnesi dali e pusten vo funkcija
	}
	
    //povik na funkcijata najgolemKapacitet
	
	return 0;
}
*/
//RESENIE
#include<stdio.h>
#include<string.h>

typedef struct SkiLift{
	char ime[20];
	int max_skijaci;
	int voUpotreba;
}skiLift;

typedef struct SkiCenter {
	char ime[20];
	char drzava[20];
	skiLift niza[20];
	int br_lifts;
}skiCenter;

int kapacitet(skiCenter sc)
{
	int i;
	int tmp = 0;
	for (i = 0; i < sc.br_lifts; i++)
	{
		if (sc.niza[i].voUpotreba == 1)
		{
			tmp += sc.niza[i].max_skijaci;
		}
	}
    return tmp;

}
void najgolemKapacitet(skiCenter *sc, int n)
{
	int tmp, i, j, max, max_ind;
	max = 0;
    max_ind = 0;
	for (i = 0; i < n; i++)
	{
		tmp = kapacitet(sc[i]);
        if ((tmp > max) || (tmp == max&&sc[i].br_lifts > sc[max_ind].br_lifts)) { max = tmp; max_ind = i; } 
	}
	printf("%s\n%s\n%d\n", sc[max_ind].ime, sc[max_ind].drzava, max);
}

int main()
{
	int i, j, n, broj;
	skiCenter sc[20];
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		//printf("Ime:");
		scanf("%s", sc[i].ime);
		//printf("\nDrzava:");
		scanf("%s", sc[i].drzava);
		scanf("%d", &sc[i].br_lifts);
        
		for (j = 0; j < sc[i].br_lifts; j++){
			scanf("%s", sc[i].niza[j].ime);
			scanf("%d", &sc[i].niza[j].max_skijaci);
			scanf("%d", &sc[i].niza[j].voUpotreba);
		}
	}
	najgolemKapacitet(sc, n);
	
	return 0;
}
