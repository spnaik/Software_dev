

#include "MyComplex.h"

// include standard header files
#include <iostream>
#include <cmath>
using std::acos;
double const pi = acos(-1.0);
using std::abs;

// default constructor
MyComplex::MyComplex()    // initialize complex number with real =0 and imag=0
{
	real_ = 0.0;
	imag_ = 0.0;

	calcPolar_();
}

MyComplex::MyComplex(double x) : real_(x), imag_(0.0)// initialize fraction with n
{
	calcPolar_();
}

MyComplex::MyComplex(double x, double y) : real_(x), imag_(y)
{
	calcPolar_();
}

//print

void MyComplex::print() const
{
	std::cout << real_ << '+' << imag_ << 'i' << std::endl;
}

void MyComplex::operator() () const
{
	print();		// Functor that prints the fraction
}

//Copy constructor
/*MyComplex::MyComplex(const MyComplex &c)
{
	this->real_ = c.real_;
	this->imag_ = c.imag_;
}*/

// bool operations

bool MyComplex::operator == (const MyComplex& rhs) const
{
	return ((sqrt(pow(this->real_, 2) + pow(this->imag_, 2))) ==  (sqrt(pow(rhs.real_, 2) + pow(rhs.imag_, 2))));
}

bool MyComplex::operator != (const MyComplex& rhs) const
{
	return !(*this==rhs);
}

bool MyComplex::operator < (const MyComplex& rhs) const
{
	return ((sqrt(pow(this->real_, 2) + pow(this->imag_, 2))) < (sqrt(pow(rhs.real_, 2) + pow(rhs.imag_, 2))));
}

bool MyComplex::operator > (const MyComplex& rhs) const
{
	return !(*this < rhs);
}

bool MyComplex::operator <= (const MyComplex& rhs) const
{
	return ((*this < rhs) || (*this == rhs));
}

bool MyComplex::operator >= (const MyComplex& rhs) const
{
	return ((*this > rhs) || (*this == rhs));
}



// new: operator family + (addition)
MyComplex MyComplex::operator + (const MyComplex& rhs) const
{
	MyComplex Cmplxadd(this->real_ + rhs.real_, this->imag_ + rhs.imag_);
	return Cmplxadd;			
}

// new: operator family + (addition)
MyComplex MyComplex::operator - (const MyComplex& rhs) const
{
	MyComplex Cmplxsub(this->real_ - rhs.real_, this->imag_ - rhs.imag_);
	return Cmplxsub;
}

// new: operator family * (multiplication)
MyComplex MyComplex::operator * (const MyComplex& rhs) const
{
	MyComplex Cmplxmul(this->real_ *rhs.real_ - this->imag_ * rhs.imag_ , this->real_ *rhs.imag_ + this->imag_ * rhs.real_);
	return Cmplxmul;
}

// Assignment operators
void MyComplex::operator += (const MyComplex& rhs) 
{
	//real_ = real_ + rhs.real_;
	//imag_ = imag_ + rhs.imag_;
	*this = *this + rhs;

}

void MyComplex::operator -= (const MyComplex& rhs) 
{
	*this = *this - rhs;
}

void MyComplex::operator *= (const MyComplex& rhs) 
{
	*this = *this * rhs;
}

// This is a 'friend' of the MyComplex class
/*std::ostream& operator << (std::ostream& os, const MyComplex& rhs)
{
	os << rhs.real_ << '+' << rhs.imag_ <<'i' <<;
	return os;
} */

double MyComplex::real() const
{
	return real_;
}

double MyComplex::imag() const
{
	return imag_;
}

double MyComplex::radius() const
{
	return radius_;
}

double MyComplex::theta() const
{
	return theta_;
}


void MyComplex::reset(double x, double y)
{
	real_ = x; imag_ = y;
	calcPolar_();
}

void MyComplex::calcPolar_()
{
	radius_ = sqrt(pow(this->real_, 2) + pow(this->imag_, 2));

	if (this->imag_ < 0)
	{
		theta_ = -acos(this->real_ / this->radius_);
	}
	else
	{
		theta_ = acos(this->real_ / this->radius_);
	}
	
}    
  
