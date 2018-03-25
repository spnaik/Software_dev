
#include "Functions.h"
#include"ContaminatedNormal.h"
#include <random>
#include <iostream>
#include <vector>
#include <exception>
#include <cassert>
#include <stdexcept>

using std::mt19937_64;
using std::uniform_int_distribution;
using std::normal_distribution;
using std::student_t_distribution;
using std::cauchy_distribution;
using std::cout;
using std::endl;
using std::vector;
using std::length_error;
using std::out_of_range;
using std::invalid_argument;

void montyHallParadox(int seedCarPos, int seedChoicePos, int nSim)
{
	mt19937_64 mtre1(seedCarPos);	// mtre = Mersenne Twister Random Engine
	mt19937_64 mtre2(seedChoicePos);	// mtre = Mersenne Twister Random Engine
	uniform_int_distribution<> dis(1, 3);

	int change = 0; int nochange = 0;

	for (int sim = 0; sim < nSim; ++sim)
	{
		int carChoice, carPos, newchoice;
		carPos = dis(mtre1);
		carChoice = dis(mtre2);

		// case when he does not switch the carchoice
		if (carPos == carChoice)
		{
			nochange++;
		}

		// case when he switches the carchoice
		else {
			switch (carPos) {
			case 1:
				newchoice = 1;
				change++;
				break;
			case 2:
				newchoice = 2;
				change++;
				break;
			case 3:
				newchoice = 3;
				change++;
				break;
			default:
				assert(carPos <=3 && carPos >=1);
			
			}
		}
	}
	cout << "Percentage of wins with no change: " << static_cast<double>(nochange * 100.0 / nSim) << "%" << endl;
	cout << "Percentage of wins with change: " << static_cast<double>(change * 100.0 / nSim) << "%" << endl;

	

}


void testNormSquareBracketOper()
{
	auto print = [](double x) {cout << x << " "; }; // creating a lambda
	ContaminatedNormal conNorm(0, 0.15, 0.30, 0.05, 0, 12);

	conNorm.generate();
	int a = conNorm.numVariates();

	cout << " \n random variates generated are: \n" << endl;
	for (int i = 0; i < a; ++i)
	{

		print(conNorm.operator[](i));
	}

	cout << '\n' << endl;

	
	conNorm.generate(0.10, 0.18, 0.50, 0.10, -20, 24);


	conNorm.generate();

	cout << "new random variates generated are: \n"<< endl;

	for (int k = 0; k < conNorm.numVariates(); ++k)
	{
		
		print(conNorm.operator[](k));
	}

	// throwing exceptions

	cout << "\n\n"<< endl;
	try
	{
		conNorm.generate(0.10, 0.18, -0.50, 0.10, -20, 24); //  testing positivity of standard deviation
	}

	catch (const invalid_argument& e)
	{
		cout << "invalid_argument_Error() : " << e.what() << endl << endl;
	}

	try
	{
		conNorm.generate(0.10, -0.18, 0.50, 0.10, -20, 24); //  testing positivity of standard deviation
	}

	catch (const invalid_argument& e)
	{
		cout << "invalid_argument_Error() : " << e.what() << endl << endl;
	}

	try
	{
		conNorm.generate(0.10, 0.50, 0.18, 0.10, -20, 24); //  testing positivity of standard deviation
	}

	catch (const invalid_argument& e)
	{
		cout << "invalid_argument_Error() : " << e.what() << endl << endl;
	}

	try
	{
		ContaminatedNormal conNorm1(0.10, 0.50, 0.18, 0.10, -20, 24);//  testing positivity of standard deviation
	}

	catch (const invalid_argument& e)
	{
		cout << "invalid_argument_Error() : " << e.what() << endl << endl;
	}
	try
	{
		conNorm.operator[](-1);//  testing positivity of standard deviation
	}

	catch (const length_error& e)
	{
		cout << "indexError() : " << e.what() << endl << endl;
	}

	try
	{
		conNorm.operator[](24);//  testing positivity of standard deviation
	}

	catch (const out_of_range& exp)
	{
		cout << "out_of_range_error() : " << exp.what() << endl << endl;
	}

}   





