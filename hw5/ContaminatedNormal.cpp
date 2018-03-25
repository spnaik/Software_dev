#include "ContaminatedNormal.h"
#include <cmath>
#include<iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <random>
#include <stdexcept>

using std::vector;
using std::length_error;
using std::transform;
using std::mt19937_64;
using std::normal_distribution;
using std::sort;
using std::out_of_range;
using std::invalid_argument;
using std::cout;
using std::endl;
using std::bernoulli_distribution;

ContaminatedNormal::ContaminatedNormal(double mean, double sdOne, double sdTwo, double epsilon, int seed, int numVariates) :
	mean_(mean), sdOne_(sdOne), sdTwo_(sdTwo), epsilon_(epsilon), seed_(seed), numVariates_(numVariates)
{
	
		if (((std::abs(sdTwo_)) < (std::abs(sdOne_))) || ((sdOne_ < 0) || (sdTwo_ < 0)))
		{
			throw invalid_argument("Check for inequalities and positivity of volatilities \n");

		}
}

void ContaminatedNormal::generate()
{
	
	mt19937_64 mtre(seed_);
	mt19937_64 mtreBool(seed_);
	normal_distribution<> nd1(mean_,sdOne_);
	normal_distribution<> nd2(mean_,sdTwo_);
	bernoulli_distribution bd(1.0 - epsilon_);

	

	for (int i = 0; i < numVariates_; ++i)
	{
		if (bd(mtreBool) == 1)
		{
			double cnd = nd1(mtre);
			contNormVariates_.push_back(cnd);
		}
		else
		{
			double cnd = nd2(mtre);
			contNormVariates_.push_back(cnd);
		}
	}

}


//resets the values
void ContaminatedNormal::generate(double mean, double sdOne, double sdTwo, double epsilon, int seed, int numVariates)
{
	
		contNormVariates_.clear();
		mean_ = mean; sdOne_ = sdOne; sdTwo_ = sdTwo; epsilon_ = epsilon; seed_ = seed; numVariates_ = numVariates;

		if (((std::abs(sdTwo_)) < (std::abs(sdOne_)))  || ( (sdOne_ < 0) || (sdTwo_ < 0) ))
		{
			throw invalid_argument("Check for inequalities and positivity of volatilities \n");

		}
		
}

// number of elements in contNormVariates
int ContaminatedNormal::numVariates() const
{
	return contNormVariates_.size();
}

// ith element in contNormVariates

double ContaminatedNormal::operator [](int k) const
{
	
		if (k < 0)
		{
			throw length_error("Input index must be positive \n");

		}
		if (k >= contNormVariates_.size())
		{
			throw out_of_range("Input index exceeds the number of elements in the vector \n");

		}
		return contNormVariates_.at(k);
			
}
