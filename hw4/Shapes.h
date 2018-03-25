#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <string>
#include <cmath>

class Shape
{
public:
	virtual double operator()() const = 0;		// Returns the area of the shape
	virtual std::string whatAmI() const = 0;	// std::string shape identifier
	virtual ~Shape() = default; 				// Always implement virtual dtor on base class!
												// And, use " = default " (modern C++ way).
};

class Rectangle :public Shape
{
public:
	Rectangle(double length, double height);
	virtual double operator()() const override;			// Area of the rectangle
	virtual std::string whatAmI() const override;		// "Rectangle"

private:
	double length_;
	double height_;
	const std::string whatAmI_ = "Rectangle";
};

class Circle :public Shape
{
public:
	Circle(double radius);
	virtual double operator()() const override;			// Area of the circle
	virtual std::string whatAmI() const override;		// "Circle"

private:
	double radius_;
	const double pi_ = 2.0 * std::acos(0.0);
	const std::string whatAmI_ = "Circle";
};

class Triangle :public Shape
{
public:
	Triangle(double base, double altitude);
	virtual double operator()() const override;			// Area of the triangle
	virtual std::string whatAmI() const override;		// "Triangle"

private:
	double base_;
	double altitude_;
	const std::string whatAmI_ = "Triangle";
};

class Trapezoid :public Shape
{
public:
	Trapezoid(double a, double b, double h);
	virtual double operator()() const override;			// Area of the trapezoid
	virtual std::string whatAmI() const override;		// "Trapezoid"

private:
	double base1_;
	double base2_;
	double height_;
	const std::string whatAmI_ = "Trapezoid";
};


// This is a templated print function for you to use.  It will
// print a string object or any basic C++ type (we will discuss 
// templates in more detail soon; for now, you may just use this).
template<typename T>
void print(const T& t)
{
	std::cout << t <<" ";
}



#endif
