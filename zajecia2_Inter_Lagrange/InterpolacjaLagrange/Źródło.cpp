#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
using namespace std;

double lagrange(int liczba_punktow, double* X, double* Y, double szukana) {	//funkcja realizuj�ca Interpolacje Lagrange'a.
	double wspolczynnik_l = 0;  //zmienna przechowuj�ca warto�� pojedynczego iloczynu Y[i]*L[i](x) 
	double wynik = 0;
	for (int i = 0; i < liczba_punktow; i++) { 
		wspolczynnik_l = Y[i];					//zapisanie warto�ci kolejnych Y[i](x)
		for (int j = 0; j < liczba_punktow; j++)
		{
			if (j != i) {
				wspolczynnik_l *= (szukana - X[j]) / (X[i] - X[j]);	//obliczenie wsp�czynnika L[i](x)
			}
		}
		wynik += wspolczynnik_l;
	}
	return wynik;
}

int pobranie_z_pliku(vector <double>* data, string fileName) { //Funkcja pobierj�ca dane z pliku tekstowego i zapisuj�ce je do wektora.
	string linia;
	fstream plik;

	plik.open(fileName, ios::in);
	if (plik.good() == true)
	{
		while (!plik.eof())
		{
			getline(plik, linia, ',');		//zapisuje s�owa odzielane przecinkami 
			double d = atof(linia.c_str());
			data->push_back(d);				//zapis s�owa parsowanego na typ double do wektora
		}
		plik.close();
	}
	if (data->size() % 2 == 1) {	//zabezpiecznie w razie �le wype�nionego pliku tekstowego 
		cout << "bledne dane w pliku" << endl;
		return -1;
	}
	return data->size();		//funkcja zwraca wielkosc wektora potrzebna do stworzenia tablic przechowuj�cych X i Y
}

int main() {

	vector < double > dane;
	string nazwaPliku = "punkty.txt";
	int wielkosc_wektora = pobranie_z_pliku(&dane, nazwaPliku);
	if (wielkosc_wektora == -1)	//program zostanie przerwany jesli plik tekstowy by� b��dny
	{
		return -1;
	}
	int liczba_punktow = wielkosc_wektora / 2; //wielkosc wektora podzielona przez 2 powinna nam da� ilo� punkt�w zapisanych w pliku 
	double* X = new double[liczba_punktow];		//tablica wsp�rz�dnych x
	double* Y = new double[liczba_punktow];		//tablica wsp�rz�dnych y
	int j = 0;
	for (size_t i = 0; i < dane.size(); i++)	//wype�anienie tablic
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