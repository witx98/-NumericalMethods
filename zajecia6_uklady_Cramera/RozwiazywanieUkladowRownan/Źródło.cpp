#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
using namespace std;
vector < double > dane;
string nazwaPliku = "punkty.txt";

//Funkcja pobierj¹ca dane z pliku tekstowego i zapisuj¹ce je do wektora.
int pobranie_z_pliku(vector <double>* data, string fileName) {
	string linia;
	fstream plik;

	plik.open(fileName, ios::in);		//otwarcie pliku
	if (plik.good() == true)			//sprawdzenie poprawnosci pliku 
	{
		while (!plik.eof())
		{
			getline(plik, linia, ',');		//zapisuje s³owa odzielane przecinkami 
			double d = atof(linia.c_str());	//konwersja stringa na double
			data->push_back(d);				//zapis s³owa parsowanego na typ double do wektora
		}
		plik.close();		//zamkniêcie pliku 
	}
	if (data->size() % 4 == 1) {	//zabezpiecznie w razie Ÿle wype³nionego pliku tekstowego 
		cout << "bledne dane w pliku" << endl;
		return -1;
	}
	return data->size();	//funkcja zwraca wielkosc wektora potrzebna do stworzenia tablic X, Y, Z i R 
}

double wyznacznik(double* i, double* j) {
	double wynik = i[0] * j[1] - j[0] * i[1];
	return wynik;
}

double wyznacznik(double* i, double* j, double* k) {	//Pomocnicza funkcja licz¹ca wartoœæ przes³anego wyznacznika 
	double wynik = i[0] * j[1] * k[2] + j[0] * k[1] * i[2] + k[0] * i[1] * j[2] - j[0] * i[1] * k[2] - i[0] * k[1] * j[2] - k[0] * j[1] * i[2];
	return wynik;
}


double interpolacjaWielomianowa(double* X, double* Y, double* Z, double* R, double szukana) {

	double W = wyznacznik(X, Y, Z);
	double Wx = wyznacznik(R, Y, Z);
	double Wy = wyznacznik(X, R, Z);
	double Wz = wyznacznik(X, Y, R);

	if (W == 0) {		//Sprawdzenie 
		if (Wx == 0 && Wy == 0 && Wz == 0) {
			cout << "Uk³ad nieoznaczony" << endl;
			return 0;
		}
		else if (Wx != 0 || Wy != 0 && Wz != 0) {
			cout << "Uk³ad sprzeczny" << endl;
			return -1;
		}
	}
	else if (W != 0) {
		double wspX = Wx / W;
		double wspY = Wy / W;
		double wspZ = Wz / W;
		cout << "X " << wspX << endl;
		cout << "Y " << wspY << endl;
		cout << "Z " << wspZ << endl;
		double wynik = wspX * szukana * szukana + wspY * szukana + wspZ;
		return wynik;
	}	
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
	int liczba_punktow = wielkosc_wektora / 4; //wielkosc wektora podzielona przez 4 powinna nam daæ iloœ punktów zapisanych w pliku 
	double* X = new double[liczba_punktow];		//tablica wspó³czynnikow x
	double* Y = new double[liczba_punktow];		//tablica wspó³czynnikow y
	double* Z = new double[liczba_punktow];		//tablica wspó³czynnikow Z
	double* R = new double[liczba_punktow];		//tablica wynikow r
	int j = 0;
	for (size_t i = 0; i < dane.size(); i++)	//wype³anienie tablic
	{
		if (i % 4 == 0) {
			X[j] = dane[i];
		}
		if (i % 4 == 1) {
			Y[j] = dane[i];
		}
		if (i % 4 == 2) {
			Z[j] = dane[i];
		}
		if (i % 4 == 3) {
			R[j] = dane[i];
			j++;
		}
	}

	double szukana;
	cout << "Wzory Cramera i interpolacja Wielomianowa" << endl;
	for (size_t i = 0; i < liczba_punktow; i++)	//wypisanie zawartosci tablic
	{
		cout  << X[i] << "x + " << Y[i] <<"y + " << Z[i] <<"z = "<<R[i] << endl;
	}
	cout << "Podaj wartosc szukanego x: ";
	cin >> szukana;
	cout << endl;
	cout << "Wartosc funkcji dla podanego x to: " << interpolacjaWielomianowa(X, Y, Z, R, szukana) << endl;

	getchar(); getchar();

	return 0;
}