#include "Functions.h"
#include "ContaminatedNormal.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <cassert>
#include <vector>
#include <exception>
#include<stdexcept>
using std::mt19937_64;
using std::uniform_int_distribution;
using std::normal_distribution;
using std::student_t_distribution;
using std::cauchy_distribution;
using std::cout;
using std::endl;
using std::vector;
using std::length_error;



void main()
{
	int seedCarPos = 0;
	int seedChoicePos = 1;
	int nSim = 2500;
	montyHallParadox(seedCarPos, seedChoicePos, nSim);
	testNormSquareBracketOper();
	
	return ;

}