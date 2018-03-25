/*
Copyright (c) 2018, Daniel Hanson
AMATH 520, University of Washington
For instructional purposes only
*/

#ifndef DAY_COUNT_H
#define DAY_COUNT_H

#include "Date.h"


class DayCount
{
public:
	// The operator should just call the member function yearFraction(.)
	virtual double operator() (const Date& date1, const Date& date2) const = 0;
	virtual double yearFraction(const Date& date1, const Date& date2) const = 0;
	virtual ~DayCount() = default;
};


class Act365 : public DayCount
{
public:
	virtual double operator() (const Date& date1, const Date& date2) const;
	virtual double yearFraction(const Date& date1, const Date& date2) const;
};

/*
class Act360 : public DayCount
{
public:
	virtual double operator() (const Date& date1, const Date& date2) const;
	virtual double yearFraction(const Date& date1, const Date& date2) const;
};


class Thirty360Eur : public DayCount	// see https://sqlsunday.com/2014/08/17/30-360-day-count-convention/
										// The Excel equivalent of this is YEARFRAC(fromDate; toDate; 4)
{
public:
	virtual double operator() (const Date& date1, const Date& date2) const;
	virtual double yearFraction(const Date& date1, const Date& date2) const;

private:	
	unsigned dateDiff_(const Date& date1, const Date& date2);
};*/


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