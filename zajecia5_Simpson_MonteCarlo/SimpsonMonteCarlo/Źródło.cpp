#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;
mt19937 rnd(std::time(NULL));

double funkcja(double x) {
	double fx = 4*x*x*x*x -3*x*x*x + 2*x*x;
	return fx;
}
double calkowanieMetodaProstokatow(double dolna_granica, double gorna_granica, int licznosc) {

	double dx = (gorna_granica - dolna_granica) / licznosc;	//Obliczenie szerokosci prostokata
	double wynik = 0;
	double x = dolna_granica;
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
	double suma = 0;
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

	double dx = (gorna_granica - dolna_granica) / licznosc;	//Obliczenie wyskosci trapezu
	double wynik = 0;
	double x = dolna_granica;
	double sumaH = 0;
	double sumaH2 = 0;
	
	for (size_t i = 1; i <= licznosc; i++)
	{
		x += dx;						//Obliczanie kolejnych punktów
		sumaH2 += funkcja(x - dx / 2);	//Wylicznie wartosci dla f(xp + i*dx - dx/2)
		if (i < licznosc) {				//if zapobiaga dodaniu wartosci granicznych 
			sumaH += funkcja(x);		//Wylicznie wartosci dla f(xp + i*dx)
		}
	}
	wynik = (dx / 6) * (funkcja(dolna_granica) + 2 * sumaH + 4 * sumaH2 + funkcja(gorna_granica));
	return wynik;
}
double calkowanieMonteCarlo(double dolna_granica, double gorna_granica, int licznosc) {

	double wynik = 0;
	double sredniaF = 0;
	double losowyX;
	//cout << "Wylosowane punkty: " << endl;
	for (size_t i = 1; i <= licznosc; i++)
	{
		//utworzenie i przekazanie odpowiedniego przedzia³u do obiektu dist
		uniform_real_distribution < double > dist(dolna_granica, gorna_granica); 
		losowyX = dist(rnd);	//zapisanie wylosowanego punktu
		//cout << losowyX << endl;
		sredniaF += funkcja(losowyX)/ licznosc;		//Wylicznie œredniej
	}
	wynik = sredniaF*fabs(gorna_granica- dolna_granica);	//Oblicznie wartosci ca³ki
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
	//cout << "Wynik dla metody prostokatow " << calkowanieMetodaProstokatow(xp, xk, n) << endl;
	//cout << "Wynik dla metody trapezow " << calkowanieMetodaTrapezow(xp, xk, n) << endl;
	cout << "Wynik dla metody Simpsona " << calkowanieMetodaSimpsona(xp, xk, n) << endl;
	cout << "Wynik dla metody Monte Carlo " << calkowanieMonteCarlo(xp, xk, n) << endl;
	return 0;
}