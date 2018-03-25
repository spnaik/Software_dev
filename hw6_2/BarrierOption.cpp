/*
Copyright (c) 2018, Daniel Hanson
AMATH 520, University of Washington
For instructional purposes only
*/

#include "BarrierOption.h"
#include "EquityPriceGenerator.h"
#include "ResultSet.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <future>
#include <ctime>
#include <limits>
#include <cassert>
#include <iostream>

using std::vector;
using std::map;
using std::make_pair;
using std::max;			// <algorithm>
using std::transform;
using std::for_each;
using std::exp;
using std::accumulate;
using std::async;
using std::future;
using std::cout;
using std::endl;

BarrierOption::BarrierOption(double barrierlevel, double strike, double spot, double riskFreeRate, double volatility,
	double quantity, OptionType optionType, Barrier opt, const Date& valueDate, const Date& expiryDate,
	const Date& settlementDate, unsigned numTimeSteps, unsigned numScenarios, int seed, double greekShift, const DayCount& dc) : barrierlevel_(barrierlevel),strike_(strike), spot_(spot),
	riskFreeRate_(riskFreeRate), volatility_(volatility), quantity_(quantity),
	porc_(optionType), opt_(opt), numTimeSteps_(numTimeSteps), numScenarios_(numScenarios), seed_(seed),
	greekShift_(greekShift), tau_(dc.yearFraction(valueDate, expiryDate)), settlement_(dc.yearFraction(valueDate, settlementDate))
{
	calculate_();
}

OptionResults BarrierOption::operator()() const
{
	return results_;
}

double BarrierOption::time() const
{
	return time_;
}

void BarrierOption::calculate_()
{
	clock_t begin = clock();		// begin time with threads
	

	computePrice_();
	computeDelta_();
	computeVega_();
	computeRho_();

	

	clock_t end = clock();		// end time with threads
	time_ = double(end - begin) / CLOCKS_PER_SEC;

	results_.resultSet.insert(make_pair(results_.PRICE, price_));
	results_.resultSet.insert(make_pair(results_.DELTA, delta_));
	results_.resultSet.insert(make_pair(results_.VEGA, vega_));
	results_.resultSet.insert(make_pair(results_.RHO, rho_));
}

void BarrierOption::computePrice_()
{
	EquityPriceGenerator epg(spot_, numTimeSteps_, tau_, riskFreeRate_, volatility_);

	vector<int> seeds;
	seeds.push_back(seed_);		// seed_ is actually our starting seed value

	for (unsigned i = 1; i < numScenarios_; ++i)	// We might, instead, wish to use
	{												// an arbitrary vector of seeds.
		seeds.push_back(seed_ + i);
	}

	// typedef vector<double> realVector;	// Old way
	using realVector = vector<double>;		// Modern C++ way
	vector<future<realVector> > futures;

	for (auto& seed : seeds)
	{
		futures.push_back(async(epg, seed));
	}

	vector<double> discountedPayoffs;

	for (auto& future : futures)
	{
		vector<double> prices = future.get();
		double maxspotprice = *std::max_element(prices.begin(), prices.end());
		double minspotprice = *std::min_element(prices.begin(), prices.end());
		double terminalPrice;
		double payoff = 0.0;
		switch (opt_)
		{
		case Barrier::UP_AND_OUT:
			if (maxspotprice > barrierlevel_)
				terminalPrice = strike_;
			else
				terminalPrice = prices.back();
			break;
		case Barrier::DOWN_AND_PUT:
			if (maxspotprice < barrierlevel_)
				terminalPrice = strike_;
			else
				terminalPrice = prices.back();
			break;
		default:	// Should put assert here; this case should NEVER happen
			payoff = std::numeric_limits<double>::quiet_NaN();	// Returns NaN (Not a Number)
			break;
		}



		switch (porc_)
		{
		case OptionType::CALL:
			payoff = max(terminalPrice - strike_, 0.0);
			break;
		case OptionType::PUT:
			payoff = max(strike_ - terminalPrice, 0.0);
			break;
		default:	// Should put assert here; this case should NEVER happen
			payoff = std::numeric_limits<double>::quiet_NaN();	// Returns NaN (Not a Number)
			break;
		}

		discountedPayoffs.push_back(discFactor_(0.0, settlement_) * payoff);
	}

	price_ = quantity_ * (1.0 / discountedPayoffs.size()) * accumulate(discountedPayoffs.begin(), discountedPayoffs.end(), 0.0);

	
}

void BarrierOption::computeDelta_()
{
	double origSpot = spot_;
	double origPrice = price_;
	spot_ += greekShift_;
	computePrice_();

	delta_ = (price_ - origPrice) / greekShift_;

	// reset state to original:
	spot_ = origSpot;
	price_ = origPrice;
}

void BarrierOption::computeVega_()
{
	double origVol = volatility_;
	double origPrice = price_;
	volatility_ += greekShift_;
	computePrice_();

	vega_ = (price_ - origPrice) / greekShift_;

	// reset state to original:
	volatility_ = origVol;
	price_ = origPrice;
}

void BarrierOption::computeRho_()
{
	double origRfRate_ = riskFreeRate_;
	double origPrice = price_;
	riskFreeRate_ += greekShift_;	// If we were using a term structure, we would need to 
									// shock the entire curve
	computePrice_();

	rho_ = (price_ - origPrice) / greekShift_;

	// reset state to original:
	riskFreeRate_ = origRfRate_;
	price_ = origPrice;
}

double BarrierOption::discFactor_(double yearFraction1, double yearFraction2)
{
	if (yearFraction1 <= yearFraction2)
	{
		return exp(-(yearFraction2 - yearFraction1)*riskFreeRate_);
	}
	else
	{
		// handle error:  For now, just return NaN (Not a Number).
		// Should put in an exception for production.
		return std::numeric_limits<double>::quiet_NaN();
	}
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