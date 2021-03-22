#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <iomanip> 
#include <chrono>
using namespace std;
vector < double > dane;
string nazwaPliku = "punkty.txt";
int podzial = 7;

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
		plik.close();		//zamkniêcie pliku 
	}
	if (data->size() % podzial != 0) {	//zabezpiecznie w razie zle wypelnionego pliku tekstowego 
		cout << "bledne dane w pliku" << endl;
		return -1;
	}
	return data->size();	//funkcja zwraca wielkosc wektora potrzebna do stworzenia tablic.
}

int Gauss(double** uklad_rownan, double* Wyniki, int liczba_wierszy, int dlugosc_wiersza) {
	for (size_t i = 0; i < liczba_wierszy; i++) //sprowadzenie ukladu to postaci trojkatnej 
	{
		for (size_t j = i+1; j < liczba_wierszy; j++)
		{
			double iloraz = uklad_rownan[j][i] / uklad_rownan[i][i];	//Obliczamy iloraz wartosci jednego wiersza przez drugi 
			uklad_rownan[j][i] = 0;		//zerujemy tworzac "schodki"
			for (size_t k = i+1; k < dlugosc_wiersza; k++)
			{
				uklad_rownan[j][k] = uklad_rownan[j][k] - uklad_rownan[i][k] * iloraz; //Obliczamy wartosci kolejnych wspolczynnikow w wierszu
			}
		}
	}
	if (uklad_rownan[liczba_wierszy - 1][liczba_wierszy - 1] == 0 && uklad_rownan[liczba_wierszy - 1][liczba_wierszy] != 0) {
		return -1;	//Funkcja zakonczy sie z wynikiem -1 jesli uklad jest sprzeczny
	}
	if (uklad_rownan[liczba_wierszy - 1][liczba_wierszy - 1] == 0 && uklad_rownan[liczba_wierszy - 1][liczba_wierszy] == 0) {
		return 0;	//Funkcja zakonczy sie z wynikiem 0 jesli uklad jest nieoznaczony 
	}
	for (int w = liczba_wierszy - 1; w > -1; w--) {		//Obliczenie wartosci kolejnych X
		Wyniki[w] = uklad_rownan[w][liczba_wierszy];	
		for (size_t i = w+1; i < liczba_wierszy; i++)
		{
			double iloczyn = (uklad_rownan[w][i] * Wyniki[i]);
			double wynik = Wyniki[w];
			int roznica = wynik - iloczyn;
			/*if (w == 0) {
				Wyniki[w] = roznica;
			}
			else {*/
				Wyniki[w] = wynik - iloczyn;
			//}
		}
		Wyniki[w] = Wyniki[w] / uklad_rownan[w][w];		
	}
	return 1;
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
	double** uklad_rownan;
	int liczba_weirszy = wielkosc_wektora / podzial; //wielkosc wektora podzielona przez maksymalna ilosc zmiennych w danym rownaniu,
	cout << "Liczba wierszy " << liczba_weirszy << endl;										   //powinna nam dac ilosc rownan zapisanych w pliku 
	int dlugosc_wiersza = liczba_weirszy + 1;
	double* Wyniki = new double[liczba_weirszy];		//tablica rozwiazan x

	uklad_rownan = new double* [liczba_weirszy];		//utworzenie macierzy
	for (int i = 0; i < liczba_weirszy; i++) {
		uklad_rownan[i] = new double[dlugosc_wiersza]; //tworzenie wiersza
	}
	int x = 0;
	for (size_t i = 0; i < liczba_weirszy; i++)	//wypelnienie tablic
	{
		for (size_t j = 0; j < dlugosc_wiersza; j++)
		{
			uklad_rownan[i][j] = dane[x];
			x++;
		
		}
	}
	for (size_t i = 0; i < liczba_weirszy; i++)	//wypisanienie tablicy
	{
		for (size_t j = 0; j < dlugosc_wiersza; j++)
		{
				
				if (j == liczba_weirszy) {
					cout << "| " << uklad_rownan[i][j];
				}
				else {
					cout  << uklad_rownan[i][j] << setw(6);
				}
		}
		cout << endl;
	}
	cout << endl;

	
	
	//typedef duration<long long, milli> milliseconds
	


	auto start = std::chrono::steady_clock::now();
	int result = Gauss(uklad_rownan, Wyniki, liczba_weirszy, dlugosc_wiersza);
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double, milli> elapsed_seconds = end - start;
	std::cout << "Czas wykonania algorytmu: " << elapsed_seconds.count() << "ms\n";
	cout << "Macierz po eliminacji Gaussa" << endl;
	cout << endl;

	for (size_t i = 0; i < liczba_weirszy; i++)	//wypisanienie tablicy
	{
		for (size_t j = 0; j < dlugosc_wiersza; j++)
		{

			if (j == liczba_weirszy) {
				cout << "| " << uklad_rownan[i][j];
			}
			else {
				cout << uklad_rownan[i][j] << setw(6);
			}
		}
		cout << endl;
	}
	cout << endl;
	if (result == 1) {
		cout << "Wyniki:" << endl;
		for (size_t i = 0; i < liczba_weirszy; i++)
		{
			cout << "X" << i + 1 << ": " << Wyniki[i] << endl;
		}
	}
	else if (result == 0) {
		cout << "Uklad nieoznaczny" << endl;

	}
	else if (result == -1) {
		cout << "Uklad sprzeczny" << endl;

	}	
	getchar(); getchar();
	return 0;
}