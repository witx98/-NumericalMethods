#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
using namespace std;

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

int pobranie_z_pliku(vector <double>* data, string fileName) { //Funkcja pobierj¹ca dane z pliku tekstowego i zapisuj¹ce je do wektora.
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
	return data->size();		//funkcja zwraca wielkosc wektora potrzebna do stworzenia tablic przechowuj¹cych X i Y
}

int main() {

	vector < double > dane;
	string nazwaPliku = "punkty.txt";
	int wielkosc_wektora = pobranie_z_pliku(&dane, nazwaPliku);
	if (wielkosc_wektora == -1)	//program zostanie przerwany jesli plik tekstowy by³ b³êdny
	{
		return -1;
	}
	int liczba_punktow = wielkosc_wektora / 2; //wielkosc wektora podzielona przez 2 powinna nam daæ iloœ punktów zapisanych w pliku 
	double* X = new double[liczba_punktow];		//tablica wspó³rzêdnych x
	double* Y = new double[liczba_punktow];		//tablica wspó³rzêdnych y
	int j = 0;
	for (size_t i = 0; i < dane.size(); i++)	//wype³anienie tablic
	{
		if (i % 2 == 0) {
			X[j] = dane[i];		
			cout << "f(" << X[j] << ") = ";
		}
		else {
			Y[j] = dane[i];
			cout << Y[j] << endl;
			j++;
		}
	}

	




	double szukana;
	cout << "Podaj wartosc szukanego x: ";
	cin >> szukana;
	cout << endl;
	cout << "Wartosc dla podanego x to: " << lagrange(liczba_punktow, X, Y, szukana) << endl;	
	return 0;
}