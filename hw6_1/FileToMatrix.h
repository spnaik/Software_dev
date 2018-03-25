/*
Copyright (c) 2018, Daniel Hanson
AMATH 520, University of Washington
For instructional purposes only
*/

#ifndef FILE_TO_MATRIX_H
#define FILE_TO_MATRIX_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <Eigen/Dense>

class FileToMatrix
{
public:
	FileToMatrix(long nrow, long ncol, const std::string& filePathAndName);

	Eigen::MatrixXd operator()() const;

private:
	void constructEigDataMatrix_();
	void csvToMatrix_();

	Eigen::MatrixXd eigDataMatrix_;
	Eigen::VectorXd eigDataVector_;
	long nrow_, ncol_;
	std::vector<std::string> dataAsString_;
	std::string filePathAndName_;
};

#endif