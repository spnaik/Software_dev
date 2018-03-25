#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>

class RealFunction
{
public:
	virtual double operator()(double x) const = 0;		// Returns the value of the implemented function
	virtual ~RealFunction() = default;					// implemention of virtual dtor on base class
};

class PolyFunction :public RealFunction
{
public:
	PolyFunction(double a, double b, double c, double d);
	virtual double operator()(double x) const override;			// value of poly function
	

private:
	double a_;
	double b_;
	double c_;
	double d_;
	
};

class LogFunction :public RealFunction
{
public:
	LogFunction(double a1, double b1);
	virtual double operator()(double x) const override;			// value of implementation function


private:
	double a_;
	double b_;
};

class MixFunction :public RealFunction
{
public:
	MixFunction(double a2, double b2, double c2);
	virtual double operator()(double x) const override;			// value of implementation function


private:
	double a_;
	double b_;
	double c_;
};

#endif