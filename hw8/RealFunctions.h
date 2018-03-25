#pragma once
#ifndef REAL_FUNCTIONS_H
#define REAL_FUNCTIONS_H

#include <iostream>
#include <string>

class Linear 
{
public:
	Linear(double a, double b);
	double operator() (double x) const ;
private:
	double a_, b_;
};

class PolyFunction
{
public:
	PolyFunction(double a, double b, double c, double d);
	double operator()(double x) const;			// value of poly function
	

private:
	double a_;
	double b_;
	double c_;
	double d_;
	
};

class LogFunction
{
public:
	LogFunction(double a1, double b1);
	double operator()(double x) const;			// value of implementation function


private:
	double a_;
	double b_;
};

class MixFunction
{
public:
	MixFunction(double a2, double b2, double c2);
	double operator()(double x) const;			// value of implementation function


private:
	double a_;
	double b_;
	double c_;
};

#endif