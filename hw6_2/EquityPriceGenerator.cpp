/*
Copyright (c) 2018, Daniel Hanson
AMATH 520, University of Washington
For instructional purposes only
*/

#include "EquityPriceGenerator.h"
#include <random>
#include <algorithm>	
#include <ctime>
#include <cmath>

using std::vector;
using std::mt19937_64;
using std::normal_distribution;

using std::exp;

using std::vector;

EquityPriceGenerator::EquityPriceGenerator(double initEquityPrice, unsigned numTimeSteps, double timeToMaturity, double drift, double volatility) :
	initEquityPrice_(initEquityPrice), numTimeSteps_(numTimeSteps), timeToMaturity_(timeToMaturity), drift_(drift), volatility_(volatility),
	yearFraction_(timeToMaturity/numTimeSteps) {}

vector<double> EquityPriceGenerator::operator()(int seed) const
{
	vector<double> v;

	mt19937_64 mtre(seed);
	normal_distribution<> nd;

	auto newPrice = [this](double previousEquityPrice, double norm)
	{
		double price = 0.0;

		double expArg1 = (drift_ - ((volatility_ * volatility_) / 2.0)) * yearFraction_;
		double expArg2 = volatility_ * norm * sqrt(yearFraction_);
		price = previousEquityPrice * exp(expArg1 + expArg2);

		return price;
	};

	v.push_back(initEquityPrice_);				// put initial equity price into the 1st position in the vector
	double equityPrice = initEquityPrice_;

	for (int i = 1; i <= numTimeSteps_; ++i)	// i <= numTimeSteps_ since we need a price at the end of the
	{											// final time step.
		equityPrice = newPrice(equityPrice, nd(mtre));	// norm = nd(mtre)
		v.push_back(equityPrice);
	}
	
	return v;

}

/*
Unless explicitly acquired and licensed from Licensor under another
license, the contents of this file are subject to the Reciprocal Public
License ("RPL") Version 1.5, or subsequent versions as allowed by the RPL,
and You may not copy or use this file in either source code or executable
form, except in compliance with the terms and conditions of the RPL.

All software distributed under the RPL is provided strictly on an "AS
IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND
LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the RPL for specific
language governing rights and limitations under the RPL.
*/