#include "RealFunctions.h"
#include <exception>
#include <numeric>
#include <iostream>
#include <tuple>

using std::pair;
using std::tuple;
using std::make_pair;
using std::make_tuple;

double tupalooza(const tuple<Linear, PolyFunction, LogFunction, MixFunction>& fcns, double x);

int main()
{
	Linear lin(5,5);
	PolyFunction poly(0.1,0.25,-3,-1);
	LogFunction myLog(10,0.5);
	MixFunction mix(25,5,-10);

	std::tuple<Linear, PolyFunction, LogFunction, MixFunction> myFcns(lin, poly, myLog, mix);

	double sum1 = tupalooza(myFcns, 2.0);

	std::cout << " The sum of each function " << sum1 << std::endl;

	return 0;

}

double tupalooza(const tuple<Linear, PolyFunction, LogFunction, MixFunction>& fcns, double x)
{
	return  (std::get<0>(fcns)(x) + std::get<1>(fcns)(x) + std::get<2>(fcns)(x) + std::get<3>(fcns)(x));
}