#include "FileToMatrix.h"
#include "CorrelatedNormals.h"
#include <stdexcept>
#include <exception>
#include <Eigen/Dense>
#include <algorithm>
#include <iterator>
#include <future>
#include <ctime>
#include <random>
#include <numeric>
#include <iostream>

using std::vector;
using std::fstream;
using std::ifstream;
using std::string;
using std::invalid_argument;
using std::length_error;
using Eigen::LLT;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::async;
using std::future;
using std::generate;
using std::mt19937_64;
using std::normal_distribution;
using std::for_each;
using std::transform;
using std::back_inserter;


using std::cout;		// for debug mode
using std::endl;		// for debug mode

CorrelatedNormals::CorrelatedNormals(const Eigen::MatrixXd& corrMtx, const Eigen::VectorXd& vols,
	int seed, int numTimeSteps) : corrMtx_(corrMtx), volDiagMtx_(vols.asDiagonal()), seed_(seed), numTimeSteps_(numTimeSteps)
{
	validate_();
	computeSqrtMatrix_();
	generateStdNormalMatrix_();
	computeScenarioMatrix_();
	scenarioMatrix();
}



void CorrelatedNormals::validate_() const
{
	if (volDiagMtx_.cols() != corrMtx_.rows() )
	{
		throw invalid_argument("CorrelatedNormals::validate_(): ERROR: input matrix dimensionsare incompatible.");
	}

	if ((corrMtx_.cols() != corrMtx_.rows()) || (volDiagMtx_.cols() != volDiagMtx_.rows()))
	{
		throw length_error("CorrelatedNormals::validate_(): ERROR: both matrices must be symmetric.");
	} 

	if (numTimeSteps_ < 0)
	{
		throw length_error("CorrelatedNormals::validate_(): ERROR: number of time steps must be positive.");
	}
	
	
}

void CorrelatedNormals::computeSqrtMatrix_()
{
	sqrtMtx_.resize(corrMtx_.rows(), corrMtx_.rows());
	LLT<MatrixXd> lltOfA(corrMtx_);
	MatrixXd L = lltOfA.matrixL();
	sqrtMtx_ = volDiagMtx_ * L;

	
}

void CorrelatedNormals::generateStdNormalMatrix_()
{
	
	vector<future<vector<double> > > v;
	auto genNorms = [this](int seed)
	{
		mt19937_64 mtre(seed);
		normal_distribution<> nd;
		vector<double> x;
		for (int i = 0; i < numTimeSteps_; ++i)
		{    
			x.push_back(nd(mtre));
		}
		return x ;
	};
	
	int seed = seed_;
	vector<vector<double> > y;

	for (int i = 0; i< corrMtx_.rows(); ++i)
	{ 
		
		v.push_back(async(genNorms,++seed));
		
	}

	transform(v.begin(), v.end(), back_inserter(y), std::mem_fn(&future<vector<double> >::get));
	VectorXd v1;

	stdNormMtx_.resize(corrMtx_.rows(),numTimeSteps_);

	for (unsigned j = 0; j< corrMtx_.rows(); ++j)
	{
		v1 = VectorXd::Map(y[j].data(), numTimeSteps_);
		stdNormMtx_.row(j) = v1;
	}
	
	
}

Eigen::MatrixXd CorrelatedNormals::scenarioMatrix() const
{
	
	return scenarioMatrix_;
}

void CorrelatedNormals::computeScenarioMatrix_()
{

	scenarioMatrix_.resize(corrMtx_.rows(), numTimeSteps_);
	scenarioMatrix_ = sqrtMtx_ * stdNormMtx_;	
	
}



