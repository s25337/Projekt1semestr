#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  

//generowanie tablicy,grafu i macierzy sąsiedztwa
int tab[110][110];
int macierz[12300][12300];
int n,m;
int gdzie (int a, int b){  //komórka a w tab w macierzy x
int pom;
pom=(a-1)*m+b;
return pom;
}
void dodaj_dol(int a, int b){
	macierz[gdzie(a,b)][gdzie(a+1,b)]=tab[a+1][b];
}
void dodaj_dol_lewo(int a, int b){
	macierz[gdzie(a,b)][gdzie(a+1,b-1)]=tab[a+1][b-1];
}

void dodaj_dol_prawo(int a, int b){
	macierz[gdzie(a,b)][gdzie(a+1,b+1)]=tab[a+1][b+1];
}

void dodaj_lewo(int a, int b){
	macierz[gdzie(a,b)][gdzie(a,b-1)]=tab[a][b-1];
}

void dodaj_prawo(int a, int b){
	macierz[gdzie(a,b)][gdzie(a,b+1)]=tab[a][b+1];
}

void dodaj_gora(int a, int b){
		macierz[gdzie(a,b)][gdzie(a-1,b)]=tab[a-1][b];
}

void dodaj_gora_lewo(int a, int b){
		macierz[gdzie(a,b)][gdzie(a-1,b-1)]=tab[a-1][b-1];
}

void dodaj_gora_prawo(int a, int b){
			macierz[gdzie(a,b)][gdzie(a-1,b+1)]=tab[a-1][b+1];
}



int main(){
	
 	srand (time(NULL));
	n = rand() % 5 + 1;
	m = rand() % 5 + 1;
	
	std::cout<<"Generujemy rozmiar tablicy: "<<n<<" x "<<m<<"\n";
	for (int i=1; i<=n; i++){
		for(int j=1; j<=m; j++) tab[i][j]=rand() % 10 + 1;
	}
	
	
	for (int i=1; i<=n; i++){
		for(int j=1; j<=m; j++) std::cout<<tab[i][j]<<" ";
		std::cout<<"\n";
	}

	
	//generujemy macierz sąsiedztwa	 
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
		// 1 i 
		dodaj_lewo(1,i);
		dodaj_prawo(1,i);
		dodaj_dol_prawo(1,i);
		dodaj_dol_lewo(1,i);
		dodaj_dol(1,i);
		
		// n i
		
		dodaj_lewo(n,i);
		dodaj_prawo(n,i);
		dodaj_gora(n,i);
		dodaj_gora_prawo(n,i);
		dodaj_gora_lewo(n,i);

	}
		for(int i=2; i<n; i++){

		// i 1
		
		dodaj_prawo(i,1);
		dodaj_gora(i,1);
		dodaj_gora_prawo(i,1);
		dodaj_dol(i,1);
		dodaj_dol_prawo(i,1);
		
		//i m
		
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
	macierz[0][i]=tab[k][1];
	macierz[i+m-1][(n*m)+1]=1;
	k++;
	}
	
	
	std::cout<<"macierz: \n";
	for(int i=0; i<=n*m+1; i++){
		for(int j=0; j<=n*m+1; j++) std::cout<<macierz[i][j]<<" ";
		std::cout<<"\n";
	}
	
}
