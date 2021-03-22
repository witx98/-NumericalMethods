#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <string>
using namespace std;


double funkcja(double x) {
	double fx = x*x*x + 2;
	return fx;
}

double calkowanieMetodaProstokatow(double dolna_granica, double gorna_granica, int licznosc) {

	double dx = (gorna_granica - dolna_granica) / licznosc;	//Obliczenie szerokosci prostokata
	double wynik=0;
	double x=dolna_granica;
	for (size_t i = 0; i < licznosc; i++)
	{
		 x += dx;					//Obliczanie kolejnych x: x[1],x[2],...,x[n]
		 wynik += dx * funkcja(x);	//Wylicznie i dodanie do wyniku wartosci bloku f[i]*dx
	}
	return wynik;
}



double calkowanieMetodaTrapezow(double dolna_granica, double gorna_granica, int licznosc) {

	double dx = (gorna_granica - dolna_granica) / licznosc;	//Obliczenie wyskosci trapezu
	double wynik = 0;
	double x = dolna_granica;
	double suma= 0;
	for (size_t i = 0; i < licznosc; i++)
	{
		suma += funkcja(x);		//Wylicznie wartosci dla f[i]
		x += dx;
		suma += funkcja(x);		//Wylicznie wartosci dla f[i+1]
	}
	wynik = (suma / 2) * dx;
	return wynik;
}
double calkowanieMetodaSimpsona(double dolna_granica, double gorna_granica, int licznosc) {

	double H = (gorna_granica - dolna_granica) / licznosc;	//Obliczenie wyskosci trapezu
	double wynik = 0;
	double x = dolna_granica;
	double sumaH = 0;
	double sumaH2 = 0;
	for (size_t i = 1; i <= licznosc; i++)
	{
		x += H;
		sumaH2 += funkcja(x-H/2);		//Wylicznie wartosci dla f[i+1]
		if (i < licznosc) {
			sumaH += funkcja(x);		//Wylicznie wartosci dla f[i]
		}
	}
	wynik = (H/6)*(funkcja(dolna_granica) + 2*sumaH + 4*sumaH2 + funkcja(gorna_granica)) ;
	return wynik;
}



int main() {
	double xp, xk;
	int n;

	cout << "Podaj dolna granice ";
	cin >> xp;
	cout << endl;
	cout << "Podaj gorna granice ";
	cin >> xk;
	cout << endl;
	cout << "Podaj ilosc czesci ";
	cin >> n;
	cout << endl;


	cout << "Wynik dla metody prostokatow " << calkowanieMetodaProstokatow(xp, xk, n) << endl;
	cout << "Wynik dla metody trapezow " << calkowanieMetodaTrapezow(xp, xk, n) << endl;
	cout << "Wynik dla metody Simpsona " << calkowanieMetodaSimpsona(xp, xk, n) << endl;

	return 0;
}