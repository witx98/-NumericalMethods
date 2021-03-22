#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <iomanip> 
using namespace std;
double Dokladnosc = 0.0000001;	//Dokladnosc obliczen 
int prec = 11;	//Liczba wyswietlanych miejsc po przecinku 

double f(double x) {	//Pomocnicza fukncja obliczajaca wartosc w punkcie x
	return log(pow(x,5)-pow(x,3));
}
double d(double x) {	//Pomocnicza fukncja obliczajaca wartosc pochodnej w punkcie x
	return (5*x*x - 3)/(x*x*x - x);
}

double Bisekcja(double a, double b, double precision) {
	double Fa = f(a);	//wartosc funkcji na lewej granicy 
	double Fb = f(b);	//wartosc funkcji na prawej granicy
	double l_granica = a;
	double p_granica = b;
	double Xo;
	double Fo;
	if (Fa * Fb > 0) {	//sprawdzenie warunku 
		cout << "Funkcja nie spelnia zalozen" << endl;
		return -1;
	}
	while (fabs(l_granica - p_granica) > precision)
	{
		Xo = (l_granica + p_granica) / 2;	//wyznaczenie punktu srodkowego
		Fo = f(Xo);	//wartosc punktu srodkowego

		if (fabs(Fo) < precision) {		//sprawdzenie drugiego warunku 
			cout << "Pierwiastek Funkcji w przedziale: "  << setprecision(prec) << Xo << endl;
			return 0;	//spelnienie warunku konczy algorytm 
		}
		if (Fa * Fo < 0)	//sprawdzenie warunku dla podprzedzialow
		{
			p_granica = Xo;
		}
		else
		{
			l_granica = Xo;
			Fa = Fo;
		}
	}
	cout << "Pierwiastek Funkcji w przedziale: " << setprecision(prec) << Xo << endl;
	return 1;
}
double NewtonRaphson(double a, double b, double precision, double start) {
	double Fa = f(a);	//wartosc funkcji na lewej granicy 
	double Fb = f(b);	//wartosc funkcji na prawej granicy 
	
	if (Fa * Fb > 0) {	//sprawdzenie warunku 
		cout << "Funkcja nie spelnia zalozen" << endl;
		return -1;
	}
	double X1 = start;
	double X0;
	double f1 = f(X1);	//wartosc funkcji dla punktu startowego 
	while (fabs(f1) >= precision)	//warunek zakonczenia algorytmu 
	{
		double df = d(X1);	//obliczenie pochodnej
		X0 = X1;
		X1 = X1 - (f1 / df);	//oblicznie kolejnego punktu startowego
		f1 = f(X1);
		if (fabs(X1 - X0) <= precision) break; //warunek zakonczenia algorytmu
	}
	cout << "Pierwiastek Funkcji w przedziale: " << setprecision(prec) << X1 << endl;
	return 1;
}

int main() {
	
	double a, b;
	double start;
	cout << "Obliczanie pierwiastka funkcji" <<endl;
	cout << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Metoda Bisekcji" << endl;
	cout << "Podaj zakres poszukiwan pierwiastka: " << endl;
	cout << "a = "; cin >> a;	//Pobranie granic przedzialu 
	cout << "b = "; cin >> b;
	Bisekcja(a, b, Dokladnosc);
	cout << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Metoda Newtona-Raphsona" << endl;
	cout <<	"Podaj punkt startowy:"<<endl;
	cout << "Start = "; cin >> start;	//Pobranie punktu startowego 
	NewtonRaphson(a, b, Dokladnosc, start);

	getchar(); getchar();
	return 0;
}