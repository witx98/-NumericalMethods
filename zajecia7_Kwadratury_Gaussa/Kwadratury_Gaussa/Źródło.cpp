#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
vector < double > dane;
string nazwaPliku = "punkty.txt";
double waga[2] = { 1.0,1.0 };
double punkt[2] = { -0.5773502692, 0.5773502692 };

//Funkcja pobierjıca dane z pliku tekstowego i zapisujıce je do wektora.
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
	if (data->size() % 2 == 1) {	//zabezpiecznie w razie le wype³nionego pliku tekstowego 
		cout << "bledne dane w pliku" << endl;
		return -1;
	}
	return data->size();	//funkcja zwraca wielkosc wektora potrzebna do stworzenia tablic X, Y
}


double Gauss2D(double * X, double * Y) {
	double Poch_KSI[2][4];	//Pochodne wzgledem ksi
	double Poch_NI[2][4];	//pochodne wzgledem ni
	double Fun_DETJ[2][2];	//Wyznacznik macierzy Jacobiego

	for (size_t j = 0; j < 2; j++)
	{
		for (size_t i = 0; i < 2; i++)
		{
			Poch_NI[i][0] = -0.25 * (1.0 - punkt[i]);
			Poch_KSI[j][0] = -0.25 * (1.0 - punkt[j]);
			
			
			
			Poch_NI[i][1] = -0.25 * (1.0 + punkt[i]);
			Poch_KSI[j][1] = 0.25 * (1.0 - punkt[j]);
			
			
			Poch_NI[i][2] = 0.25 * (1.0 + punkt[i]);
			Poch_KSI[j][2] = 0.25 * (1.0 + punkt[j]);
			
		
			Poch_NI[i][3] = 0.25 * (1.0 - punkt[i]);
			Poch_KSI[j][3] = -0.25 * (1.0 + punkt[j]);
		}
	}

	for (size_t j = 0; j < 2; j++)
	{
		for (size_t i = 0; i < 2; i++)
		{
			double dx_dKSI = Poch_KSI[j][0] * X[0] + Poch_KSI[j][1] * X[1] + Poch_KSI[j][2] * X[2] + Poch_KSI[j][3] * X[3];
			double dy_dKSI = Poch_KSI[j][0] * Y[0] + Poch_KSI[j][1] * Y[1] + Poch_KSI[j][2] * Y[2] + Poch_KSI[j][3] * Y[3];

			double dx_dNI = Poch_NI[i][0] * X[0] + Poch_NI[i][1] * X[1] + Poch_NI[i][2] * X[2] + Poch_NI[i][3] * X[3];
			double dy_dNI = Poch_NI[i][0] * Y[0] + Poch_NI[i][1] * Y[1] + Poch_NI[i][2] * Y[2] + Poch_NI[i][3] * Y[3];

			Fun_DETJ[i][j] = dx_dKSI * dy_dNI - dx_dNI * dy_dKSI;
		}
	}

	double Powierzchnia = 0.0;
	for (size_t j = 0; j < 2; j++)
	{
		for (size_t i = 0; i < 2; i++)
		{
			Powierzchnia = Powierzchnia + fabs(Fun_DETJ[i][j]) * waga[i] * waga[j];
		}
	}
	return Powierzchnia;
}
int main()
{
	////////////SPRAWDZZANIE POPRAWNOSCI PLIKU////////////
	int wielkosc_wektora = pobranie_z_pliku(&dane, nazwaPliku);
	if (wielkosc_wektora == -1)	//program zostanie przerwany jesli plik tekstowy byl bledny
	{
		return -1;
	}
	////////////////////////
	////////////WYPE£NIANIE TABLIC////////////
	int liczba_punktow = wielkosc_wektora / 2; //wielkosc wektora podzielona przez 2 powinna nam daĉ ilo punktów zapisanych w pliku 
	double* X = new double[liczba_punktow];		//tablica wspólczynnikow x
	double* Y = new double[liczba_punktow];		//tablica wspólczynnikow y
	int j = 0;
	for (size_t i = 0; i < dane.size(); i++)	//wypełnienie tablic
	{
		if (i % 2 == 0) {
			X[j] = dane[i];
		}
		if (i % 2 == 1) {
			Y[j] = dane[i];
			j++;
		}
	}

	
	cout << "Powierzchnia wynosi = " << Gauss2D(X,Y) << endl;
	system("Pause");

	return 0;
}