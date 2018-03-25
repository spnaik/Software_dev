/*
Copyright (c) 2018, Daniel Hanson
AMATH 520, University of Washington
For instructional purposes only
*/

#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include<string>
#include "FileToMatrix.h"
#include "CorrelatedNormals.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::Matrix;
using Eigen::Map;
using Eigen::DiagonalMatrix;
using std::vector;
using std::cout;
using std::endl;
using std::string;

void eigenMapExamples();
void eigenMtxExamples();

int main()
{
	// Put your work here...
	string filePath = "F:/UW/C++/Homework6_1/Assgn6_Cholesky.csv"; 
	int nrows = 7; int ncols = 8; 
	
	FileToMatrix ftm(nrows, ncols, filePath);

	VectorXd vec1 = ftm().block(0,0,nrows,1);  // extract the volatilities in the first column
	MatrixXd Avol = vec1.asDiagonal();   // convert the volatilities to a diagonal matrix
	MatrixXd Acorr = ftm().block(0, 1, nrows, ncols-1);  // extract the correlation matrix
	//cout << Acorr.rows() << endl;
	CorrelatedNormals cn(Acorr, vec1, 100, 10);

	cout << cn.scenarioMatrix() << endl;

	
	




	// These functions demonstrate features in Eigen that you will find
	// useful for completing this assignment.  These do not need to
	// be turned in with your work; they are provided for your entertainment ;-)
	//eigenMapExamples();
	//eigenMtxExamples();
}

void eigenMapExamples()
{
	// Here are some examples that may help you with this assignment.
	// The static method Map(.) on the VectorXd and MatrixXd classes
	// allows one to "map" the contents of a std::vector<double> into 
	// either of the Eigen "Xd" class types.

	// Let's initialise a std::vector<double>
	vector<double> x = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

	// Now, we can copy this data into a VectorXd in one shot rather
	// than looping through element by element.  It works like this:
	VectorXd v = VectorXd::Map(x.data(), 6);

	// x.data() returns the contents of x as a contiguous C-style dynamic array,
	// and then the Map function copies it into v.  Note that the dimension (6) must
	// be included as an argument for Map(.).  Check the result:
	cout << "Contents of VectorXd v copied from std::vector<double> x: " << endl;
	cout << v << endl << endl;		// Column vector

	// One can also copy the contents of x into a matrix, in column major
	// order.  Note that this is different from using the << operator to 
	// populate a MatrixXd, which is done in row major order.  It is basically
	// the same as copying into a VectorXd, but one has to include both the row (2)
	// and column (3) dimensions in the arguments for this overload of Map(.):
	MatrixXd mtx = MatrixXd::Map(x.data(), 2, 3);
	cout << "Contents of 2 x 3 MatrixXd mtx copied from std::vector<double> x: " << endl;
	cout << mtx << endl << endl;
}

void eigenMtxExamples()
{
	// Two more things that will be useful for you.  1st, suppose you are given 
	// a VectorXd of volatilities, and you need to put these into a diagonal 
	// matrix.  This is how you do it:

	VectorXd vols(3);
	vols << 0.1, 0.2, 0.3;

	// Put in diagonal of a matrix:
	MatrixXd volMtx = vols.asDiagonal();	// Done!

											// Check result:
	cout << "Diagonal matrix of volatilities: " << endl;
	cout << volMtx << endl << endl;

	// One other useful tool is copying the elements of an Eigen VectorXd
	// into a row or column of an Eigen MatrixXd.  This is easily done
	// as follows (just use the vols vector above for thix example):
	MatrixXd mtx(3, 3);
	// Copy into a row:
	mtx.row(0) = vols;

	// Check result:
	cout << "Matrix mtx with 1st row elements from VectorXd: " << endl;
	cout << mtx << endl << endl;

	// Similar for a column:
	mtx.col(1) = vols;

	// Check result:
	cout << "Matrix mtx with 2nd column elements in VectorXd: " << endl;
	cout << mtx << endl << endl;
}
