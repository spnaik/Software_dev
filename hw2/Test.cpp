
#include "MyComplex.h"
#include "Test.h"
// include standard header files
#include <iostream>
#include <cmath>
#include<array>
#include<vector>
 
using std::cout;
using std::endl;

void arrayApplication()
{
	MyComplex z1(1.0, 1.0);
	MyComplex z2(2.0, 2.0);
	MyComplex z3(3.0, 3.0);
	std::array<MyComplex, 3> mca;  // create an array of objects

	mca.at(0) = z1;
	mca.at(1) = z2;
	mca.at(2) = z3;

	for (auto i : mca)
	{
		(i)();  // using functor to print MyComplex objects
	}


}

void vectorApplication()
{
	MyComplex z1(10.0, 5.0);
	MyComplex z2(-1.0, -1.0);
	MyComplex z3(5.0, 4.0);

	std::vector<MyComplex> mcv;
	mcv.push_back(z1);
	mcv.push_back(z2);
	mcv.push_back(z3);

	MyComplex zsub;
	zsub.reset(4.0, 4.0);

	for (const auto &j : mcv)
	{
		MyComplex diff = j - zsub*(j - zsub);
		
		cout << "radius is " << diff.radius() << " and theta is " << diff.theta() << endl << endl;

	}




}