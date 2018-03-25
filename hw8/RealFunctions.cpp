#include "RealFunctions.h"
#include <iostream>
#include<cmath>
#include <cstdlib>
#include <limits>

using std::cout;
using std::endl;
using std::string;
double const Zero = std::numeric_limits<double>::min();

PolyFunction::PolyFunction(double a, double b, double c, double d) :a_(a), b_(b), c_(c), d_(d) {}

double PolyFunction::operator()(double x) const
{
	return ( x*x*x*(a_*x*x + b_) + c_ * x + d_);
}

Linear::Linear(double a, double b) : a_(a), b_(b) {}

double Linear:: operator()(double x) const
{
	double y = a_ * x + b_;
	return y;

}


LogFunction::LogFunction(double a1, double b1) :a_(a1), b_(b1) {}

double LogFunction::operator()(double x) const
{
	if (std::abs(x - b_) <= Zero)
	{
		// exit program with error message
		std::cout << "error: log is undefined " << std::endl;
		std::exit(EXIT_FAILURE);		// This is a stopgap measure until we cover exceptions.
	}
	return (a_ * std::log(x - b_));
}

MixFunction::MixFunction(double a2, double b2, double c2) :a_(a2), b_(b2), c_(c2) {}

double MixFunction::operator()(double x) const
{
	if (std::abs(x) <= Zero)
	{
		// exit program with error message
		std::cout << "error: denominator is 0" << std::endl;
		std::exit(EXIT_FAILURE);		// This is a stopgap measure 
	}

	return ((( x*x + std::sin(a_*x + b_))/(x)) + c_);
}





