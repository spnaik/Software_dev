#include "Functions.h"
#include "Secant.h"
#include <iostream>
#include<cmath>
#include<vector>

using std::cout;
using std::endl;
using std::string;

double secant(const RealFunction& slice, double x1, double x2, int maxIter, double tol)
{   
	double p;
	for (int i = 0; i <= maxIter; i++)
	{
		if ((std::abs(x2 - x1) <= tol) )
		{
			return x2;
		}
		if (i == maxIter)
		{
			return  std::numeric_limits<double>::quiet_NaN();
		}
		p = x1;
		x1 = x2;
		x2 = (p*slice.operator()(x1) - x1*slice.operator()(p))/(slice.operator()(x1) - slice.operator()(p));
		
		if (slice.operator()(x2) == 0)
		{
			return x2;
		}

	}
	
	
}
