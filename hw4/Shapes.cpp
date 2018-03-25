#include "Shapes.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

Rectangle::Rectangle(double length, double height) :length_(length), height_(height) {}

double Rectangle::operator()() const
{
	return length_ * height_;
}

string Rectangle::whatAmI() const
{
	return whatAmI_;
}


Circle::Circle(double radius) :radius_(radius) {}

double Circle::operator()() const
{
	return pi_ * radius_ * radius_;
}

string Circle::whatAmI() const
{
	return whatAmI_;
}


Triangle::Triangle(double base, double altitude) :base_(base), altitude_(altitude) {}

double Triangle::operator()() const
{
	return 0.5*(base_ * altitude_);
}

string Triangle::whatAmI() const
{
	return whatAmI_;
}

Trapezoid::Trapezoid(double a, double b, double h) :base1_(a), base2_(b), height_(h) {}

double Trapezoid::operator()() const
{
	return 0.5*((base1_ + base2_)*(height_));
}

string Trapezoid::whatAmI() const
{
	return whatAmI_;
}