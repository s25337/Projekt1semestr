#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  

//generowanie tablicy,grafu i macierzy sąsiedztwa
int tab[110][110];
int u,n,m,x,y,z,v0,np;
const int MAX_N = 100000; // maksymalna ilość wierzchołków w grafie (100x100)
const int INF = 2147483647;
int d[MAX_N+1],p[MAX_N+1];
bool QS[MAX_N+1];
struct TW *L[MAX_N+1],*pw;

struct TW
{
  int wierzcholek;            // numer wierzchołka
  int waga;          // waga krawędzi
  struct TW * next; // następny element listy
};

void dodaj_krawedz(int x, int y, int z){

    if(x > np) np = x;
    if(y > np) np = y;
    pw = new TW;
    pw->next = L[x]; pw->wierzcholek = y; pw->waga = z; L[x] = pw;
	
}

int gdzie (int a, int b){  //nr wierzchołka
int pom;
pom=(a-1)*m+b;
return pom;
}
int gdzie_odwrotnie(int x){  //wierzchołek x w tablicy
int a=0,b=0;
a=x/m;
a = x/m + (x % m != 0);
b=x%m;
if(b==0) b=m;
return tab[a][b];

}


void dodaj_dol(int a, int b){
	dodaj_krawedz(gdzie(a,b),gdzie(a+1,b),tab[a+1][b]);
}
void dodaj_dol_lewo(int a, int b){
	dodaj_krawedz(gdzie(a,b),gdzie(a+1,b-1),tab[a+1][b-1]);
}

void dodaj_dol_prawo(int a, int b){
	dodaj_krawedz(gdzie(a,b),gdzie(a+1,b+1),tab[a+1][b+1]);
}

void dodaj_lewo(int a, int b){
		dodaj_krawedz(gdzie(a,b),gdzie(a,b-1),tab[a][b-1]);
}

void dodaj_prawo(int a, int b){
		dodaj_krawedz(gdzie(a,b),gdzie(a,b+1),tab[a][b+1]);
}

void dodaj_gora(int a, int b){
	dodaj_krawedz(gdzie(a,b),gdzie(a-1,b),tab[a-1][b]);
}

void dodaj_gora_lewo(int a, int b){
	dodaj_krawedz(gdzie(a,b),gdzie(a-1,b-1),tab[a-1][b-1]);
}

void dodaj_gora_prawo(int a, int b){
	dodaj_krawedz(gdzie(a,b),gdzie(a-1,b+1),tab[a-1][b+1]);
}


int main(){
	std::cout<<"Podaj ilość wierszy: ";
	std::cin>>n;
	std::cout<<"Podaj ilość kolumn: ";
	std::cin>>m;
 	srand (time(NULL));
	int rozmiar=n*m+1;
	std::cout<<"Generujemy tablicę... \n";
	
	for(int i=0; i<=rozmiar; i++){
    d[i]  = INF;    // koszty dojścia
    p[i]  = 0;      // poprzednik na ścieżce
    QS[i] = false; // przynależność do Q (false) lub S (true)
    L[i]  = NULL;   // lista sąsiedztwa
  }
  	v0=0;  //wierzchołek startowy
	
	for (int i=1; i<=n; i++){
		for(int j=1; j<=m; j++) tab[i][j]=rand() % 9 + 1;
	}
	

	
	
	for (int i=1; i<=n; i++){
		for(int j=1; j<=m; j++) std::cout<<tab[i][j]<<" ";
		std::cout<<"\n";
	}
	//przypadki brzegowe
	
	if(n==1 && m==1){
	std::cout<<"sciezka: "<<tab[1][1]<<"\n";
	std::cout<<"wynik: "<<tab[1][1];
	return 0;
	}	
	
	if(n==1){
	int wyn=0;
	std::cout<<"sciezka: ";
	for(int i=1; i<=m; i++){
		std::cout<<tab[1][i]<<" ";
		wyn+=tab[1][i];
	}
		std::cout<<"\n";
		std::cout<<"wynik: "<<wyn;
		return 0;
	}	
	
	if(m==1){
	int wyn=2345265;
	int miejsce=0;
	for(int i=1; i<=n; i++){
		if(tab[i][1]<wyn) {
		wyn=tab[i][1]; 
		miejsce=i;		
		}
	}
		std::cout<<"sciezka: \n"<<wyn;
		std::cout<<"\n";
		std::cout<<"wynik: "<<wyn;
		return 0;
	}	

	//dodawanie krawędzi do wszystkich wierzchołków, które mają 8 krawędzi (są w środku)
	
	for (int i=2; i<n; i++){
	for(int j=2; j<m; j++){
		dodaj_gora(i,j);
		dodaj_dol(i,j);
		dodaj_lewo(i,j);
		dodaj_prawo(i,j);
		dodaj_gora_prawo(i,j);
		dodaj_gora_lewo(i,j);
		dodaj_dol_prawo(i,j);
		dodaj_dol_lewo(i,j);
		}
	}
	//kazdy róg ma trzy krawędzie
	dodaj_dol(1,1);
	dodaj_prawo(1,1);
	dodaj_dol_prawo(1,1);
	dodaj_dol(1,m);
	dodaj_lewo(1,m);
	dodaj_dol_lewo(1,m);	
	dodaj_prawo(n,1);
	dodaj_gora(n,1);
	dodaj_gora_prawo(n,1);
	dodaj_lewo(n,m);
	dodaj_gora(n,m);
	dodaj_gora_lewo(n,m);

	//krawędzie które mają po 5 krawędzi
	
	for(int i=2; i<m; i++){
		dodaj_lewo(1,i);
		dodaj_prawo(1,i);
		dodaj_dol_prawo(1,i);
		dodaj_dol_lewo(1,i);
		dodaj_dol(1,i);	
		dodaj_lewo(n,i);
		dodaj_prawo(n,i);
		dodaj_gora(n,i);
		dodaj_gora_prawo(n,i);
		dodaj_gora_lewo(n,i);
	}
		for(int i=2; i<n; i++){	
		dodaj_prawo(i,1);
		dodaj_gora(i,1);
		dodaj_gora_prawo(i,1);
		dodaj_dol(i,1);
		dodaj_dol_prawo(i,1);	
		dodaj_lewo(i,m);
		dodaj_gora_lewo(i,m);
		dodaj_gora(i,m);
		dodaj_dol(i,m);
		dodaj_dol_lewo(i,m);	
	}
	
	
	//dodajemy dwa wierzchołki - pierwszy posiada krawędź do całej pierwszej kolumny, drugi od całej ostatniej
	int pom=(n-1)*m;
	int k=1;
	for(int i=1; i<pom+2; i+=m){
	dodaj_krawedz(0,i,tab[k][1]);
	dodaj_krawedz(i+m-1,n*m+1,1);
	k++;
	}
	
	d[v0] = 0;
	np=n*m+1;  

	for(int i = 0; i <= np; i++){

// szukamy wierzchołka w Q o najmniejszym d
    u = -1;
    for(int j = 0; j <= np; j++)
      if(!QS[j] && ((u == -1) || (d[j] < d[u]))) u = j;
// znaleziony wierzchołek przenosimy do S
    QS[u] = true;
// Modyfikujemy odpowiednio wszystkich sąsiadów z Q
    pw = L[u];
    while(pw)
    {
      if(!QS[pw->wierzcholek] && (d[pw->wierzcholek] > d[u] + pw->waga))
      {
        d[pw->wierzcholek] = d[u] + pw->waga;
        p[pw->wierzcholek] = u;
      }
      pw = pw->next;
    }
  }
// Gotowe, wyświetlamy wyniki - odległości od wierzchołka n*m+1
	int stos[MAX_N],ws; 
    ws = 0; 
	int j = n*m+1;
// Wierzchołki z końca ścieżki umieszczamy na stosie
    while(j)
    {
      stos[ws++] = j; j = p[j]; 
    }
// Wypisujemy kolejne wierzchołki ze szczytu stosu
	ws--; //niech nie wypisuje dodanego zerowego wierzchołka
	int sprawdz=0;
	std::cout << "ściezka:\n";
	while(ws){
//	std::cout << stos[ws] << " ";
	std::cout << gdzie_odwrotnie(stos[ws])<< " ";
	sprawdz+=gdzie_odwrotnie(stos[ws]);
	ws--;
	
} 
// Wypisujemy koszt dojścia
	std::cout<<"\n";
    std::cout << "wynik: " << d[n*m+1]-1 <<"\n";    
  }                
	


