#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <string>
using namespace std;
vector < double > dane;
string nazwaPliku = "punkty.txt";


double newton(int liczba_punktow, double* X, double* Y, double szukana) {
	//na poczatku do wyniku dopisujemy Y[0], czyli f(x[0])  - tak jak w rownaniu W[n](x) = f(x[0]) + ...
	double wynik = Y[0];	

	//tablica ta bedzie przechowywac ilorazy roznicowe kolejnych rzedow.
	double* ilorazy_roznicowe = new double[liczba_punktow];	
	ilorazy_roznicowe[0] = Y[0];		
		
	for (size_t i = 1; i < liczba_punktow; i++)
	{
		ilorazy_roznicowe[i] = Y[i];
		double iloczyn_roznic = 1.0;
		//zmienna potrzebna do wyliczania kolejnych iloczynow 
		//(x-x[0])(x-x[1])(x-x[2])*...*(x-x[n-1]) -> x to nasza szukana w tym przypadku

		for (size_t j = 0; j < i; j++)
		{
			//obliczanie ilorazow kolejnych rzedow
			ilorazy_roznicowe[i] = (ilorazy_roznicowe[i] - ilorazy_roznicowe[j]) / (X[i] - X[j]);	
			iloczyn_roznic = iloczyn_roznic*(szukana - X[j]);	//obliczanie kolejnych iloczynow 
			
		}
		cout << "iloraz roznicowy rzedu " << i << " rowny jest " << ilorazy_roznicowe[i] << endl;	
		//wyswietlenie ilorazow roznicowych kolejnych rzedow.
		wynik += ilorazy_roznicowe[i] * iloczyn_roznic;		
		//powiekszanie wyniku o kolejne "bloki": 
		//-> [x[0],x[1]](x-x[0])+...+ [x[0],x[1],...,x[n]](x-x[0])(x-x[1])(x-x[2])*...*(x-x[n-1])

	}
	delete[] ilorazy_roznicowe;		//zwalniamy miejsce w pamieci
	return wynik;		//zwracamy wynik
}


double lagrange(int liczba_punktow, double* X, double* Y, double szukana) {	//funkcja realizuj¹ca Interpolacje Lagrange'a.
	double wspolczynnik_l = 0;  //zmienna przechowuj¹ca wartoœæ pojedynczego iloczynu Y[i]*L[i](x) 
	double wynik = 0;
	for (int i = 0; i < liczba_punktow; i++) {
		wspolczynnik_l = Y[i];					//zapisanie wartoœci kolejnych Y[i](x)
		for (int j = 0; j < liczba_punktow; j++)
		{
			if (j != i) {
				wspolczynnik_l *= (szukana - X[j]) / (X[i] - X[j]);	//obliczenie wspó³czynnika L[i](x)
			}
		}
		wynik += wspolczynnik_l;
	}
	return wynik;
}

//Funkcja pobierj¹ca dane z pliku tekstowego i zapisuj¹ce je do wektora.
int pobranie_z_pliku(vector <double>* data, string fileName) { 
	string linia;
	fstream plik;

	plik.open(fileName, ios::in);
	if (plik.good() == true)
	{
		while (!plik.eof())
		{
			getline(plik, linia, ',');		//zapisuje s³owa odzielane przecinkami 
			double d = atof(linia.c_str());
			data->push_back(d);				//zapis s³owa parsowanego na typ double do wektora
		}
		plik.close();
	}
	if (data->size() % 2 == 1) {	//zabezpiecznie w razie Ÿle wype³nionego pliku tekstowego 
		cout << "bledne dane w pliku" << endl;
		return -1;
	}
	return data->size();	//funkcja zwraca wielkosc wektora potrzebna do stworzenia tablic przechowuj¹cych X i Y
}

int main() {
	////////////SPRAWDZZANIE POPRAWNOSCI PLIKU////////////
	int wielkosc_wektora = pobranie_z_pliku(&dane, nazwaPliku);
	if (wielkosc_wektora == -1)	//program zostanie przerwany jesli plik tekstowy by³ b³êdny
	{
		return -1;
	}
	////////////////////////

	////////////WYPE£NIANIE TABLIC////////////
	int liczba_punktow = wielkosc_wektora / 2; //wielkosc wektora podzielona przez 2 powinna nam daæ iloœ punktów zapisanych w pliku 
	double* X = new double[liczba_punktow];		//tablica wspó³rzêdnych x
	double* Y = new double[liczba_punktow];		//tablica wspó³rzêdnych y
	int j = 0;
	for (size_t i = 0; i < dane.size(); i++)	//wype³anienie tablic
	{
		if (i % 2 == 0) {
			X[j] = dane[i];
		}
		else {
			Y[j] = dane[i];
			j++;
		}
	}
	////////////////////////
	double szukana;
	char wybor;	
	////////////MENU////////////
	for (;;)
	{
		cout << endl;
		cout << "MENU GLOWNE" << endl;
		cout << "-----------------" << endl;
		cout << "1. Interpolacja Lagrange'a" << endl;
		cout << "2. Interpolacja Newtona'a" << endl;
		cout << "3. Koniec programu" << endl;

		cout << endl;
		cin >> wybor;

		switch (wybor)		//switch pozwalajacy wybrac funkcje z menu
		{
		case '1':
			cout << "Interpolacja Lagrange'a dla punktow" << endl;
			for (size_t i = 0; i < liczba_punktow; i++)	//wypisanie zawartosci tablic
			{
					cout << "f(" << X[i] << ") = " << Y[i] <<endl;
			}
			cout << "Podaj wartosc szukanego x: ";
			cin >> szukana;
			cout << endl;
			cout << "Wartosc dla podanego x to: " << lagrange(liczba_punktow, X, Y, szukana) << endl;
			break;

		case '2':
			cout << "Interpolacja Newtona'a dla punktow" << endl;
			for (size_t i = 0; i < liczba_punktow; i++)	//wypisanie zawartosci tablic
			{
				cout << "f(" << X[i] << ") = " << Y[i] << endl;
			}
			cout << "Podaj wartosc szukanego x: ";
			cin >> szukana;
			cout << endl;
			cout << "Wartosc dla podanego x to: " << newton(liczba_punktow, X, Y, szukana) << endl;
			break;
		
		case '3':
			exit(0);
			break;

		default: cout << "Nie ma takiej opcji w menu!";
		}
		getchar(); getchar();
		system("cls");
	}
	////////////////////////

	
	return 0;
}