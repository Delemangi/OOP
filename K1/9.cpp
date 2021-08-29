/*
Во програмскиот јазик C++ да се креира структура Laptop за опишување на спецификациите на даден преносен компјутер. Структурата треба да содржи: (5 поени)

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
#include <iostream> 
using namespace std;

struct Laptop{
	char firma[100];
    float golemina;
    bool touch;
    int cena;
    
    void print();
 
};

void Laptop::print(){
	cout << firma << " " << golemina << " " << cena << endl; 

}

struct ITStore{
	char ime[100];
    char lokacija[100];
    Laptop lp[100];
    int n;
    
    void print();
};

void ITStore::print() {
	cout << ime << " " << lokacija << endl;
    for(int i = 0; i < n; i++){
    	lp[i].print();
    }
}

int najmalaCena(ITStore its){
	int min, f = 0;
    for(int i = 0; i<its.n; i++){
        if(its.lp[i].touch){
            if(!f){
            	min = its.lp[i].cena;
                f=1;
            }
            else if(its.lp[i].cena<min)
                min = its.lp[i].cena;
        }
    }
    
    return min;
       
}

void najeftina_ponuda(ITStore its[], int n){
	int min = najmalaCena(its[0]);
    int minI = 0;
    for(int i = 0; i<n; i++){
        if(najmalaCena(its[i]) < min){
            min = najmalaCena(its[i]);
            minI = i;
        }
    }
    
    cout << "Najeftina ponuda ima prodavnicata: " << endl;
    cout << its[minI].ime << " " << its[minI].lokacija << endl;
    cout << "Najniskata cena iznesuva: " << najmalaCena(its[minI]) << endl;
}


int main() {
    ITStore s[100];
    int n;
    cin >> n; //broj na IT prodavnici
    
    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for(int i = 0; i < n; i++){
    	cin >> s[i].ime;
        cin >> s[i].lokacija;
        cin >> s[i].n;
            for(int j = 0; j < s[i].n; j++){
        		cin >> s[i].lp[j].firma;
            	cin >> s[i].lp[j].golemina;
            	cin >> s[i].lp[j].touch;
            	cin >> s[i].lp[j].cena;
        }
    
    }
    
    
    //pecatenje na site prodavnici
    
    for(int i = 0; i<n; i++){
    	s[i].print();
    }
    
    
    //povik na glavnata metoda
    
    najeftina_ponuda(s,n);
    
    return 0;
}