/*
Во програмскиот јазик C да се креира структура Vozenje за опишување на адреналински возења во забавен парк. Структурата треба да содржи: (5 поени)

Име на возењето ( низа од 100 знаци)
Времетраење во минути (цел број)
Цена (децимален број)
Дали има студентски попуст (1-да, 0-не)
Да се креира структура ZabavenPark, што содржи: (10 поени)

Име на забавниот парк (низа од 100 знаци)
Локација (низа од 100 знаци)
Низа од адреналински возења во паркот (низа од максимум 100 елементи од структурата Vozenje)
Број на елементи во низата (цел број)
Да се креира функција print за печатење на информациите за сите возења во забавниот парк во формат: (10 поени)

[Ime na parkot] [Lokacija]
[Ime1] [Vremetraenje1] [Cena1]
[Ime2] [Vremetraenje2] [Cena2]
[Ime3] [Vremetraenje3] [Cena3]
...
Да се креира функција najdobar_park, што прима низа од променливи од типот ZabavenPark и го печати името и локацијата на паркот кој е најефтин за посета од страна на студенти. Најефтин парк е оној што содржи најголем број возења со студентски попуст. Ако повеќе паркови ги делат овие карактеристики, да се испечати паркот со најголемото времетраење од сите возења.* (20 поени)*

Да се дополни функцијата main (5 поени).
*/
#include <stdio.h>
#include <string.h>

struct Vozenje{
char ime[100];
int traenje;
float cena;
int daliPopust;
};

typedef struct Vozenje Vozenje;

struct ZabavenPark{
char ime[100];
char lokacija[100];
Vozenje niza[100];
int n;
};

typedef struct ZabavenPark ZabavenPark;

void pecati(ZabavenPark * niza, int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
    printf("%s %s\n",niza[i].ime,niza[i].lokacija);
    for(j=0;j<niza[i].n;j++)
    {

    printf("%s %d %.2f\n",niza[i].niza[j].ime,niza[i].niza[j].traenje,niza[i].niza[j].cena);
    }
    }
}

void najdobar_park(ZabavenPark * niza, int n)
{
    int i,j, maxI=0, maxV=0,maxVremetraenje= 0;

    for(i=0;i<n;i++)
    {
        int count=0;
        int vreme=0;
        for(j=0;j<niza[i].n;j++)
        {
            if(niza[i].niza[j].daliPopust==1)
                count++;
            vreme+= niza[i].niza[j].traenje;
        }
        if(count>maxV)
        {
            maxV = count;
            maxI = i;
            maxVremetraenje = vreme;
        }
        else if(count==maxV&&vreme>maxVremetraenje)
        {
            maxI = i;
            maxVremetraenje = vreme;
        }
    }
    printf("Najdobar park: %s %s\n",niza[maxI].ime,niza[maxI].lokacija);
}

int main()
{
	int i, j, n, broj;
	//kreiraj niza od maksimum 100 zabavni parkovi
	ZabavenPark ff[100];
	scanf("%d", &n);
    //citanje na podatocite
    for (i = 0; i < n; i++){
		//ime na festivalot
		scanf("%s", ff[i].ime);
        //mesto
		scanf("%s", ff[i].lokacija);
		//broj na filmovi
		scanf("%d", &ff[i].n);

		for (j = 0; j < ff[i].n; j++){
			scanf("%s", ff[i].niza[j].ime);  			/* Ime na filmot */
			scanf("%d", &ff[i].niza[j].traenje); 		/* Vremetraenje   */
			scanf("%f", &ff[i].niza[j].cena); 	/* Cena */
            scanf("%d", &ff[i].niza[j].daliPopust);	/* Popust */

		}


			}
    pecati(ff,n);
    najdobar_park(ff,n);

	return 0;
}
