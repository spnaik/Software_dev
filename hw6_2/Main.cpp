/*
Copyright (c) 2018, Daniel Hanson
AMATH 520, University of Washington
For instructional purposes only
*/

#include "EquityPriceGenerator.h"
#include "BarrierOption.h"
#include "ResultSet.h"
#include "Date.h"
#include <iostream>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::for_each;

void mcBarrCall();
void mcBarrPut();

int main()
{
	
	mcBarrCall();
	mcBarrPut();
	
	return 0;
}

void mcBarrCall()
{
	double barrierlevel = 103.0;
	double strike = 102.0;
	double spot = 100.0;
	double riskFreeRate = 0.025;
	double volatility = 0.06;
	double quantity = 7000.00;	// 1.0;
	OptionType call = OptionType::CALL;
	Barrier up1 = Barrier::UP_AND_OUT;
	Date valueDate(2015, 10, 1);
	Date expiryDate(2017, 9, 30);
	Date settlementDate(++expiryDate);		// expiryDate + 1
	unsigned numTimeSteps = 720;
	unsigned numScenarios = 10000;
	int seed = -106;
	Act365 act365;

	

	BarrierOption qlCall(barrierlevel, strike, spot, riskFreeRate, volatility, quantity, call, up1,
		valueDate, expiryDate, settlementDate, numTimeSteps, numScenarios, seed, 0.01, act365);
	OptionResults res = qlCall();
	
	res.print();
	
}

void mcBarrPut()
{
	double barrierlevel = 93.0;
	double strike = 102.0;
	double spot = 100.0;
	double riskFreeRate = 0.025;
	double volatility = 0.06;
	double quantity = 7000.00;	// 1.0;
	OptionType put = OptionType::PUT;
	Barrier down1 = Barrier::DOWN_AND_PUT;
	Date valueDate(2015, 10, 1);
	Date expiryDate(2017, 9, 30);
	Date settlementDate(++expiryDate);		// expiryDate + 1
	unsigned numTimeSteps = 720;
	unsigned numScenarios = 10000;
	int seed = -106;
	Act365 act365;

	BarrierOption qlPut(barrierlevel, strike, spot, riskFreeRate, volatility, quantity, put, down1,
		valueDate, expiryDate, settlementDate, numTimeSteps, numScenarios, seed, 0.01, act365);
	OptionResults res1 = qlPut();
	res1.print();

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