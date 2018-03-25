// Homework 1

#include<iostream>
#include<cmath>

//using Real = double;
using std::cout;
using std::cin;
using std::endl;
using std::abs;
double const pi = acos(-1.0);
enum BoeingJet
{
	B727 = 727,
	B747 = 747,
	B777 = 777,
	B787 = 787,
	
} ;

enum class NasaProject
{
	MERCURY,
	GEMINI,
	APOLLO
};


double trigFun(double x, double y);
double expApprox(double x, int N);
int numEngines(BoeingJet aircraft);
int numAstronauts(NasaProject mission);

int main()
{
	// testing TrigFun

	double X1 = pi / 4; double Y1 = pi / 4; double X2 = 2 * pi; double Y2 = 2 * pi;
	double Z1 = trigFun(X1,Y1); // first case 
	double Z2 = trigFun(X2,Y2); // second case
	cout << "Result of trigFun when x = "<< X1 <<" and y = " << Y1 << " is " << Z1 << endl;
	cout << "Result of trigFun when x = " << X2 << " and y = " << Y2 << " is " << Z2 << endl;

	// testing expApprox

	double x1 = 1; double x2 = -0.5;  int N1 = 3; int N2 = 15;
	double apx1 = expApprox(x1, N1); double tval1 = std::exp(x1);
	double apx2 = expApprox(x2, N2); double tval2 = std::exp(x2);
	double apx3 = expApprox(x1, N2); 
	double apx4 = expApprox(x2, N1); 
	cout << "Result of expApprox when x1 = "<<x1<<" and N1 = " << N1 << " is " << apx1 << endl;
	cout << "Result of expApprox when x2 = " << x2 << " and N2 = " << N2 << " is " << apx2 << endl;
	cout << "Result of expApprox when x1 = " << x1 << " and N2 = " << N2 << " is " << apx3 << endl;
	cout << "Result of expApprox when x2 = " << x2 << " and N1 = " << N1 << " is " << apx4 << endl;
	cout << "Result of exp using standard library when x1 = " << x1 << " is " << tval1 << endl;
	cout << "Result of exp using standard library when x2 = " << x2 << " is " << tval2 << endl;

	// testing the Boeing aircraft model and engines
	
    int engine1 = numEngines(B727); 
	int engine2 = numEngines(B747);
	int engine3 = numEngines(B777);
	int engine4 = numEngines(B787);
	cout << "A Boeing " << B727 << " has " << engine1 << " engine(s)" << endl;
	cout << "A Boeing " << B747 << " has " << engine2 << " engine(s)" << endl;
	cout << "A Boeing " << B777 << " has " << engine3 << " engine(s)" << endl;
	cout << "A Boeing " << B787 << " has " << engine4 << " engine(s)" << endl;

	// testing numAstronauts 

	int astr1 = numAstronauts(NasaProject::MERCURY);
	int astr2 = numAstronauts(NasaProject::GEMINI);
	int astr3 = numAstronauts(NasaProject::APOLLO);
	cout << "The Mercury missions had "<< astr1 <<" astronaut(s)"<< endl;
	cout << "The Gemini missions had " << astr2 << " astronaut(s)" <<  endl;
	cout << "The Apollo missions had " << astr3 << " astronaut(s)" <<  endl;
	
	return 0;
	
}

// function for calculating trigFun 

double trigFun(double x, double y)
{
	double ret = 0.0;

	abs(x) < pi / 2 && abs(y) < pi / 2 ? ret = tan(x) + tan(y) : ret = sin(x) + cos(y);
	return ret;
}

// function for calculating the exponential approximation

double expApprox(double x, int N)
{
	double fctrl;  double num;  double apx; int i;

	// compute the approximation apx here
	for (i = 0; i <= N; i++)
		if (i == 0)
		{
			apx = 1;
			fctrl = 1;
		}
		else
		{
			num = std::pow(x, i);
			fctrl = fctrl * i;
			apx = apx + (num) / (fctrl);
		}
	if (x==0 || N<=0)
	{
		apx = 1;
	}

	return apx;

}

// BoingJet function to get the number of engines

int numEngines(BoeingJet aircraft)
{
	int eng;
	switch (aircraft) {
	case B727:
		eng = 3;
		break;
	case B747:
		eng = 4;
		break;
	case B777: case 787:
		eng = 2;
		break;
	default:
		eng = 0;
		break;
	}
	return eng;
}

// NasaProject function to get the number of astronauts

int numAstronauts(NasaProject mission)
{
	int astr;
	switch (mission) {
	case NasaProject::MERCURY:
		astr = 1;
		break;
	case NasaProject::GEMINI:
		astr = 2;
		break;
	case NasaProject::APOLLO:
		astr = 3;
		break;
	default:
		astr = 0;
		break;
	}
	return astr;
}