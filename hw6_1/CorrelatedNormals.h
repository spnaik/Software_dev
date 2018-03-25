/*
Copyright (c) 2018, Daniel Hanson
AMATH 520, University of Washington
For instructional purposes only
*/

#ifndef CORRELATED_NORMALS_H
#define CORRELATED_NORMALS_H

#include <Eigen/Dense>

class CorrelatedNormals
{
public:
	CorrelatedNormals(const Eigen::MatrixXd& corrMtx, const Eigen::VectorXd& vols,
		int seed, int numTimeSteps);

	Eigen::MatrixXd scenarioMatrix() const;		// Return the result with a functor.

private:
	void validate_() const;				// Called at construction.  Throw appropriate
										// exception if problem encountered.
	void computeSqrtMatrix_();			// Use Eigen method to compute Cholesky
										// Decomposition, and then compute the 
										// "square root matrix" and set it to sqrtMtx_.	
	void generateStdNormalMatrix_();	// Generate the stdNormMtx_ (see below for description).
	void computeScenarioMatrix_();

	const Eigen::MatrixXd& corrMtx_;		// Correlation matrix.
	const Eigen::MatrixXd& volDiagMtx_;		// Diagonal matrix of volatilities.
	Eigen::MatrixXd sqrtMtx_;				// Diagonal matrix of vols x Chol Decomp of corr mtx.
	Eigen::MatrixXd stdNormMtx_;			// Matrix of std normal variates; number of columns =
											// number of time steps.
	Eigen::MatrixXd scenarioMatrix_;		// Resultant matrix of correlated random variates.
	int seed_;								// Seed for generating standard random normal variates.
	int numTimeSteps_;						// Number of time steps in the scenario set.
};


#endif
