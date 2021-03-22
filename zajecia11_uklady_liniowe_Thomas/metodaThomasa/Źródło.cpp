#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <iomanip> 
#include <chrono>
using namespace std;
vector < double > dane;			 //Pojemnik na dane z pliku
string nazwaPliku = "punkty.txt";//Nazwa pliku tekstowego

//Funkcja pobierjıca dane z pliku tekstowego i zapisujıce je do wektora.
int pobranie_z_pliku(vector <double>* data, string fileName) {
	string linia;
	fstream plik;

	plik.open(fileName, ios::in);		//otwarcie pliku
	if (plik.good() == true)			//sprawdzenie poprawnosci pliku 
	{
		while (!plik.eof())
		{
			getline(plik, linia, ',');		//zapisuje slowa odzielane przecinkami 
			double d = atof(linia.c_str());	//konwersja stringa na double
			data->push_back(d);				//zapis slowa parsowanego na typ double do wektora
		}
		plik.close();		//zamkniecie pliku 
	}
	if (data->size() % 4 != 0) {	//zabezpiecznie w razie zle wypelnionego pliku tekstowego 
		cout << "bledne dane w pliku" << endl;
		return -1;
	}
	return data->size();	//funkcja zwraca wielkosc wektora potrzebna do stworzenia tablic.
}

int Thomas(double *a, double* b, double* c, double* d, double* Wyniki, int dlugosci_tablic) {
	for (int i = 1; i < dlugosci_tablic; i++) //reukowanie wartosci wspolczynnikow 'a'
	{										//wyliczanie wartosci wspolczynnikow 'b','c' i 'd'
		double l = a[i] / b[i - 1];
		a[i] = 0.0;
		b[i] -= l * c[i - 1];
		d[i] -= l * d[i - 1];
	}
	Wyniki[dlugosci_tablic - 1] = d[dlugosci_tablic - 1] / b[dlugosci_tablic - 1]; //wyliczenie pierwszego rozwiazania
	for (int i = dlugosci_tablic - 2; i >= 0; i--)
	{
		Wyniki[i] = (d[i] - c[i] * Wyniki[i + 1]) / b[i];	//wyliczanie reszty rozwiazan 
	}
	return 1;
}
int main() {
	////////////SPRAWDZZANIE POPRAWNOSCI PLIKU////////////
	int wielkosc_wektora = pobranie_z_pliku(&dane, nazwaPliku);
	if (wielkosc_wektora == -1)	//program zostanie przerwany jesli plik tekstowy byl bledny
	{
		return -1;
	}
	//////////////////////////////////////////////////////
	////////////WYPE£NIANIE TABLIC////////////////////////
	double** uklad_rownan;
	size_t liczba_wspolcznnikow = 4;
	size_t dlugosci_tablic = wielkosc_wektora / liczba_wspolcznnikow;
	double* Wyniki = new double[dlugosci_tablic];		//tablica rozwiazan x
	uklad_rownan = new double* [liczba_wspolcznnikow];		//utworzenie macierzy
	for (int i = 0; i < liczba_wspolcznnikow; i++) {
		uklad_rownan[i] = new double[dlugosci_tablic]; //tworzenie wiersza
	}
	int x = 0;
	for (size_t j = 0; j < dlugosci_tablic; j++)
	{
		for (size_t i = 0; i < liczba_wspolcznnikow; i++)	//wypelnienie tablic
		{
			uklad_rownan[i][j] = dane[x];
			x++;
		}
	}
	//////////////////////////////////////////////////////

	////////////WYPISANIE POCZATKOWEGO UKLADU/////////////
	cout << "a" << setw(6) << "b" << setw(6) << "c" << setw(6) << "| " << "d"<< endl;
	for (size_t i = 0; i < 20; i++)
	{
		cout << "-";
	}
	cout << endl;
	for (size_t j = 0; j < dlugosci_tablic; j++)
	{
		for (size_t i = 0; i < liczba_wspolcznnikow; i++)
	{
			if (i == liczba_wspolcznnikow-1) {
				cout << "| " << uklad_rownan[i][j];
			}
			else {
				cout << uklad_rownan[i][j] << setw(6);
			}
		}
		cout << endl;
	}
	cout << endl;

	auto start = std::chrono::steady_clock::now();		//punkt startowy pomiaru czasu
	int result = Thomas(uklad_rownan[0], uklad_rownan[1], uklad_rownan[2], uklad_rownan[3], Wyniki, dlugosci_tablic);
	auto end = std::chrono::steady_clock::now();		//punkt koncowy pomiaru czasu
	std::chrono::duration<double, milli> elapsed_seconds = end - start;		//wyliczamy czas ktory uplynal
	std::cout << "Czas wykonania algorytmu: " << elapsed_seconds.count() << "ms\n";

	for (int i = 0; i < dlugosci_tablic; i++)
	{
		cout << "x["<<i+1<<"] = " << Wyniki[i] << endl;
	}
	getchar(); getchar();
	return 0;
}
	//////////////////////////////////////////////////////
	//int result = Gauss(uklad_rownan, Wyniki, liczba_weirszy, dlugosc_wiersza);

	//cout << "Macierz po eliminacji Gaussa" << endl;
	//cout << endl;

	//for (size_t i = 0; i < liczba_weirszy; i++)	//wypisanienie tablicy
	//{
	//	for (size_t j = 0; j < dlugosc_wiersza; j++)
	//	{

	//		if (j == liczba_weirszy) {
	//			cout << "| " << uklad_rownan[i][j];
	//		}
	//		else {
	//			cout << uklad_rownan[i][j] << setw(6);
	//		}
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//if (result == 1) {
	//	cout << "Wyniki:" << endl;
	//	for (size_t i = 0; i < liczba_weirszy; i++)
	//	{
	//		cout << "X" << i + 1 << ": " << Wyniki[i] << endl;
	//	}
	//}
	//else if (result == 0) {
	//	cout << "Uklad nieoznaczny" << endl;

	//}
	//else if (result == -1) {
	//	cout << "Uklad sprzeczny" << endl;

	//}
