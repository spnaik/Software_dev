#pragma once
// The MyComplex class header file (MyComplex.h)

#ifndef MYCOMPLEX_H
#define MYCOMPLEX_H

class MyComplex {
public:
	MyComplex();
	MyComplex(double x);
	MyComplex(double x, double y); // Constructor with default real arguments - x and y
	//MyComplex(const MyComplex&);

	// output
	void print() const;

	void operator() () const;  // functor


	//Comparison with other complex numbers ; overloading
	bool operator == (const MyComplex & rhs) const;
	bool operator != (const MyComplex & rhs) const;
	bool operator < (const MyComplex & rhs) const;
	bool operator > (const MyComplex & rhs) const;
	bool operator <= (const MyComplex & rhs) const;
	bool operator >= (const MyComplex & rhs) const;

	MyComplex operator + (const MyComplex& rhs) const;
	MyComplex operator - (const MyComplex& rhs) const;
	MyComplex operator * (const MyComplex& rhs) const;

	void operator += (const MyComplex& rhs) ;
	void operator -= (const MyComplex& rhs) ;
	void operator *= (const MyComplex& rhs) ;

	// friend operator so that we can output a complex number
	//friend std::ostream& operator << (std::ostream& os, const MyComplex& rhs);

	// new: Accessor methods for numerator and denominator:
	double real() const;
	double imag() const;
	double radius() const;
	double theta() const;

	// new: Mutator methods for numerator and denominator:
	void reset(double x, double y);

	

	// private members : no access from outside
	
private:
	double real_;
	double imag_;
	double theta_;
	double radius_;

	void calcPolar_();

};

#endif // MYCOMPLEX_H