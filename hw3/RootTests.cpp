#include "Functions.h"
#include "Secant.h"
#include "RootTests.h"
#include <iostream>
#include<cmath>

using std::cout;
using std::endl;
using std::string;

void PolyRootTests()
{
	PolyFunction pf(0.1,0.25,-3.0,-1.0);
	double p1 = secant(pf, -2.5, -1.5, 1000, 0.0001);
	cout << "The 1st root of the PolyFunction is " << p1 << endl;
	double p2 = secant(pf, 0, 1, 1000, 0.0001);
	cout << "The 2nd root of the PolyFunction is " << p2 << endl;
	double p3 = secant(pf, 1.0, 2.0, 1000, 0.0001);
	cout << "The 3rd root of the PolyFunction is " << p3 << endl;
	
}

void LogRootTests()
{
	LogFunction lf(10.0, 0.5);
	double p4 = secant(lf, 1.0, 1.2, 1000, 0.0001);
	cout << "The 1st root of the LogFunction is " << p4 << endl;
	
}

void MixRootTests()
{
	MixFunction mf(25.0, 5.0, -10);
	double p5 = secant(mf, 9.8, 9.9, 1000, 0.0001);
	cout << "The 1st root of the MixFunction is " << p5 << endl;
	double p6 = secant(mf, 9.91, 10.0, 1000, 0.0001);
	cout << "The 2nd root of the MixFunction is " << p6 << endl;
	double p7 = secant(mf, 10.1, 10.2, 1000, 0.0001);
	cout << "The 3rd root of the MixFunction is " << p7 << endl;
}