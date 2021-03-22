#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <iomanip> 
#include <chrono>
using namespace std;

double f(double x, double y) {	//Funkcja pomocnicza 
	return (cos(x) - sin(x)  - y);
}
void Euler(double a, double b, double y0, double h) {
	double N = (b - a) / h;	//wyliczamy liczbe iteracji 
	double x = a;	//przypisujemy x punkt startowy
	double y = y0;	//przypisujemy parametr poczatkowy
	for (size_t i = 0; i < N; i++)
	{
		y = y + h * f(x, y);	//wyliczamy i wypisujemy kolejne y
		cout << "y[" << i + 1 << "] = " << y << endl;
		x = x + h;				//wyliczamy i wypisujemy kolejne x
		cout << "x[" << i + 1 << "] = " << x << endl;
		cout << endl;
	}
}

double fh(double x, double y) {	//Funkcja pomocnicza 
	//return (cos(x) - sin(x) - y);
	return x * x + y;
}
void Huen(double a, double b, double y0, double h) {
	double N = (b - a) / h;	//wyliczamy liczbe iteracji 
	double x = a;	//przypisujemy x punkt startowy
	double y = y0;	//przypisujemy parametr poczatkowy
	for (size_t i = 0; i < N; i++)
	{
		y = y + (h/2) * (fh(x, y) + fh(x+h, y + h * fh(x, y)));	//wyliczamy i wypisujemy kolejne y
		cout << "y[" << i + 1 << "] = " << y << endl;
		x = x + h;				//wyliczamy i wypisujemy kolejne x
		cout << "x[" << i + 1 << "] = " << x << endl;
		cout << endl;
	}
}

double fR(double x, double y) {	//Funkcja pomocnicza 
	return x * x + y;
	//return x + y;
}
void RK4(double a, double b, double y0, double h) {
	double N = (b - a) / h;	//wyliczamy liczbe iteracji 
	double x = a;	//przypisujemy x punkt startowy
	double y = y0;	//przypisujemy parametr poczatkowy
	double k1,k2,k3,k4;
	for (size_t i = 0; i < N; i++)
	{
		//Obliczanie kolejnych wartosci k
		k1 = h * fR(x, y);
		cout << "k1: " <<setprecision(6) << k1 << endl;
		k2 = h * fR(x + 0.5 * h, y + 0.5 * k1);
		cout << "k2: " << k2 << endl;
		k3 = h * fR(x + 0.5 * h, y + 0.5 * k2);
		cout << "k3: " << k3 << endl;
		k4 = h * fR(x + h, y + k3);
		cout << "k4: " << k4 << endl;

		y = y + (k1 + 2 * k2 + 2* k3 + k4)/6;	//wyliczamy i wypisujemy kolejne y
		cout << "y[" << i + 1 << "] = " << y << endl;
		x = x + h;				//wyliczamy i wypisujemy kolejne x
		cout << "x[" << i + 1 << "] = " << x << endl;
		cout << endl;
	}
}

int main() {

	auto start = std::chrono::steady_clock::now();		//punkt startowy pomiaru czasu
	//Huen(0, 0.3, 0.1, 0.01);
	RK4(0, 0.2, 0.1, 0.01);
	auto end = std::chrono::steady_clock::now();		//punkt koncowy pomiaru czasu
	std::chrono::duration<double, milli> elapsed_seconds = end - start;		//wyliczamy czas ktory uplynal
	std::cout << "Czas wykonania algorytmu: " << elapsed_seconds.count() << "ms\n";

	getchar(); getchar();
	return 0;
}

