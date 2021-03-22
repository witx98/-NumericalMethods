#include <iostream>
#include <vector>
#include <fstream>	
#include <sstream>	
#include <cmath>
#include <string>
#include <iomanip> 
using namespace std;
double Dokladnosc = 0.00000001;	//Dokladnosc obliczen 
double phi = 0.61803398;	//Wartosc odwrotnosci zlotej liczby 
int prec = 11;	//Liczba wyswietlanych miejsc po przecinku 

double f(double x) {	//Pomocnicza fukncja obliczajaca wartosc w punkcie x				
	return  pow(x,3) + 5*pow(x,2) + log(x + 4);
}

double zlotyPodzial(double a, double b, double Phi, double precision) {
	double l_granica = a;
	double p_granica = b;
	
	while (fabs(p_granica - l_granica) > precision)
	{
		double Xl = p_granica - Phi*(p_granica - l_granica);	//obliczanie punktow pomocniczych 
		double Xp = l_granica + Phi*(p_granica - l_granica);	//w kazdym obiegu petli 

		if (f(Xl) > f(Xp)) {	//jesli warunek spelniony - miniumu w przedziale [Xl;p_granica]
			l_granica = Xl;		//zawezenie przedzialu
		}
		else{				//jesli warunek nie spelniony - miniumu w przedziale [l_granica;Xp]
			p_granica = Xp;	//zawezenie przedzialu	
		}
	}
	//cout << "Lewa granica: " << setprecision(prec) << l_granica << endl;
	//
	cout << "Prawa granica: " << setprecision(prec) <<  p_granica << endl;
	return (p_granica + l_granica) / 2;	//wybieramy punkt dokladnie posrodku otrzymanych granic 
}

int main() {

	double a, b;	//deklaracja zmiennych 
	cout << "Obliczanie minimum" << endl;
	cout << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Metoda zlotego podzialu" << endl;
	cout << "Podaj przedzial poszukiwania minimum: " << endl;
	cout << "a = "; cin >> a;	//Pobranie granic przedzialu 
	cout << "b = "; cin >> b;
	cout << "Wspolrzedna x minimum lokalnego: " << setprecision(prec) << zlotyPodzial(a, b, phi, Dokladnosc) <<endl;	
	cout << "Wspolrzedna y minimum lokalnego: " << setprecision(prec) << f(zlotyPodzial(a, b, phi, Dokladnosc)) << endl;
	cout << endl;	//Wyswitlenienie wyniku

	getchar(); getchar();
	return 0;
}