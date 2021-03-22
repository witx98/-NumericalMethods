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
	return (x*x + y);
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
int main() {
	
	auto start = std::chrono::steady_clock::now();		//punkt startowy pomiaru czasu
	Euler(0,3,0.1,0.5);
	auto end = std::chrono::steady_clock::now();		//punkt koncowy pomiaru czasu
	std::chrono::duration<double, milli> elapsed_seconds = end - start;		//wyliczamy czas ktory uplynal
	std::cout << "Czas wykonania algorytmu: " << elapsed_seconds.count() << "ms\n";

	getchar(); getchar();
	return 0;
}

