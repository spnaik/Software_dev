/*
Copyright (c) 2018, Daniel Hanson
AMATH 520, University of Washington
For instructional purposes only
*/

#ifndef   BARRIER_OPTION_H
#define   BARRIER_OPTION_H

#include "Date.h"
#include "DayCount.h"
#include "ResultSet.h"
#include "EquityPriceGenerator.h"


class BarrierOption
{
	// Proposed defaults: bool runParallel = true, int seed = 0, double greekShift = 0.01
public:
	BarrierOption(double barrierlevel, double strike, double spot, double riskFreeRate, double volatility,
		double quantity, OptionType optionType, Barrier opt, const Date& valueDate, const Date& expiryDate,
		const Date& settlementDate, unsigned numTimeSteps, unsigned numScenarios, int seed, double greekShift, const DayCount& dc);

	OptionResults operator()() const;
	double time() const;		// Time required to run calcutions (for comparison using concurrency)

private:
	void calculate_();			// Compute price and risk values (called from ctor)

	// Indicates whether to run pricing scenarios in parallel
	//bool runParallel_;			// default = true

	// Private helper functions:
	void computePrice_();
	void computeDelta_();
//	void computeGamma_();
	void computeVega_();
	void computeRho_();
	

	

	// Compute discount factor P(t1, t2)
	double discFactor_(double yearFactor1, double yearFactor2);

	// Inputs to model:
	OptionType porc_;	// porc_: put or call
	Barrier opt_;
	double barrierlevel_;
	double spot_;
	double strike_;
	double riskFreeRate_;
	double volatility_;
	double quantity_;
	unsigned numTimeSteps_;	
	double yearFraction_;
	double greekShift_;		// Percentage shift to use for risk value approximations (default = 1%)
	double tau_;			// Daycount adjusted time to expiration (as year fraction)
	double settlement_;		// Daycount adjusted time to settlement (as year fraction)
	unsigned numScenarios_;
	int seed_;

	// Calculated values stored in these private members:
	double price_;
	double delta_;
//	double gamma_;
	double vega_;
	double rho_;

	// Runtime comparison using concurrency
	double time_;

	// Result set of option values:
	OptionResults results_;
};

#endif

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