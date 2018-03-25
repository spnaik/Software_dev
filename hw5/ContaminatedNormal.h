#pragma once
#ifndef CONTAMINATED_NORMAL_H
#define CONTAMINATED_NORMAL_H

#include <vector>

class ContaminatedNormal
{
public:
	ContaminatedNormal(double mean, double sdOne, double sdTwo, double epsilon, int seed, int numVariates);

	double operator [](int k) const;
	int numVariates() const;

	// Should these be const? Make sure to convince yourself either way.
	void generate();
	void generate(double mean, double sdOne, double sdTwo, double epsilon, int seed, int numVariates);

private:
	double mean_, sdOne_, sdTwo_;
	double epsilon_;
	int seed_, numVariates_;
	std::vector<double> contNormVariates_;
};

#endif // !CONTAMINATED_NORMAL_H

