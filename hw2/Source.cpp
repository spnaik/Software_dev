#include "MyComplex.h"
#include "Test.h"
#include <iostream>
#include<cmath>
using std::cout;
using std::endl;

int main()
{
	
	MyComplex complex1(1,-0.1);
	//complex1.print();
	MyComplex complex2(2.0, 1.0); MyComplex complex3(-3.0, 2.0);
	 complex2 = complex2 * complex3;

	complex2.print();
	//complex1.print();
	cout << "f21 < f22? (expect 1) " << (complex2 < complex3) << endl;

	arrayApplication();
	vectorApplication();
	return 0;
}